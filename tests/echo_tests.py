from argparse import ArgumentParser
from pathlib import Path
from os import listdir
from os.path import isfile, join
from difflib import unified_diff
from dataclasses import dataclass

import subprocess

@dataclass
class TestCase:
    file: str
    stdout: str
    stderr: bool
    exitcode: int

def diff(expected: str, actual: str) -> str:
    expected_lines = expected.splitlines(keepends=True)
    actual_lines = actual.splitlines(keepends=True)
    return ''.join(unified_diff(expected_lines, actual_lines,
                                fromfile="expected", tofile="actual"))

def run_shell(*cmd_line) -> subprocess.CompletedProcess:
    return subprocess.run(cmd_line, capture_output=True, text=True)

def perform_checks(expected: subprocess.CompletedProcess, actual: subprocess.CompletedProcess):
    assert (not expected.stderr) or actual.stderr != "", \
        "Something was expected on stderr"

    assert expected.returncode == actual.returncode, \
        f"Exited with {actual.returncode} expected {expected.returncode}"

    assert expected.stdout == actual.stdout, \
        f"stdout differ\n{diff(expected.stdout, actual.stdout)}"

if __name__ == "__main__":
    parser = ArgumentParser("TestSuite")
    parser.add_argument("--binary", required=True, type=Path)
    args = parser.parse_args()

    binary_path = args.binary.absolute()

    test_repo = "echo_tests"
    test_files = [join(test_repo, f) for f in listdir(test_repo) if isfile(join(test_repo, f))]

    for testcase in test_files:
        file = testcase

        sh_proc = run_shell(binary_path, file)
        sh_ref = run_shell("bash", "--posix", file)

        try:
            perform_checks(sh_ref, sh_proc)
        except AssertionError as err:
            print(f"{file}\n{err}")
        else:
            print(f"{file}")
            pass
