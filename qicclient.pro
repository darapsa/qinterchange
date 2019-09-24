QT -= gui
TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
	qicclient/client.hxx
SOURCES += \
	client.cxx
INCLUDEPATH += $$PWD/libicclient
LIBS += \
	$$PWD/libicclient/libicclient.a \
	-lcurl 

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
	QMAKE_CFLAGS += -I/usr/local/aarch64-linux-android/sysroot/usr/include
	LIBS += -L/usr/local/aarch64-linux-android/sysroot/usr/lib
}

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
	QMAKE_CFLAGS += -I/usr/local/arm-linux-androideabi/sysroot/usr/include
	LIBS += -L/usr/local/arm-linux-androideabi/sysroot/usr/lib
}

debug: DEFINES += DEBUG
