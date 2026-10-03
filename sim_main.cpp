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
    constexpr std::uint32_t samples[] = {15u, 0u, 5u, 10u};
    constexpr unsigned expected_cases = 4;
    constexpr unsigned expected_checks = 1 + expected_cases * 4;
    constexpr unsigned expected_cycles = 1 + expected_cases;

    unsigned cases = 0;
    unsigned cycle = 0; // 已完成求值的上升沿数量
    unsigned checks = 0;
    unsigned errors = 0;

    auto check_q = [&](unsigned case_id,
                       const char *phase,
                       std::uint32_t expected)
    {
        ++checks;
        const std::uint32_t actual = dut.q;

        if (actual != expected)
        {
            ++errors;
            std::cerr << "FAIL case=" << case_id
                      << " cycle=" << cycle
                      << " phase=" << phase
                      << " clk=" << static_cast<unsigned>(dut.clk)
                      << " d=" << static_cast<unsigned>(dut.d)
                      << " signal=q"
                      << " expected=" << expected
                      << " actual=" << actual << '\n';
        }
    };

    // 建立已知的低电平；此时不检查 q 的初值。
    dut.clk = 0;
    dut.d = 0;
    dut.eval();

    // TODO 1：
    // 产生上升沿并 eval()，然后 ++cycle。
    // 调用 check_q(0, "init-rise", 0u)，验证初始化采样。
    // 再将 clk 拉低并 eval()，为正式用例做好准备。
    // #error "TODO 1: initialize through a real rising edge"
    // TODO1 My Code Start
    dut.clk = 1;
    dut.eval();
    ++cycle;
    check_q(0, "init-rise", 0u);
    dut.clk = 0;
    dut.eval();
    // TODO1 My Code End
    // 软件期望状态来自规格：初始化上升沿采样了 0。
    // 不要写成 expected_q = dut.q。
    std::uint32_t expected_q = 0;

    for (const std::uint32_t sample : samples)
    {
        ++cases;
        const std::uint32_t sampled_d = sample & mask;
        const std::uint32_t changed_d = sampled_d ^ mask;

        // TODO 2：完成以下两个阶段。
        //
        // A. low-before-rise：
        //    时钟当前为 0。
        //    将 sampled_d 写入 d，eval()。
        //    check_q 检查 q 仍等于 expected_q。
        //
        // B. rise：
        //    将 clk 置为 1，eval()，然后 ++cycle。
        //    根据采样规格更新 expected_q。
        //    check_q 检查 q 等于更新后的 expected_q。
        // #error "TODO 2: drive before edge and check capture"
        // TODO2 My Code Start
        dut.clk = 0;
        dut.d = sampled_d;
        dut.eval();
        check_q(cases, "low-before-rise", expected_q);
        dut.clk = 1;
        dut.eval();
        ++cycle;
        expected_q = sample;
        check_q(cases, "rise", expected_q);
        // TODO2 My Code End

        // TODO 3：完成以下两个阶段。
        //
        // C. high-after-change：
        //    保持 clk=1，将 changed_d 写入 d，eval()。
        //    check_q 检查 q 仍等于 expected_q。
        //
        // D. fall：
        //    保持 d 不变，将 clk 置为 0，eval()。
        //    check_q 检查 q 仍等于 expected_q。
        //
        // C、D 都不更新 expected_q，也不增加 cycle。
        // #error "TODO 3: check high-level and falling-edge hold"
        // TODO3 My Code Start
        dut.clk = 1;
        dut.d = changed_d;
        dut.eval();
        check_q(cases, "high-after-change", expected_q);
        dut.clk = 0;
        dut.eval();
        check_q(cases, "fall", expected_q);
        // TODO3 My Code End
    }

    dut.final();

    if (cases != expected_cases ||
        checks != expected_checks ||
        cycle != expected_cycles)
    {
        std::cerr << "INCOMPLETE cases=" << cases
                  << " cycles=" << cycle
                  << " checks=" << checks
                  << " expected_cases=" << expected_cases
                  << " expected_cycles=" << expected_cycles
                  << " expected_checks=" << expected_checks << '\n';
        return 2;
    }

    std::cout << (errors == 0 ? "PASS" : "FAIL")
              << " cases=" << cases
              << " cycles=" << cycle
              << " checks=" << checks
              << " errors=" << errors << '\n';

    return errors == 0 ? 0 : 1;
}