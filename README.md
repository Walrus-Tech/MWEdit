# MWEdit
### Cloned from the MWEdit CVS repo on sourceforge.
MWEdit was made by Dave Humphrey, all credit for the project goes to him.

This code is based off of the 0.6.0 sourcecode from Sourceforge due to the latest repository being incomplete.

This is a continuation of the original MWEdit and its subsequent updates by [NimrodPSI](https://github.com/NimrodPSI/MWEdit) and [rfuzzo](https://github.com/rfuzzo/MWEdit). The aim of this project is to modernize the codebase and bring it into the modern era.

MWEdit is an alternative Morrowind plugin editor.

## Build

Currently, MWEdit only supports building with Visual Studio and requires at least C++20.

- The project requires [CMake](https://cmake.org/) for building. To build, you can simply set up the directory and run CMake with `mkdir build; cmake -G "Visual Studio 17 2022" -B build`
- The MWEdit application requires [DevIL 1.8.0](http://openil.sourceforge.net/). The development files are expected in the `IL/` directory on setups that don't support CMake's [FindDevIL module](https://cmake.org/cmake/help/latest/module/FindDevIL.html). For distribution, the three DLLs supplied in the download are required. The Unicode version and [ResIL](https://sourceforge.net/projects/resil/) may work but are untested.

Bugs and suggestions are welcome at either the [OpenMW Forums](https://forum.openmw.org/viewtopic.php?t=8280), [Stearn Vault](https://stearnvault.com/forums/topic/mwedit/), on [GitHub](https://github.com/Walrus-Tech/MWEdit), or on [Discord](https://discord.gg/AAAnesEgJe)
