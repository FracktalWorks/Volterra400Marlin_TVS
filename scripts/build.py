from subprocess import Popen, PIPE
from sys import exit
import os
import platform

print("Fracktal Works PIO Build Generator")
if "TRAVIS" in os.environ:
  print("Not running script on Travis")
  exit(0)

if platform.system() != 'Windows':
  print("Not Windows")
  exit(0)

bash_exe = "C:\\Program Files\\Git\\bin\\bash.exe"
cmd = "\"./scripts/build 2\""
# cmd = "\"echo $PWD\""

proc = Popen(bash_exe + " -c " + cmd, stdin=PIPE, stdout=PIPE, stderr=PIPE)
output, error = proc.communicate()
if output:
  print("Output: " + output)
if error:
  print("Error: " + error)
ret = proc.returncode
