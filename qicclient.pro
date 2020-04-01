QT -= gui
TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
	qicclient/user.hxx \
	qicclient/product.hxx \
	qicclient/catalog.hxx \
	qicclient/basket.hxx \
	qicclient/client.hxx
SOURCES += \
	user.cxx \
	catalog.cxx \
	basket.cxx \
	client.cxx
LIBS += -licclient

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
	INCLUDEPATH += \
		/usr/local/aarch64-linux-android/include/c++/4.9.x \
		/usr/local/aarch64-linux-android/sysroot/usr/include
	LIBS += -L/usr/local/aarch64-linux-android/sysroot/usr/lib
}

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
	INCLUDEPATH += \
		/usr/local/arm-linux-androideabi/include/c++/4.9.x \
		/usr/local/arm-linux-androideabi/sysroot/usr/include
	LIBS += -L/usr/local/arm-linux-androideabi/sysroot/usr/lib
}

contains(ANDROID_TARGET_ARCH,x86) {
	INCLUDEPATH += \
		/usr/local/i686-linux-android/include/c++/4.9.x \
		/usr/local/i686-linux-android/sysroot/usr/include
	LIBS += -L/usr/local/i686-linux-android/sysroot/usr/lib
}

contains(ANDROID_TARGET_ARCH,x86_64) {
	INCLUDEPATH += \
		/usr/local/x86_64-linux-android/include/c++/4.9.x \
		/usr/local/x86_64-linux-android/sysroot/usr/include
	LIBS += -L/usr/local/x86_64-linux-android/sysroot/usr/lib
}

debug: DEFINES += DEBUG
