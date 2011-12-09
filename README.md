Zamara
======

Zamara is a C++ library written for reading Starcraft II replay files.  It's still very much in beta, could break at any moment and the API may change.

This is my first C++ application in a long time and I'm using it as a learning project to get back into it.  If you see anything weird about the way something is coded or an interface seems awkward, please let me know!

I've attempted to follow the [Google Style Guide] but there are some things I disagree with (<s>possibly</s> probably due to my lack of C++ experience) that I haven't followed.

If you end up using Zamara in a project, please let me know!  I'm always interested to see the ways my code is being used. :)

What's a Zamara?
----------------

This library started out as a C++ "port" of the Tassadar ruby library (see credits below) and when I was trying to think of a name of the project I wanted to keep the name in the Starcraft universe, hopefully a Protoss as well.  As I was reading through the [SC wiki] I found a Protoss named Zamara that sounded interesting.  She's a Protoss Preserver, someone who has the ability to preserve the memories of all members of their species.  I thought it was the perfect name for a library meant to read all the memories of past SC2 games!

Goals
-----

* Open Source, cross-platform Starcraft II replay parser
* Support for multiple Starcraft 2 replay versions
* Few external dependencies
* Support for Little- and Big-Endian systems

Requirements
------------

Zamara is written for UNIX-like environments such as Linux, OS X, BSDs and Solaris.  One of the goals of the project is to have as few external dependencies as possible, at least avoiding any that wouldn't come by default in a standard installation.

Currently the libraries/applications required are:

* CMake (build system)
* Zlib
* BZip2

To build the tests, the following are required:

* [Google C++ Test Framework]

Building/Testing
----------------

### To build:

With tests:

    cmake .
    make

Without Tests:

    cmake -DNO_TESTS=1 .
    make

Include Debug Symbols:

    cmake -DDEBUG=1 .
    make

### To run the tests:

    test/bin/ZAMARA_test

Planned Features
----------------

* Parsing for actions performed in the replay
* Parsing for message actions
* Stat calculations such as APM, EAPM

Known Issues
------------

* The API will be changing a lot! This library is still very much beta.
* Teams are not parsed yet.
* Winning players don't seem to be parsed correctly. It could be the replay I'm testing with at the moment.
* Big-Endian systems are not working correctly.
* The library has currently only been tested with older replay files.  It needs to be tested with newer replays.

Contact
-------

Website: https://github.com/aphistic/zamara

Credits
-------

* [Tassadar](https://github.com/agoragames/tassadar) -
The initial inspiration for this project and a source of structure and processes for reading replay files.
* libmpq -
A lot of help when writing the code for reading MPQ files.
* [mpyq](https://github.com/arkx/mpyq) -
This utility was very helpful when validating the values I was getting from the MPQ when writing the MPQ code.
* [sc2reader](https://github.com/GraylinKim/sc2reader) -
The wiki is an invaluable source of information on the format of the files within the MPQ.
* [WARP](http://trac.erichseifert.de/warp) -
Another good source for how to process SC2 replay files.
* [sc2gears](https://sites.google.com/site/sc2gears/) -
A great way to validate that my SC2 data is being read correctly.

[SC Wiki]: http://starcraft.wikia.com/
[Google Style Guide]: http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml
[Google C++ Test Framework]: http://code.google.com/p/googletest/

License
-------

Copyright (c) 2011, Erik Davidson
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
