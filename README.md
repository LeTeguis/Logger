# ValueProperty

ValueProperty is a cross-platform library that allows us to notify the system if the values of a data type have been modified for further processing. It is similar to the ValueProperty in JavaFx.

## Repository Usage

The current repository is structured in a very simple way and has basic elements to enable compiling and running all the projects.

### Solution Hierarchy

#### The Solution

The solution is structured as follows:

    ValueProperty/
    ├── .gitignore
    ├── ValueProperty/
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
    ├── utest/
    │   ├── src/
    │   ├── premake5.lua
    │   └── README.md
    ├── nts.bat
    ├── nts.py
    ├── nts.sh
    ├── LICENCE
    ├── premake5.lua
    └── README.md

* ValueProperty: This is the root directory of all projects, tests, and examples.
    - ValueProperty: This is the ValueProperty library.
    - external: This is where external libraries and useful binaries for the proper functioning of the projects (third-party) will be stored.
    - tools: These are the basic scripts for installing libraries in a portable manner.
    - utest: These are the unit and functional tests for each project.
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