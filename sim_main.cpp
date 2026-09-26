//
#include "Vmux2.h"
#include "verilated.h"

#include <iostream>

int main(int argc, char **argv)
{
    VerilatedContext context; // 仿真上下文
    context.commandArgs(argc, argv);
    Vmux2 dut{&context}; // 模块实例

    unsigned cases = 0;
    unsigned errors = 0;

    // lambda：这里把它当作 main 内可以重复调用的小函数。
    // [&] 允许它访问外面的 dut、cases、errors。
    auto run_case = [&](unsigned a, unsigned b,
                        unsigned sel, unsigned expected)
    {
        ++cases;

        // TODO 1：
        // 把 a、b、sel 写入 DUT 的对应端口，然后调用 eval()。
        // 完成后删除下面这一行；它防止未完成的骨架被误用。
        // #error "TODO 1: drive all inputs, then eval"

        // My Code Start
        dut.a = a;
        dut.b = b;
        dut.sel = sel;
        dut.eval();
        const unsigned actual = dut.y;
        // My Code End

        if (actual != expected)
        {
            ++errors;
            std::cerr
                << "FAIL case=" << cases
                << " cycle=N/A"
                << " a=" << a
                << " b=" << b
                << " sel=" << sel
                << " expected=" << expected
                << " actual=" << actual << '\n';
        }
    };

    // 已完成的第一个用例：
    run_case(0x00, 0xFF, 0, 0x00); // 选择 a，输出全零

    // TODO 2：
    // 按下表补齐剩余 7 次 run_case(...) 调用。
    // 每次的 expected 都先根据接口规格手算，再填入常量。

    // My Code Start
    run_case(0x00, 0xFF, 1, 0xFF); // 只改变选择信号
    run_case(0xA5, 0x5A, 0, 0xA5); // 混合位图案，检查选路与数据
    run_case(0xA5, 0x3C, 0, 0xA5); // 只改未选输入，输出应保持
    run_case(0x81, 0x3C, 0, 0x81); // 改变被选输入，输出应跟随
    run_case(0x81, 0x3C, 1, 0x3C); // 同一对输入切换选路
    run_case(0x00, 0x3C, 1, 0x3C); // 只改未选输入，输出应保持
    run_case(0xFF, 0xFF, 1, 0xFF); // 两路相等，输出全一
    // My Code End

    dut.final();

    if (cases != 8)
    {
        std::cerr << "INCOMPLETE expected_cases=8"
                  << " actual_cases=" << cases << '\n';
        return 2;
    }

    if (errors != 0)
    {
        std::cerr << "FAIL cases=" << cases
                  << " errors=" << errors << '\n';
        return 1;
    }

    std::cout << "PASS cases=" << cases
              << " errors=" << errors << '\n';
    return 0;
}