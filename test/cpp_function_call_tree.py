import os
import re
from collections import defaultdict

# === Regex Patterns ===
FUNC_DEF_PATTERN = re.compile(
    r'^\s*(?:[\w:<>\*&]+\s+)+((?:\w+::)?\w+)\s*\(([^)]*)\)\s*(\{)?\s*$'
)
FUNC_CALL_PATTERN = re.compile(r'\b(\w+)\s*\(')

# === Data Structures ===
function_defs = {}  # function_name -> (filename, line_number)
function_calls = defaultdict(set)  # caller -> set(callees)
call_counts = defaultdict(int)     # callee -> total # of calls
called_by = defaultdict(set)       # callee -> set(callers)

# === File Finder ===
def find_source_files(root='.'):
    exts = ('.cpp', '.cc', '.c')
    source_files = []
    for dirpath, _, filenames in os.walk(root):
        for file in filenames:
            if file.endswith(exts):
                source_files.append(os.path.join(dirpath, file))
    return source_files

# === Parser ===
def extract_functions_and_calls(filepath):
    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
        lines = f.readlines()

    current_func = None
    brace_depth = 0
    pending_func_name = None

    for i, line in enumerate(lines):
        stripped = line.strip()

        # Detect function definitions (support ClassName::func)
        match = FUNC_DEF_PATTERN.match(line)
        if match:
            func_name = match.group(1)
            has_brace = match.group(3)

            if has_brace:
                current_func = func_name
                brace_depth = 1
                function_defs[func_name] = (filepath, i + 1)
            else:
                pending_func_name = func_name
                continue

        elif pending_func_name and '{' in stripped:
            current_func = pending_func_name
            brace_depth = 1
            function_defs[pending_func_name] = (filepath, i + 1)
            pending_func_name = None

        elif pending_func_name and not stripped:
            continue  # wait if blank line

        elif pending_func_name:
            pending_func_name = None  # cancel if nothing found

        # Inside a function body
        if current_func:
            brace_depth += line.count("{") - line.count("}")
            if brace_depth <= 0:
                current_func = None
                continue

            # Track calls inside body
            for call in FUNC_CALL_PATTERN.findall(line):
                if call == current_func or call + "()" == current_func:
                    continue
                function_calls[current_func].add(call)
                call_counts[call] += 1
                called_by[call].add(current_func)

# === Tree Printer ===
def print_call_tree(func, visited=None, indent=0):
    if visited is None:
        visited = set()
    print("    " * indent + func)
    visited.add(func)
    for callee in sorted(function_calls.get(func, [])):
        if callee not in visited and callee in function_defs:
            print_call_tree(callee, visited, indent + 1)

# === Main ===
def main():
    source_files = find_source_files()

    if not source_files:
        print("❌ No .cpp, .cc, or .c files found in the current directory.")
        return

    print(f"📁 Found {len(source_files)} source files. Parsing...\n")

    for filepath in source_files:
        extract_functions_and_calls(filepath)

    print("\n🔍 FUNCTION CALL TREES:\n")
    root_funcs = [
        f for f in function_defs
        if all(f not in callees for callees in function_calls.values())
    ]

    for root in sorted(root_funcs):
        file, line = function_defs[root]
        print(f"\n📂 From: {file}:{line}")
        print_call_tree(root)

    print("\n📊 FUNCTION USAGE SUMMARY:\n")
    for func in sorted(function_defs):
        file, line = function_defs[func]
        print(f"{func}  (defined at {file}:{line})")
        print(f"  ↳ Called {call_counts[func]} time(s) by {len(called_by[func])} function(s)\n")

if __name__ == "__main__":
    main()
