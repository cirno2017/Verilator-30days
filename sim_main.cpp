//
#include "Vadder4.h"
#include "verilated.h"

#include <charconv>
#include <cstdint>
#include <iostream>
#include <random>
#include <string_view>
#include <system_error>

struct Expected
{
    std::uint32_t sum;
    std::uint32_t carry;
};

Expected reference_add(std::uint32_t a, std::uint32_t b)
{
    const std::uint64_t total = static_cast<std::uint64_t>(a) + b;
    return {
        static_cast<std::uint32_t>(total % 16u),
        static_cast<std::uint32_t>(total / 16u)};
}

int main(int argc, char **argv)
{
    // 接受一个十进制 uint32_t seed，例如 ./obj_dir/Vadder4 12345
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <decimal_seed>\n";
        return 2;
    }

    std::uint32_t seed = 0;
    const std::string_view arg{argv[1]};
    const auto parsed =
        std::from_chars(arg.data(), arg.data() + arg.size(), seed);
    if (parsed.ec != std::errc{} ||
        parsed.ptr != arg.data() + arg.size())
    {
        std::cerr << "Invalid seed\n";
        return 2;
    }

    VerilatedContext context;
    context.commandArgs(argc, argv);
    Vadder4 dut{&context};

    constexpr unsigned random_cases = 200;
    constexpr unsigned expected_cases = 4 + random_cases;
    constexpr unsigned expected_checks = expected_cases * 2;
    constexpr std::uint32_t mask = 0xFu;

    unsigned cases = 0;
    unsigned checks = 0;
    unsigned errors = 0;

    std::cout << "CONFIG seed=" << seed
              << " random_cases=" << random_cases << '\n';

    // TODO 1：
    // 创建名为 rng 的 std::mt19937，用 seed 初始化。
    // 创建名为 dist 的 uint32_t 均匀整数分布，范围为 0～15。
    // 两者只在这里创建一次。
    // #error "TODO 1: create engine and distribution"
    // My TODO 1 Code Start
    std::mt19937 rng{seed};
    std::uniform_int_distribution<std::uint32_t> dist{0u, 15u};
    // My TODO 2 Code End

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
            std::cerr << "FAIL seed=" << seed
                      << " case=" << case_id
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
        // 将 a、b 分别写入 DUT，使用 mask 清除高位。
        // 调用 eval()。
        // 分别调用 check_equal 检查 sum、carry。
        // case_id=cases，cycle="N/A"，报告输入使用 a、b。
        // #error "TODO 2: drive evaluate and check"
        // My TODO 2 Code Start
        dut.a = a & mask;
        dut.b = b & mask;
        dut.eval();
        check_equal(cases, "N/A", a, b, "sum", expected.sum, dut.sum);
        check_equal(cases, "N/A", a, b, "carry", expected.carry, dut.carry);
        // My TODO 2 Code End
    };

    // 定向用例：不消耗 rng 的随机数。
    run_case(0, 0);
    run_case(7, 8);
    run_case(15, 1);
    run_case(15, 15);

    for (unsigned i = 0; i < random_cases; ++i)
    {
        // TODO 3：
        // 分别调用 dist(rng)，依次生成局部变量 a、b。
        // 两个变量都使用 const std::uint32_t。
        // 不在循环内重新设 seed。
        // #error "TODO 3: draw a then b"
        // My TODO 3 Code Start
        const std::uint32_t a = dist(rng);
        const std::uint32_t b = dist(rng);
        // My TODO 3 Code End

        std::cout << "INPUT random_index=" << i
                  << " case=" << cases + 1
                  << " a=" << a
                  << " b=" << b << '\n';
        run_case(a, b);
    }

    dut.final();

    if (cases != expected_cases || checks != expected_checks)
    {
        std::cerr << "INCOMPLETE seed=" << seed
                  << " cases=" << cases
                  << " checks=" << checks
                  << " expected_cases=" << expected_cases
                  << " expected_checks=" << expected_checks << '\n';
        return 2;
    }

    std::cout << (errors == 0 ? "PASS" : "FAIL")
              << " seed=" << seed
              << " cases=" << cases
              << " checks=" << checks
              << " errors=" << errors << '\n';

    return errors == 0 ? 0 : 1;
}