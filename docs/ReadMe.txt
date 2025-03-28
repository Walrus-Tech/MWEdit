
					MWEdit v0.6.0
				 Source Readme -- 9 September 2006
				Dave Humphrey - uesp@sympatico.ca


This is the source code for v0.6.0 of MWEdit, an alternative Morrowind plugin editor. There
are a few importants things to note:

	- The project was created with MS Visual Studio C++ v6.0. It has not been tested
          or compiled on any other platform.
	- This source code has been modified to use a self-contained directory structure.
          You should just be able to load the project/workspace and compile the project
          with no further modifications.
	- This source code has been modified to use the Devil DLLs (image library) instead
          of compiling and linking the Devil source code directly. The MWEdit application
          compiled with this source will need to be redestributed with the 4 Devil DLLs as
	  found in the IL subdirectory. This is unlike the released MWEdit package which
          does not use these DLLs as it is linked directly to the Devil source. You can
          download the Devil source code from http://openil.sourceforge.net/ if you wish to
          use this method.

Bugs and suggestions are welcome at the above e-mail address.


	Number of Source Files = 452 (4.7 Mb)
		252 H files, 1.3 Mb
		200 CPP Files, 3.4 Mb

	Number of Lines = 131316
		22813 Empty Lines
		48784 Comment Lines
		62714 Coded Lines
