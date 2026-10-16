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

// 来自接口规格，不读取 DUT 内部状态。
static std::uint32_t model_data(std::uint32_t x)
{
    return (x + 1u) % 256u;
}

class Testbench
{
private:
    VerilatedContext &context;
    Vpipe2 dut;
    std::deque<Slot> expected{Slot{false, 0}};

    unsigned cycle = 0;
    unsigned checks = 0;
    unsigned errors = 0;
    unsigned sent = 0;
    unsigned received = 0;
    unsigned dropped = 0;
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
        data &= 0xffu;

        const unsigned old_valid = dut.out_valid;
        const unsigned old_data = dut.out_data;

        context.timeInc(1);
        dut.rst = rst;
        dut.in_valid = valid;
        dut.in_data = data;
        dut.eval();

        if (check_before)
        {
            check_equal("low/out_valid", old_valid, dut.out_valid);
            check_equal("low/out_data", old_data, dut.out_data);
        }

        Slot due{false, 0};
        unsigned flushed = 0;

        // 在上升沿前，根据规格预测本沿结果。
        if (rst)
        {
            // TODO 1：复位参考模型。
            // 1. 遍历 expected，把有效位置数累加到 flushed。
            // 2. dropped 增加 flushed。
            // 3. expected 恢复为一个无效位置。
            // 不增加 sent；due 保持无效。
            // #error "TODO 1: account for and flush pending transactions"
            // TODO 1 My Code Start
            for (const auto &slot : expected)
                flushed += slot.valid ? 1u : 0u;
            dropped += flushed;
            expected.assign(1, Slot{false, 0});
            // TODO 1 My Code End
        }
        else
        {
            if (valid)
                ++sent;

            // TODO 2：推进一个时间位置。
            // 1. 无论 valid 是什么，都向队尾加入 Slot。
            //    有效数据使用 model_data(data)，无效数据填 0。
            // 2. 复制队首到 due，再删除队首。
            // #error "TODO 2: advance the expected time slots"
            // TODO 2 My Code Start
            expected.push_back(Slot{valid, valid ? model_data(data) : 0u});
            due = expected.front();
            expected.pop_front();
            // TODO 2 My Code End
        }

        context.timeInc(4);
        dut.clk = 1;
        dut.eval();

        // TODO 3：逐拍检查。
        // 每拍检查 "rise/out_valid"。
        // 仅由 due.valid 决定是否检查 "rise/out_data"。
        // 使用 check_equal；不得修改 due 或 DUT 输出。
        // #error "TODO 3: compare expected validity and data"
        // TODO 3 My Code Start
        check_equal("rise/out_valid", due.valid ? 1u : 0u, dut.out_valid);
        if (due.valid)
            check_equal("rise/out_data", due.data, dut.out_data);
        // TODO 3 My Code End

        if (dut.out_valid)
            ++received;

        if (flushed != 0)
        {
            std::cout << "FLUSH case=" << case_name
                      << " cycle=" << cycle
                      << " dropped=" << flushed << '\n';
        }

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
        case_name = "continuous";
        tick(false, true, 10);
        tick(false, true, 20);
        tick(false, true, 255);
        drain();

        case_name = "bubbles";
        tick(false, true, 42);
        tick(false, false, 99);
        tick(false, true, 7);
        tick(false, false, 123);
        tick(false, false, 55);

        case_name = "mid_reset";
        tick(false, true, 100);
        tick(false, true, 101);

        // 有待输出事务时复位；复位期间的输入被忽略。
        tick(true, true, 222);
        tick(true, true, 223);

        // 先给一个气泡，观察是否有旧事务重新出现。
        tick(false, false, 77);

        tick(false, true, 200);
        tick(false, true, 201);
        drain();
    }

    int finish()
    {
        case_name = "finish";

        unsigned pending = 0;
        for (const auto &slot : expected)
            pending += slot.valid ? 1u : 0u;

        check_equal("end/sent", 9, sent);
        check_equal("end/received", 8, received);
        check_equal("end/dropped", 1, dropped);
        check_equal("end/pending", 0, pending);
        check_equal("end/out_valid", 0, dut.out_valid);
        check_equal("end/balance",
                    sent, received + dropped + pending);

        dut.final();

        std::cout << (errors == 0 ? "PASS" : "FAIL")
                  << " cycles=" << cycle
                  << " checks=" << checks
                  << " errors=" << errors
                  << " sent=" << sent
                  << " received=" << received
                  << " dropped=" << dropped
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