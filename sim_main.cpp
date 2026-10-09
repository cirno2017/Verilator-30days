//
#include "Vcounter2.h"
#include "verilated.h"

#include <cstdint>
#include <iostream>

std::uint32_t model_next(std::uint32_t old_state,
                         bool rst, bool en)
{
    if (rst)
        return 0;
    if (en)
        return (old_state + 1u) % 4u;
    return old_state;
}

struct Case
{
    const char *name;
    bool rst;
    bool en;
};

int main(int argc, char **argv)
{
    VerilatedContext context;
    context.commandArgs(argc, argv);
    Vcounter2 dut{&context};

    constexpr Case cases[] = {
        {"increment-to-1", false, true},
        {"hold-at-1", false, false},
        {"increment-to-2", false, true},
        {"increment-to-3", false, true},
        {"hold-at-maximum", false, false},
        {"wrap-to-zero", false, true},
        {"increment-again", false, true},
        {"reset-with-en-0", true, false},
        {"resume", false, true},
        {"reset-with-en-1", true, true}};

    unsigned completed = 0;
    unsigned cycle = 0;
    unsigned checks = 0;
    unsigned errors = 0;
    bool diagnosed = false;
    std::uint32_t expected_state = 0;

    auto check_equal = [&](unsigned case_id,
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
    };

    // 初始化：先让模型看见低电平。
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

    for (const Case &c : cases)
    {
        const unsigned case_id = completed + 1;
        const std::uint32_t old_state = expected_state;
        const std::uint32_t next_state =
            model_next(old_state, c.rst, c.en);

        // 输入提前驱动、求值；此时仍应保持旧状态。
        context.timeInc(1);
        dut.rst = c.rst;
        dut.en = c.en;
        dut.eval();
        check_equal(case_id, "low-before-rise", "q",
                    old_state, dut.q);

        context.timeInc(4);
        dut.clk = 1;

        // TODO 2：首次诊断完成后，修复下面的采样顺序。
        // 保留 observed 变量，不修改规格、参考模型或检查次数。

        dut.eval();
        const std::uint32_t observed = dut.q;  //调换顺序，先采样，然后求值。

        ++cycle;
        expected_state = next_state;
        check_equal(case_id, "rise", "q",
                    expected_state, observed);

        if (!diagnosed && observed != expected_state)
        {
            // TODO 1：增加一条 DIAG 输出，包含：
            // case_id、cycle、context.time()、
            // old_state、next_state、observed，以及此刻的 dut.q。
            // uint8_t 类型端口打印时转成 unsigned。
            // 不推进时间，不改端口，不额外调用 eval()。
            printf("old = %u next = %u observed = %u dut.q = %u\n", old_state, next_state, observed, (unsigned)dut.q);
            // TODO 1： Complete
            diagnosed = true;
        }

        context.timeInc(5);
        dut.clk = 0;
        dut.eval();
        check_equal(case_id, "fall", "q",
                    expected_state, dut.q);

        ++completed;
        std::cout << "CASE case=" << case_id
                  << " cycle=" << cycle
                  << " time_ns=" << context.time()
                  << " name=" << c.name
                  << " old=" << old_state
                  << " next=" << expected_state
                  << " actual=" << static_cast<unsigned>(dut.q)
                  << '\n';
    }

    check_equal(completed, "end", "clk", 0, dut.clk);
    check_equal(completed, "end", "time_ns", 110, context.time());
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