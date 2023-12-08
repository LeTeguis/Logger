import commands
import sys

def help_cmd():
    print("Command name{}: description\n".format(" " * (20 - len("command name"))))
    for key, value in commands.COMMAND_PROMPT.items():
        leng = 20 - len(key)
        
        print("{}{}: {}".format(key, " " * leng, value))


print("Command: ")
print("nts command_name [options1] [options2] [...]\n")
help_cmd()

sys.exit(0)