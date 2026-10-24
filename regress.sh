#!/usr/bin/env bash
set -u
set -o pipefail

cd -- "$(dirname -- "$0")" || exit 2
mkdir -p logs || exit 2

# 只允许生成新目录，避免把旧结果误当本次结果。
root=${1:-logs/day29_normal}
if ! mkdir -- "$root"; then
    echo "Choose a new result directory: $root" >&2
    exit 2
fi

verilator --version > "$root/tool.txt" 2>&1

# 本课沿用 --trace；按本机支持情况也可改为 --trace-vcd。
if verilator --cc --exe --build -Wall \
    --coverage-line --trace \
    --Mdir obj_reg --top-module fifo4 \
    -CFLAGS "-std=c++17" \
    fifo4.v sim_main.cpp > "$root/build.log" 2>&1
then
    :
else
    rc=$?
    echo "BUILD_FAIL exit=$rc log=$root/build.log"
    exit "$rc"
fi

bin="$PWD/obj_reg/Vfifo4"
seeds=(650182638 1 20261024)
failed=0
first_saved=0
printf 'seed\texit\n' > "$root/summary.tsv"

for seed in "${seeds[@]}"; do
    dir="$root/seed_$seed"
    mkdir -p "$dir/logs" || exit 2

    inject=0
    if [[ "${REG_NEGATIVE:-0}" == "1" && "$seed" == "1" ]]; then
        inject=1
    fi

    if (
        cd -- "$dir" || exit 2
        TB_SEED="$seed" TB_TRACE=0 TB_INJECT_FAIL="$inject" \
            "$bin" > run.log 2>&1
    ); then
        rc=0
    else
        rc=$?
    fi

    printf '%s\t%s\n' "$seed" "$rc" >> "$root/summary.tsv"

    if (( rc != 0 )); then
        failed=$((failed + 1))

        if (( first_saved == 0 )); then
            {
                printf 'seed=%s exit=%s inject_fail=%s\n' \
                    "$seed" "$rc" "$inject"
                printf 'log=%s/run.log\n' "$dir"
                if ! rg -m 1 '^FAIL' "$dir/run.log"; then
                    echo "No FAIL line; inspect the full log."
                fi
            } > "$root/first_failure.txt"
            first_saved=1
        fi
    fi
done

cat "$root/summary.tsv"

if (( failed != 0 )); then
    cat "$root/first_failure.txt"
    printf 'REGRESSION FAIL failed=%s total=3\n' "$failed"
    exit 1
fi

echo "REGRESSION PASS failed=0 total=3"
exit 0
