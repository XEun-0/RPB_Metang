import os
import re
import shutil
import subprocess
from concurrent.futures import ThreadPoolExecutor, as_completed

# ==== CONFIGURATION ====
PROJECT_ROOT = "."         # Root directory containing the Makefile
SOURCE_DIR = "./src"       # Where to scan for .cpp/.h files
EXTENSIONS = (".cpp", ".cc", ".cxx", ".h", ".hpp")
MAKE_COMMAND = ["make", "-C", PROJECT_ROOT]  # Command to build project
THREADS = 4                # Number of parallel jobs
INCLUDE_PATTERN = re.compile(r'^\s*#\s*include\s+[<"].+[>"]')

# ========================

def run_make():
    """Run the make command in the project root. Returns True if build succeeds."""
    result = subprocess.run(
        MAKE_COMMAND,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    )
    return result.returncode == 0

def test_include_removal(filepath, idx, original_line):
    """Comment out one include, rebuild, restore file."""
    backup_path = filepath + ".bak"
    shutil.copyfile(filepath, backup_path)

    try:
        with open(filepath, "r", encoding="utf-8") as f:
            lines = f.readlines()

        lines[idx] = "// " + original_line
        with open(filepath, "w", encoding="utf-8") as f:
            f.writelines(lines)

        success = run_make()
        return (filepath, original_line.strip(), success)

    finally:
        shutil.move(backup_path, filepath)

def collect_includes():
    """Find all include statements across files."""
    jobs = []
    for root, _, files in os.walk(SOURCE_DIR):
        for file in files:
            if file.endswith(EXTENSIONS):
                filepath = os.path.join(root, file)
                with open(filepath, "r", encoding="utf-8") as f:
                    lines = f.readlines()

                for idx, line in enumerate(lines):
                    if INCLUDE_PATTERN.match(line):
                        jobs.append((filepath, idx, line))
    return jobs

def main():
    jobs = collect_includes()
    print(f"[+] Found {len(jobs)} includes to check\n")

    with ThreadPoolExecutor(max_workers=THREADS) as executor:
        future_to_job = {executor.submit(test_include_removal, *job): job for job in jobs}

        for future in as_completed(future_to_job):
            filepath, include_line, success = future.result()
            if success:
                print(f"[REMOVABLE] {include_line}  ({filepath})")
            else:
                print(f"[NEEDED]    {include_line}  ({filepath})")

if __name__ == "__main__":
    main()
