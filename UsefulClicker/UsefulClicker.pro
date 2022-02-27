QT += core gui widgets opengl openglwidgets
QMAKE_CXXFLAGS += -std=c++17
TARGET = cube
TEMPLATE = app
QMAKE_FLAGS_RELEASE += -O3 -msse4.1 -mssse3 -msse3 -msse2 -msse
QMAKE_CXXFLAGS_RELEASE += -O3 -msse4.1 -mssse3 -msse3 -msse2 -msse

OPENCV_451_PATH = "e:\\opencv"
INCLUDEPATH += $$(PYTHON_PATH)\\include
#INCLUDEPATH +=$$OPENCV_451_PATH\\dlib\\dlib\\external\\pybind11\\include\\
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\core\\include"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\build_mingw\\modules"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\build_mingw\\"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\include\\opencv2"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\include\\"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\calib3d\\include\\"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\calib3d\\include"
INCLUDEPATH+=-L "$$OPENCV_451_PATH\\modules\\core\\include"
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

LIBS += -luser32 -lgdi32
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_core453.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_ml453.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_flann453.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_imgproc453.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_photo453.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_features2d453.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_imgcodecs453.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_videoio453.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_highgui453.dll
#LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\" -lopencv_ts453.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_calib3d453.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_objdetect453.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_stitching453.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_dnn453.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_video453.dll
LIBS+=-L$$OPENCV_451_PATH\\build_mingw\\lib\\ -lopencv_shape453.dll

#LIBS+="$$(PYTHON_PATH)\\libs\\python39



SOURCES += main.cpp \
    areaselectordialog.cpp \
    dspmodule.cpp \
    imagesearchdialog.cpp \
    mainwindow.cpp

HEADERS += \
    areaselectordialog.h \
    dspmodule.h \
    imagesearchdialog.h \
    mainwindow.h

# install

FORMS += \
    areaselectordialog.ui \
    imagesearchdialog.ui \
    mainwindow.ui

RESOURCES += \
    res.qrc
