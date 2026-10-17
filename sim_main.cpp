//
#include "Vrv_buffer.h"
#include "verilated.h"

#include <cstdint>
#include <iostream>

class Testbench
{
private:
    VerilatedContext &context;
    Vrv_buffer dut;

    // 规格模型：一个尚未被取走的数据。
    bool full = false;
    std::uint32_t payload = 0;

    unsigned cycle = 0;
    unsigned checks = 0;
    unsigned errors = 0;
    unsigned sent = 0;
    unsigned received = 0;
    unsigned both = 0;
    unsigned stalls = 0;
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
            check_equal("low/out_data", old_data, dut.out_data);

            check_equal("pre/in_ready",
                        !full || ready, dut.in_ready);
            check_equal("pre/out_valid", full, dut.out_valid);
            if (full)
                check_equal("pre/out_data", payload, dut.out_data);
        }

        // 这些是本沿发生前的接口快照。
        const bool pre_ready = dut.in_ready != 0;
        const bool pre_valid = dut.out_valid != 0;
        const unsigned pre_data = dut.out_data;

        bool take_in = false;
        bool take_out = false;

        // TODO 1：用 rst、valid、ready 和边沿前快照，
        // 分别计算输入握手 take_in、输出握手 take_out。
        // 复位时二者必须为 false。
        // #error "TODO 1: snapshot the transfers before the edge"
        // TODO 1 My Code Start
        take_in = !rst && valid && pre_ready;
        take_out = !rst && pre_valid && ready;
        // TODO 1 My Code End

        const bool stalled = !rst && pre_valid && !ready;

        sent += take_in;
        received += take_out;
        both += take_in && take_out;
        stalls += stalled;

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

        // TODO 2：更新规格模型。
        // rst：清空 full。
        // 非复位：
        //   先处理 take_out，移除旧数据；
        //   再处理 take_in，保存 data 并置 full。
        // 两个握手可以同时成立，不能写成互斥的 else if。
        // #error "TODO 2: update the one-slot transaction model"
        // TODO 2 My Code Start
        if (rst)
        {
            full = false;
        }
        else
        {
            if (take_out)
                full = false;
            if (take_in)
            {
                payload = data;
                full = true;
            }
        }
        // TODO 2 My Code End

        context.timeInc(4);
        dut.clk = 1;
        dut.eval();

        check_equal("rise/out_valid", full, dut.out_valid);
        if (full)
            check_equal("rise/out_data", payload, dut.out_data);

        // TODO 3：若 stalled，本沿之后输出必须仍有效，
        // 且数据等于 pre_data。
        // 使用 check_equal，标签分别为
        // "stall/out_valid"、"stall/out_data"。
        // #error "TODO 3: check stability under backpressure"
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

        // 首次同步复位前，不假设上电输出。
        tick(true, false, 0, false, false);
    }

    void run()
    {
        case_name = "empty";
        tick(false, false, 99, true); // cycle 2

        case_name = "backpressure";
        tick(false, true, 17, false); // cycle 3：空缓冲接收
        tick(false, true, 34, false); // cycle 4：34 尚未接收
        tick(false, true, 34, false); // cycle 5：继续保持 34

        case_name = "replace";
        tick(false, true, 34, true);  // cycle 6：取走17，接收34
        tick(false, true, 51, true);  // cycle 7：取走34，接收51
        tick(false, false, 88, true); // cycle 8：仅取走51

        case_name = "late_ready";
        tick(false, true, 68, true);   // cycle 9：只接收，不直通
        tick(false, false, 99, false); // cycle 10：保持68
        tick(false, false, 77, true);  // cycle 11：取走68
        tick(false, false, 0, true);   // cycle 12：确认已空
    }

    int finish()
    {
        case_name = "finish";

        check_equal("end/sent", 4, sent);
        check_equal("end/received", 4, received);
        check_equal("end/both", 2, both);
        check_equal("end/stalls", 3, stalls);
        check_equal("end/pending", 0, full);
        check_equal("end/out_valid", 0, dut.out_valid);
        check_equal("end/balance", sent, received + unsigned(full));

        dut.final();

        std::cout << (errors == 0 ? "PASS" : "FAIL")
                  << " cycles=" << cycle
                  << " checks=" << checks
                  << " errors=" << errors
                  << " sent=" << sent
                  << " received=" << received
                  << " both=" << both
                  << " stalls=" << stalls
                  << " pending=" << unsigned(full)
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