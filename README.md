# MWEdit
### Cloned from the MWEdit CVS repo on sourceforge.
MWEdit was made by Dave Humphrey, all credit for the project goes to him.

This code is based off of the 0.6.0 sourcecode from Sourceforge due to the latest repository being incomplete.

This is a continuation of the original MWEdit and its subsequent updates by [NimrodPSI](https://github.com/NimrodPSI/MWEdit) and [rfuzzo](https://github.com/rfuzzo/MWEdit). The aim of this project is to modernize the codebase and bring it into the modern era.

MWEdit is an alternative Morrowind plugin editor. There are a few importants things to note:

- The project was created with MS Visual Studio C++ v6.0. It has not been tested or compiled on any other platform. 
- This source code has been modified to use a self-contained directory structure. You should just be able to load the project/workspace and compile the project with no further modifications.
- This source code has been modified to use the Devil DLLs (image library) instead of compiling and linking the Devil source code directly. The MWEdit application compiled with this source will need to be redestributed with the 4 Devil DLLs as found in the IL subdirectory. This is unlike the released MWEdit package which  does not use these DLLs as it is linked directly to the Devil source. You can  download the Devil source code from http://openil.sourceforge.net/ if you wish to use this method.

Bugs and suggestions are welcome at either the [OpenMW Forums](https://forum.openmw.org/viewtopic.php?t=8280), [Stearn Vault](https://stearnvault.com/forums/topic/mwedit/), or on [GitHub](https://github.com/Walrus-Tech/MWEdit)
