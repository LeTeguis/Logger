import subprocess, sys
import globals

ret = 0

if globals.IsWindows():
    ret = subprocess.call(["cmd.exe", "/c", f"External\\Bin\\Premake5\\premake5.exe --libtype={globals.LIB_TYPE}", "vs2022"])

if globals.IsLinux():
    ret = subprocess.call([f"External/Bin/Premake5/premake5.linux --libtype={globals.LIB_TYPE}", "gmake2"])

if globals.IsMac():
    ret = subprocess.call([f"External/Bin/Premake5/premake5 --libtype={globals.LIB_TYPE}", "gmake2"])
    if ret == 0:
        subprocess.call([f"External/Bin/Premake5/premake5 --libtype={globals.LIB_TYPE}", "xcode4"])

sys.exit(ret)