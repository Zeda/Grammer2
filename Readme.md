# Readme
For a tutorial/documentation on the commands open [/readme/commands.html](/docs/readme.md)
Once downloads are ready, you'll be able to find them in the [releases](https://github.com/Zeda/Grammer2/releases) section.

Before going on, I do want to thank @NonstickAtom. I had to delete the commit history because I was misusing `git`, and that
has unfortunately removed the logs of many of NonstickAtom's contributions to the project (especially in documentation).

# Building
If you want to build this project yourself, you'll first need to clone the repository:
```
git clone --recursive-submodules https://github.com/Zeda/Grammer2.git
```

This project uses [`spasm-ng`](https://github.com/alberthdev/spasm-ng) to compile, and I use Linux. On windows you can either use the [`linux subsytem`](https://www.windowscentral.com/install-windows-subsystem-linux-windows-10)(only on windows 10) and install spasm from there or you can download the [`spasm-ng`](https://github.com/alberthdev/spasm-ng/releases) for Windows release.

***NOTE:** at the time of this writing, it appears that spasm-ng has a bug that doesn't parse the name field correctly.
Please use this version for now: [alberthdev/spasm-ng/tree/feature/app-name-var-size](https://github.com/alberthdev/spasm-ng/tree/feature/app-name-var-size). If you are on
Windows, @NonstickAtom785 has built the fixed version and posted it [here](https://ourl.ca/22728) with permission.*

## Linux:
From the command line, run `./compile`

## Windows:
Download the Windows [`spasm-ng`](https://github.com/alberthdev/spasm-ng/releases) release, rename it to `spasm.exe` and place it in the project directory. From command prompt do `compile` (or if you prefer powershell... do `./compile`). Read the above note if you are getting errors.

This generates the jump table and compiles the app and Grammer package.
