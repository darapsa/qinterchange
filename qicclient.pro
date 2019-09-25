QT -= gui
TEMPLATE = lib
CONFIG += staticlib

HEADERS += \
	qicclient/client.hxx
SOURCES += \
	client.cxx
INCLUDEPATH += $$PWD/libicclient
LIBS += $$PWD/libicclient/libicclient.a

debug: DEFINES += DEBUG
