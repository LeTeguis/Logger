COMMAND_PROMPT = {
    "build" : "This command build all project for this solution",
    "run" : "This command run the build solution with the default project",
    "gen" : "This command generated all project for this solution",
    "clean" : "This command clear all project for this solution",
    "version" : "This command get version for all projects for this solution",
    "help" : "This command get help command"
}

def IsCommand(cmd):
    if cmd in COMMAND_PROMPT.keys():
        return True
    return False