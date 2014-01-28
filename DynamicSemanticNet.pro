#-------------------------------------------------
#
# Project created by QtCreator 2013-12-28T14:20:34
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = DynamicSemanticNet
TEMPLATE = app

#QMAKE_CXXFLAGS += -mmacosx-version-min=10.7 -std=gnu0x -stdlib=libc+
QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11

SOURCES += main.cpp\
        widget.cpp \
    fileloader.cpp \
    kifloader.cpp \
    dynamicsemanticnet.cpp \
    player.cpp \
    GDL/gdl.cpp \
    GDL/gdl_constant.cpp \
    GDL/gdl_term.cpp \
    GDL/gdl_sentence.cpp \
    GDL/gdl_variable.cpp \
    GDL/gdl_functionalterm.cpp \
    GDL/gdl_relationalsentence.cpp \
    GDL/gdl_notsentence.cpp \
    GDL/gdl_orsentence.cpp \
    GDL/gdl_rule.cpp \
    propnet.cpp

HEADERS  += widget.h \
    fileloader.h \
    kifloader.h \
    dynamicsemanticnet.h \
    player.h \
    tree.hh \
    GDL/gdl.h \
    GDL/gdl_constant.h \
    GDL/gdl_term.h \
    GDL/gdl_sentence.h \
    GDL/gdl_variable.h \
    GDL/gdl_functionalterm.h \
    GDL/gdl_relationalsentence.h \
    GDL/gdl_notsentence.h \
    GDL/gdl_orsentence.h \
    GDL/gdl_rule.h \
    Trilogic.h \
    propnet.h

FORMS    += widget.ui
