from typing import Tuple

PROGRAMME_PATH = './main'

def execute_programme(stdin:str) -> Tuple[int, str, str]:
    """Executes the programme with the given input and returns (status code, stdout, stderr)"""
    import subprocess
    # runs process and saves stdin and stdout to variables
    process = subprocess.Popen([PROGRAMME_PATH], stdout=subprocess.PIPE, stdin=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout, stderr = process.communicate(stdin.encode())

    return process.returncode, stdout.decode() if stdout else '', stderr.decode() if stderr else ''
