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
$ mkdir build-qicclient-Android_Qt_5_15_1_Clang_Multi_Abi-Debug
$ cd build-qicclient-Android_Qt_5_15_1_Clang_Multi_Abi-Debug
```

and then

```sh
$ cmake -DCMAKE_TOOLCHAIN_FILE=/opt/android-sdk-update-manager/ndk/21.1.6352462/build/cmake/android.toolchain.cmake -DCMAKE_FIND_ROOT_PATH=/opt/Qt/5.15.1/android -DANDROID_NATIVE_API_LEVEL=21 -DANDROID_ABI=arm64-v8a -DCMAKE_INSTALL_PREFIX=/opt/Qt/5.15.1/android -DCMAKE_BUILD_TYPE=Debug ../qicclient
```

or

```sh
$ cmake -DCMAKE_TOOLCHAIN_FILE=/opt/android-sdk-update-manager/ndk/21.1.6352462/build/cmake/android.toolchain.cmake -DCMAKE_FIND_ROOT_PATH=/opt/Qt/5.15.1/android -DANDROID_NATIVE_API_LEVEL=21 -DANDROID_ABI=armeabi-v7a -DCMAKE_INSTALL_PREFIX=/opt/Qt/5.15.1/android -DCMAKE_BUILD_TYPE=Debug ../qicclient
```

or

```sh
$ cmake -DCMAKE_TOOLCHAIN_FILE=/opt/android-sdk-update-manager/ndk/21.1.6352462/build/cmake/android.toolchain.cmake -DCMAKE_FIND_ROOT_PATH=/opt/Qt/5.15.1/android -DANDROID_NATIVE_API_LEVEL=21 -DANDROID_ABI=x86 -DCMAKE_INSTALL_PREFIX=/opt/Qt/5.15.1/android -DCMAKE_BUILD_TYPE=Debug ../qicclient
```

or

```sh
$ cmake -DCMAKE_TOOLCHAIN_FILE=/opt/android-sdk-update-manager/ndk/21.1.6352462/build/cmake/android.toolchain.cmake -DCMAKE_FIND_ROOT_PATH=/opt/Qt/5.15.1/android -DANDROID_NATIVE_API_LEVEL=21 -DANDROID_ABI=x86_64 -DCMAKE_INSTALL_PREFIX=/opt/Qt/5.15.1/android -DCMAKE_BUILD_TYPE=Debug ../qicclient
```

or so on.

## Compiling, linking, and installing

```sh
$ make # -jN (with N an integer number of parallel tasks you allow your computer to run for compiling this)
$ sudo make install
```
