# -------------------------------------------------
# Project created by QtCreator 2014-05-06T16:13:14
# -------------------------------------------------
QT += network
QT += core \
    gui
TARGET = frameworkRFID
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    armazenamento.cpp \
    leitor.cpp \
    comunicacao.cpp \
    posicao.cpp \
    visualizacao.cpp \
    rastreavel.cpp \
    leitura_visualizacao.cpp \
    graphics.cpp \
    interfacearmz.cpp
HEADERS += armazenamento.h \
    leitor.h \
    comunicacao.h \
    posicao.h \
    visualizacao.h \
    rastreavel.h \
    objetos.h \
    interfacearmz.h
LIBS += -lmysqlclient \
    -lboost_system \
    -lboost_thread \
    -lmysqlclient
/usr/local/include/boost
LIBS += `allegro-config \
    --libs`

QT += sql
QT += widgets

LIBS += -L/home/lucas/Instalados/Qt/Tools/QtCreator/bin/plugins/sqldrivers -lqsqlmysql
LIBS += -L/usr/lib/mysql -lmysqlclient

LIBS += -L/usr/local/include/allegro5 -lallegro
LIBS += -L/usr/local/include/allegro5 -lallegro_image
LIBS += -L/usr/local/include/allegro5 -lallegro_dialog
LIBS += -L/usr/local/include/allegro5 -lallegro_primitives
LIBS += -L/usr/local/include/allegro5 -lallegro_font
LIBS += -L/usr/local/include/allegro5 -lallegro_ttf

FORMS += interfacearmz.ui
