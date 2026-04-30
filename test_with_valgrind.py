import subprocess
import os
import re

# Colors
GREEN = "\033[92m"
RED = "\033[91m"
YELLOW = "\033[93m"
RESET = "\033[0m"
BOLD = "\033[1m"

def run_valgrind(command):
    """Runs minishell through valgrind and returns (output, leak_count, error_count)"""
    valgrind_cmd = [
        "valgrind",
        "--leak-check=full",
        "--errors-exitcode=42", # Custom exit code if leaks/errors found
        "--show-leak-kinds=all",
        "./minishell"
    ]
    
    try:
        process = subprocess.Popen(
            valgrind_cmd,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        # Pass the command and exit the shell
        stdout, stderr = process.communicate(input=command + "\nexit\n")
        
        # Extract the actual shell output (first line)
        shell_output = stdout.strip().split('\n')[0] if stdout else ""
        
        # Check for leaks/errors in stderr
        has_leaks = "definitely lost: 0 bytes in 0 blocks" not in stderr and "lost:" in stderr
        has_errors = "ERROR SUMMARY: 0 errors" not in stderr
        
        return shell_output, has_leaks, has_errors, stderr
    except Exception as e:
        return f"Error: {str(e)}", False, False, ""

def run_bash(command):
    process = subprocess.Popen(
        ["bash"],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    stdout, _ = process.communicate(input=command + "\nexit\n")
    return stdout.strip().split('\n')[0] if stdout else ""

test_cases = [
    "echo \"$HOME\"'$HOME'",
    "echo \"$HO\"'ME'",
    "echo ''$HOME''",
    "echo '$HOME $USER $?'",
    "echo \"exit:\"$?\"!\"",
    "echo '\"$HOME\"'",
    "echo '$'HOME",
    "echo \"$\"HOME",
    "echo hello\"   \"world",
    "echo \"$USER\"'is'\"$USER\"",
    "true && echo $?\"$?\"'$?'",
    "export EMPTY=\"\" && echo \"$EMPTY\"'$EMPTY'\"$EMPTY\"end",
    "echo \"hel$USERlo\""
]

def main():
    if not os.path.exists("./minishell"):
        print(f"{RED}Error: ./minishell not found.{RESET}")
        return

    print(f"{BOLD}Minishell Valgrind & Logic Tester{RESET}\n")
    
    for i, cmd in enumerate(test_cases, 1):
        bash_res = run_bash(cmd)
        mini_res, leaked, errored, full_log = run_valgrind(cmd)
        
        # 1. Check Logic
        status_logic = f"{GREEN}OK{RESET}" if bash_res == mini_res else f"{RED}KO{RESET}"
        
        # 2. Check Memory
        status_mem = f"{GREEN}CLEAN{RESET}"
        if leaked or errored:
            status_mem = f"{RED}LEAK/ERR{RESET}"
        
        print(f"Test {i:02}: [{status_logic}] [{status_mem}] -> {cmd}")
        
        if status_logic.startswith(f"{RED}KO") or status_mem.startswith(f"{RED}LEAK"):
            if bash_res != mini_res:
                print(f"   {YELLOW}Expected:{RESET} {bash_res} | {YELLOW}Got:{RESET} {mini_res}")
            if leaked or errored:
                print(f"   {RED}Valgrind detected issues. Check your free() calls!{RESET}")

if __name__ == "__main__":
    main()