#include "Vadder4.h"
#include "verilated.h"

#include <cstdint>
#include <iostream>

constexpr unsigned W = 4;
constexpr std::uint32_t MASK = (std::uint32_t{1} << W) - 1;

std::int32_t signed4(std::uint32_t bits)
{
    bits &= MASK;

    // TODO 1：按 4 位补码解释 bits。
    // 提示：先转成 int32_t，再根据第 3 位决定是否减去 16。
    // #error "TODO 1: implement signed4"
    std::int32_t val = static_cast<std::int32_t>(bits);
    if (bits & (1 << (W - 1)))
    {
        val -= 1 << W;
    }
    return val;
    // return 0; // 替换
}

int main(int argc, char **argv)
{
    VerilatedContext context;
    context.commandArgs(argc, argv);
    Vadder4 dut{&context};

    unsigned cases = 0;
    unsigned errors = 0;

    auto run_case = [&](std::uint32_t raw_a,
                        std::uint32_t raw_b,
                        std::int32_t expected_signed)
    {
        ++cases;

        // TODO 2：用 MASK 保留两个原始输入的低 4 位。
        // #error "TODO 2: mask inputs"
        const std::uint32_t a = raw_a & MASK;
        ; // 替换右侧
        const std::uint32_t b = raw_b & MASK;
        ; // 替换右侧

        // TODO 3：先扩宽再相加；从完整和提取低位与进位。
        // 期望值只根据 a、b 和接口规格计算，不读取 DUT。
        // #error "TODO 3: calculate full sum, low bits and carry"
        const std::uint64_t full = static_cast<std::uint64_t>(a) + static_cast<std::uint64_t>(b);
        ;                                                     // 替换右侧
        const std::uint32_t expected_sum = full & MASK;       // 替换右侧
        const std::uint32_t expected_carry = (full >> W) & 1; // 替换右侧

        dut.a = a;
        dut.b = b;
        dut.eval();

        const std::uint32_t actual_sum = dut.sum;
        const std::uint32_t actual_carry = dut.carry;
        const std::int32_t actual_signed = signed4(actual_sum);

        if (actual_sum != expected_sum ||
            actual_carry != expected_carry ||
            actual_signed != expected_signed)
        {
            ++errors;
            std::cerr
                << "FAIL case=" << cases << " cycle=N/A"
                << " raw_a=" << raw_a << " raw_b=" << raw_b
                << " a=" << a << " b=" << b
                << " full=" << full
                << " sum(expected/actual)="
                << expected_sum << '/' << actual_sum
                << " carry(expected/actual)="
                << expected_carry << '/' << actual_carry
                << " signed(expected/actual)="
                << expected_signed << '/' << actual_signed << '\n';
        }
    };

    // 第三个参数：低 4 位结果按补码解释后的手算值。
    run_case(0x0, 0x0, 0);
    run_case(0x1, 0x2, 3);
    run_case(0xF, 0x0, -1);
    run_case(0xF, 0x1, 0);
    run_case(0xF, 0xF, -2);
    run_case(0x7, 0x1, -8);
    run_case(0x8, 0x8, 0);
    run_case(0x1F, 0x11, 0);

    dut.final();

    if (cases != 8)
    {
        std::cerr << "INCOMPLETE expected_cases=8 actual_cases="
                  << cases << '\n';
        return 2;
    }

    if (errors != 0)
    {
        std::cerr << "FAIL cases=" << cases
                  << " errors=" << errors << '\n';
        return 1;
    }

    std::cout << "PASS cases=" << cases << " errors=0\n";
    return 0;
}