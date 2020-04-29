TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    animal.cpp \
    bird.cpp \
    owl.cpp \ 
    cockatoo.cpp \
    mammal.cpp \
    giraffe.cpp

HEADERS += \
    animal.hh \
    bird.hh \
    owl.hh \ 
    cockatoo.hh \
    mammal.hh \
    giraffe.hh
