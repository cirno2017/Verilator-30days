//
#include "Vfifo4.h"
#include "verilated.h"
#include "verilated_cov.h"

#include <cstdint>
#include <deque>
#include <iostream>
#include <cstdint>
#include <cstdio>
#include <random>

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

        if (!rst)
        {
            sample_coverage(
                static_cast<unsigned>(expected.size()),
                take_in,
                take_out);
        }

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

    struct Coverage
    {
        unsigned empty = 0;
        unsigned full = 0;
        unsigned both = 0;
        unsigned blocked = 0;
        unsigned stall = 0;
        unsigned write_wrap = 0;
        unsigned read_wrap = 0;
    };

    Coverage cov{};

    void sample_coverage(unsigned pre_size, bool push, bool pop)
    {
        // 示例：按沿前参考模型状态统计空周期。
        if (pre_size == 0)
            ++cov.empty;

        // TODO13：
        // 按覆盖清单补齐 full、both、blocked、stall。
        // blocked/stall 使用本次沿前的 DUT 端口值。
        // #error "TODO13: count pre-edge scenarios"
        // TODO 13 My Code Start
        if (pre_size == 4)
            ++cov.full;
        if (push && pop)
            ++cov.both;
        if (dut.in_valid && !dut.in_ready)
            ++cov.blocked;
        if (dut.out_valid && !dut.out_ready)
            ++cov.stall;
        // TODO 13 My Code End

        // TODO14：
        // push 成立且 (sent + 1) 为4的倍数：write_wrap加1。
        // pop  成立且 (received + 1) 为4的倍数：read_wrap加1。
        // 此处 sent/received 必须仍是本沿更新前的计数。
        // #error "TODO14: count expected wrap opportunities"
        // TODO 14 My Code Start
        if (push && (sent + 1) % 4 == 0)
            ++cov.write_wrap;
        if (pop && (received + 1) % 4 == 0)
            ++cov.read_wrap;
        // TODO 14 My Code End
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

    void coverage_row(const char *name, unsigned hits, bool enforce)
    {
        std::printf("COVER item=%s hits=%u status=%s\n",
                    name, hits, hits ? "HIT" : "MISS");

        if (enforce)
        {
            // TODO15：
            // 使用已有 check_equal() 检查 hits != 0。
            // 期望值为1，实际值为布尔表达式 hits != 0。
            // item 使用 name，错误仍进入原来的 errors。
            // #error "TODO15: make missing coverage fail the test"
            // TODO 15 My Code Start
            check_equal(name, 1, hits != 0);
            // TODO 15 My Code End
        }
    }

    void report_coverage(bool enforce)
    {
        coverage_row("cover/empty", cov.empty, enforce);
        coverage_row("cover/full", cov.full, enforce);
        coverage_row("cover/both", cov.both, enforce);
        coverage_row("cover/blocked", cov.blocked, enforce);
        coverage_row("cover/stall", cov.stall, enforce);
        coverage_row("cover/write_wrap", cov.write_wrap, enforce);
        coverage_row("cover/read_wrap", cov.read_wrap, enforce);
    }

    void clear_code_coverage()
    {
        // TODO16：
        // 清零当前 DUT 所属 context 的代码覆盖计数。
        // 不复位 DUT，不清空 expected，不修改 sent/received/errors。
        // #error "TODO16: clear code coverage counters"
        // TODO 16 My Code Start
        VerilatedCov::zero();
        // TODO 16 My Code End
    }

    void save_code_coverage(const char *path)
    {
        // TODO17：
        // 将当前 context 的代码覆盖计数写到 path。
        // #error "TODO17: write code coverage snapshot"
        // TODO 17 My Code Start
        VerilatedCov::write(path);
        // TODO 17 My Code End

        std::printf("CODE_COVER file=%s\n", path);
    }

    void run()
    {
        // 先完成 Day27 的全部测试与强制功能覆盖检查。
        run_day27();

        case_name = "codecov_start";
        check_equal("codecov/start_empty", 0, expected.size());

        // 新建独立统计窗口；硬件与事务计数继续运行。
        cov = Coverage{};
        clear_code_coverage();

        case_name = "codecov_fill";
        tick(false, true, 0xD1, false);
        tick(false, true, 0xD2, false);
        tick(false, true, 0xD3, false);
        tick(false, true, 0xD4, false);

        check_equal("codecov/filled", 4, expected.size());

        std::puts("COVERAGE phase=code_fill");
        report_coverage(false);
        save_code_coverage("logs/day28_before.dat");

        case_name = "codecov_patch";

        // TODO18：补三次 tick，沿用昨天已经理解的握手规则。
        // 1. 满时提出 0xD5，下游不就绪：无传输。
        // 2. 保持 0xD5，下游就绪：只输出，输入仍受阻。
        // 3. 继续保持 0xD5，下游就绪：同时输出和接收。
        // #error "TODO18: add three directed cycles"
        // TODO 18 My Code Start
        tick(false, true, 0xD5, false); // 满时提出0xD5，无传输
        tick(false, true, 0xD5, true);  // 满时只输出，0xD5仍受阻
        tick(false, true, 0xD5, true);  // 同时输出和接收0xD5
        // TODO 18 My Code End

        case_name = "codecov_drain";
        drain_all(); // 继续使用已有八拍上限

        case_name = "codecov_end";
        tick(false, false, 0, true);

        check_equal("codecov/pending", 0, expected.size());
        check_equal("codecov/balance", sent, received);

        std::puts("COVERAGE phase=code_patched");
        report_coverage(true);
        save_code_coverage("logs/day28_after.dat");
    }

    void run_day27()
    {
        // 完整保留昨天的定向与固定seed随机测试。
        run_day26();

        case_name = "coverage_all";
        std::puts("COVERAGE phase=day26");
        report_coverage(false);

        check_equal("coverage/start_empty", 0, expected.size());

        // 开始一个单独统计的覆盖阶段。
        // 只清零覆盖计数，不复位硬件，不清空参考队列，
        // 不改变 sent/received。
        cov = Coverage{};

        case_name = "coverage_fill";

        tick(false, true, 0xE1, false);
        tick(false, true, 0xE2, false);
        tick(false, true, 0xE3, false);
        tick(false, true, 0xE4, false);

        check_equal("coverage/filled", 4, expected.size());

        std::puts("COVERAGE phase=fill_only");
        report_coverage(false);

        case_name = "coverage_patch";

        // FIFO已满，提出E5并等待。
        tick(false, true, 0xE5, false);

        // 满时释放下游：本沿只输出，E5仍需保持。
        tick(false, true, 0xE5, true);

        // 此时已有空间：同时输出和接收E5。
        tick(false, true, 0xE5, true);

        case_name = "coverage_drain";
        drain_all(); // 保留原来的八拍上限

        case_name = "coverage_end";
        tick(false, false, 0, true);

        check_equal("coverage/pending", 0, expected.size());
        check_equal("coverage/balance", sent, received);

        std::puts("COVERAGE phase=patched");
        report_coverage(true);
    }

    void run_day26()
    {
        constexpr uint32_t seed = 0x26C0FFEEu;
        constexpr unsigned random_cycles = 200;

        std::printf("CONFIG seed=%u random_cycles=%u\n",
                    static_cast<unsigned>(seed), random_cycles);

        // 保留昨天的定向测试；不在两个阶段之间复位。
        run_directed();

        check_equal("directed/sent", 8, sent);
        check_equal("directed/received", 8, received);
        check_equal("directed/both", 4, both);
        check_equal("directed/blocked", 3, blocked);
        check_equal("directed/pending", 0, expected.size());

        std::mt19937 rng(seed);
        bool holding = false;
        uint8_t held_data = 0;
        unsigned generated = 0;
        const auto sent_before_random = sent;

        case_name = "random";

        for (unsigned step = 0; step < random_cycles; ++step)
        {
            // 每拍固定取三个随机数，便于追踪随机序列。
            const bool offer = (rng() & 3u) != 0;
            const bool ready = (rng() & 1u) != 0;
            const auto candidate =
                static_cast<uint8_t>(rng() & 0xffu);

            // TODO10：
            // 仅当“没有等待中的事务”且offer为真时，
            // 把candidate保存到held_data，置holding，
            // 并将generated增加1。
            // 已有事务等待时，不覆盖held_data。
            // #error "TODO10: create a new offer only when idle"

            // 无效周期的数据统一置0，方便阅读日志。
            // TODO 10 My Code Start
            if (!holding && offer)
            {
                held_data = candidate;
                holding = true;
                ++generated;
            }
            // TODO 10 My Code End
            const uint8_t drive_data = holding ? held_data : 0;

            std::printf("DRIVE step=%u valid=%u data=%u ready=%u\n",
                        step,
                        static_cast<unsigned>(holding),
                        static_cast<unsigned>(drive_data),
                        static_cast<unsigned>(ready));

            const auto before = sent;

            // TODO11：
            // 调用tick()：不复位，以holding作为输入valid，
            // drive_data作为输入数据，ready作为下游ready。
            // 随后仅在本拍确实输入握手时清除holding。
            // 用sent与before比较，不读取沿后的in_ready。
            // #error "TODO11: drive one cycle and retire an accepted offer"
            // TODO 11 My Code Start
            tick(false, holding, drive_data, ready);
            if (sent != before)
                holding = false;
            // TODO 11 My Code End
        }

        case_name = "source_flush";

        // 停止生成新数据，但必须交付已提出的最后一笔。
        for (unsigned waited = 0;
             holding && waited < 8;
             ++waited)
        {

            std::printf("FLUSH step=%u data=%u\n",
                        waited, static_cast<unsigned>(held_data));

            const auto before = sent;

            // TODO12：
            // 不复位；继续有效地发送held_data；
            // 下游始终ready。
            // 本拍输入握手成功后清除holding。
            // 不产生新数据，不增加generated。
            // #error "TODO12: finish the outstanding input with a bound"
            // TODO 12 My Code Start
            tick(false, true, held_data, true);
            if (sent != before)
                holding = false;
            // TODO 12 My Code End
        }

        check_equal("source/holding", 0, holding);
        check_equal("source/generated_nonzero", 1, generated != 0);
        check_equal("source/accepted",
                    sent_before_random + generated, sent);

        case_name = "drain";
        drain_all();

        case_name = "end_empty";
        tick(false, false, 0, true);

        check_equal("random/pending", 0, expected.size());
        check_equal("random/all_received", sent, received);

        std::printf("RANDOM seed=%u generated=%u holding=%u\n",
                    static_cast<unsigned>(seed),
                    generated,
                    static_cast<unsigned>(holding));
    }

    void run_directed()
    {
        /*
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
        */
        case_name = "empty_accept";
        tick(false, true, 17, true); // cycle 2
        check_equal("empty/received", 0, received);
        check_equal("empty/pending", 1, expected.size());

        case_name = "seed";
        tick(false, true, 34, false); // cycle 3

        case_name = "both_steady";

        // TODO 7：
        // cycle 4：发送51，下游ready。
        // cycle 5：发送68，下游ready。
        // 两拍均不复位；使用tick()。
        //
        // 完成后应：
        //   输出过17、34；
        //   参考队列为[51,68]。
        // #error "TODO 7: two consecutive simultaneous transfers"
        // TODO 7 My Code Start
        tick(false, true, 51, true); // cycle 4：收17、发51
        tick(false, true, 68, true); // cycle 5：收34、发68
        // TODO 7 My Code End

        check_equal("both/pending", 2, expected.size());
        check_equal("both/count", 2, both);

        case_name = "backpressure";

        // TODO 8：
        // cycle 6：发送85，下游不ready。
        // cycle 7：发送102，下游不ready。
        //   此时队列应满：[51,68,85,102]。
        //   加入pending=4的检查。
        //
        // cycle 8、9：持续发送119，下游不ready。
        // cycle 10：继续发送119，下游ready。
        //   本沿只输出51，119仍未被接收。
        //   加入pending=3、sent=6的检查。
        //
        // cycle 11：继续发送119，下游ready。
        //   本沿输出68，同时接收119。
        //
        // 六拍均不复位；不要自行修改参考队列。
        // #error "TODO 8: stall, fill, block, and resume"
        // TODO 8 My Code Start
        tick(false, true, 85, false);  // cycle 6：背压下写入85
        tick(false, true, 102, false); // cycle 7：写满[51,68,85,102]
        check_equal("fill/pending", 4, expected.size());
        tick(false, true, 119, false); // cycle 8：满，119被阻塞
        tick(false, true, 119, false); // cycle 9：满，119仍被阻塞
        tick(false, true, 119, true);  // cycle 10：只输出51，仍不接收119
        check_equal("release/pending", 3, expected.size());
        check_equal("release/sent", 6, sent);
        tick(false, true, 119, true); // cycle 11：输出68，同时接收119
        // TODO 8 My Code End

        check_equal("resume/pending", 3, expected.size());
        check_equal("resume/both", 3, both);
        check_equal("resume/blocked", 3, blocked);

        case_name = "stream_tail";

        // TODO 9：
        // cycle 12：发送136，下游ready。
        // cycle 13：不发送，下游ready。
        // cycle 14：不发送，下游不ready。
        //
        // 三拍均不复位。
        // 此时参考队列应为[119,136]。
        // #error "TODO 9: finish the stream and stall again"
        // TODO 9 My Code Start
        tick(false, true, 136, true); // cycle 12：输出85，同时接收136
        tick(false, false, 0, true);  // cycle 13：输出102
        tick(false, false, 0, false); // cycle 14：再次背压，119保持有效稳定
        // TODO 9 My Code End

        check_equal("tail/pending", 2, expected.size());
        check_equal("tail/both", 4, both);

        case_name = "drain";
        drain_all(); // 正常为cycles 15、16

        case_name = "end_empty";
        tick(false, false, 0, true); // 正常为cycle 17
        tick(false, false, 0, true); // 新增的代码，原本没有，cycle 18：空FIFO保持稳定
    }

    int finish()
    {
        case_name = "finish";
        /*
        check_equal("end/sent", 8, sent);
        check_equal("end/received", 8, received);
        check_equal("end/both", 4, both);
        check_equal("end/blocked", 3, blocked);
        */
        check_equal("end/received", sent, received); // 新增检查
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