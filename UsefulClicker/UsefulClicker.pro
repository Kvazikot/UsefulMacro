QT += core gui widgets xml svg
QT += multimedia
QT += multimediawidgets
QMAKE_CXXFLAGS += -std=c++17
TARGET = UsefulClicker
UI_DIR = "./ui"
TEMPLATE = app
#QMAKE_FLAGS_RELEASE += -O3 -msse4.1 -mssse3 -msse3 -msse2 -msse -Wno-unused-variable
#QMAKE_CXXFLAGS_RELEASE += -O3 -msse4.1 -mssse3 -msse3 -msse2 -msse
OPENCV_451_PATH = "C:\Projects\opencv_new"
#PYTHON_PATH = "C:\\Program Files\\Python37"
#INCLUDEPATH += "C:\\Program Files\\Python37\\include"
#INCLUDEPATH +=$$OPENCV_451_PATH\\dlib\\dlib\\external\\pybind11\\include\\
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\core\\include"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\build_mingw\\modules"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\build_mingw\\"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\include\\opencv2"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\include\\"
#INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\calib3d\\include\\"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\calib3d\\include"
#INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\core\\include"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\dnn\\include"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\features2d\\include"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\flann\\include"
#INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\gapi\\include"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\highgui\\include"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\imgcodecs\\include"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\imgproc\\include"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\videoio\\include"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\video\\include"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\gapi\\include"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\objdetect\\include"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\photo\\include"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\opencv_contrib-4.x\modules\shape\include"
#INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\java\\include"
#INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\js\\include"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\ml\\include"
#INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\objc\\include"
#INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\objdetect\\include"
#INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\photo\\include"
#INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\python\\include"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\stitching\\include"
#INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\ts\\include"
#INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\video\\include"
#INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\videoio\\include"
#INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\world\\include"
INCLUDEPATH+= "./interpreter"

LIBS += -luser32 -lgdi32
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_core455.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_ml455.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_flann455.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_imgproc455.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_photo455.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_features2d455.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_imgcodecs455.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_videoio455.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_highgui455.dll
#LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\" -lopencv_ts455.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_calib3d455.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_objdetect455.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_stitching455.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_dnn455.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_video455.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_shape455.dll
#LIBS+=-L$$PYTHON_PATH\\libs\\ -lpython37
#LIBS+="$$(PYTHON_PATH)\\libs\\python39



SOURCES += main.cpp \
    interpreter/expression_calculator.cpp \
    log/logger.cpp \
    tests/cool_tests_form.cpp \
    interpreter/interpreter.cpp \
    interpreter/interpreterpy.cpp \
    interpreter/interpreterwin64.cpp \
    cv/dspmodule.cpp \
    tests/highlighter.cpp \
    ui/coordselector.cpp \
    ui/createdialog.cpp \
    ui/mousedialog.cpp \
    ui/screenbuttonsdetector.cpp \
    ui/aboutbox.cpp \
    ui/areaselectordialog.cpp \
    ui/autocompleteeditor.cpp \
    ui/imagesearchdialog.cpp \
    ui/mainwindow.cpp \
    ui/shelldialog.cpp \
    ui/typedialog.cpp \
    ui/widgets/areabutton.cpp \
    ui/widgets/comboedit.cpp \
    ui/widgets/crossbutton.cpp \
    ui/widgets/delaywidget.cpp \
    ui/widgets/keyboardbutton.cpp \
    ui/widgets/mousebutton.cpp \
    ui/widgets/shellbutton.cpp \
    ui/widgets/svg_path_parser.cpp \
    ui/widgets/svgwidget.cpp \
    ui/widgets/qconsole.cpp \
    xml/clickerdocument.cpp \
    xml/xmleditor.cpp \
    xml/xmlstreamer.cpp \
    #xml/serialisationtest.cpp
    model/clickermodel.cpp \
    model/domitem.cpp \
    model/fancydelegate.cpp \
    settings/clickersettings.cpp \
    model/simpledelegate.cpp
    #model/treeitem.cpp \
    #model/treemodel.cpp

HEADERS += \
    interpreter/expression_calculator.h \
    log/logger.h \
    myproxystyle.h \
    tests/cool_tests_form.h \
    cv/dspmodule.h \
    tests/highlighter.h \
    ui/mousedialog.h \
    ui/typedialog.h \
    ui/widgets/qconsole.h \
    ui/coordselector.h \
    ui/dialogtype.h \
    ui/screenbuttonsdetector.h \
    ui/aboutbox.h \
    ui/areaselectordialog.h \
    ui/autocompleteeditor.h \
    ui/shelldialog.h \
    ui/widgets/areabutton.h \
    ui/widgets/comboedit.h \
    ui/widgets/crossbutton.h \
    ui/widgets/delaywidget.h \
    ui/widgets/keyboardbutton.h \
    ui/widgets/mousebutton.h \
    ui/mainwindow.h \
    ui/imagesearchdialog.h \
    interpreter/interpreter.h \
    interpreter/interpreterpy.h \
    interpreter/interpreterwin64.h \
    ui/widgets/shellbutton.h \
    ui/widgets/svgwidget.h \
    xml/clickerdocument.h \
    xml/xmleditor.h \
    xml/xmlstreamer.h \
    #xml/serialisationtest.h
    model/clickermodel.h \
    model/domitem.h \
    model/fancydelegate.h \
    model/simpledelegate.h \
    #model/treeitem.h \
    #model/treemodel.h \
    settings/clickersettings.h

# install

FORMS += \
    tests/cool_tests_form.ui \
    ui/aboutbox.ui \
    ui/areaselectordialog.ui \
    ui/autocompleteeditor.ui \
    ui/coordselector.ui \
    ui/imagesearchdialog.ui \
    ui/mainwindow.ui \
    ui/mousedialog.ui \
    ui/screenbuttonsdetector.ui \
    ui/shelldialog.ui \
    ui/typedialog.ui

RESOURCES += \
    res.qrc

DISTFILES += \
    settings/UsefulClicker.ini \
    tests/UsefulClicker_tests.xml \
    xml/sheme1.xml \
    xml/sheme2.xml
