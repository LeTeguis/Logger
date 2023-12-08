import sys
import globals

print("{} Tools - version {}.{}".format(globals.SOLUTION_NAME, globals.NK_TOOLS_MAJOR_VERSION, globals.NK_TOOLS_MINOR_VERSION))
print("{} Kernel - version {}.{}".format(globals.SOLUTION_NAME, globals.NK_KERNEL_MAJOR_VERSION, globals.NK_KERNEL_MINOR_VERSION))

sys.exit(0)