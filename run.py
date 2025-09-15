import os
import subprocess
os.chdir(os.path.dirname(os.path.abspath(__file__)))


gcc = "C:\\MinGW\\bin\\gcc.exe"
src = "src/*.c"
include = "-Iinclude"
 
#subprocess.run(f"gcc -g -o out.exe {src} {include} && out.exe", shell=True)
subprocess.run(f"{gcc} -g -o out.exe {src} {include} && out.exe a.asm", shell=True)