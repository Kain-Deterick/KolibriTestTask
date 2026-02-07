/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *Setting;
    QHBoxLayout *Settings;
    QVBoxLayout *QLabels;
    QLabel *maskText;
    QLabel *workDirText;
    QLabel *outputDirText;
    QLabel *xorText;
    QVBoxLayout *inputFields;
    QLineEdit *mask;
    QLineEdit *workDir;
    QLineEdit *outputDir;
    QLineEdit *xorValue;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *chooseWorkDir;
    QPushButton *chooseOutputDir;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *overWriteValue;
    QCheckBox *fileDeleteValue;
    QCheckBox *periodMode;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpinBox *surveyTime;
    QLabel *label_3;
    QListWidget *listWidget;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *Start;
    QPushButton *Stop;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1250, 600);
        MainWindow->setMinimumSize(QSize(1250, 600));
        MainWindow->setMaximumSize(QSize(1250, 800));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        Setting = new QWidget(centralwidget);
        Setting->setObjectName("Setting");
        Setting->setGeometry(QRect(20, 20, 1201, 151));
        Settings = new QHBoxLayout(Setting);
        Settings->setSpacing(2);
        Settings->setObjectName("Settings");
        Settings->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        QLabels = new QVBoxLayout();
        QLabels->setSpacing(5);
        QLabels->setObjectName("QLabels");
        QLabels->setContentsMargins(3, 0, 3, 0);
        maskText = new QLabel(Setting);
        maskText->setObjectName("maskText");

        QLabels->addWidget(maskText);

        workDirText = new QLabel(Setting);
        workDirText->setObjectName("workDirText");

        QLabels->addWidget(workDirText);

        outputDirText = new QLabel(Setting);
        outputDirText->setObjectName("outputDirText");

        QLabels->addWidget(outputDirText);

        xorText = new QLabel(Setting);
        xorText->setObjectName("xorText");

        QLabels->addWidget(xorText);


        Settings->addLayout(QLabels);

        inputFields = new QVBoxLayout();
        inputFields->setObjectName("inputFields");
        inputFields->setContentsMargins(0, 0, 0, 0);
        mask = new QLineEdit(Setting);
        mask->setObjectName("mask");

        inputFields->addWidget(mask);

        workDir = new QLineEdit(Setting);
        workDir->setObjectName("workDir");

        inputFields->addWidget(workDir);

        outputDir = new QLineEdit(Setting);
        outputDir->setObjectName("outputDir");

        inputFields->addWidget(outputDir);

        xorValue = new QLineEdit(Setting);
        xorValue->setObjectName("xorValue");

        inputFields->addWidget(xorValue);


        Settings->addLayout(inputFields);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(Setting);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        chooseWorkDir = new QPushButton(Setting);
        chooseWorkDir->setObjectName("chooseWorkDir");

        verticalLayout->addWidget(chooseWorkDir);

        chooseOutputDir = new QPushButton(Setting);
        chooseOutputDir->setObjectName("chooseOutputDir");

        verticalLayout->addWidget(chooseOutputDir);

        label_4 = new QLabel(Setting);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);


        Settings->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        overWriteValue = new QCheckBox(Setting);
        overWriteValue->setObjectName("overWriteValue");

        verticalLayout_2->addWidget(overWriteValue);

        fileDeleteValue = new QCheckBox(Setting);
        fileDeleteValue->setObjectName("fileDeleteValue");

        verticalLayout_2->addWidget(fileDeleteValue);

        periodMode = new QCheckBox(Setting);
        periodMode->setObjectName("periodMode");

        verticalLayout_2->addWidget(periodMode);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_2 = new QLabel(Setting);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        surveyTime = new QSpinBox(Setting);
        surveyTime->setObjectName("surveyTime");
        surveyTime->setMinimumSize(QSize(104, 0));
        surveyTime->setMinimum(1000);
        surveyTime->setMaximum(999999999);

        horizontalLayout->addWidget(surveyTime);

        label_3 = new QLabel(Setting);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);


        verticalLayout_2->addLayout(horizontalLayout);


        Settings->addLayout(verticalLayout_2);

        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(20, 180, 971, 331));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(1000, 180, 221, 331));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        Start = new QPushButton(verticalLayoutWidget_2);
        Start->setObjectName("Start");

        horizontalLayout_3->addWidget(Start);

        Stop = new QPushButton(verticalLayoutWidget_2);
        Stop->setObjectName("Stop");

        horizontalLayout_3->addWidget(Stop);


        verticalLayout_3->addLayout(horizontalLayout_3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1250, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        maskText->setText(QCoreApplication::translate("MainWindow", "\320\234\320\260\321\201\320\272\320\260 \320\262\321\205\320\276\320\264\320\275\321\213\321\205 \321\204\320\260\320\271\320\273\320\276\320\262:", nullptr));
        workDirText->setText(QCoreApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \321\200\320\260\320\261\320\276\321\207\320\265\320\271 \320\264\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\320\270:", nullptr));
        outputDirText->setText(QCoreApplication::translate("MainWindow", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\217 \320\264\320\273\321\217 \321\201\320\276\321\205\321\200\320\260\320\275\320\265\320\275\320\270\321\217 \321\200\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\320\276\320\262:", nullptr));
        xorText->setText(QCoreApplication::translate("MainWindow", "XOR \320\267\320\275\320\260\321\207\320\265\320\275\320\270\320\265:", nullptr));
        mask->setPlaceholderText(QCoreApplication::translate("MainWindow", ".txt, test.bin", nullptr));
        label->setText(QString());
        chooseWorkDir->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\277\320\260\320\277\320\272\321\203", nullptr));
        chooseOutputDir->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\277\320\260\320\277\320\272\321\203", nullptr));
        label_4->setText(QString());
        overWriteValue->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\267\320\260\320\277\320\270\321\201\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", nullptr));
        fileDeleteValue->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\265\320\275\320\270\320\265 \320\270\321\201\321\205\320\276\320\264\320\275\320\276\320\263\320\276 \321\204\320\260\320\271\320\273\320\260", nullptr));
        periodMode->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\261\320\276\321\202\320\260 \320\277\320\276 \321\202\320\260\320\271\320\274\320\265\321\200\321\203", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\274\321\201", nullptr));
        Start->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        Stop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
