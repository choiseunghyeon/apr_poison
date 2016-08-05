TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    arplib.c \
    netinfo.c

HEADERS += \
    arplib.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../usr/lib/x86_64-linux-gnu/release/ -lpcap
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../usr/lib/x86_64-linux-gnu/debug/ -lpcap
else:unix: LIBS += -L$$PWD/../../../usr/lib/x86_64-linux-gnu/ -lpcap

INCLUDEPATH += $$PWD/../../../usr/lib/x86_64-linux-gnu
DEPENDPATH += $$PWD/../../../usr/lib/x86_64-linux-gnu

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/lib/x86_64-linux-gnu/release/libpcap.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/lib/x86_64-linux-gnu/debug/libpcap.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/lib/x86_64-linux-gnu/release/pcap.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../usr/lib/x86_64-linux-gnu/debug/pcap.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../usr/lib/x86_64-linux-gnu/libpcap.a
