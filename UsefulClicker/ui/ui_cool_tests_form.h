/********************************************************************************
** Form generated from reading UI file 'cool_tests_form.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COOL_TESTS_FORM_H
#define UI_COOL_TESTS_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CoolTestsForm
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *checkBox_2;
    QPushButton *pushButton;
    QPlainTextEdit *plainTextEdit_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *pushButton_7;
    QPushButton *pushButton_6;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QPushButton *typeTest;
    QPushButton *pushButton_3;
    QPushButton *scrollTest;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_4;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox;
    QPlainTextEdit *plainTextEdit;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QPushButton *stopTest;
    QPushButton *runFunction;
    QComboBox *functionsList;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QPushButton *buttonsDetector1;
    QSpinBox *spinBox;
    QPushButton *imageSearch;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_5;
    QPlainTextEdit *xmlEditor;
    QPlainTextEdit *logEdit;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *screen0;
    QRadioButton *screen1;
    QPushButton *areaButton;
    QPushButton *pickPoint;
    QPushButton *shellDialog;
    QGroupBox *buttonsGroup;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_7;
    QPushButton *createTestXml;
    QPushButton *setFunctionTest;
    QLabel *testStatusLabel;

    void setupUi(QDialog *CoolTestsForm)
    {
        if (CoolTestsForm->objectName().isEmpty())
            CoolTestsForm->setObjectName(QString::fromUtf8("CoolTestsForm"));
        CoolTestsForm->setWindowModality(Qt::NonModal);
        CoolTestsForm->resize(856, 877);
        buttonBox = new QDialogButtonBox(CoolTestsForm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(1330, 30, 81, 61));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(CoolTestsForm);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(160, 50, 128, 228));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        checkBox_2 = new QCheckBox(layoutWidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setStyleSheet(QString::fromUtf8("font: 600 12pt \"Segoe UI\";"));

        verticalLayout_2->addWidget(checkBox_2);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        plainTextEdit_2 = new QPlainTextEdit(layoutWidget);
        plainTextEdit_2->setObjectName(QString::fromUtf8("plainTextEdit_2"));
        plainTextEdit_2->setStyleSheet(QString::fromUtf8("background-color: rgb(10, 75, 255);\n"
"color: rgb(255, 255, 255);"));

        verticalLayout_2->addWidget(plainTextEdit_2);

        groupBox = new QGroupBox(CoolTestsForm);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(310, 30, 161, 101));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton_7 = new QPushButton(groupBox);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        gridLayout->addWidget(pushButton_7, 0, 0, 1, 1);

        pushButton_6 = new QPushButton(groupBox);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        gridLayout->addWidget(pushButton_6, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(CoolTestsForm);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(660, 30, 171, 131));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        typeTest = new QPushButton(groupBox_2);
        typeTest->setObjectName(QString::fromUtf8("typeTest"));

        gridLayout_2->addWidget(typeTest, 0, 0, 1, 1);

        pushButton_3 = new QPushButton(groupBox_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout_2->addWidget(pushButton_3, 2, 0, 1, 1);

        scrollTest = new QPushButton(groupBox_2);
        scrollTest->setObjectName(QString::fromUtf8("scrollTest"));

        gridLayout_2->addWidget(scrollTest, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(CoolTestsForm);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(310, 140, 161, 61));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        pushButton_4 = new QPushButton(groupBox_3);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout_3->addWidget(pushButton_4, 0, 0, 1, 1);

        layoutWidget1 = new QWidget(CoolTestsForm);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 50, 125, 228));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        checkBox = new QCheckBox(layoutWidget1);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setStyleSheet(QString::fromUtf8("font: 600 12pt \"Segoe UI\";"));

        verticalLayout->addWidget(checkBox);

        plainTextEdit = new QPlainTextEdit(layoutWidget1);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(10, 75, 255);\n"
"color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(plainTextEdit);

        layoutWidget2 = new QWidget(CoolTestsForm);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(20, 10, 261, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        stopTest = new QPushButton(layoutWidget2);
        stopTest->setObjectName(QString::fromUtf8("stopTest"));

        horizontalLayout->addWidget(stopTest);

        runFunction = new QPushButton(layoutWidget2);
        runFunction->setObjectName(QString::fromUtf8("runFunction"));

        horizontalLayout->addWidget(runFunction);

        functionsList = new QComboBox(layoutWidget2);
        functionsList->addItem(QString());
        functionsList->setObjectName(QString::fromUtf8("functionsList"));

        horizontalLayout->addWidget(functionsList);

        groupBox_4 = new QGroupBox(CoolTestsForm);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(670, 170, 161, 141));
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        buttonsDetector1 = new QPushButton(groupBox_4);
        buttonsDetector1->setObjectName(QString::fromUtf8("buttonsDetector1"));

        gridLayout_4->addWidget(buttonsDetector1, 0, 0, 1, 1);

        spinBox = new QSpinBox(groupBox_4);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMaximum(1000);
        spinBox->setValue(100);

        gridLayout_4->addWidget(spinBox, 2, 0, 1, 1);

        imageSearch = new QPushButton(groupBox_4);
        imageSearch->setObjectName(QString::fromUtf8("imageSearch"));

        gridLayout_4->addWidget(imageSearch, 1, 0, 1, 1);

        groupBox_5 = new QGroupBox(CoolTestsForm);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(20, 300, 821, 561));
        gridLayout_5 = new QGridLayout(groupBox_5);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        xmlEditor = new QPlainTextEdit(groupBox_5);
        xmlEditor->setObjectName(QString::fromUtf8("xmlEditor"));
        xmlEditor->setMaximumSize(QSize(16777215, 11));

        gridLayout_5->addWidget(xmlEditor, 1, 0, 1, 1);

        logEdit = new QPlainTextEdit(groupBox_5);
        logEdit->setObjectName(QString::fromUtf8("logEdit"));
        logEdit->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_5->addWidget(logEdit, 0, 0, 1, 1);

        groupBox_6 = new QGroupBox(CoolTestsForm);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(510, 30, 141, 157));
        gridLayout_6 = new QGridLayout(groupBox_6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        screen0 = new QRadioButton(groupBox_6);
        screen0->setObjectName(QString::fromUtf8("screen0"));
        screen0->setChecked(true);
        screen0->setAutoRepeat(true);

        horizontalLayout_2->addWidget(screen0);

        screen1 = new QRadioButton(groupBox_6);
        screen1->setObjectName(QString::fromUtf8("screen1"));
        screen1->setAutoRepeat(true);

        horizontalLayout_2->addWidget(screen1);


        gridLayout_6->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        areaButton = new QPushButton(groupBox_6);
        areaButton->setObjectName(QString::fromUtf8("areaButton"));

        gridLayout_6->addWidget(areaButton, 1, 0, 1, 1);

        pickPoint = new QPushButton(groupBox_6);
        pickPoint->setObjectName(QString::fromUtf8("pickPoint"));

        gridLayout_6->addWidget(pickPoint, 2, 0, 1, 1);

        shellDialog = new QPushButton(groupBox_6);
        shellDialog->setObjectName(QString::fromUtf8("shellDialog"));

        gridLayout_6->addWidget(shellDialog, 3, 0, 1, 1);

        buttonsGroup = new QGroupBox(CoolTestsForm);
        buttonsGroup->setObjectName(QString::fromUtf8("buttonsGroup"));
        buttonsGroup->setGeometry(QRect(310, 200, 181, 101));
        groupBox_7 = new QGroupBox(CoolTestsForm);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(510, 200, 151, 101));
        gridLayout_7 = new QGridLayout(groupBox_7);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        createTestXml = new QPushButton(groupBox_7);
        createTestXml->setObjectName(QString::fromUtf8("createTestXml"));

        gridLayout_7->addWidget(createTestXml, 0, 0, 1, 1);

        setFunctionTest = new QPushButton(groupBox_7);
        setFunctionTest->setObjectName(QString::fromUtf8("setFunctionTest"));

        gridLayout_7->addWidget(setFunctionTest, 1, 0, 1, 1);

        testStatusLabel = new QLabel(CoolTestsForm);
        testStatusLabel->setObjectName(QString::fromUtf8("testStatusLabel"));
        testStatusLabel->setGeometry(QRect(360, 10, 291, 16));
        testStatusLabel->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 900 9pt \"Segoe UI\";\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(9, 41, 4, 255), stop:0.085 rgba(2, 79, 0, 255), stop:0.19 rgba(50, 147, 22, 255), stop:0.275 rgba(236, 191, 49, 255), stop:0.39 rgba(243, 61, 34, 255), stop:0.555 rgba(135, 81, 60, 255), stop:0.667 rgba(121, 75, 255, 255), stop:0.825 rgba(164, 255, 244, 255), stop:0.885 rgba(104, 222, 71, 255), stop:1 rgba(93, 128, 0, 255));"));
        testStatusLabel->setAlignment(Qt::AlignCenter);

        retranslateUi(CoolTestsForm);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, CoolTestsForm, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, CoolTestsForm, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(CoolTestsForm);
    } // setupUi

    void retranslateUi(QDialog *CoolTestsForm)
    {
        CoolTestsForm->setWindowTitle(QCoreApplication::translate("CoolTestsForm", "UsefulClicker Tests Form", nullptr));
        checkBox_2->setText(QCoreApplication::translate("CoolTestsForm", "Message 2", nullptr));
        pushButton->setText(QCoreApplication::translate("CoolTestsForm", "Generate", nullptr));
        plainTextEdit_2->setPlainText(QCoreApplication::translate("CoolTestsForm", "\320\255\321\202\320\276 \320\277\321\200\320\270\320\274\320\265\321\200 \321\202\320\265\320\272\321\201\321\202\320\260 \320\272\320\276\321\202\320\276\321\200\321\213\320\271 \320\261\321\213\320\273 \321\201\320\263\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\320\275 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\276\320\271 UsefulClicker \321\201\320\265\320\263\320\276\320\264\320\275\321\217.", nullptr));
        groupBox->setTitle(QCoreApplication::translate("CoolTestsForm", "2 Group. Gmail tests", nullptr));
        pushButton_7->setText(QCoreApplication::translate("CoolTestsForm", "Compose Message ", nullptr));
        pushButton_6->setText(QCoreApplication::translate("CoolTestsForm", "Compose Message ", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("CoolTestsForm", "1 Group. Notepad tests", nullptr));
        typeTest->setText(QCoreApplication::translate("CoolTestsForm", " Type test", nullptr));
        pushButton_3->setText(QCoreApplication::translate("CoolTestsForm", "Change font ", nullptr));
        scrollTest->setText(QCoreApplication::translate("CoolTestsForm", "Scroll test", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("CoolTestsForm", "3 Group. Twitter tests", nullptr));
        pushButton_4->setText(QCoreApplication::translate("CoolTestsForm", "Post Twit ", nullptr));
        checkBox->setText(QCoreApplication::translate("CoolTestsForm", "Message 1", nullptr));
        plainTextEdit->setPlainText(QCoreApplication::translate("CoolTestsForm", "\320\255\321\202\320\276 \320\277\321\200\320\270\320\274\320\265\321\200 \321\202\320\265\320\272\321\201\321\202\320\260 \320\272\320\276\321\202\320\276\321\200\321\213\320\271 \320\261\321\213\320\273 \321\201\320\263\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\320\275 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\276\320\271 UsefulClicker \321\201\320\265\320\263\320\276\320\264\320\275\321\217.", nullptr));
        stopTest->setText(QCoreApplication::translate("CoolTestsForm", "STOP TEST", nullptr));
        runFunction->setText(QCoreApplication::translate("CoolTestsForm", "Run Function", nullptr));
        functionsList->setItemText(0, QCoreApplication::translate("CoolTestsForm", "func1", nullptr));

        groupBox_4->setTitle(QCoreApplication::translate("CoolTestsForm", "4 Group. CV tests", nullptr));
        buttonsDetector1->setText(QCoreApplication::translate("CoolTestsForm", "Buttons Detector 1", nullptr));
        spinBox->setPrefix(QCoreApplication::translate("CoolTestsForm", "cannyThreshold = ", nullptr));
        imageSearch->setText(QCoreApplication::translate("CoolTestsForm", "Image Search", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("CoolTestsForm", "Xml editor", nullptr));
        logEdit->setPlainText(QCoreApplication::translate("CoolTestsForm", "x=\"\" y=\"\"", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("CoolTestsForm", "Pick point from screen", nullptr));
        screen0->setText(QCoreApplication::translate("CoolTestsForm", " 0", nullptr));
        screen1->setText(QCoreApplication::translate("CoolTestsForm", "1", nullptr));
        areaButton->setText(QCoreApplication::translate("CoolTestsForm", "Area selector", nullptr));
        pickPoint->setText(QCoreApplication::translate("CoolTestsForm", "Coord selector", nullptr));
        shellDialog->setText(QCoreApplication::translate("CoolTestsForm", "Shell Dialog", nullptr));
        buttonsGroup->setTitle(QCoreApplication::translate("CoolTestsForm", "5. Xml tests", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("CoolTestsForm", "5 Group. Xml Tests", nullptr));
        createTestXml->setText(QCoreApplication::translate("CoolTestsForm", "Create Test Document", nullptr));
        setFunctionTest->setText(QCoreApplication::translate("CoolTestsForm", "SetFunction Test", nullptr));
        testStatusLabel->setText(QCoreApplication::translate("CoolTestsForm", "<html><head/><body><p>SELECT THE TEST</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CoolTestsForm: public Ui_CoolTestsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COOL_TESTS_FORM_H
