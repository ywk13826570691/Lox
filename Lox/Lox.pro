TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    lex.yy.c \
        lox.c \
    lox_foreach.c \
        lox_function.c \
    lox_lib.c \
    lox_math_lib.c \
        lox_opcode.c \
        lox_register.c \
        lox_stack.c \
        main.c \
    lox_handle.c \
    lox_object.c \
    lox_keywords.c \
    lox_array.c \
    lox_if.c \
    y.tab.c \
    lox_while.c \
    lox_repeat.c \
    lox_loop.c \
    lox_string.c \
    lox_string.c \
    lox_builtin_lib.c

HEADERS += \
    lox.h \
    lox_config.h \
    lox_def.h \
    lox_foreach.h \
    lox_function.h \
    lox_lib.h \
    lox_math_lib.h \
    lox_opcode.h \
    lox_register.h \
    lox_stack.h \
    lox_handle.h \
    lox_object.h \
    lox_keywords.h \
    lox_array.h \
    lox_if.h \
    lox_while.h \
    lox_repeat.h \
    lox_loop.h \
    lox_string.h \
    lox_string.h \
    lox_builtin_lib.h

OTHER_FILES += \
    vkang.l \
    vkang.y \
    b.txt \
    vkang.txt
