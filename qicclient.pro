QT -= gui
TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
	qicclient/user.hxx \
	qicclient/product.hxx \
	qicclient/catalog.hxx \
	qicclient/client.hxx
SOURCES += \
	user.cxx \
	catalog.cxx \
	client.cxx
INCLUDEPATH += $$PWD/libicclient
LIBS += $$PWD/libicclient/libicclient.a

debug: DEFINES += DEBUG
