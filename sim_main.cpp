//
#include "Vcounter4.h"
#include "verilated.h"

#include <cstdint>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

// 来自接口规格：复位、模 16 递增、保持。
static unsigned model_next(unsigned old, bool rst, bool en)
{
    // TODO 1：返回下一状态。
    // 不读取 DUT；加法使用 unsigned，然后限制为 4 位。
    // #error "TODO 1: implement the specification model"
    // TODO 1 My Code Start
    if (rst)
    {
        return 0;
    }
    else if (en)
    {
        return ++old & 0xF;
    }
    else
    {
        return old;
    }
    // TODO 1 My Code End
}

struct InputRecord
{
    unsigned cycle;
    bool rst;
    bool en;
    unsigned old_state;
    unsigned next_state;
};

class Testbench
{
private:
    VerilatedContext &context;
    Vcounter4 dut;
    const std::uint32_t seed;

    unsigned cycle = 0;
    unsigned expected_state = 0;
    unsigned checks = 0;
    unsigned errors = 0;
    unsigned random_steps = 0;
    const char *case_name = "init";
    std::vector<InputRecord> recent;

    void remember(const InputRecord &row)
    {
        if (recent.size() == 8)
            recent.erase(recent.begin());
        recent.push_back(row);
    }

    void check_equal(const char *item,
                     std::uint64_t want, std::uint64_t actual)
    {
        ++checks;
        if (want == actual)
            return;

        ++errors;
        std::cerr << "FAIL seed=" << seed
                  << " case=" << case_name
                  << " cycle=" << cycle
                  << " time_ns=" << context.time()
                  << " item=" << item
                  << " rst=" << static_cast<unsigned>(dut.rst)
                  << " en=" << static_cast<unsigned>(dut.en)
                  << " expected=" << want
                  << " actual=" << actual << '\n';

        // 只在首次失败时展开历史，避免重复刷屏。
        if (errors == 1)
        {
            for (const auto &row : recent)
            {
                std::cerr << "HIST cycle=" << row.cycle
                          << " rst=" << row.rst
                          << " en=" << row.en
                          << " old=" << row.old_state
                          << " next=" << row.next_state << '\n';
            }
        }
    }

    // cycle 表示当前正在执行的 tick 编号。
    // 进入、退出时 clk=0，每拍推进 10 ns。
    void tick(bool rst, bool en, bool check_before = true)
    {
        ++cycle;
        const unsigned old = expected_state;
        const unsigned next = model_next(old, rst, en);
        remember({cycle, rst, en, old, next});

        context.timeInc(1);
        dut.rst = rst;
        dut.en = en;
        dut.eval();
        if (check_before)
            check_equal("low/q", old, dut.q);

        context.timeInc(4);
        dut.clk = 1;
        dut.eval();
        expected_state = next;
        check_equal("rise/q", next, dut.q);

        context.timeInc(5);
        dut.clk = 0;
        dut.eval();
        check_equal("fall/q", expected_state, dut.q);

        // 完整输入记录，用来比较两次运行是否完全一致。
        std::cout << "STEP seed=" << seed
                  << " case=" << case_name
                  << " cycle=" << cycle
                  << " rst=" << rst
                  << " en=" << en
                  << " old=" << old
                  << " next=" << next
                  << " actual=" << static_cast<unsigned>(dut.q)
                  << '\n';
    }

public:
    Testbench(VerilatedContext &ctx, std::uint32_t s)
        : context(ctx), dut(&ctx), seed(s)
    {
        dut.clk = 0;
        dut.rst = 1;
        dut.en = 0;
        dut.eval();

        // 首次复位前，不假设 DUT 上电值。
        tick(true, false, false);
    }

    void run()
    {
        case_name = "directed";
        for (unsigned i = 0; i < 17; ++i)
            tick(false, true); // 经历 15→0，最后到 1
        tick(false, false);    // 非零状态保持
        tick(true, true);      // 从 1 清零，验证复位优先

        case_name = "random";
        std::mt19937 rng(seed);

        // TODO 2：恰好执行 200 个周期。
        // 每拍：
        // ① 调用一次 rng()，保存到 word。
        // ② word 低四位全为 0 时 rst=true。
        // ③ word 的第 4 位为 1 时 en=true。
        // ④ tick(rst, en)。
        // ⑤ ++random_steps。
        // 不重新播种，不清空 expected_state/errors/cycle。
        // #error "TODO 2: drive the reproducible random sequence"
        // TODO 2 My Code Start
        for (unsigned i = 0; i < 200; ++i)
        {
            const auto word = rng();
            const bool rst = (word & 0xF) == 0;
            const bool en = ((word >> 4) & 0x1) == 1;
            tick(rst, en);
            ++random_steps;
        }
        // TODO 2 My Code End
    }

    int finish()
    {
        check_equal("end/random_steps", 200, random_steps);
        check_equal("end/clk", 0, dut.clk);
        dut.final();

        std::cout << (errors == 0 ? "PASS" : "FAIL")
                  << " seed=" << seed
                  << " random_steps=" << random_steps
                  << " cycles=" << cycle
                  << " checks=" << checks
                  << " errors=" << errors
                  << " time_ns=" << context.time() << '\n';
        return errors == 0 ? 0 : 1;
    }
};

int main(int argc, char **argv)
{
    // 可选参数：十进制 uint32_t seed。
    std::uint32_t seed = 20261013u;
    try
    {
        if (argc > 2)
            throw std::invalid_argument("too many arguments");
        if (argc == 2)
        {
            const std::string text = argv[1];
            if (text.empty() ||
                text.find_first_not_of("0123456789") != std::string::npos)
                throw std::invalid_argument("not decimal");
            const auto value = std::stoull(text);
            if (value > UINT32_MAX)
                throw std::out_of_range("seed too large");
            seed = static_cast<std::uint32_t>(value);
        }
    }
    catch (const std::exception &)
    {
        std::cerr << "Usage: " << argv[0]
                  << " [decimal_uint32_seed]\n";
        return 2;
    }

    std::cout << "RUN seed=" << seed << '\n';
    VerilatedContext context;
    context.commandArgs(argc, argv);
    Testbench tb{context, seed};
    tb.run();
    return tb.finish();
}