//
#include "Vcounter2.h"
#include "verilated.h"

#include <cstdint>
#include <iostream>

// 独立的接口规格模型，不访问 DUT。
std::uint32_t model_next(std::uint32_t old_state,
                         bool rst, bool en)
{
    if (rst)
        return 0;
    if (en)
        return (old_state + 1u) % 4u;
    return old_state;
}

class Testbench
{
private:
    // context 引用 main 中的对象，不创建第二份上下文。
    VerilatedContext &context;
    Vcounter2 dut;

    std::uint32_t expected_state = 0;
    unsigned cycle = 0;
    unsigned completed = 0;
    unsigned checks = 0;
    unsigned errors = 0;

    void check_equal(unsigned case_id,
                     const char *phase,
                     const char *signal,
                     std::uint64_t want,
                     std::uint64_t actual)
    {
        ++checks;
        if (want != actual)
        {
            ++errors;
            std::cerr << "FAIL case=" << case_id
                      << " cycle=" << cycle
                      << " time_ns=" << context.time()
                      << " phase=" << phase
                      << " signal=" << signal
                      << " rst=" << static_cast<unsigned>(dut.rst)
                      << " en=" << static_cast<unsigned>(dut.en)
                      << " expected=" << want
                      << " actual=" << actual << '\n';
        }
    }

public:
    explicit Testbench(VerilatedContext &ctx)
        : context(ctx), dut(&ctx)
    {
        // 初始复位：不检查未保证的上电输出。
        dut.clk = 0;
        dut.rst = 1;
        dut.en = 0;
        dut.eval();

        context.timeInc(5);
        dut.clk = 1;
        dut.eval();
        ++cycle;
        check_equal(0, "init-rise", "q", 0, dut.q);

        context.timeInc(5);
        dut.clk = 0;
        dut.eval();
        check_equal(0, "init-fall", "q", 0, dut.q);

        // expected_state=0 来自复位规格，不读取 DUT 来对齐。
    }

    // 约定：进入和退出时 clk 都为 0。
    // 每次调用推进 10 ns，产生一个上升沿和一个下降沿。
    void step(unsigned case_id, bool rst, bool en)
    {
        const std::uint32_t old_state = expected_state;
        const std::uint32_t next_state =
            model_next(old_state, rst, en);

        // TODO 1：完成周期起点 +1 ns 的输入阶段。
        // 1. 时间推进 1 ns。
        // 2. 将参数 rst、en 写入 DUT 对应端口。
        // 3. 调用 eval()。
        // 4. 调用 check_equal，检查 q 等于 old_state。
        //    phase="low-before-rise"，signal="q"。
        // #error "TODO 1: drive inputs and check the old state"
        // TODO 1 My Code Start
        context.timeInc(1);
        dut.rst = rst;
        dut.en = en;
        dut.eval();
        check_equal(case_id, "low-before-rise", "q", old_state, dut.q);
        // TODO 1 My Code End

        // TODO 2：完成周期起点 +5 ns 的上升沿阶段。
        // 1. 再推进 4 ns，设置 clk=1，然后 eval()。
        // 2. cycle 加一。
        // 3. 将 next_state 提交到 expected_state。
        // 4. 在 eval() 之后读取 dut.q，保存为：
        //    const std::uint32_t observed
        // 5. 调用 check_equal，比较 expected_state 和 observed。
        //    phase="rise"，signal="q"。
        // #error "TODO 2: evaluate the rising edge and check the new state"
        // TODO 2 My Code Start
        context.timeInc(4);
        dut.clk = 1;
        dut.eval();
        ++cycle;
        expected_state = next_state;
        dut.eval();
        const std::uint32_t observed = dut.q;
        check_equal(case_id, "rise", "q", expected_state, observed);
        // TODO 2 My Code End

        // 周期起点 +10 ns：处理下降沿，参考状态不更新。
        context.timeInc(5);
        dut.clk = 0;
        dut.eval();
        check_equal(case_id, "fall", "q",
                    expected_state, dut.q);

        ++completed;
        std::cout << "CASE case=" << case_id
                  << " cycle=" << cycle
                  << " time_ns=" << context.time()
                  << " rst=" << rst
                  << " en=" << en
                  << " old=" << old_state
                  << " next=" << expected_state
                  << " actual=" << static_cast<unsigned>(dut.q)
                  << '\n';
    }

    // 执行一个同步复位周期，返回时 rst 仍为 1。
    // 下一次 step() 在自己的 +1 ns 阶段设置新的 rst。
    void reset(unsigned case_id, bool en)
    {
        // TODO 3：只调用一次 step()。
        // 使用传入的 case_id；复位有效；保留传入的 en。
        // 不直接修改 expected_state，不清空任何统计量。
        // #error "TODO 3: reuse step for a reset cycle"
        // TODO 3 My Code Start
        step(case_id, 1, en);
        // TODO 3 My Code End
    }

    // 本课约定：全部用例完成后只调用一次。
    int finish()
    {
        check_equal(completed, "end", "clk", 0, dut.clk);
        check_equal(completed, "end", "time_ns",
                    110, context.time());

        dut.final();

        if (completed != 10 || cycle != 11 || checks != 34)
        {
            std::cerr << "INCOMPLETE cases=" << completed
                      << " cycles=" << cycle
                      << " checks=" << checks
                      << " expected=10/11/34\n";
            return 2;
        }

        std::cout << (errors == 0 ? "PASS" : "FAIL")
                  << " cases=" << completed
                  << " cycles=" << cycle
                  << " checks=" << checks
                  << " errors=" << errors
                  << " time_ns=" << context.time() << '\n';

        return errors == 0 ? 0 : 1;
    }
};

struct Case
{
    bool rst;
    bool en;
};

int main(int argc, char **argv)
{
    VerilatedContext context;
    context.commandArgs(argc, argv);
    Testbench tb{context};

    constexpr Case cases[] = {
        {false, true},  // 1: 递增到 1
        {false, false}, // 2: 保持 1
        {false, true},  // 3: 递增到 2
        {false, true},  // 4: 递增到 3
        {false, false}, // 5: 保持最大值
        {false, true},  // 6: 回绕到 0
        {false, true},  // 7: 再次递增到 1
        {true, false},  // 8: 禁用时复位
        {false, true},  // 9: 释放复位，恢复递增
        {true, true}    // 10: 复位优先于使能
    };

    unsigned case_id = 0;
    for (const Case &c : cases)
    {
        ++case_id;
        if (c.rst)
            tb.reset(case_id, c.en);
        else
            tb.step(case_id, c.rst, c.en);
    }

    return tb.finish();
}