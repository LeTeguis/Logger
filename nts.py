# nts build
# nts run
# nts gen
# nts version
# nts di [extension] [project_name] [-all]
# nts gen build run

import os, sys
import subprocess
from Tools import commands

TOOLS_DIR = "Tools"

"""source ~/.bash_env"""

def RunCommand(cmd, options):
    ret = 0
    script = os.path.join(os.getcwd(), TOOLS_DIR, f"{cmd}.py")

    if os.path.exists(script):
        args_cmd = ["python3", script]
        if len(options) >= 1:
            for e in options:
                args_cmd.append(e)
        print("----------------------------------- Executing : {} -----------------------------------\n".format(cmd))
        ret = subprocess.call(args_cmd)
        print("\n----------------------------------- End executing : {} -----------------------------------\n".format(cmd))
    else:
        print("Error: corrupted environment command ({}) ".format(cmd))
        ret = -1
    return ret

len_cmd = len(sys.argv)
i = 1
cmd_separator = ";"

while i < len_cmd:
    cmd = ""
    options = []
    j = i
    run_cmd = False

    while j < len_cmd:
        actual = sys.argv[j]

        if actual == cmd_separator:
            run_cmd = True
            j += 1
            break

        if cmd_separator in actual:
            actual_split = actual.split(cmd_separator)
            if actual_split[0] != "":
                options.append(actual_split[0])

        if j == i:
            cmd = sys.argv[j]
        else:
            # options = f"{options} {sys.argv[j]}"
            options.append(sys.argv[j])
        
        j += 1
        if j >= len_cmd:
            run_cmd = True
            break
    
    i = j

    if not commands.IsCommand(cmd):
        print("Error: {} is not a command tips [nts help] to get all command".format(cmd))
        break

    if RunCommand(cmd, options) != 0:
        print("Error: command {} fail ".format(cmd))
        break
