QT -= gui
TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
	qicclient/catalog.hxx \
	qicclient/client.hxx
SOURCES += \
	catalog.cxx \
	client.cxx
INCLUDEPATH += $$PWD/libicclient
LIBS += $$PWD/libicclient/libicclient.a

debug: DEFINES += DEBUG
