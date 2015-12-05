# pempo

```pempo``` is a Mac OS X injector tool. It uses [mach_inject](https://github.com/rentzsch/mach_inject) to inject a C/C++ dynamic library (.dylib) into a target process. A bootstrap C++ dynamic library is provided for injecting Mono dynamic linked libraries (.dll). This is accomplished by [embedding Mono](http://www.mono-project.com/docs/advanced/embedding/) into the target process.

## Screenshots

![League of Legends](/screenshots/leagueoflegends.png?raw=true "League of Legends")
![GLEssentials](/screenshots/GLEssentials.png?raw=true "GLEssentials")

## How to build
1. Download and install [Mono Universal Installer](http://www.mono-project.com/download/).
2. Build Pempo. See [Running CMake](http://www.cmake.org/runningcmake/)

## How to Inject

1. Determine architecture of target application: ```file PATH_TO_TARGET_APPLICATION``` (should be i386 or x86_64)
2. Inject into target process: ```sudo arch ARCHITECTURE ./injector TARGET_PROCESS_NAME LIBRARY_PATH```

### Mono

Any Mono dynamic link library can be injected into a target process as long as the following conditions are met:

1. The code [AssemblyEntryPointAttribute.cs](src/MonoTestLibrary/MonoTestLibrary/AssemblyEntryPointAttribute.cs) is included **as is** in your Mono library. 
2. An ```AssemblyEntryPoint``` attribute is applied to the library's ```AssemblyInfo.cs``` with a string representing the static method you wish to be the entry point of the injected code. For an example see [AssemblyInfo.cs](src/MonoTestLibrary/MonoTestLibrary/Properties/AssemblyInfo.cs)

## License

The MIT License (MIT)

Copyright (c) 2015 Lucas Girouard-Stranks (Alias: LithiumToast)

See the full [license file](LICENSE)
