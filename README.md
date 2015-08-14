# pempo

```pempo``` is a Mac OS X injector tool. It uses [mach_inject](https://github.com/rentzsch/mach_inject) to inject a C/C++ dynamic library (.dylib) into a target process. A bootstrap C++ dynamic library is provided for injecting Mono dynamic linked libraries (.dll). This is accomplished by [embedding Mono](http://www.mono-project.com/docs/advanced/embedding/) into the target process.

## How to:

1. Determine architecture of target application via terminal```file PATH_TO_TARGET_APPLICATION```
2. Build ```pempo``` for target application architecture by setting the CMake variable ```ARCHITECTURE``` to the desired value (either i386, x86_64, or ppc)
  * For information on how to build with CMake see [Running CMake](http://www.cmake.org/runningcmake/)
4. Inject into target process via terminal ```sudo ./injector TARGET_PROCESS_NAME LIBRARY_PATH```

## License

The MIT License (MIT)

Copyright (c) 2015 Lucas Girouard-Stranks (Alias: LithiumToast)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
