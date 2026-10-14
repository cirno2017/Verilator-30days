//
#include "Vcounter_param.h"
#include "verilated.h"

#include <cstdint>
#include <iostream>

//
#ifdef __INTELLISENSE__
#ifndef TB_WIDTH
#define TB_WIDTH 8
#endif
#endif
// 上面这段是消除vscode报错用的

#ifndef TB_WIDTH
// #error "Build with -CFLAGS containing -DTB_WIDTH=..."
#endif

static constexpr unsigned Width = TB_WIDTH;
static_assert(Width >= 1 && Width <= 8,
              "This exercise supports widths 1 through 8");

// Modulus：W 位计数器的状态数。
// Mask：W 位计数器的最大值。
static constexpr std::uint64_t Modulus = std::uint64_t{1} << Width;
static constexpr std::uint64_t Mask = Modulus - 1u;
//

static std::uint64_t model_next(std::uint64_t old,
                                bool rst, bool en)
{
    if (rst)
        return 0;
    if (en)
        return (old + 1u) % Modulus;
    return old;
}

class Testbench
{
private:
    VerilatedContext &context;
    Vcounter_param dut;

    std::uint64_t expected_state = 0;
    unsigned cycle = 0;
    unsigned checks = 0;
    unsigned errors = 0;
    const char *case_name = "init";

    void check_equal(const char *item,
                     std::uint64_t want,
                     std::uint64_t actual)
    {
        ++checks;
        if (want == actual)
            return;

        ++errors;
        std::cerr << "FAIL width=" << Width
                  << " case=" << case_name
                  << " cycle=" << cycle
                  << " time_ns=" << context.time()
                  << " item=" << item
                  << " expected=" << want
                  << " actual=" << actual << '\n';
    }

    // 进入、退出时 clk=0；每拍推进 10 ns。
    void tick(bool rst, bool en, bool check_before = true)
    {
        ++cycle;
        const auto old = expected_state;
        const auto next = model_next(old, rst, en);

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
    }

public:
    explicit Testbench(VerilatedContext &ctx)
        : context(ctx), dut(&ctx)
    {
        dut.clk = 0;
        dut.rst = 1;
        dut.en = 0;
        dut.eval();

        // 首次有效复位前，不假设 DUT 上电值。
        tick(true, false, false);
    }

    void run()
    {
        case_name = "config";
        check_equal("build/width", Width, dut.width_tag);
        if (dut.width_tag != Width)
            return;

        // 使用 tick()；不得直接修改 expected_state 或 dut.q。

        case_name = "count_to_max";
        // 从零开始，恰好 Mask 次有效递增，停在最大值。
        for (std::uint64_t i = 0; i < Mask; ++i)
            tick(false, true);

        case_name = "hold_max";
        // 禁用一拍，保持最大值。
        tick(false, false);

        case_name = "wrap";
        // 使能一拍，最大值回绕到零。
        tick(false, true);

        case_name = "hold_zero";
        // 禁用一拍，保持零。
        tick(false, false);

        case_name = "reset_priority";
        // 先使能一拍到 1，再施加 rst=en=1 一拍清零。
        tick(false, true);
        tick(true, true);
    }

    int finish()
    {
        case_name = "finish";
        if (dut.width_tag == Width)
            check_equal("end/cycles", Modulus + 5u, cycle);
        check_equal("end/clk", 0, dut.clk);
        check_equal("end/q", 0, dut.q);

        dut.final();
        std::cout << (errors == 0 ? "PASS" : "FAIL")
                  << " width=" << Width
                  << " mask=" << Mask
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

    std::cout << "RUN width=" << Width
              << " modulus=" << Modulus
              << " mask=" << Mask << '\n';

    Testbench tb{context};
    tb.run();
    return tb.finish();
}