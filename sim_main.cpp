//
#include "Vcounter2.h"
#include "verilated.h"

#include <cstdint>
#include <iostream>

// 纯规格模型：不访问 DUT，不推进时间，不修改其他变量。
std::uint32_t model_next(std::uint32_t old_state,
                         bool rst, bool en)
{
    // TODO 1：
    // 根据本课数学规格返回下一状态。
    // 使用 C++ 的 % 表达模 4 递增。
    // 覆盖复位、递增、保持三个分支。
    // #error "TODO 1: implement the specification model"
    // TODO 1 My Code Start
    if (rst == 1)
    {
        return 0;
    }
    else if (rst == 0 && en == 1)
    {
        return (old_state + 1) % 4;
    }
    else
    {
        return old_state;
    }
    // TODO 1 My Code End
}

struct Case
{
    const char *name;
    bool rst;
    bool en;
    // 注意：这里已经没有逐项 want。
};

int main(int argc, char **argv)
{
    VerilatedContext context;
    context.commandArgs(argc, argv);
    Vcounter2 dut{&context};

    constexpr Case cases[] = {
        {"increment-to-1", false, true},   // 1
        {"hold-at-1", false, false},       // 2
        {"increment-to-2", false, true},   // 3
        {"increment-to-3", false, true},   // 4
        {"hold-at-maximum", false, false}, // 5
        {"wrap-to-zero", false, true},     // 6
        {"increment-again", false, true},  // 7
        {"reset-with-en-0", true, false},  // 8
        {"resume", false, true},           // 9
        {"reset-with-en-1", true, true},   // 10
        {"keep-reset", true, true},        // 11
        {"resume-again", false, true}      // 12
    };

    unsigned completed = 0;
    unsigned cycle = 0;
    unsigned checks = 0;
    unsigned errors = 0;
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

    // 初始化：先建立低电平，不检查未保证的初始 q。
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

    // expected_state=0 来自复位规格，不从 dut.q 读取。

    for (const Case &c : cases)
    {
        const unsigned case_id = completed + 1;
        const std::uint32_t old_state = expected_state;

        // 周期起点 +1 ns：提前驱动非时钟输入。
        context.timeInc(1);
        dut.rst = c.rst;
        dut.en = c.en;
        dut.eval();

        // TODO 2：
        // A. 声明 const std::uint32_t next_state，
        //    用 model_next(old_state, c.rst, c.en) 计算。
        // B. 调用一次 check_equal：
        //    phase="low-before-rise"，signal="q"，
        //    检查 DUT 仍等于 old_state。
        // #error "TODO 2: predict next state and check old state"
        // TODO 2 My Code Start
        const std::uint32_t next_state = model_next(old_state, c.rst, c.en);
        check_equal(case_id, "low-before-rise", "q", old_state, dut.q);
        // TODO 2 My Code End

        // 周期起点 +5 ns：产生并处理上升沿。
        context.timeInc(4);
        dut.clk = 1;
        dut.eval();
        ++cycle;

        // TODO 3：
        // A. 将 expected_state 更新为 next_state。
        // B. 调用一次 check_equal：
        //    phase="rise"，signal="q"，
        //    检查 DUT 等于 expected_state。
        // #error "TODO 3: commit prediction and check the new state"
        // TODO 3 My Code Start
        expected_state = next_state;
        check_equal(case_id, "rise", "q", expected_state, dut.q);
        // TODO 3 My Code End

        // 周期起点 +10 ns：下降沿不更新参考状态。
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
                  << " rst=" << c.rst
                  << " en=" << c.en
                  << " old=" << old_state
                  << " next=" << expected_state
                  << " actual=" << static_cast<unsigned>(dut.q)
                  << '\n';
    }

    check_equal(completed, "end", "clk", 0, dut.clk);
    check_equal(completed, "end", "time_ns", 130, context.time());
    dut.final();

    if (completed != 12 || cycle != 13 || checks != 40)
    {
        std::cerr << "INCOMPLETE cases=" << completed
                  << " cycles=" << cycle
                  << " checks=" << checks
                  << " expected=12/13/40\n";
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