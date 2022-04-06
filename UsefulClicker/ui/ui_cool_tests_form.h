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
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
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
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_4;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QCheckBox *checkBox;
    QPlainTextEdit *plainTextEdit;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_5;
    QComboBox *comboBox;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QPushButton *buttonsDetector1;
    QPushButton *pushButton_9;

    void setupUi(QDialog *CoolTestsForm)
    {
        if (CoolTestsForm->objectName().isEmpty())
            CoolTestsForm->setObjectName(QString::fromUtf8("CoolTestsForm"));
        CoolTestsForm->setWindowModality(Qt::NonModal);
        CoolTestsForm->resize(1451, 912);
        buttonBox = new QDialogButtonBox(CoolTestsForm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(1330, 30, 81, 61));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        layoutWidget = new QWidget(CoolTestsForm);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(160, 210, 121, 228));
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
        groupBox->setGeometry(QRect(320, 280, 161, 101));
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
        groupBox_2->setGeometry(QRect(320, 170, 160, 97));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout_2->addWidget(pushButton_2, 0, 0, 1, 1);

        pushButton_3 = new QPushButton(groupBox_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout_2->addWidget(pushButton_3, 1, 0, 1, 1);

        groupBox_3 = new QGroupBox(CoolTestsForm);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(500, 170, 161, 91));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        pushButton_4 = new QPushButton(groupBox_3);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

        gridLayout_3->addWidget(pushButton_4, 0, 0, 1, 1);

        layoutWidget1 = new QWidget(CoolTestsForm);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 210, 121, 228));
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
        layoutWidget2->setGeometry(QRect(20, 170, 261, 26));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_5 = new QPushButton(layoutWidget2);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        horizontalLayout->addWidget(pushButton_5);

        comboBox = new QComboBox(layoutWidget2);
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        groupBox_4 = new QGroupBox(CoolTestsForm);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(690, 170, 160, 97));
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        buttonsDetector1 = new QPushButton(groupBox_4);
        buttonsDetector1->setObjectName(QString::fromUtf8("buttonsDetector1"));

        gridLayout_4->addWidget(buttonsDetector1, 0, 0, 1, 1);

        pushButton_9 = new QPushButton(groupBox_4);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));

        gridLayout_4->addWidget(pushButton_9, 1, 0, 1, 1);


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
        pushButton_2->setText(QCoreApplication::translate("CoolTestsForm", " Type test", nullptr));
        pushButton_3->setText(QCoreApplication::translate("CoolTestsForm", "Change font ", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("CoolTestsForm", "3 Group. Twitter tests", nullptr));
        pushButton_4->setText(QCoreApplication::translate("CoolTestsForm", "Post Twit ", nullptr));
        checkBox->setText(QCoreApplication::translate("CoolTestsForm", "Message 1", nullptr));
        plainTextEdit->setPlainText(QCoreApplication::translate("CoolTestsForm", "\320\255\321\202\320\276 \320\277\321\200\320\270\320\274\320\265\321\200 \321\202\320\265\320\272\321\201\321\202\320\260 \320\272\320\276\321\202\320\276\321\200\321\213\320\271 \320\261\321\213\320\273 \321\201\320\263\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\320\275 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\276\320\271 UsefulClicker \321\201\320\265\320\263\320\276\320\264\320\275\321\217.", nullptr));
        pushButton_5->setText(QCoreApplication::translate("CoolTestsForm", "Run Function", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("CoolTestsForm", "func1", nullptr));

        groupBox_4->setTitle(QCoreApplication::translate("CoolTestsForm", "4 Group. CV tests", nullptr));
        buttonsDetector1->setText(QCoreApplication::translate("CoolTestsForm", "Buttons Detector 1", nullptr));
        pushButton_9->setText(QCoreApplication::translate("CoolTestsForm", "Change font ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CoolTestsForm: public Ui_CoolTestsForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COOL_TESTS_FORM_H
