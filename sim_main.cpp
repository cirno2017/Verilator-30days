//
#include "Vmux4_en.h"
#include "verilated.h"

#include <cstdint>
#include <iostream>
#include <iterator> // std::size

struct TestCase
{
    const char *name;
    std::uint32_t a;
    std::uint32_t b;
    bool en;
    bool sel;
    std::uint32_t expected_y;
};

int main(int argc, char **argv)
{
    VerilatedContext context;
    context.commandArgs(argc, argv);
    Vmux4_en dut{&context};

    // TODO 1：按接口规格填写每行最后一列 expected_y。
    // 目前的 0 是占位值；有些行的正确答案也确实是 0。
    // 不修改输入或成员排列顺序。
    // #error "TODO 1: fill expected_y"
    const TestCase vectors[] = {
        // name             a    b   en sel expected_y
        {"zero_max_a", 0x0, 0xF, 1, 0, 0},
        {"zero_max_b", 0x0, 0xF, 1, 1, 0xF},
        {"max_zero_b", 0xF, 0x0, 1, 1, 0},
        {"max_zero_a", 0xF, 0x0, 1, 0, 0xF},

        {"disabled_max_0", 0xF, 0xF, 0, 0, 0},
        {"disabled_max_1", 0xF, 0xF, 0, 1, 0},
        {"disabled_mix_0", 0x5, 0xA, 0, 0, 0},
        {"disabled_mix_1", 0x5, 0xA, 0, 1, 0},

        {"alternate_a", 0x5, 0xA, 1, 0, 0x5},
        {"alternate_b", 0x5, 0xA, 1, 1, 0xA},
        {"equal_a", 0x9, 0x9, 1, 0, 0x9},
        {"equal_b", 0x9, 0x9, 1, 1, 0x9},
    };

    unsigned cases = 0;
    unsigned checks = 0;
    unsigned errors = 0;

    auto check_equal = [&](unsigned case_id,
                           const char *name,
                           const char *cycle,
                           const char *signal,
                           std::uint32_t expected,
                           std::uint32_t actual)
    {
        ++checks;
        if (expected != actual)
        {
            ++errors;
            std::cerr << "FAIL case=" << case_id
                      << " name=" << name
                      << " cycle=" << cycle
                      << " signal=" << signal
                      << " expected=" << expected
                      << " actual=" << actual << '\n';
        }
    };

    for (const auto &tc : vectors)
    {
        ++cases;

        // TODO 2：
        // 将 tc 的四个输入全部写入 DUT。
        // a、b 用 0xFu 掩码；en、sel 已是 bool。
        // 写完全部输入后调用 eval()。
        // #error "TODO 2: drive all inputs and evaluate"
        // My TODO 2 Code Start
        dut.a = tc.a & 0xFu;
        dut.b = tc.b & 0xFu;
        dut.en = tc.en;
        dut.sel = tc.sel;
        dut.eval();
        // My TODO 2 Code End

        // TODO 3：
        // 调用一次 check_equal，检查输出 y。
        // 用例编号为 cases，名称为 tc.name；
        // cycle 为 "N/A"，signal 为 "y"；
        // expected 来自表格，actual 来自 DUT。
        // #error "TODO 3: check y"
        // My TODO 3 Code Start
        check_equal(cases, tc.name, "N/A", "N/A", tc.expected_y, dut.y);
        // My TODO 3 Code End
    }

    dut.final();

    if (std::size(vectors) != 12 || cases != 12 || checks != 12)
    {
        std::cerr << "INCOMPLETE table_rows=" << std::size(vectors)
                  << " cases=" << cases
                  << " checks=" << checks
                  << " expected_each=12\n";
        return 2;
    }

    std::cout << (errors == 0 ? "PASS" : "FAIL")
              << " cases=" << cases
              << " checks=" << checks
              << " errors=" << errors << '\n';

    return errors == 0 ? 0 : 1;
}