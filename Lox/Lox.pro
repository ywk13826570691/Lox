TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        lox.c \
        lox_function.c \
        lox_opcode.c \
        lox_register.c \
        lox_stack.c \
        main.c \
    lox_handle.c \
    lox_object.c

HEADERS += \
    lox.h \
    lox_config.h \
    lox_def.h \
    lox_function.h \
    lox_opcode.h \
    lox_register.h \
    lox_stack.h \
    lox_handle.h \
    lox_object.h

OTHER_FILES += \
    vkang.l \
    vkang.y \
    b.txt \
    vkang.txt
