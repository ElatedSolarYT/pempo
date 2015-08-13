# pempo

How to:

1. Determine architecture of target application (game or whatever)
  1. Open up [Terminal](https://en.wikipedia.org/wiki/Terminal_(OS_X)).
  2. Enter command ```file PATH_TO_TARGET_APPLICATION```
  3. Take note of the output, you need this information for the next step.
2. Build C++ bootstrap library ```pempo/Bootstrap/``` for target application architecture
  * Change the CMake variable ```ARCHITECTURE``` in [CMakeLists.txt](Bootstrap/CMakeLists.txt).
  * For information on how to build source code with CMake see [Running CMake](http://www.cmake.org/runningcmake/).
  * Note: The CMake build will also build ```osxinj``` via XCode.
3. Build Mono library ```pempo/MonoMagic```
  * For information on building Mono source code for MacOS see [Xamarin:Mac:Installation:GettingStarted](http://developer.xamarin.com/guides/mac/getting_started/installation/)  
  * Note: Could also build the mono library via [Visual Studio](https://www.visualstudio.com/vs-2015-product-editions) on Windows since all MacOS platform specific code is restricted to the C++ bootstrap. 
4. Inject into target process
  1. Open up [Terminal](https://en.wikipedia.org/wiki/Terminal_(OS_X)).
  2. Change directory to the bin folder with the configuration you built for: ```cd pempo/bin/debug```
  3. Inject into target process via ```sudo ./osxinj TARGET_PROCESS_NAME libpempo.dylib```
