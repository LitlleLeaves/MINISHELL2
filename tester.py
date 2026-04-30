import subprocess
import os

# Define colors for terminal output
GREEN = "\033[92m"
RED = "\033[91m"
RESET = "\033[0m"
BOLD = "\033[1m"

def run_shell(shell_path, command):
    try:
        # We use a heredoc to pass the command to minishell/bash
        process = subprocess.Popen(
            shell_path,
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
        stdout, stderr = process.communicate(input=command + "\nexit\n")
        # Strip the 'exit' output often printed by minishell
        return stdout.strip().split('\n')[0] if stdout else ""
    except Exception as e:
        return f"Error: {str(e)}"

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
    "echo $?\"$?\"'$?'",
    "echo \"hel$USERlo\"",
    "echo \"$USER\"'$HOME'\"$?\"''$?$USER'\"$$\"'"
]

def main():
    minishell_path = "./minishell"
    bash_path = "bash"
    
    if not os.path.exists(minishell_path):
        print(f"{RED}Error: {minishell_path} not found. Compile your project first!{RESET}")
        return

    print(f"{BOLD}Starting Minishell Expansion Tests...{RESET}\n")
    
    passed = 0
    for i, cmd in enumerate(test_cases, 1):
        bash_res = run_shell(bash_path, cmd)
        mini_res = run_shell(minishell_path, cmd)
        
        if bash_res == mini_res:
            print(f"{GREEN}[PASS]{RESET} Test {i}: {cmd}")
            passed += 1
        else:
            print(f"{RED}[FAIL]{RESET} Test {i}: {cmd}")
            print(f"   Expected: [{bash_res}]")
            print(f"   Got:      [{mini_res}]")
            
    print(f"\n{BOLD}Results: {passed}/{len(test_cases)} tests passed.{RESET}")

if __name__ == "__main__":
    main()