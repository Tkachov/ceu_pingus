# Environment Information

I've been developing this port on Windows 7 x64 within Cygwin.

You can find more information on how to prepare Céu for work on Windows in my [ceu-windows](https://github.com/Tkachov/ceu-windows) repository. I didn't add any `jpg` support while building SDL2_img, so I had to convert some pictures from `data` folder to `png`.

I've installed Cygwin packages and built libraries only once, in the beginning of this project, so I don't really remember which packages and libraries are necessary and which pitfalls you might encounter. I can't list *all* Cygwin packages I have because there are too many of those and only few are needed. I can say that you might need the following:

* boost;
* libpng, opengl, freetype, etc;
* g++, gcc, git, gdb;
* scons, pkg-config.

I was using Sublime Text 2 as editor and Cygwin for building, debugging and testing. I'm not sure that any project files or non-Windows/Cygwin files (`.macosx`, etc) are still working. I've removed some C++ files and added a lot of Céu files, so you'll have to at least update file list in these. Plus, I've edited Makefile, so some changes in build/debug configurations of these project files might be necessary.

To build the project, I usually used `./rebuild`. That's a small bash script which first runs Céu compiler and then compiles all C++ code. If the build is successful, it playes a `~/win.wav` sound and runs launches the game within **gdb**. If not, it playes a `~/fail.wav` sound. Sounds notify me that I can continue working, because compilation process is not instant. Of course, you can remove these if you want. `./rebuild` does `make do_ceu && make build/debug`. You can use `build/pingus` instead of `build/debug`.