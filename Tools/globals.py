import sys
import platform
import os

# tools directory
TOOLS_DIR = "Tools"

# tools version
NK_TOOLS_MAJOR_VERSION = 1
NK_TOOLS_MINOR_VERSION = 0

# nkentseu version
NK_KERNEL_MAJOR_VERSION = 1
NK_KERNEL_MINOR_VERSION = 0

# solution name
SOLUTION_NAME = "Logger"

# Plateforme
PLATFORM = sys.platform

for x in platform.uname():
    if "microsoft" in x.lower() or "windows" in x.lower():
        PLATFORM = "windows"
        break

def IsWindows():
    return PLATFORM == "windows"

def IsLinux():
    return PLATFORM == "linux"

def IsMac():
    return PLATFORM == "darwin"

# configuration debug, release, dist
CONFIG = "debug"

# project name
PROJECTS_NAME = [
    "AllExemple"
]

DEFAULT = "AllExemple"

# architecture
ARCHITECTURE = "x86_64"

# Encoding run
ENCODING = "build/{}/{}/"

# build configuration
config = "{}{}".format(CONFIG[0].upper(), CONFIG[1:])
BUILD_CONFIG = "{}-{}-{}".format(config, PLATFORM, ARCHITECTURE)

# path to run executable
EXE_PATH = {}
for name in PROJECTS_NAME:
    EXE_PATH[name] = ENCODING.format(BUILD_CONFIG, name)

# solution name ["STATIC_LIB", "DYNAMIC_LIB"]
LIB_TYPE = "DYNAMIC_LIB"