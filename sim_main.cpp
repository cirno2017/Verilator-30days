//
#include "Vpipe2.h"
#include "verilated.h"

#include <cstdint>
#include <deque>
#include <iostream>

struct Slot
{
    bool valid;
    std::uint32_t data;
};

// 独立参考计算：来自接口的模 256 规格。
static std::uint32_t model_data(std::uint32_t x)
{
    return (x + 1u) % 256u;
}

class Testbench
{
private:
    VerilatedContext &context;
    Vpipe2 dut;

    // 第 n 沿输入，第 n+1 沿输出：
    // 初始放一个无效位置。
    std::deque<Slot> expected{Slot{false, 0}};

    unsigned cycle = 0;
    unsigned checks = 0;
    unsigned errors = 0;
    unsigned sent = 0;
    unsigned received = 0;
    const char *case_name = "init";

    void check_equal(const char *item,
                     std::uint64_t want,
                     std::uint64_t actual)
    {
        ++checks;
        if (want == actual)
            return;

        ++errors;
        std::cerr << "FAIL case=" << case_name
                  << " cycle=" << cycle
                  << " time_ns=" << context.time()
                  << " item=" << item
                  << " expected=" << want
                  << " actual=" << actual << '\n';
    }

    // 进入、退出时 clk=0；每拍推进 10 ns。
    void tick(bool rst, bool valid, std::uint32_t data,
              bool check_before = true)
    {
        ++cycle;
        const unsigned old_valid = dut.out_valid;
        const unsigned old_data = dut.out_data;

        context.timeInc(1);
        dut.rst = rst;
        dut.in_valid = valid;
        dut.in_data = data & 0xffu;
        dut.eval();

        if (check_before)
        {
            check_equal("low/out_valid", old_valid, dut.out_valid);
            check_equal("low/out_data", old_data, dut.out_data);
        }

        // 在边沿前，根据本拍输入预测边沿后的输出。
        Slot due{false, 0};

        if (rst)
        {
            expected.assign(1, Slot{false, 0});
        }
        else
        {
            if (valid)
                ++sent;

            // TODO 1：
            // 1. 构造本拍 Slot：valid 来自输入。
            //    有效时用 model_data(data) 计算数据；
            //    无效时 data 字段可以填 0。
            // 2. 无论 valid 是什么，都把这个位置加入队尾。
            // 3. 把队首复制给 due，再删除队首。
            // 不得从 DUT 输出生成期望值。
            // #error "TODO 1: advance the expected time slots"
            // TODO 1 My Code Start
            Slot cur{valid, valid ? model_data(data) : 0u};
            expected.push_back(cur);
            due = expected.front();
            expected.pop_front();
            // TODO 1 My Code End
        }

        context.timeInc(4);
        dut.clk = 1;
        dut.eval();

        // TODO 2：
        // 每拍检查 out_valid 与 due.valid 相等。
        // 仅当 due.valid 为真时，检查 out_data 与 due.data 相等。
        // 使用 check_equal：
        //   "rise/out_valid"
        //   "rise/out_data"
        // 是否检查数据，必须由期望 valid 决定。
        // #error "TODO 2: check validity and valid output data"
        // TODO 2 My Code Start
        check_equal("rise/out_valid", due.valid ? 1u : 0u, dut.out_valid);
        if (due.valid)
        {
            check_equal("rise/out_data", due.data, dut.out_data);
        }
        // TODO 2 My Code End

        if (dut.out_valid)
            ++received;

        if (due.valid)
        {
            std::cout << "OUT case=" << case_name
                      << " cycle=" << cycle
                      << " expected=" << due.data
                      << " actual=" << unsigned(dut.out_data)
                      << '\n';
        }

        const unsigned rise_valid = dut.out_valid;
        const unsigned rise_data = dut.out_data;

        context.timeInc(5);
        dut.clk = 0;
        dut.eval();

        check_equal("fall/out_valid", rise_valid, dut.out_valid);
        check_equal("fall/out_data", rise_data, dut.out_data);
    }

    void drain()
    {
        tick(false, false, 0);
        tick(false, false, 0);
    }

public:
    explicit Testbench(VerilatedContext &ctx)
        : context(ctx), dut(&ctx)
    {
        dut.clk = 0;
        dut.rst = 1;
        dut.in_valid = 0;
        dut.in_data = 0;
        dut.eval();

        // 第一次同步复位前，不假设上电输出。
        tick(true, false, 0, false);
    }

    void run()
    {
        case_name = "single";
        tick(false, true, 37);
        drain();

        case_name = "continuous";
        for (unsigned x : {0u, 1u, 254u, 255u})
            tick(false, true, x);
        drain();

        case_name = "bubbles";
        tick(false, true, 42);
        tick(false, false, 99);
        tick(false, true, 7);
        tick(false, false, 123);
        tick(false, false, 55);
        tick(false, true, 128);
        drain();
    }

    int finish()
    {
        case_name = "finish";

        unsigned pending = 0;
        for (const auto &slot : expected)
            pending += slot.valid ? 1u : 0u;

        check_equal("end/sent", 8, sent);
        check_equal("end/received", 8, received);
        check_equal("end/pending", 0, pending);
        check_equal("end/out_valid", 0, dut.out_valid);

        dut.final();

        std::cout << (errors == 0 ? "PASS" : "FAIL")
                  << " cycles=" << cycle
                  << " checks=" << checks
                  << " errors=" << errors
                  << " sent=" << sent
                  << " received=" << received
                  << " pending=" << pending
                  << " time_ns=" << context.time() << '\n';

        return errors == 0 ? 0 : 1;
    }
};

int main(int argc, char **argv)
{
    VerilatedContext context;
    context.commandArgs(argc, argv);

    Testbench tb{context};
    tb.run();
    return tb.finish();
}