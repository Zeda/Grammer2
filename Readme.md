# Readme
For a tutorial/documentation on the commands open [/readme/commands.html](/docs/readme.md)

# Building

Binaries are available in the `/bin` folder, but for developers, building from source might be useful.

This project uses [`spasm-ng`](https://github.com/alberthdev/spasm-ng) to compile, and I use Linux. On windows you can either use the [`linux subsytem`](https://www.windowscentral.com/install-windows-subsystem-linux-windows-10)(only on windows 10) and install spasm from there or you can download the [`spasm-ng`](https://github.com/alberthdev/spasm-ng/releases) for Windows release.

***NOTE:** at the time of this writing, it appears that spasm-ng has a bug that doesn't parse the name field correctly.
Please use this version for now: https://github.com/alberthdev/spasm-ng/tree/feature/app-name-var-size.*

## Linux:
From the command line, run `./compile`

## Windows:
Download Windows [`spasm-ng`](https://github.com/alberthdev/spasm-ng/releases) release, rename it to `spasm.exe` and place it in the project directory. From command prompt or powershell cd to the project directory and run `compile.bat`.

This generates the jump table and compiles the app and Grammer package.
