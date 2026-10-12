//
#include "Vdelayed_done.h"
#include "verilated.h"

#include <cstdint>
#include <iostream>
#include <string>

class Testbench
{
private:
    VerilatedContext &context;
    Vdelayed_done dut;

    unsigned cycle = 0;
    unsigned completed = 0;
    unsigned checks = 0;
    unsigned errors = 0;
    unsigned case_id = 0;
    const char *case_name = "init";
    bool stall_mode = false;

    void check_equal(const char *item,
                     std::uint64_t want, std::uint64_t actual)
    {
        ++checks;
        if (want != actual)
        {
            ++errors;
            std::cerr << "FAIL case=" << case_id
                      << " name=" << case_name
                      << " cycle=" << cycle
                      << " time_ns=" << context.time()
                      << " item=" << item
                      << " expected=" << want
                      << " actual=" << actual << '\n';
        }
    }

    // 进入和退出时 clk=0；每次推进 10 ns。
    void tick(bool rst, bool start, bool check_before = true)
    {
        const unsigned old_done = dut.done;
        const unsigned old_busy = dut.busy;

        context.timeInc(1);
        dut.rst = rst;
        dut.start = start;
        dut.stall = stall_mode;
        dut.eval();

        if (check_before)
        {
            check_equal("low/done", old_done, dut.done);
            check_equal("low/busy", old_busy, dut.busy);
        }

        context.timeInc(4);
        dut.clk = 1;
        dut.eval();
        ++cycle;

        const unsigned new_done = dut.done;
        const unsigned new_busy = dut.busy;

        context.timeInc(5);
        dut.clk = 0;
        dut.eval();
        check_equal("fall/done", new_done, dut.done);
        check_equal("fall/busy", new_busy, dut.busy);
    }

    bool wait_until(unsigned max_cycles, unsigned &waited)
    {
        // TODO 1：
        // ① 每次调用先把 waited 设为 0。
        // ② 当前 done 已为 1，立即返回 true。
        // ③ 最多推进 max_cycles 个周期：
        //    tick(false, false)，然后增加 waited；
        //    检查求值后的 done，为 1 就返回 true。
        // ④ 预算耗尽仍未完成，返回 false。
        // 不复位 DUT，不清空 errors，不修改 stall_mode。
        // #error "TODO 1: implement bounded waiting"
        // TODO 1 My Code Start
        waited = 0;
        if (dut.done)
            return true;
        for (unsigned i = 0; i < max_cycles; ++i)
        {
            tick(false, false);
            ++waited;
            if (dut.done)
                return true;
        }
        return false;
        // TODO 1 My Code End
    }

    void check_zero_budget(bool want_done)
    {
        // TODO 2：
        // 保存调用前的 cycle 和 context.time()。
        // 声明 unsigned waited = 999。
        // 调用 wait_until(0, waited)。
        // 使用 check_equal 检查以下四项：
        //   "zero/result"：返回值等于 want_done；
        //   "zero/waited"：waited 等于 0；
        //   "zero/cycle" ：cycle 没有变化；
        //   "zero/time"  ：context.time() 没有变化。
        // #error "TODO 2: verify zero-budget behavior"
        // TODO 2 My Code Start
        const unsigned old_cycle = cycle;
        const vluint64_t old_time = context.time();
        unsigned waited = 999;
        const bool got = wait_until(0, waited);
        check_equal("zero/result", want_done, got);
        check_equal("zero/waited", 0, waited);
        check_equal("zero/cycle", old_cycle, cycle);
        check_equal("zero/time", old_time, context.time());
        // TODO 2 My Code End
    }

public:
    explicit Testbench(VerilatedContext &ctx)
        : context(ctx), dut(&ctx)
    {
        dut.clk = 0;
        dut.rst = 1;
        dut.start = 0;
        dut.stall = 0;
        dut.eval();

        // 第一次复位前，不假设上电寄存器值。
        tick(true, false, false);
        check_equal("init/done", 0, dut.done);
        check_equal("init/busy", 0, dut.busy);
    }

    void run_case(const char *name, bool stall,
                  unsigned budget, bool want_complete,
                  unsigned want_waited)
    {
        case_id = completed + 1;
        case_name = name;
        stall_mode = stall;

        tick(true, false);
        check_equal("reset/done", 0, dut.done);
        check_equal("reset/busy", 0, dut.busy);

        // 空闲且复位已释放，接受一次 start。
        tick(false, true);
        check_equal("launch/done", 0, dut.done);
        check_equal("launch/busy", 1, dut.busy);

        check_zero_budget(false);

        unsigned waited = 999;
        const bool got = wait_until(budget, waited);

        if (!got)
        {
            std::cout << "TIMEOUT case=" << case_id
                      << " name=" << case_name
                      << " cycle=" << cycle
                      << " time_ns=" << context.time()
                      << " budget=" << budget
                      << " waited=" << waited
                      << " expected=" << (!want_complete)
                      << " done=" << static_cast<unsigned>(dut.done)
                      << " busy=" << static_cast<unsigned>(dut.busy)
                      << '\n';
        }

        check_equal("wait/completed", want_complete, got);
        check_equal("wait/cycles", want_waited, waited);
        check_equal("wait/busy", !want_complete, dut.busy);

        // 已经完成时，零预算也应立即成功。
        if (got)
            check_zero_budget(true);

        ++completed;
        std::cout << "CASE case=" << case_id
                  << " name=" << case_name
                  << " waited=" << waited
                  << " completed=" << got
                  << " total_errors=" << errors << '\n';
    }

    int finish()
    {
        check_equal("end/clk", 0, dut.clk);
        dut.final();

        if (completed != 4)
        {
            std::cerr << "INCOMPLETE cases=" << completed
                      << " expected=4\n";
            return 2;
        }

        std::cout << (errors == 0 ? "PASS" : "FAIL")
                  << " cases=" << completed
                  << " cycles=" << cycle
                  << " checks=" << checks
                  << " errors=" << errors
                  << " time_ns=" << context.time() << '\n';
        return errors == 0 ? 0 : 1;
    }
};

int main(int argc, char **argv)
{
    VerilatedContext context;
    context.commandArgs(argc, argv);

    const bool fault =
        argc > 1 && std::string(argv[1]) == "--fault";

    Testbench tb{context};

    // --fault 只改变第一个用例的实际故障开关，
    // 不改变其“应当完成”的期望。
    tb.run_case("normal", fault, 5, true, 3);
    tb.run_case("boundary", false, 3, true, 3);
    tb.run_case("stuck", true, 4, false, 4);
    tb.run_case("recovery", false, 3, true, 3);

    return tb.finish();
}