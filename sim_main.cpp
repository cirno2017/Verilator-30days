//
#include "Vdff4.h"
#include "verilated.h"

#include <cstdint>
#include <iostream>

int main(int argc, char **argv)
{
    VerilatedContext context;
    context.commandArgs(argc, argv);
    Vdff4 dut{&context};

    constexpr std::uint32_t mask = 0xFu;
    constexpr std::uint64_t half_period = 5;
    constexpr std::uint32_t samples[] = {15u, 0u, 5u, 10u};

    constexpr unsigned expected_cases = 4;
    constexpr unsigned expected_cycles = 5;
    constexpr unsigned expected_checks = 24;
    constexpr std::uint64_t expected_end_time = 70;

    unsigned cases = 0;
    unsigned cycle = 0;
    unsigned checks = 0;
    unsigned errors = 0;
    std::uint32_t expected_q = 0;

    auto check_equal = [&](unsigned case_id,
                           const char *phase,
                           const char *signal,
                           std::uint64_t expected,
                           std::uint64_t actual)
    {
        ++checks;
        if (expected != actual)
        {
            ++errors;
            std::cerr << "FAIL case=" << case_id
                      << " cycle=" << cycle
                      << " time_ns=" << context.time()
                      << " phase=" << phase
                      << " signal=" << signal
                      << " expected=" << expected
                      << " actual=" << actual << '\n';
        }
    };

    // 推进半周期，到达指定时钟电平，并完成求值。
    // 本函数不修改 cycle，也不修改 expected_q。
    auto half_step = [&](std::uint32_t next_clk)
    {
        // TODO 1：
        // 依次完成：
        // 1. 时间增加 half_period。
        // 2. 将 next_clk 的最低位写入 dut.clk。
        // 3. 调用 eval()。
        // #error "TODO 1: advance time, drive clock, evaluate"
        // TODO 1 My Code Start
        context.timeInc(half_period);
        dut.clk = next_clk & 0x1u;
        dut.eval();
        // TODO 1 My Code End
    };

    // 入口和出口都约定 clk=0。
    auto tick = [&](unsigned case_id, std::uint32_t sample)
    {
        const std::uint64_t start_time = context.time();
        const std::uint32_t sampled_d = sample & mask;

        // TODO 2：完成以下步骤，共调用 check_equal 五次。
        //
        // A. 写入 sampled_d，eval()。
        //    检查 q == expected_q，phase="low-before-rise"。
        //
        // B. 调用 half_step(1u)，然后 ++cycle。
        //    根据采样规格更新 expected_q。
        //    检查 q == expected_q，phase="rise"。
        //
        // C. 调用 half_step(0u)。
        //    检查 q == expected_q，phase="fall"。
        //
        // D. phase="tick-end"：
        //    检查 clk == 0。
        //    检查 time == start_time + 2 * half_period。
        //
        // 检查信号名分别使用 "q"、"clk"、"time_ns"。
        // #error "TODO 2: implement one full clock cycle"
        // TODO 2 My Code Start
        // A Start
        dut.d = sampled_d;
        dut.eval();
        check_equal(case_id, "low-before-rise", "q", expected_q, dut.q);
        // B Start
        half_step(1u);
        ++cycle;
        expected_q = sampled_d;
        check_equal(case_id, "rise", "q", expected_q, dut.q);
        // C Start
        half_step(0u);
        check_equal(case_id, "fall", "q", expected_q, dut.q);
        // D Start
        check_equal(case_id, "tick-end", "clk", 0u, dut.clk);
        check_equal(case_id, "tick-end", "time_ns", start_time + 2 * half_period, context.time());
        // TODO 2 My Code End

        std::cout << "TICK case=" << case_id
                  << " cycle=" << cycle
                  << " time_ns=" << context.time()
                  << " q=" << static_cast<unsigned>(dut.q)
                  << '\n';
    };

    // 建立低电平，此时不检查 q 的初值。
    dut.clk = 0;
    dut.d = 0;
    dut.eval();

    // 初始化：t=5 上升沿采样 0，t=10 回到低电平。
    half_step(1u);
    ++cycle;
    check_equal(0, "init-rise", "q", 0u, dut.q);
    half_step(0u);

    // TODO 3：验证只有时间前进时，寄存器不会采样。
    //
    // 当前 t=10、clk=0，按规格 q 已为 0。
    // 1. 写入 d=15，并 eval()。
    // 2. 只将时间增加 20，再 eval()；不修改 clk。
    // 3. phase="idle-time-only"，调用 check_equal 三次：
    //    q 应为 0，clk 应为 0，time_ns 应为 30。
    //
    // 不更新 expected_q，不增加 cycle。
    // #error "TODO 3: time passes without a clock edge"
    // TODO 3 My Code Start
    dut.d = 15u;
    dut.eval();
    context.timeInc(20);
    dut.eval();
    check_equal(0, "idle-time-only", "q", 0u, dut.q);
    check_equal(0, "idle-time-only", "clk", 0u, dut.clk);
    check_equal(0, "idle-time-only", "time_ns", 30u, context.time());
    // TODO 3 My Code End

    for (const std::uint32_t sample : samples)
    {
        ++cases;
        tick(cases, sample);
    }

    dut.final();

    if (cases != expected_cases ||
        cycle != expected_cycles ||
        checks != expected_checks)
    {
        std::cerr << "INCOMPLETE cases=" << cases
                  << " cycles=" << cycle
                  << " checks=" << checks
                  << " expected_cases=" << expected_cases
                  << " expected_cycles=" << expected_cycles
                  << " expected_checks=" << expected_checks << '\n';
        return 2;
    }

    // 时间错误也必须导致失败，不能只打印出来。
    if (context.time() != expected_end_time)
    {
        ++errors;
        std::cerr << "FAIL case=" << cases
                  << " cycle=" << cycle
                  << " phase=end signal=time_ns"
                  << " expected=" << expected_end_time
                  << " actual=" << context.time() << '\n';
    }

    std::cout << (errors == 0 ? "PASS" : "FAIL")
              << " cases=" << cases
              << " cycles=" << cycle
              << " checks=" << checks
              << " errors=" << errors
              << " time_ns=" << context.time() << '\n';

    return errors == 0 ? 0 : 1;
}