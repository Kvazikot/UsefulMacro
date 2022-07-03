QT += core gui widgets xml svg
QT += multimedia
QT += multimediawidgets
CONFIG += c++17
QMAKE_CXXFLAGS += /FS /std:c++17 /Zc:__cplusplus
QMAKE_CXXFLAGS +=  -Zc:rvalueCast -Zc:inline -Zc:strictStrings -Zc:throwingNew -permissive- -Zc:externConstexpr -utf-8 -w34100 -w34189 -w44996 -w44456 -w44457 -w44458
#QMAKE_CXXFLAGS += //std:c++17
QMAKE_CXXFLAGS += -v
TARGET = UsefulClicker
UI_DIR = "./ui"
TEMPLATE = app

INCLUDEPATH+="C:\Program Files (x86)\Windows Kits\10\\Include\10.0.19041.0\um"
# Py torch 1.13
LIBS+=-L"C:\\Projects\\pytorch-cpp-master\\libtorch\\lib" -ltorch -ltorch_cpu -lc10 -lkineto
#INCLUDEPATH+="C:\\Projects\\pytorch-cpp-master\\libtorch\\include"
#INCLUDEPATH+="C:\\Projects\\pytorch-cpp-master\\libtorch\\include"
INCLUDEPATH+="C:\Projects\pytorch-cpp-master\utils\image_io\include"
INCLUDEPATH+="C:\Projects\pytorch-cpp-master\extern\stb_image"
INCLUDEPATH+="C:\Projects\pytorch-cpp-master\extern\stb_image_write"
INCLUDEPATH+="C:\Projects\pytorch-cpp-master\extern\stb_image_resize"
INCLUDEPATH+="C:\Projects\pytorch-cpp-master\libtorch\include"
INCLUDEPATH+="C:\Projects\pytorch-cpp-master\libtorch\include\torch\csrc\api\include"

#INCLUDEPATH+="C:\\Projects\\libtorch\\include"

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
INCLUDEPATH+=-L "./interpreter"

LIBS += -luser32 -lgdi32

OPENCV_451_LIB_PATH = C:\\Projects\\opencv_new\\build\\lib\\Release

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_core455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_ml455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_imgproc455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_imgproc455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_features2d455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_features2d455



INCLUDEPATH += $$PWD/../opencv_new/build/include
DEPENDPATH += $$PWD/../opencv_new/build/include

LIBS+=-L$$OPENCV_451_LIB_PATH\\opencv_core455.lib
LIBS+=-L$$OPENCV_451_LIB_PATH -lopencv_ml455
LIBS+=-L$$OPENCV_451_LIB_PATH -lopencv_flann455
LIBS+=-L$$OPENCV_451_LIB_PATH -lopencv_imgproc455
LIBS+=-L$$OPENCV_451_LIB_PATH -lopencv_photo455
LIBS+=-L$$OPENCV_451_LIB_PATH -lopencv_features2d455
LIBS+=-L$$OPENCV_451_LIB_PATH -lopencv_imgcodecs455
LIBS+=-L$$OPENCV_451_LIB_PATH -lopencv_videoio455
LIBS+=-L$$OPENCV_451_LIB_PATH -lopencv_highgui455
LIBS+=-L$$OPENCV_451_LIB_PATH -lopencv_ts455
LIBS+=-L$$OPENCV_451_LIB_PATH -lopencv_calib3d455
LIBS+=-L$$OPENCV_451_LIB_PATH -lopencv_objdetect455
LIBS+=-L$$OPENCV_451_LIB_PATH -lopencv_stitching455
LIBS+=-L$$OPENCV_451_LIB_PATH -lopencv_dnn455
LIBS+=-L$$OPENCV_451_LIB_PATH -lopencv_video455
LIBS+=-L$$OPENCV_451_LIB_PATH -lopencv_shape455

#import os
#path = "C:\\Projects\\opencv_new\\build\\lib\\release"
#for root,d_names,f_names in os.walk(path):
#    for f in f_names:
#        if (".lib" in f) and (".exp" not in f):
#            f=f.replace(".lib","")
#            s= f"win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -l{f}\n"
#            s+= f"else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -l{f}"
#            print(s)

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_aruco455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_aruco455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_barcode455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_barcode455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_bgsegm455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_bgsegm455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_bioinspired455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_bioinspired455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_calib3d455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_calib3d455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_ccalib455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_ccalib455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_core455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_core455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_datasets455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_datasets455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_dnn455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_dnn455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_dnn_objdetect455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_dnn_objdetect455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_dnn_superres455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_dnn_superres455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_dpm455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_dpm455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_face455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_face455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_features2d455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_features2d455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_flann455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_flann455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_fuzzy455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_fuzzy455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_gapi455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_gapi455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_hfs455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_hfs455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_highgui455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_highgui455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_imgcodecs455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_imgcodecs455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_imgproc455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_imgproc455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_img_hash455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_img_hash455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_intensity_transform455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_intensity_transform455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_line_descriptor455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_line_descriptor455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_mcc455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_mcc455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_ml455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_ml455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_objdetect455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_objdetect455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_optflow455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_optflow455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_phase_unwrapping455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_phase_unwrapping455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_photo455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_photo455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_plot455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_plot455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_quality455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_quality455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_rapid455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_rapid455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_reg455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_reg455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_rgbd455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_rgbd455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_saliency455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_saliency455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_shape455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_shape455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_stereo455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_stereo455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_stitching455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_stitching455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_structured_light455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_structured_light455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_superres455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_superres455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_surface_matching455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_surface_matching455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_text455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_text455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_tracking455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_tracking455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_ts455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_ts455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_video455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_video455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_videoio455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_videoio455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_videostab455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_videostab455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_wechat_qrcode455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_wechat_qrcode455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_xfeatures2d455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_xfeatures2d455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_ximgproc455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_ximgproc455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_xobjdetect455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_xobjdetect455
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/release/ -lopencv_xphoto455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../opencv_new/build/lib/debug/ -lopencv_xphoto455
#LIBS+=-L$$PYTHON_PATH\\libs\\ -lpython37
#LIBS+="$$(PYTHON_PATH)\\libs\\python39



SOURCES += main.cpp \
    apocaliptoLib/apocaliptolib.cpp \
    globals.cpp \
    interpreter/expression_calculator.cpp \
    log/logger.cpp \
    tests/cool_tests_form.cpp \
    interpreter/interpreter.cpp \
    interpreter/interpreterpy.cpp \
    interpreter/interpreterwin64.cpp \
    cv/dspmodule.cpp \
    tests/highlighter.cpp \
    tests/torch_test.cpp \
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
    ui/widgets/dimensionswidget.cpp \
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
    apocaliptoLib/apocaliptolib.h \
    cv/rectangle_descriptor.h \
    globals.h \
    interpreter/expression_calculator.h \
    log/logger.h \
    myproxystyle.h \
    tests/cool_tests_form.h \
    cv/dspmodule.h \
    tests/highlighter.h \
    tests/torch_test.h \
    ui/mousedialog.h \
    ui/typedialog.h \
    ui/widgets/dimensionswidget.h \
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
    apocaliptoLib/apocaliptolib.ui \
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
    ui/typedialog.ui \
    ui/widgets/dimensionswidget.ui

RESOURCES += \
    res.qrc

DISTFILES += \
    codegen/codegen_model.qmodel \
    settings/UsefulClicker.ini \
    tests/UsefulClicker_tests.xml \
    xml/sheme1.xml \
    xml/sheme2.xml

QMAKE_EXTRA_TARGETS += before_build makefilehook

makefilehook.target = $(MAKEFILE)
makefilehook.depends = .beforebuild

PRE_TARGETDEPS += .beforebuild


before_build.target = .beforebuild
before_build.depends = FORCE
before_build.commands = chcp 1251

