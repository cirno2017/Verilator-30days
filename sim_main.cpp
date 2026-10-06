//
#include "Vcounter3.h"
#include "verilated.h"

#include <cstdint>
#include <iostream>

struct Case
{
    const char *name;
    std::uint32_t rst;
    std::uint32_t en;
};

int main(int argc, char **argv)
{
    VerilatedContext context;
    context.commandArgs(argc, argv);
    Vcounter3 dut{&context};

    constexpr std::uint64_t half_period = 5;

    constexpr Case cases[] = {
        {"hold-zero", 0, 0},            // 1
        {"increment-to-1", 0, 1},       // 2
        {"hold-nonzero", 0, 0},         // 3
        {"increment-to-2", 0, 1},       // 4
        {"increment-to-3", 0, 1},       // 5
        {"increment-to-4", 0, 1},       // 6
        {"increment-to-5", 0, 1},       // 7
        {"increment-to-6", 0, 1},       // 8
        {"increment-to-7", 0, 1},       // 9
        {"hold-at-maximum", 0, 0},      // 10
        {"wrap-to-zero", 0, 1},         // 11
        {"increment-after-wrap", 0, 1}, // 12
        {"reset-with-en-0", 1, 0},      // 13
        {"resume-after-reset", 0, 1},   // 14
        {"reset-with-en-1", 1, 1},      // 15
        {"keep-reset-active", 1, 1},    // 16
        {"resume-again", 0, 1}          // 17
    };

    // 每项表示对应 case 的上升沿之后，q 应有的值。
    constexpr std::uint32_t expected_after[] = {
        0u,
        1u,
        1u,
        2u,
        // TODO 1 My Code Start
        3u,
        4u,
        5u,
        6u,
        7u,
        7u,
        0u,
        1u,
        0u,
        1u,
        0u,
        0u,
        1u
        // TODO 1 My Code End

        // TODO 1：补齐 case 5～17 的 13 个期望值。
        // 根据接口规格手算，不读取 DUT 输出。
        // #error "TODO 1: complete expected values"
    };

    constexpr unsigned case_count =
        sizeof(cases) / sizeof(cases[0]);
    constexpr unsigned expectation_count =
        sizeof(expected_after) / sizeof(expected_after[0]);

    unsigned completed = 0;
    unsigned cycle = 0;
    unsigned checks = 0;
    unsigned errors = 0;
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

    auto half_step = [&](std::uint32_t next_clk)
    {
        context.timeInc(half_period);
        dut.clk = next_clk & 1u;
        dut.eval();
    };

    if (expectation_count != case_count)
    {
        std::cerr << "INCOMPLETE expected_rows="
                  << expectation_count
                  << " required_rows=" << case_count << '\n';
        dut.final();
        return 2;
    }

    // 建立低电平，不检查未保证的初始 q。
    dut.clk = 0;
    dut.rst = 1;
    dut.en = 0;
    dut.eval();

    // 初始化复位周期：t=5 上升沿，t=10 下降沿。
    half_step(1u);
    ++cycle;
    check_equal(0, "init-rise", "q", 0u, dut.q);
    half_step(0u);
    check_equal(0, "init-fall", "q", 0u, dut.q);

    for (unsigned i = 0; i < case_count; ++i)
    {
        const Case &c = cases[i];
        const unsigned case_id = i + 1;
        const std::uint32_t before = expected_q;
        const std::uint32_t want = expected_after[i];

        // 每个用例入口 clk=0。
        // 非时钟输入提前驱动并单独求值。
        dut.rst = c.rst & 1u;
        dut.en = c.en & 1u;
        dut.eval();

        // TODO 2：调用 check_equal 一次。
        // phase="low-before-rise"，signal="q"。
        // 此时没有上升沿，应检查 q == before。
        // 即使本用例 rst=1，也不能提前要求 q 清零。
        // #error "TODO 2: check state before the rising edge"
        // TODO 2 My Code Start
        check_equal(case_id, "low-before-rise", "q", before, dut.q);
        // TODO 2 My Code End

        // TODO 3：完成一个周期的剩余操作。
        // A. half_step(1u)，然后 ++cycle。
        // B. expected_q 更新为独立表中的 want。
        // C. check_equal：phase="rise"，检查 q == expected_q。
        // D. half_step(0u)。
        // E. check_equal：phase="fall"，检查 q == expected_q。
        // 本 TODO 共调用 check_equal 两次。
        // #error "TODO 3: clock and check the counter"
        // TODO 3 My Code Start
        half_step(1u);
        ++cycle;
        expected_q = want;
        check_equal(case_id, "rise", "q", expected_q, dut.q);
        half_step(0u);
        check_equal(case_id, "fall", "q", expected_q, dut.q);
        // TODO 3 My Code End

        ++completed;
        std::cout << "CASE case=" << case_id
                  << " cycle=" << cycle
                  << " time_ns=" << context.time()
                  << " name=" << c.name
                  << " rst=" << c.rst
                  << " en=" << c.en
                  << " q=" << static_cast<unsigned>(dut.q)
                  << '\n';
    }

    check_equal(completed, "end", "clk", 0u, dut.clk);
    check_equal(completed, "end", "time_ns", 180u, context.time());
    dut.final();

    if (completed != 17 || cycle != 18 || checks != 55)
    {
        std::cerr << "INCOMPLETE cases=" << completed
                  << " cycles=" << cycle
                  << " checks=" << checks
                  << " expected_cases=17 expected_cycles=18"
                  << " expected_checks=55\n";
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