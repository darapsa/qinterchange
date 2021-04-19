# Qt Core wrapper for [libicclient](http://darapsa.org/libicclient)

# Building

## Getting

```sh
$ git clone git://darapsa.org/qicclient.git
```

## Configuring for various target hosts (with optional debugging)

```sh
$ mkdir build-qicclient-Desktop-Debug
$ cd build-qicclient-Desktop-Debug
$ cmake -DCMAKE_BUILD_TYPE=Debug ../qicclient
```

or

```sh
$ mkdir build-qicclient-Android_for_armeabi_v7a_arm64_v8a_x86_x86_64_Clang_Qt_5_15_2_android-Debug
$ cd build-qicclient-Android_for_armeabi_v7a_arm64_v8a_x86_x86_64_Clang_Qt_5_15_2_android-Debug
```

and then

```sh
$ cmake -DCMAKE_TOOLCHAIN_FILE=/opt/android-sdk-update-manager/ndk/21.3.6528147/build/cmake/android.toolchain.cmake -DCMAKE_FIND_ROOT_PATH=/usr/local/Qt/5.15.2/android -DANDROID_NATIVE_API_LEVEL=21 -DANDROID_ABI=arm64-v8a -DCMAKE_INSTALL_PREFIX=/usr/local/Qt/5.15.2/android -DCMAKE_BUILD_TYPE=Debug ../qicclient
```

or

```sh
$ cmake -DCMAKE_TOOLCHAIN_FILE=/opt/android-sdk-update-manager/ndk/21.3.6528147/build/cmake/android.toolchain.cmake -DCMAKE_FIND_ROOT_PATH=/usr/local/Qt/5.15.2/android -DANDROID_NATIVE_API_LEVEL=16 -DANDROID_ABI=armeabi-v7a -DCMAKE_INSTALL_PREFIX=/usr/local/Qt/5.15.2/android -DCMAKE_BUILD_TYPE=Debug ../qicclient
```

or

```sh
$ cmake -DCMAKE_TOOLCHAIN_FILE=/opt/android-sdk-update-manager/ndk/21.3.6528147/build/cmake/android.toolchain.cmake -DCMAKE_FIND_ROOT_PATH=/usr/local/Qt/5.15.2/android -DANDROID_NATIVE_API_LEVEL=16 -DANDROID_ABI=x86 -DCMAKE_INSTALL_PREFIX=/usr/local/Qt/5.15.2/android -DCMAKE_BUILD_TYPE=Debug ../qicclient
```

or

```sh
$ cmake -DCMAKE_TOOLCHAIN_FILE=/opt/android-sdk-update-manager/ndk/21.3.6528147/build/cmake/android.toolchain.cmake -DCMAKE_FIND_ROOT_PATH=/usr/local/Qt/5.15.2/android -DANDROID_NATIVE_API_LEVEL=21 -DANDROID_ABI=x86_64 -DCMAKE_INSTALL_PREFIX=/usr/local/Qt/5.15.2/android -DCMAKE_BUILD_TYPE=Debug ../qicclient
```

or so on.

## Compiling, linking, and installing

```sh
$ make # -jN (with N an integer number of parallel tasks you allow your computer to run for compiling this)
$ sudo make install
```
