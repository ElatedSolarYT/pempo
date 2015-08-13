# pempo

```pempo``` is a Mac OS X game injector & hack tool. It uses [osxinj](https://github.com/scen/osxinj) to inject C/C++ dynamic library (.dylib) into a target process. The dynamic library [embeds Mono](http://www.mono-project.com/docs/advanced/embedding/) then loads a Mono library (.dll).

How to:

1. Determine architecture of target application (game or whatever)
  1. Open up [Terminal](https://en.wikipedia.org/wiki/Terminal_(OS_X)).
  2. Enter command ```file PATH_TO_TARGET_APPLICATION```
  3. Take note of the output, you need this information for the next step.
2. Build ```pempo``` for target application architecture
  * Change the CMake variable ```ARCHITECTURE``` in [CMakeLists.txt](CMakeLists.txt) to match your target application. (i386 or x86_64)
  * For information on how to build with CMake see [Running CMake](http://www.cmake.org/runningcmake/).
  * Note: The CMake build will also build ```osxinj``` via XCode and ```pempo/MonoLibrary``` via Mono. As such, XCode and Mono need to be installed; see [XCode in App Store](https://itunes.apple.com/us/app/xcode/id497799835?ls=1&mt=12) and [Install Mono on Mac OS X](http://www.mono-project.com/docs/getting-started/install/mac/) 
4. Inject into target process
  1. Open up [Terminal](https://en.wikipedia.org/wiki/Terminal_(OS_X)).
  2. Change directory to the bin folder with the configuration you built for: ```cd pempo/bin/debug```
  3. Inject into target process via ```sudo ./osxinj TARGET_PROCESS_NAME libpempo.dylib```
