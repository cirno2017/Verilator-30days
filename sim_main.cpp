//
#include "Vsatadd4.h"
#include "verilated.h"

#include <cstdint>
#include <iostream>

struct Expected
{
    std::uint32_t y;
    std::uint32_t overflow;
};

Expected reference(std::uint32_t a,
                   std::uint32_t b,
                   std::uint32_t sat_en)
{
    // TODO 1：
    // 根据接口规格计算 Expected。
    // 先扩宽再计算数学和。
    // overflow 与 sat_en 无关。
    // 不访问 DUT，不照抄 RTL 的分支条件。
    // #error "TODO 1: independent reference model"
    // My TODO 1 Code Start
    std::uint64_t full_u64 = static_cast<std::uint64_t>(a) + b;
    std::uint32_t overflow = full_u64 > 15 ? 1 : 0;
    if (sat_en != 0)
    {
        std::uint32_t full = full_u64 > 15 ? 15 : full_u64;
        return Expected{full, overflow};
    }
    else
    {
        std::uint32_t full = full_u64 % 16;
        return Expected{full, overflow};
    }
    // My TODO 1 Code End
}

int main(int argc, char **argv)
{
    VerilatedContext context;
    context.commandArgs(argc, argv);
    Vsatadd4 dut{&context};

    constexpr std::uint32_t values = 16;
    constexpr std::uint32_t modes = 2;
    constexpr std::uint32_t mask = 0xFu;
    constexpr unsigned expected_cases = modes * values * values;
    constexpr unsigned expected_checks = expected_cases * 2;

    unsigned cases = 0;
    unsigned checks = 0;
    unsigned errors = 0;

    auto check_equal = [&](unsigned case_id,
                           std::uint32_t a,
                           std::uint32_t b,
                           std::uint32_t sat_en,
                           const char *signal,
                           std::uint32_t expected,
                           std::uint32_t actual)
    {
        ++checks;
        if (expected != actual)
        {
            ++errors;
            std::cerr << "FAIL case=" << case_id
                      << " cycle=N/A"
                      << " a=" << a
                      << " b=" << b
                      << " sat_en=" << sat_en
                      << " signal=" << signal
                      << " expected=" << expected
                      << " actual=" << actual << '\n';
        }
    };

    auto run_case = [&](std::uint32_t a,
                        std::uint32_t b,
                        std::uint32_t sat_en)
    {
        ++cases;
        const Expected expected = reference(a, b, sat_en);

        // TODO 2：
        // 写入全部三个输入，a/b 使用 mask，sat_en 使用 1u。
        // 调用 eval()。
        // 分别检查 y 和 overflow，不要短路或提前返回。
        // check_equal 的输入信息使用本次 a、b、sat_en。
        // #error "TODO 2: drive evaluate and check"
        // My TODO 2 Code Start
        dut.a = a & mask;
        dut.b = b & mask;
        dut.sat_en = sat_en & 1u;
        dut.eval();
        check_equal(cases, a, b, sat_en, "sum", expected.y, dut.y);
        check_equal(cases, a, b, sat_en, "overflow", expected.overflow, dut.overflow);
        // My TODO 2 Code End
    };

    // TODO 3：
    // 三层循环：sat_en 最外层，a 中间，b 最内层。
    // 范围分别为 [0,modes)、[0,values)、[0,values)。
    // 每组输入调用一次 run_case(a, b, sat_en)。
    // #error "TODO 3: exhaustive enumeration"
    // My TODO 3 Code Start
    for (unsigned sat_en = 0; sat_en < modes; ++sat_en)
    {
        for (unsigned a = 0; a < values; ++a)
        {
            for (unsigned b = 0; b < values; ++b)
            {
                run_case(a, b, sat_en);
            }
        }
    }
    // My TODO 3 Code End

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