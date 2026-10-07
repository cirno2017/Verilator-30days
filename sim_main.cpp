//
#include "Vcounter2.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

#include <cstdint>
#include <iostream>

struct Case
{
    const char *name;
    std::uint32_t rst;
    std::uint32_t en;
    std::uint32_t want; // 本用例上升沿之后的独立期望
};

int main(int argc, char **argv)
{
    VerilatedContext context;
    context.commandArgs(argc, argv);
    context.traceEverOn(true); // 在首次 eval() 之前启用追踪

    Vcounter2 dut{&context};
    VerilatedVcdC trace;

    // TODO 1：
    // A. 用 dut.trace(&trace, 1) 注册追踪，深度1够用。
    // B. 用 trace.open(...) 打开 "wave.vcd"。
    // #error "TODO 1: register and open the VCD trace"
    // TODO 1 My Code Start
    dut.trace(&trace, 1);
    trace.open("wave.vcd");
    // TODO 1 My Code End

    if (!trace.isOpen())
    {
        std::cerr << "ERROR cannot open wave.vcd\n";
        dut.final();
        return 2;
    }

    constexpr Case cases[] = {
        {"increment-to-1", 0, 1, 1},  // 1
        {"hold-at-1", 0, 0, 1},       // 2
        {"increment-to-2", 0, 1, 2},  // 3
        {"increment-to-3", 0, 1, 3},  // 4
        {"hold-at-maximum", 0, 0, 3}, // 5
        {"wrap-to-zero", 0, 1, 0},    // 6
        {"increment-again", 0, 1, 1}, // 7
        {"reset-with-en-0", 1, 0, 0}, // 8
        {"resume", 0, 1, 1},          // 9
        {"reset-with-en-1", 1, 1, 0}  // 10
    };

    unsigned completed = 0;
    unsigned cycle = 0;
    unsigned checks = 0;
    unsigned errors = 0;
    unsigned samples = 0;
    std::uint32_t expected_q = 0;

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
                      << " expected=" << want
                      << " actual=" << actual << '\n';
        }
    };

    auto sample = [&]()
    {
        // TODO 2：
        // A. 先对 dut 求值。
        // B. 再以 context.time() 为时间戳记录波形。
        // 本函数不推进时间，也不改时钟。
        // #error "TODO 2: evaluate then dump"
        // TODO 2 My Code Start
        dut.eval();
        trace.dump(context.time());
        // TODO 2 My Code End
        ++samples;
    };

    // t=0：建立低电平；初始 q 只记录，不判定。
    dut.clk = 0;
    dut.rst = 1;
    dut.en = 0;
    sample();

    // t=5：初始化复位上升沿。
    context.timeInc(5);
    dut.clk = 1;
    sample();
    ++cycle;
    check_equal(0, "init-rise", "q", 0, dut.q);

    // t=10：初始化下降沿。
    context.timeInc(5);
    dut.clk = 0;
    sample();
    check_equal(0, "init-fall", "q", 0, dut.q);

    for (const Case &c : cases)
    {
        const unsigned case_id = completed + 1;
        const std::uint32_t before = expected_q;

        // 周期起点 +1 ns：非时钟输入提前驱动并求值。
        context.timeInc(1);
        dut.rst = c.rst & 1u;
        dut.en = c.en & 1u;
        sample();
        check_equal(case_id, "low-before-rise", "q",
                    before, dut.q);

        // 周期起点 +5 ns：上升沿。
        context.timeInc(4);
        dut.clk = 1;
        sample();
        ++cycle;
        expected_q = c.want;
        check_equal(case_id, "rise", "q", expected_q, dut.q);

        // 周期起点 +10 ns：下降沿。
        context.timeInc(5);
        dut.clk = 0;
        sample();
        check_equal(case_id, "fall", "q", expected_q, dut.q);

        ++completed;
        std::cout << "CASE case=" << case_id
                  << " cycle=" << cycle
                  << " time_ns=" << context.time()
                  << " name=" << c.name
                  << " q=" << static_cast<unsigned>(dut.q)
                  << '\n';
    }

    check_equal(completed, "end", "clk", 0, dut.clk);
    check_equal(completed, "end", "time_ns", 110, context.time());

    dut.final();
    trace.close();

    if (completed != 10 || cycle != 11 ||
        checks != 34 || samples != 33)
    {
        std::cerr << "INCOMPLETE cases=" << completed
                  << " cycles=" << cycle
                  << " checks=" << checks
                  << " samples=" << samples
                  << " expected=10/11/34/33\n";
        return 2;
    }

    std::cout << (errors == 0 ? "PASS" : "FAIL")
              << " cases=" << completed
              << " cycles=" << cycle
              << " checks=" << checks
              << " errors=" << errors
              << " samples=" << samples
              << " time_ns=" << context.time() << '\n';

    return errors == 0 ? 0 : 1;
}