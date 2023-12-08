# Logger Library

The Logger Library is a logging library written in C++. It provides a simple and flexible interface for logging messages in your application.

## Features

- Support for different types of loggers (e.g., console, file, network, etc.).
- Customization of log message formats.
- Asynchronous logging support.
- Ability to set default or instance-specific display options for loggers.
- Conditional logging support (e.g., based on message severity level).

## Usage

To start using the Logger Library, follow these steps:

1. Include the `Logger.h` header file in your project.
2. Create an instance of the `Logger` class, specifying the logger name and optionally the message format.
3. Use the methods provided by the `Logger` class to log messages.

Example usage:

```cpp
#include "Logger.h"

int main()
{
    nkentsuu::Logger logger("MyLogger", "[%T] %N: %M");

    logger.Log(nkentsuu::LogLevel::Info, "This is an informational message");
    logger.Log(nkentsuu::LogLevel::Warning, "This is a warning message");
    logger.Log(nkentsuu::LogLevel::Error, "This is an error message");

    return 0;
}
```
The addition of the Log.h file with an example of encapsulating the logger and assertion simplifies their usage as follows:

1. Logger encapsulation: The Log.h file defines a Log class that encapsulates the logger. This class provides a static Instance() method that returns a unique instance of Log. You can use this instance to obtain the logger using the GetLogger() method. For example, `Log::Instance().GetLogger()->ILog(__FILE__, __LINE__, __FUNCTION__)` allows you to access the logger and log messages.

2. Assertion encapsulation: The Log.h file also defines a GetAssert() method in the Log class. This method returns an assertion instance that you can use to perform assertions in your code. For example, `Log::Instance().GetAssert()->IAssert(__FILE__, __LINE__, __FUNCTION__)` allows you to access the assertion and perform checks.

By using this Log.h file as is, you can simply include the file in your project and use the LOG and ASSERT macros to access the logger and assertion respectively. For example, `LOG.Debug("Hello")` will log a debug message, and `ASSERT.True(condition, message)` will perform an assertion on the given condition.

If desired, you can also customize this Log.h file by defining your own Log class with additional features or adapting the LOG and ASSERT macros to fit your specific needs.

```cpp
## Usage (Example 2)

Another example of usage is to include the `Log.h` file, which is defined as follows:

```cpp
#ifndef __LOG_H_HEADER__
#define __LOG_H_HEADER__

#pragma once

#include "Platform/Platform.h"
#include "Logger.h"
#include "Assert.h"

namespace nkentsuu {
    class Log {
        public:

            static Log& Instance() {
                static Log unitTest;
                return unitTest;
            }

            std::shared_ptr<Logger> GetLogger() {
                return Logger__;
            }

            std::shared_ptr<Assert> GetAssert() {
                return Assert__;
            }
        private:
            std::shared_ptr<Logger> Logger__;
            std::shared_ptr<Assert> Assert__;
            Log(){
                Logger__ = std::make_shared<Logger>("Nkentsuu");
                Assert__ = std::make_shared<Assert>(Logger__);
            }
    };

    #define LOG             Log::Instance().GetLogger()->ILog(__FILE__, __LINE__, __FUNCTION__)
    #define ASSERT          Log::Instance().GetAssert()->IAssert(__FILE__, __LINE__, __FUNCTION__)
}

#endif /* __LOG_H_HEADER__ */
```

The usage of this `Log` class can be done as follows:


```cpp
#include <Logger/Log.h>

int main(int argc, char **argv){
    //nkentsuu::LOG.SetName("Bob");

    nkentsuu::LOG.Debug("Hello");
    return 0;
}
```

You can also create your own `Log.h` file by defining your own `Log` class according to your specific needs.

Feel free to customize this example according to your requirements and adapt it to your project.

## Contribution

Contributions to the Logger Library are welcome! If you would like to make improvements, fix bugs, or add new features, please feel free to submit a pull request on GitHub.

## License

This project is licensed under the MIT License. Please see the [LICENSE](./LICENSE) file for more information.

Feel free to customize this presentation based on the specific details of your project.

## Repository Usage

The current repository is structured in a very simple way and has basic elements to enable compiling and running all the projects.

### Solution Hierarchy

#### The Solution

The solution is structured as follows:

    Logger/
    ├── .gitignore
    ├── Logger/
    │   ├── docs/
    │   ├── src/
    │   ├── premake5.lua
    │   ├── README.md
    │   └── ...
    ├── external/
    │   ├── bin/
    │   ├── libs/
    │   └── ...
    ├── tools/
    │   ├── run.py
    │   ├── gen.py
    │   ├── build.py
    │   └── ...
    ├── nts.bat
    ├── nts.py
    ├── nts.sh
    ├── LICENCE
    ├── premake5.lua
    └── README.md

* Logger: This is the root directory of all projects, tests, and examples.
    - Logger: This is the Logger library.
    - external: This is where external libraries and useful binaries for the proper functioning of the projects (third-party) will be stored.
    - tools: These are the basic scripts for installing libraries in a portable manner.
    - nts.bat, nts.py, nts.sh: These are the basic scripts to access construction, build, run, and other scripts.

## Configuration

The current project configuration is done through nts* scripts.

### Windows Configuration

- To configure on Windows, you must have Visual Studio Community installed, Visual Studio Code, and WSL2.
- You must define the environment variables VS_BUILD_PATH and VS_PATH for Visual Studio Community, CODE_PATH for Visual Studio Code, as defined in the tools/tmps/script file.

### For All Other Platforms, Including Windows

Go to the tools/tmps/script file and open a Ubuntu terminal or WSL on Windows as indicated:

- Type nano ~/.bash_env.
- Copy and paste the code below before the next //---.
- Exit nano and type source ~/.bash_env.
- Type nano ~/bash_aliases.
- Copy and paste the code below before the next //---.
- Exit nano and type source ~/.bash_aliases.
- Type nano ~/.bashrc.
- Copy and paste the following code:

  ```
  if [ -f ~/.bash_env ]; then
      . ~/.bash_env
  fi
  ```

- Exit nano and restart your computer to configure all commands.

## Code Usage

To use the project, you must understand the current scripts:

- Project Generation: To generate the solution, enter "nts gen."
- Project Build: To compile the project, enter "nts build."
- Project Run: To run the project, enter "nts run."

If you want to add another project, don't forget to specify it in ./tools/globals.py, ./premake5.lua, ./config.lua, and create the premake5.lua file for that project.