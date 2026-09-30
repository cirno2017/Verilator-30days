//
#include "Vadder4.h"
#include "verilated.h"

#include <cstdint>
#include <iostream>

struct Expected
{
    std::uint32_t sum;
    std::uint32_t carry;
};

// 只根据接口输入计算期望结果，不接触 DUT。
Expected reference_add(std::uint32_t a, std::uint32_t b)
{
    // TODO 1：
    // 先将一个操作数扩宽为 uint64_t，再求完整和。
    // 根据 4 位接口，用余数和整数除法计算 sum、carry。
    // 返回 Expected{... , ...}；必要时显式转换类型。
    // #error "TODO 1: implement reference model"
    // My TODO1 Code Start
    std::uint64_t full = static_cast<std::uint64_t>(a) + b;
    std::uint32_t sum = full % 16u;
    std::uint32_t carry = full / 16u;
    return Expected{sum, carry};
    // My TODO1 Code END
}

int main(int argc, char **argv)
{
    VerilatedContext context;
    context.commandArgs(argc, argv);
    Vadder4 dut{&context};

    constexpr std::uint32_t values = 16;
    constexpr std::uint32_t mask = 0xFu;
    constexpr unsigned expected_cases = values * values;
    constexpr unsigned expected_checks = expected_cases * 2;

    unsigned cases = 0;
    unsigned checks = 0;
    unsigned errors = 0;

    auto check_equal = [&](unsigned case_id,
                           const char *cycle,
                           std::uint32_t a,
                           std::uint32_t b,
                           const char *signal,
                           std::uint32_t expected,
                           std::uint32_t actual)
    {
        ++checks;
        if (expected != actual)
        {
            ++errors;
            std::cerr << "FAIL case=" << case_id
                      << " cycle=" << cycle
                      << " a=" << a
                      << " b=" << b
                      << " signal=" << signal
                      << " expected=" << expected
                      << " actual=" << actual << '\n';
        }
    };

    auto run_case = [&](std::uint32_t a, std::uint32_t b)
    {
        ++cases;
        const Expected expected = reference_add(a, b);

        // TODO 2：
        // 将 a、b 分别写入 DUT，写入时使用 mask。
        // 调用 eval()。
        // 分别调用 check_equal 检查 sum 和 carry。
        // case_id 使用 cases，cycle 使用 "N/A"；
        // 报告中的输入使用 a、b。
        // 两次检查都执行，不要用 && 串联。
        // #error "TODO 2: drive evaluate and check"
        // My TODO2 Code Start
        dut.a = a & 0xF;
        dut.b = b & 0xF;
        dut.eval();
        check_equal(cases, "N/A", a, b, "sum", expected.sum, dut.sum);
        check_equal(cases, "N/A", a, b, "carry", expected.carry, dut.carry);
        // My TODO2 Code END
    };

    // TODO 3：
    // 写双层循环，a 为外层、b 为内层。
    // 两者都从 0 开始，条件为小于 values。
    // 每组输入调用一次 run_case(a, b)。
    // #error "TODO 3: enumerate all input pairs"
    // My TODO3 Code Start
    for (uint32_t a = 0; a < 16; ++a)
    {
        for (uint32_t b = 0; b < 16; ++b)
        {
            run_case(a, b);
        }
    }
    // My TODO3 Code END

    dut.final();

    if (cases != expected_cases || checks != expected_checks)
    {
        std::cerr << "INCOMPLETE cases=" << cases
                  << " checks=" << checks
                  << " expected_cases=" << expected_cases
                  << " expected_checks=" << expected_checks << '\n';
        return 2;
    }

    std::cout << (errors == 0 ? "PASS" : "FAIL")
              << " cases=" << cases
              << " checks=" << checks
              << " errors=" << errors << '\n';

    return errors == 0 ? 0 : 1;
}