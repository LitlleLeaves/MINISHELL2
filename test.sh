#!/usr/bin/env bash
set -uo pipefail

BIN="./minishell"
TEST_DIR="tests/cases"
OUT_DIR="tests/output"
LOG_DIR="tests/logs"
TMP_DIR="tests/tmp"

mkdir -p "$OUT_DIR" "$LOG_DIR" "$TMP_DIR"

PASS=0
FAIL=0

normalize_output() {
    # Remove prompt lines and empty lines
    sed '/^Minishell>/d' | sed '/^[[:space:]]*$/d'
}

for input in "$TEST_DIR"/*.txt; do
    name="$(basename "$input" .txt)"
    bash_out="$TMP_DIR/${name}.bash.out"
    bash_err="$TMP_DIR/${name}.bash.err"
    mini_out="$TMP_DIR/${name}.mini.out"
    mini_err="$TMP_DIR/${name}.mini.err"
    bash_out_norm="$TMP_DIR/${name}.bash.out.norm"
    bash_err_norm="$TMP_DIR/${name}.bash.err.norm"
    mini_out_norm="$TMP_DIR/${name}.mini.out.norm"
    mini_err_norm="$TMP_DIR/${name}.mini.err.norm"
    vg_log="$LOG_DIR/${name}.valgrind.log"

    echo "=== Running $name ==="

    # Run bash with the same input
    bash --noprofile --norc < "$input" > "$bash_out" 2> "$bash_err"

    # Run minishell under valgrind
    valgrind -s \
        --leak-check=full \
        --show-leak-kinds=definite \
        --track-fds=yes \
        --log-file="$vg_log" \
        "$BIN" < "$input" > "$mini_out" 2> "$mini_err" || true

    # Normalize outputs
    normalize_output < "$bash_out" > "$bash_out_norm"
    normalize_output < "$mini_out" > "$mini_out_norm"
    normalize_output < "$bash_err" > "$bash_err_norm"
    normalize_output < "$mini_err" > "$mini_err_norm"

    # Compare stdout and stderr
    if diff -u "$bash_out_norm" "$mini_out_norm" >/dev/null && \
       diff -u "$bash_err_norm" "$mini_err_norm" >/dev/null; then
        if grep -q "definitely lost: 0 bytes" "$vg_log" && \
           grep -q "ERROR SUMMARY: 0 errors" "$vg_log"; then
            echo "[PASS] $name"
            ((PASS++))
        else
            echo "[FAIL] $name (valgrind issues)"
            echo "  see: $vg_log"
            ((FAIL++))
        fi
    else
        echo "[FAIL] $name (output mismatch)"
        echo "  bash stdout:   $bash_out_norm"
        echo "  mini stdout:   $mini_out_norm"
        echo "  bash stderr:   $bash_err_norm"
        echo "  mini stderr:   $mini_err_norm"
        echo "  see: $vg_log"
        ((FAIL++))
    fi
done

echo
echo "Passed: $PASS"
echo "Failed: $FAIL"

if [ "$FAIL" -ne 0 ]; then
    exit 1
fi