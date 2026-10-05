//
#include "Vreset_pair.h"
#include "verilated.h"

#include <cstdint>
#include <iostream>

struct Step
{
    const char *phase;
    std::uint32_t clk;
    std::uint32_t reset; // 同时驱动两个复位端口
    std::uint32_t d;
};

struct Expected
{
    std::uint32_t sync;
    std::uint32_t async;
};

int main(int argc, char **argv)
{
    VerilatedContext context;
    context.commandArgs(argc, argv);
    Vreset_pair dut{&context};

    constexpr Step steps[] = {
        {"initial-assert-low", 0, 1, 9},
        {"initial-reset-rise", 1, 1, 9},
        {"initial-reset-fall", 0, 1, 9},
        {"release-low", 0, 0, 9},
        {"capture-9", 1, 0, 9},
        {"fall-after-9", 0, 0, 9},
        {"pulse-assert-low", 0, 1, 6},
        {"pulse-release-low", 0, 0, 6},
        {"capture-6", 1, 0, 6},
        {"assert-high", 1, 1, 3},
        {"release-high", 1, 0, 3},
        {"fall-after-release", 0, 0, 3},
        {"held-reset-assert", 0, 1, 15},
        {"held-reset-rise", 1, 1, 15},
        {"held-reset-release", 1, 0, 10},
        {"fall-before-10", 0, 0, 10},
        {"capture-10", 1, 0, 10}};

    // 期望值来自接口规格，不读取 DUT 输出生成。
    constexpr Expected expected[] = {
        {0, 0}, // 步骤1：sync 只是占位，不检查, 0, 1, 9
        {0, 0}, // 步骤2：initial-assert-low, 1, 1, 9
        {0, 0}, // 步骤3：initial-reset-fall, 0, 1, 9
        {0, 0}, // 步骤4：release-low, 0, 0, 9
        {9, 9}, // 步骤5：capture-9, 1, 0, 9
        // TODO 1 My Code Start
        {9, 9},  // 步骤6：fall-after-9, 0, 0, 9，时钟下降沿，复位=0，不变
        {9, 0},  // 步骤7：pulse-assert-low, 0, 1, 6，时钟不变，复位=1，同步不变，异步清零
        {9, 0},  // 步骤8：pulse-release-low, 0, 0, 6，时钟不变，复位=0，不变
        {6, 6},  // 步骤9：capture-6, 1, 0, 6，时钟上升沿，复位=0，同步异步都采样
        {6, 0},  // 步骤10：assert-high, 1, 1, 3，时钟不变，复位=1，同步不变，异步清零
        {6, 0},  // 步骤11：release-high, 1, 0, 3，时钟不变，复位=0，不变
        {6, 0},  // 步骤12：fall-after-release, 0, 0, 3，时钟下降沿，复位=0，不变
        {6, 0},  // 步骤13：held-reset-assert, 0, 1, 15，时钟不变，复位=1，同步不变，异步清零
        {0, 0},  // 步骤14：held-reset-rise, 1, 1, 15，时钟上升沿，复位=1，同步清零，异步清零
        {0, 0},  // 步骤15：held-reset-release, 1, 0, 10，时钟不变，复位=0，不变
        {0, 0},  // 步骤16：fall-before-10, 0, 0, 10，时钟下降沿，复位=0，不变
        {10, 10} // 步骤17：capture-10, 1, 0, 10，时钟上升沿，复位=0，同步异步都采样
        // TODO 1 My Code End
        // TODO 1：补齐步骤6～17的12组期望值。
        // 每组顺序为 {q_sync, q_async}。
        // #error "TODO 1: complete the independent expected table"
    };

    constexpr unsigned step_count = sizeof(steps) / sizeof(steps[0]);
    constexpr unsigned expectation_count =
        sizeof(expected) / sizeof(expected[0]);

    unsigned cases = 0;
    unsigned cycle = 0;
    unsigned checks = 0;
    unsigned errors = 0;

    auto check_equal = [&](unsigned case_id,
                           const char *phase,
                           const char *signal,
                           std::uint32_t want,
                           std::uint32_t actual)
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

    // 建立已求值的 clk=0、reset=0。
    // 不把这里观察到的输出当成有保证的初始值。
    dut.clk = 0;
    dut.rst_sync = 0;
    dut.rst_async = 0;
    dut.d = 0;
    dut.eval();

    if (expectation_count != step_count)
    {
        std::cerr << "INCOMPLETE expected_rows="
                  << expectation_count
                  << " required_rows=" << step_count << '\n';
        dut.final();
        return 2;
    }

    for (unsigned i = 0; i < step_count; ++i)
    {
        const Step &s = steps[i];
        const Expected &e = expected[i];
        const std::uint32_t old_clk = dut.clk;
        ++cases;

        // TODO 2：
        // 1. 时间推进5个单位，本课对应5 ns。
        // 2. 写入两个复位端口和 d，分别限制为1位、4位。
        // 3. eval()，让非时钟输入先得到处理。
        // 4. 写入本步骤的 clk，再 eval()。
        // 5. 仅当 old_clk==0 且新 clk==1 时，++cycle。
        // #error "TODO 2: drive inputs before clock and evaluate"
        // TODO 2 My Code Start
        context.timeInc(5);
        dut.d = s.d & 0xFu;
        dut.rst_sync = s.reset & 0x1u;
        dut.rst_async = s.reset & 0x1u;
        dut.eval();
        dut.clk = s.clk;
        dut.eval();
        if (old_clk == 0 && dut.clk == 1)
        {
            ++cycle;
        }
        // TODO 2 My Code End

        // TODO 3：
        // 步骤1（i==0）只检查 q_async；
        // 其余步骤分别检查 q_sync 和 q_async。
        // 使用 cases、s.phase 和 e 中的独立期望值。
        // 信号名使用 "q_sync"、"q_async"。
        // #error "TODO 3: compare outputs with the expected table"
        // TODO 3 My Code Start
        if (i == 0)
        {
            check_equal(cases, s.phase, "q_async", e.async, dut.q_async);
        }
        else
        {
            check_equal(cases, s.phase, "q_sync", e.sync, dut.q_sync);
            check_equal(cases, s.phase, "q_async", e.async, dut.q_async);
        }
        // TODO 3 My Code End

        std::cout << "STEP case=" << cases
                  << " cycle=" << cycle
                  << " time_ns=" << context.time()
                  << " phase=" << s.phase
                  << " q_sync=" << static_cast<unsigned>(dut.q_sync)
                  << " q_async=" << static_cast<unsigned>(dut.q_async)
                  << '\n';
    }

    dut.final();

    if (cases != 17 || cycle != 5 || checks != 33)
    {
        std::cerr << "INCOMPLETE cases=" << cases
                  << " cycles=" << cycle
                  << " checks=" << checks
                  << " expected_cases=17 expected_cycles=5"
                  << " expected_checks=33\n";
        return 2;
    }

    if (context.time() != 85)
    {
        ++errors;
        std::cerr << "FAIL case=" << cases
                  << " cycle=" << cycle
                  << " phase=end signal=time_ns"
                  << " expected=85 actual=" << context.time() << '\n';
    }

    std::cout << (errors == 0 ? "PASS" : "FAIL")
              << " cases=" << cases
              << " cycles=" << cycle
              << " checks=" << checks
              << " errors=" << errors
              << " time_ns=" << context.time() << '\n';

    return errors == 0 ? 0 : 1;
}