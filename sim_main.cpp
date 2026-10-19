//
//
#include "Vfifo4.h"
#include "verilated.h"

#include <cstdint>
#include <deque>
#include <iostream>

class Testbench
{
private:
    VerilatedContext &context;
    Vfifo4 dut;

    std::deque<std::uint32_t> expected;

    unsigned cycle = 0;
    unsigned checks = 0;
    unsigned errors = 0;
    unsigned sent = 0;
    unsigned received = 0;
    unsigned both = 0;
    unsigned blocked = 0;
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

    // 只使用参考队列预测接口，不读取 DUT 内部状态。
    void check_state(const char *ready_item,
                     const char *valid_item,
                     const char *level_item,
                     const char *data_item)
    {
        check_equal(ready_item, expected.size() < 4, dut.in_ready);
        check_equal(valid_item, !expected.empty(), dut.out_valid);
        check_equal(level_item, expected.size(), dut.level);

        if (!expected.empty())
            check_equal(data_item, expected.front(), dut.out_data);
    }

    // 进入、退出时 clk=0；每拍 10 ns。
    void tick(bool rst, bool valid, std::uint32_t data,
              bool ready, bool check_before = true)
    {
        ++cycle;
        data &= 0xffu;

        const unsigned old_valid = dut.out_valid;
        const unsigned old_data = dut.out_data;

        context.timeInc(1);
        dut.rst = rst;
        dut.in_valid = valid;
        dut.in_data = data;
        dut.out_ready = ready;
        dut.eval();

        if (check_before)
        {
            check_equal("low/out_valid", old_valid, dut.out_valid);
            if (old_valid)
                check_equal("low/out_data", old_data, dut.out_data);

            check_state("pre/in_ready", "pre/out_valid",
                        "pre/level", "pre/out_data");
        }

        const bool pre_ready = dut.in_ready != 0;
        const bool pre_valid = dut.out_valid != 0;
        const unsigned pre_data = dut.out_data;

        bool take_in = false;
        bool take_out = false;

        // TODO 1：
        // 使用沿前快照计算 take_in、take_out。
        // rst 为 true 时，两者必须为 false。
        // #error "TODO 1: calculate transfers before the edge"
        // TODO 1 My Code Start
        if (!rst)
        {
            take_in = valid && pre_ready;
            take_out = pre_valid && ready;
        }
        // TODO 1 My Code End

        const bool stalled = !rst && pre_valid && !ready;

        sent += take_in;
        received += take_out;
        both += take_in && take_out;
        blocked += !rst && valid && !pre_ready;

        if (take_out)
        {
            std::cout << "RX case=" << case_name
                      << " cycle=" << cycle
                      << " data=" << pre_data << '\n';
        }
        if (take_in)
        {
            std::cout << "TX case=" << case_name
                      << " cycle=" << cycle
                      << " data=" << data << '\n';
        }

        // TODO 2：更新参考队列。
        //
        // rst：清空 expected。
        // 非复位：
        //   ① take_out 时：
        //      若队列为空，报告：
        //        check_equal("rx/available", 1, 0);
        //      否则：
        //        用 check_equal("rx/data", ...) 比较
        //        队首期望值与 pre_data，然后移除队首。
        //   ② take_in 时：把 data 加到队尾。
        //
        // 输出与输入使用独立 if，先输出、后输入。
        // 禁止对空队列调用 front() 或 pop_front()。
        // #error "TODO 2: update the transaction queue"
        // TODO 2 My Code Start
        if (rst)
        {
            expected.clear();
        }
        else
        {
            if (take_out)
            {
                if (expected.empty())
                    check_equal("rx/available", 1, 0);
                else
                {
                    check_equal("rx/data", expected.front(), pre_data);
                    expected.pop_front();
                }
            }
            if (take_in)
                expected.push_back(data);
        }
        // TODO 2 My Code End

        context.timeInc(4);
        dut.clk = 1;
        dut.eval();

        check_state("rise/in_ready", "rise/out_valid",
                    "rise/level", "rise/out_data");

        // TODO 3：
        // stalled 时，沿后 out_valid 必须为 1，
        // out_data 必须仍等于 pre_data。
        // 标签："stall/out_valid"、"stall/out_data"。
        // #error "TODO 3: check stalled output stability"
        // TODO 3 My Code Start
        if (stalled)
        {
            check_equal("stall/out_valid", 1, dut.out_valid);
            check_equal("stall/out_data", pre_data, dut.out_data);
        }
        // TODO 3 My Code End

        const unsigned rise_valid = dut.out_valid;
        const unsigned rise_data = dut.out_data;

        context.timeInc(5);
        dut.clk = 0;
        dut.eval();

        check_equal("fall/out_valid", rise_valid, dut.out_valid);
        if (rise_valid)
            check_equal("fall/out_data", rise_data, dut.out_data);
    }

public:
    explicit Testbench(VerilatedContext &ctx)
        : context(ctx), dut(&ctx)
    {
        dut.clk = 0;
        dut.rst = 1;
        dut.in_valid = 0;
        dut.in_data = 0;
        dut.out_ready = 0;
        dut.eval();

        // 首个同步复位沿前，不假设上电输出。
        tick(true, false, 0, false, false);
    }

    // 调用前，FIFO 必须为空。
    // 下游不接收，连续发送四笔：first + 17*i。
    void fill4(unsigned first)
    {
        // TODO 4：
        // 用循环驱动四拍。
        // 每拍：rst=false，valid=true，ready=false。
        // 数据依次为 first、first+17、first+34、first+51。
        // #error "TODO 4: fill an empty FIFO"
        // TODO 4 My Code Start
        for (unsigned i = 0; i < 4; ++i)
        {
            tick(false, true, first + 17 * i, false);
        }
        // TODO 4 My Code Start

        check_equal("fill/pending", 4, expected.size());
    }

    // 停止发送，并在最多8拍内排空。
    // 不得直接修改 expected。
    void drain_all()
    {
        const std::uint64_t want = expected.size();
        const unsigned before = received;

        for (unsigned waited = 0;
             !expected.empty() && waited < 8;
             ++waited)
        {
            // TODO 6：
            // 推进一拍：不复位、不发送，下游 ready。
            // 握手和参考队列更新全部交给 tick()。
            // #error "TODO 6: drain with a finite bound"
            // TODO 6 My Code Start
            tick(false, false, 0, true);
            // TODO 6 My Code Start
        }

        check_equal("drain/pending", 0, expected.size());
        check_equal("drain/received", want, received - before);
    }

    void run()
    {
        case_name = "empty";
        tick(false, false, 0, true); // cycle 2

        case_name = "fill_first";
        fill4(17); // cycles 3～6

        case_name = "full_block";
        tick(false, true, 85, false); // cycle 7
        tick(false, true, 85, false); // cycle 8
        check_equal("full/pending", 4, expected.size());

        case_name = "full_release";
        tick(false, true, 85, true); // cycle 9：只输出17
        check_equal("release/pending", 3, expected.size());

        case_name = "accept_held";
        tick(false, true, 85, false); // cycle 10：接收85
        check_equal("accepted/pending", 4, expected.size());

        case_name = "partial_refill";

        // TODO 5：依次完成以下四拍。
        //
        // cycle 11、12：
        //   不发送，下游 ready，取走34、51。
        //   两拍后增加检查：
        //     check_equal("partial/pending", 2, expected.size());
        //
        // cycle 13、14：
        //   下游不 ready，依次发送102、119。
        //
        // 四拍均不复位；使用已有 tick()。
        // #error "TODO 5: partially drain and refill"
        // TODO 5 My Code Start
        tick(false, false, 0, true); // cycle 11：取走34
        tick(false, false, 0, true); // cycle 12：取走51
        check_equal("partial/pending", 2, expected.size());
        tick(false, true, 102, false); // cycle 13：发送102
        tick(false, true, 119, false); // cycle 14：发送119
        // TODO 5 My Code Start

        check_equal("refill/pending", 4, expected.size());

        case_name = "hold";
        tick(false, false, 0, false); // cycle 15

        case_name = "drain_first";
        drain_all(); // 正常为 cycles 16～19

        case_name = "empty_again";
        tick(false, false, 0, true); // cycle 20

        case_name = "fill_second";
        fill4(136); // cycles 21～24

        case_name = "drain_second";
        drain_all(); // 正常为 cycles 25～28

        case_name = "end_empty";
        tick(false, false, 0, true); // cycle 29
    }

    int finish()
    {
        case_name = "finish";

        check_equal("end/sent", 11, sent);
        check_equal("end/received", 11, received);
        check_equal("end/both", 0, both);
        check_equal("end/blocked", 3, blocked);
        check_equal("end/pending", 0, expected.size());
        check_equal("end/out_valid", 0, dut.out_valid);
        check_equal("end/balance",
                    sent, received + expected.size());

        dut.final();

        std::cout << (errors == 0 ? "PASS" : "FAIL")
                  << " cycles=" << cycle
                  << " checks=" << checks
                  << " errors=" << errors
                  << " sent=" << sent
                  << " received=" << received
                  << " both=" << both
                  << " blocked=" << blocked
                  << " pending=" << expected.size()
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