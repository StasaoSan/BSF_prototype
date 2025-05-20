import os
import signal
import subprocess

from config import BSF_BINARY, BSF_CONFIG


def startServer():
    return subprocess.Popen(
        [BSF_BINARY, "--config", BSF_CONFIG],
        preexec_fn=os.setsid,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.STDOUT
    )

def stopServer(proc):
    try:
        os.killpg(os.getpgid(proc.pid), signal.SIGTERM)
    except Exception as e:
        print(f"Failed to stop server: {e}")