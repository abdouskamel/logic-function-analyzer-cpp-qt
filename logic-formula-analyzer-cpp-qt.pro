QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp ui/mainwindow.cpp ui/truth_table_model.cpp logic/myfunction.cpp logic/truth_table.cpp logic/formula/analyzer.cpp logic/formula/my_parser.cpp logic/formula/simplificator.cpp logic/utils/my_utils.cpp logic/utils/operations.cpp logic/utils/tokens_exception.cpp

HEADERS += ui/mainwindow.h ui/truth_table_model.h logic/utils/binary_tree.h logic/myfunction.h logic/truth_table.h logic/formula/analyzer.h logic/formula/my_parser.h logic/formula/simplificator.h logic/utils/my_const.h logic/utils/my_utils.h logic/utils/operations.h logic/utils/tokens_exception.h

FORMS += ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
