//
#include "Vcounter2.h"
#include "verilated.h"

#include <cstdint>
#include <iostream>
#include <string>

std::uint32_t model_next(std::uint32_t old, bool rst, bool en)
{
    if (rst)
        return 0;
    if (en)
        return (old + 1u) % 4u;
    return old;
}

struct Case
{
    const char *name;
    bool enables[4];
    unsigned steps;
    std::uint32_t final_q;
};

class Testbench
{
private:
    VerilatedContext &context;
    Vcounter2 dut;

    std::uint32_t expected_state = 0;

    // 整场累计，不在 begin_case 中清零。
    unsigned cycle = 0;
    unsigned completed = 0;
    unsigned checks = 0;
    unsigned errors = 0;

    // 当前用例的信息。
    unsigned case_id = 0;
    unsigned body_steps = 0;
    const char *case_name = "init";

    void check_equal(const char *phase, const char *signal,
                     std::uint64_t want, std::uint64_t actual)
    {
        ++checks;
        if (want != actual)
        {
            ++errors;
            std::cerr << "FAIL case=" << case_id
                      << " name=" << case_name
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

    // 进入和退出时 clk=0；每次推进 10 ns、执行三次检查。
    // 它不统计 body_steps，因为复位周期不属于用例正文。
    void tick(bool rst, bool en)
    {
        const std::uint32_t old = expected_state;
        const std::uint32_t next = model_next(old, rst, en);

        context.timeInc(1);
        dut.rst = rst;
        dut.en = en;
        dut.eval();
        check_equal("low-before-rise", "q", old, dut.q);

        context.timeInc(4);
        dut.clk = 1;
        dut.eval();
        ++cycle;
        expected_state = next;
        const std::uint32_t observed = dut.q;
        check_equal("rise", "q", expected_state, observed);

        context.timeInc(5);
        dut.clk = 0;
        dut.eval();
        check_equal("fall", "q", expected_state, dut.q);
    }

    void begin_case(const Case &c)
    {
        case_id = completed + 1;
        case_name = c.name;

        // TODO 1：
        // 将 body_steps 清零。
        // 调用一次 tick，执行 rst=true、en=false 的复位周期。
        // 不直接修改 expected_state，不清空整场统计。
        // #error "TODO 1: isolate the case"
        // TODO 1 My Code Start
        body_steps = 0;
        tick(true, false);
        // TODO 1 My Code End
    }

public:
    explicit Testbench(VerilatedContext &ctx)
        : context(ctx), dut(&ctx)
    {
        // 首次建立已知状态，不检查未保证的上电输出。
        dut.clk = 0;
        dut.rst = 1;
        dut.en = 0;
        dut.eval();

        context.timeInc(5);
        dut.clk = 1;
        dut.eval();
        ++cycle;
        check_equal("init-rise", "q", 0, dut.q);

        context.timeInc(5);
        dut.clk = 0;
        dut.eval();
        check_equal("init-fall", "q", 0, dut.q);
    }

    void run_case(const Case &c)
    {
        begin_case(c);

        // TODO 2：
        // 遍历 i=0 到 c.steps-1。
        // 每次调用 tick(false, c.enables[i])，
        // 然后将 body_steps 加一。
        // 不用 dut.q 修改参考状态。
        // #error "TODO 2: run the case body"
        // TODO 2 My Code Start
        for (int i = 0; i < c.steps; ++i)
        {
            tick(false, c.enables[i]);
            ++body_steps;
        }
        // TODO 2 My Code End

        // 独立的场景后置条件，不能换成 expected_state。
        check_equal("case-end", "q", c.final_q, dut.q);
        check_equal("case-end", "body_steps", c.steps, body_steps);

        ++completed;
        std::cout << "CASE case=" << case_id
                  << " name=" << case_name
                  << " body_steps=" << body_steps
                  << " final_q=" << static_cast<unsigned>(dut.q)
                  << " cycle=" << cycle
                  << " time_ns=" << context.time()
                  << " total_errors=" << errors << '\n';
    }

    int finish()
    {
        check_equal("end", "clk", 0, dut.clk);
        check_equal("end", "time_ns", 170, context.time());
        dut.final();

        if (completed != 4 || cycle != 17 || checks != 60)
        {
            std::cerr << "INCOMPLETE cases=" << completed
                      << " cycles=" << cycle
                      << " checks=" << checks
                      << " expected=4/17/60\n";
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

int main(int argc, char **argv)
{
    VerilatedContext context;
    context.commandArgs(argc, argv);

    const bool reverse =
        argc > 1 && std::string(argv[1]) == "--reverse";

    const Case a{"A", {true, true, true, false}, 3, 3};
    const Case b{"B", {false, true, false, false}, 2, 1};
    const Case c{"C", {true, true, true, true}, 4, 0};
    const Case cases[]{a, b, a, c};

    Testbench tb{context};

    // TODO 3：
    // 循环执行四个用例。
    // 正序索引：i；逆序索引：3u-i。
    // 根据 reverse 选择索引，再调用 tb.run_case(cases[index])。
    // 使用同一个 tb，不重新创建对象。
    // #error "TODO 3: select the execution order"
    // TODO 3 My Code Start
    for (unsigned i = 0; i < 4; ++i)
    {
        const unsigned index = reverse ? 3u - i : i;
        tb.run_case(cases[index]);
    }
    // TODO 3 My Code End

    return tb.finish();
}