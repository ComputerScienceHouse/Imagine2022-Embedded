import subprocess
import sys
import re

LAUNCH_SCRIPT_LOC = "HACKING/launch-environment.sh"
FILE_LOC = "/ImagineRIT2022/main/config.h"
VAR_NAME = "CONFIG_DEVICE_NUM"

subprocess.check_output([LAUNCH_SCRIPT_LOC])
                                                                                                                                                                                                                                                     

with open(FILE_LOC, "r") as file:
    filestr = file.read()
    
lines = filestr.split("\n")


devNum = int(re.search(f"{VAR_NAME} 0x..", filestr).group()[-2:], 16)

try:
    subprocess.check_call(["idf.py", "flash"])
except subprocess.CalledProcessError as e:
    print(e.output)
    sys.exit(1)

print(f"""
=========================================
#{devNum} SAFE TO REMOVE
=========================================
""")

devNum += 1
for i, line in enumerate(lines):
    if VAR_NAME in line:
        lines[i] = f"#define {VAR_NAME} 0x{'{:02x}'.format(devNum)}"
        print(line)
        break

with open(FILE_LOC, "w") as file:
        file.write("\n".join(lines))


subprocess.check_call(["idf.py","build"])
