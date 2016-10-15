QT -= core gui opengl

APP = test_app
TARGET = test_app.elf

QMAKESPEC = cortex-m3

CONFIG += c++11

QMAKE_LFLAGS = -T$$PWD/ld/stm32f103c8.ld

DEFINES += STM32F10X_MD

DESTDIR = ./
unix:EXT = elf
win32:EXT = elf.exe

createlist.target = all
createlist.commands += arm-none-eabi-objdump -S $${OUT_PWD}/$${APP}.$${EXT} > $$join(APP,,,".lst") && arm-none-eabi-objcopy -Obinary $${OUT_PWD}/$${APP}.$${EXT} $${OUT_PWD}/$${APP}.bin && arm-none-eabi-nm -nalS --size-sort $${OUT_PWD}/$${APP}.$${EXT} | tail && arm-none-eabi-size $${OUT_PWD}/$${APP}.$${EXT}
QMAKE_EXTRA_TARGETS += createlist

INCLUDEPATH += ./include/

HEADERS += \
    include/core_cm3.h \
    include/core_cmFunc.h \
    include/core_cmInstr.h \
    include/stm32f10x.h \
    include/ISRstm32f10x_md.h \
    include/my_func.h \
    include/init.h \
    include/interrupts.h \
    include/io.h \
    include/uart.h

SOURCES += \
    src/my_func.cpp \
    src/main.cpp \
    src/init.cpp \
    src/io.cpp \
    src/uart.cpp \
    src/ISRstm32f10x_md.cpp

