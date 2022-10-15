# Dunwich Sandgeon
This is an (in-development) traditional, procedurally generated  roguelike
video game for modern computing platforms (for some definition of "modern").

<!-- Here's a [link](https://en.wikipedia.org/wiki/Roguelike) to the definition of "roguelike" being used. -->
Here's a [link](http://roguebasin.com/index.php/What_a_roguelike_is) to
more information about the style of roguelike this game is intended to be.

## Dependencies
To build the game, you will need a C++ compiler that supports C++20. 

For now, this game needs SDL2 and the C++ version of PCG Random.

This game also needs [this](https://github.com/SRombauts/SimplexNoise/)
implementation of Simplex Noise.

When downloading the game, make sure you recursively grab the submodules of
this git repo, as follows:
* `git clone --recurse-submodules https://github.com/fl4shk/dunwich_sandgeon.git`

## SRombauts/SimplexNoise License
The MIT License (MIT)

Copyright (c) 2012-2018 Sebastien Rombauts (sebastien.rombauts@gmail.com)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
