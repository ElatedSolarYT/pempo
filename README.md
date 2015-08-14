# pempo

```pempo``` is a Mac OS X injector tool. It uses [mach_inject](https://github.com/rentzsch/mach_inject) to inject a C/C++ dynamic library (.dylib) into a target process. A bootstrap C++ dynamic library is provided for injecting Mono dynamic linked libraries (.dll). This is accomplished by [embedding Mono](http://www.mono-project.com/docs/advanced/embedding/) into the target process.

## How to Inject

1. Determine architecture of target application: ```file PATH_TO_TARGET_APPLICATION```
2. Build ```pempo``` for target application architecture by setting the CMake variable ```ARCHITECTURE``` to the desired value (either i386 or x86_64)
  * For information on how to build with CMake see [Running CMake](http://www.cmake.org/runningcmake/)
4. Inject into target process: ```sudo ./injector TARGET_PROCESS_NAME LIBRARY_PATH```

### Mono

Any Mono dynamic link library can be injected into a target process as long as the following conditions are met:

1. The code [AssemblyEntryPointAttribute.cs](MonoLibrary/Pempo/AssemblyEntryPointAttribute.cs) is included **as is** in your Mono library. 
2. An ```AssemblyEntryPoint``` attribute is applied to the library's ```AssemblyInfo.cs``` with a string representing the static method you wish to be entry point of the injected code. For an example see [AssemblyInfo.cs](MonoLibrary/Pempo/Properties/AssemblyInfo.cs)

## License

The MIT License (MIT)

Copyright (c) 2015 Lucas Girouard-Stranks (Alias: LithiumToast)

See the full [license file](LICENSE) for pempo
