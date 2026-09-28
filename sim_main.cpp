#include "Vadder4.h"
#include "verilated.h"

#include <cstdint>
#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    VerilatedContext context;
    context.commandArgs(argc, argv);
    Vadder4 dut{&context};

    // 带这个参数运行时，故意破坏第 4 个用例的 sum 期望值。
    const bool inject_error =
        argc == 2 && std::string(argv[1]) == "--inject-error";

    unsigned cases = 0;
    unsigned checks = 0;
    unsigned errors = 0;

    auto check_equal = [&](unsigned case_id,
                           const char *cycle,
                           const char *signal,
                           std::uint32_t expected,
                           std::uint32_t actual)
    {
        // TODO 1：
        // 每次调用都将 checks 加 1。
        // expected != actual 时：
        //   errors 加 1；
        //   使用 std::cerr 输出一行失败报告，包含：
        //   case、cycle、signal、expected、actual。
        // 相等时不增加 errors，也不输出失败信息。
        // #error "TODO 1: implement check_equal"
        // My Code Start
        ++checks;
        if (expected != actual)
        {
            ++errors;
            std::cout << "FAIL "
                      << "case = " << case_id
                      << " cycle = N/A "
                      << "signal = " << signal
                      << " expected = " << expected
                      << " actual = " << actual
                      << std::endl;
        }
        // My Code End
    };

    auto run_case = [&](std::uint32_t a,
                        std::uint32_t b,
                        std::uint32_t expected_sum,
                        std::uint32_t expected_carry)
    {
        ++cases;

        dut.a = a & 0xFu;
        dut.b = b & 0xFu;
        dut.eval();

        if (inject_error && cases == 4)
        {
            expected_sum ^= 1u;
        }

        // TODO 2：
        // 分别调用 check_equal 检查 sum 和 carry。
        // case_id 使用 cases，cycle 使用 "N/A"；
        // signal 分别使用 "sum"、"carry"。
        // 期望值来自参数，实际值来自 DUT。
        // 两次调用都必须执行，不要使用 && 串联。
        // #error "TODO 2: check both outputs"
        // My Code Start
        check_equal(cases, "N/A", "sum", expected_sum, dut.sum);
        check_equal(cases, "N/A", "carry", expected_carry, dut.carry);

        // My Code End
    };

    //           a    b    sum carry
    run_case(0x0, 0x0, 0x0, 0);
    run_case(0x1, 0x2, 0x3, 0);
    run_case(0xF, 0x0, 0xF, 0);
    run_case(0xF, 0x1, 0x0, 1);
    run_case(0xF, 0xF, 0xE, 1);
    run_case(0x7, 0x1, 0x8, 0);

    dut.final();

    if (cases != 6 || checks != 12)
    {
        std::cerr << "INCOMPLETE cases=" << cases
                  << " checks=" << checks
                  << " expected_cases=6 expected_checks=12\n";
        return 2;
    }

    std::cout << (errors == 0 ? "PASS" : "FAIL")
              << " cases=" << cases
              << " checks=" << checks
              << " errors=" << errors << '\n';

    // TODO 3：
    // errors 为 0 时返回 0，否则返回 1。
    // 不能因为开启了 inject_error 就直接返回 1，
    // 退出码必须取决于实际检查结果。
    // #error "TODO 3: return status based on errors"
    // My Code Start
    if (errors != 0 || cases != 6 || checks != 12)
    {
        return EXIT_FAILURE;
    }
    else
    {
        return EXIT_SUCCESS;
    }
    // My Code End
}