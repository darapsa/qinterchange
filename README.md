# Qt Core wrapper for [libicclient](http://darapsa.org/libicclient)

# Building

## Getting

```sh
$ git clone git://darapsa.org/qicclient.git
$ cd qicclient
```

## Configuring for various target hosts (with optional debugging)

```sh
$ qmake CONFIG+=debug -spec android-clang qicclient.pro
```

or

```sh
$ qmake CONFIG+=debug -spec linux-g++ qicclient.pro
```

or

```sh
$ qmake CONFIG+=debug -spec macx-clang qicclient.pro
```

or

```sh
$ qmake CONFIG+=debug -spec macx-ios-clang qicclient.pro
```

or so on.

## Compiling and linking

```sh
$ make # -jN (with N an integer number of parallel tasks you allow your computer to run for compiling this)
```
