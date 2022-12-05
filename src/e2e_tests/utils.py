from typing import Tuple

PROGRAMME_PATH = './main'

def execute_programme(stdin:str) -> Tuple[int, str, str]:
    """Executes the programme with the given input and returns (status code, stdout, stderr)"""
    import subprocess
    process = subprocess.Popen(PROGRAMME_PATH, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    stdout, stderr = process.communicate(stdin.encode())
    return process.returncode, stdout.decode() if stdout else '', stderr.decode() if stderr else ''
