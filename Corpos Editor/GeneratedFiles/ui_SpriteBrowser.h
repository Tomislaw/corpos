/********************************************************************************
** Form generated from reading UI file 'SpriteBrowser.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPRITEBROWSER_H
#define UI_SPRITEBROWSER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpriteBrowser
{
public:
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout;
    QListWidget *listSprites;
    QLineEdit *lineFilter;
    QFrame *frame;
    QVBoxLayout *verticalLayout_6;
    QSplitter *splitter_3;
    QSplitter *splitter_2;
    QWidget *widgetSFML;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_4;
    QListWidget *listAnimations;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout;
    QPushButton *buttonStart;
    QPushButton *buttonStop;
    QSlider *sliderFrame;
    QPushButton *buttonSetSpeed;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_7;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *labelAnimationInfo;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_3;
    QSlider *sliderSize;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_10;
    QCheckBox *checkBox;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *SpriteBrowser)
    {
        if (SpriteBrowser->objectName().isEmpty())
            SpriteBrowser->setObjectName(QString::fromUtf8("SpriteBrowser"));
        SpriteBrowser->setWindowModality(Qt::NonModal);
        SpriteBrowser->resize(882, 556);
        SpriteBrowser->setContextMenuPolicy(Qt::DefaultContextMenu);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/CorposEditor/Resources/icons/spriteBrowser.png"), QSize(), QIcon::Normal, QIcon::Off);
        SpriteBrowser->setWindowIcon(icon);
        verticalLayout_3 = new QVBoxLayout(SpriteBrowser);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        splitter = new QSplitter(SpriteBrowser);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setFrameShape(QFrame::NoFrame);
        splitter->setOrientation(Qt::Horizontal);
        splitter->setHandleWidth(10);
        splitter->setChildrenCollapsible(true);
        frame_2 = new QFrame(splitter);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Sunken);
        frame_2->setLineWidth(2);
        frame_2->setMidLineWidth(1);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_4 = new QGroupBox(frame_2);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout = new QVBoxLayout(groupBox_4);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listSprites = new QListWidget(groupBox_4);
        listSprites->setObjectName(QString::fromUtf8("listSprites"));

        verticalLayout->addWidget(listSprites);

        lineFilter = new QLineEdit(groupBox_4);
        lineFilter->setObjectName(QString::fromUtf8("lineFilter"));

        verticalLayout->addWidget(lineFilter);


        verticalLayout_2->addWidget(groupBox_4);

        splitter->addWidget(frame_2);
        frame = new QFrame(splitter);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        frame->setLineWidth(2);
        frame->setMidLineWidth(1);
        verticalLayout_6 = new QVBoxLayout(frame);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        splitter_3 = new QSplitter(frame);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Vertical);
        splitter_2 = new QSplitter(splitter_3);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        widgetSFML = new QWidget(splitter_2);
        widgetSFML->setObjectName(QString::fromUtf8("widgetSFML"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetSFML->sizePolicy().hasHeightForWidth());
        widgetSFML->setSizePolicy(sizePolicy);
        widgetSFML->setMinimumSize(QSize(400, 400));
        widgetSFML->setBaseSize(QSize(0, 0));
        verticalLayout_8 = new QVBoxLayout(widgetSFML);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        splitter_2->addWidget(widgetSFML);
        groupBox = new QGroupBox(splitter_2);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_4 = new QVBoxLayout(groupBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        listAnimations = new QListWidget(groupBox);
        listAnimations->setObjectName(QString::fromUtf8("listAnimations"));

        verticalLayout_4->addWidget(listAnimations);

        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout = new QGridLayout(groupBox_3);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonStart = new QPushButton(groupBox_3);
        buttonStart->setObjectName(QString::fromUtf8("buttonStart"));

        gridLayout->addWidget(buttonStart, 1, 0, 1, 1);

        buttonStop = new QPushButton(groupBox_3);
        buttonStop->setObjectName(QString::fromUtf8("buttonStop"));

        gridLayout->addWidget(buttonStop, 1, 1, 1, 1);

        sliderFrame = new QSlider(groupBox_3);
        sliderFrame->setObjectName(QString::fromUtf8("sliderFrame"));
        sliderFrame->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(sliderFrame, 0, 0, 1, 1);

        buttonSetSpeed = new QPushButton(groupBox_3);
        buttonSetSpeed->setObjectName(QString::fromUtf8("buttonSetSpeed"));

        gridLayout->addWidget(buttonSetSpeed, 0, 1, 1, 1);


        verticalLayout_4->addWidget(groupBox_3);

        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_7 = new QVBoxLayout(groupBox_2);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        scrollArea_2 = new QScrollArea(groupBox_2);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 191, 85));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        labelAnimationInfo = new QLabel(scrollAreaWidgetContents_2);
        labelAnimationInfo->setObjectName(QString::fromUtf8("labelAnimationInfo"));

        verticalLayout_5->addWidget(labelAnimationInfo);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_7->addWidget(scrollArea_2);


        verticalLayout_4->addWidget(groupBox_2);

        splitter_2->addWidget(groupBox);
        splitter_3->addWidget(splitter_2);

        verticalLayout_6->addWidget(splitter_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox_5 = new QGroupBox(frame);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_5);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        sliderSize = new QSlider(groupBox_5);
        sliderSize->setObjectName(QString::fromUtf8("sliderSize"));
        sliderSize->setValue(50);
        sliderSize->setOrientation(Qt::Horizontal);
        sliderSize->setInvertedAppearance(false);
        sliderSize->setInvertedControls(false);

        horizontalLayout_3->addWidget(sliderSize);


        horizontalLayout->addWidget(groupBox_5);

        groupBox_6 = new QGroupBox(frame);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setMinimumSize(QSize(250, 0));
        verticalLayout_10 = new QVBoxLayout(groupBox_6);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        checkBox = new QCheckBox(groupBox_6);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout_10->addWidget(checkBox);


        horizontalLayout->addWidget(groupBox_6);


        verticalLayout_6->addLayout(horizontalLayout);

        splitter->addWidget(frame);

        verticalLayout_3->addWidget(splitter);

        frame_3 = new QFrame(SpriteBrowser);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setMaximumSize(QSize(16777215, 35));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 1, -1, 1);
        horizontalSpacer = new QSpacerItem(873, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(frame_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout_3->addWidget(frame_3);


        retranslateUi(SpriteBrowser);
        QObject::connect(lineFilter, SIGNAL(textChanged(QString)), SpriteBrowser, SLOT(filterChanged(QString)));
        QObject::connect(listSprites, SIGNAL(currentRowChanged(int)), SpriteBrowser, SLOT(spriteSelected(int)));
        QObject::connect(listAnimations, SIGNAL(currentRowChanged(int)), SpriteBrowser, SLOT(animationSelected(int)));
        QObject::connect(buttonStart, SIGNAL(released()), SpriteBrowser, SLOT(timerStart()));
        QObject::connect(buttonStop, SIGNAL(released()), SpriteBrowser, SLOT(timerStop()));
        QObject::connect(sliderFrame, SIGNAL(valueChanged(int)), SpriteBrowser, SLOT(sliderChanged(int)));
        QObject::connect(splitter_2, SIGNAL(splitterMoved(int,int)), SpriteBrowser, SLOT(onResize()));
        QObject::connect(splitter_3, SIGNAL(splitterMoved(int,int)), SpriteBrowser, SLOT(onResize()));
        QObject::connect(splitter, SIGNAL(splitterMoved(int,int)), SpriteBrowser, SLOT(onResize()));
        QObject::connect(sliderSize, SIGNAL(valueChanged(int)), SpriteBrowser, SLOT(sizeSliderChanged(int)));
        QObject::connect(buttonSetSpeed, SIGNAL(released()), SpriteBrowser, SLOT(animationSpeedChanged()));

        QMetaObject::connectSlotsByName(SpriteBrowser);
    } // setupUi

    void retranslateUi(QWidget *SpriteBrowser)
    {
        SpriteBrowser->setWindowTitle(QApplication::translate("SpriteBrowser", "Sprite browser", nullptr));
        groupBox_4->setTitle(QApplication::translate("SpriteBrowser", "Filter", nullptr));
        groupBox->setTitle(QApplication::translate("SpriteBrowser", "Animations", nullptr));
        groupBox_3->setTitle(QString());
        buttonStart->setText(QApplication::translate("SpriteBrowser", "Start", nullptr));
        buttonStop->setText(QApplication::translate("SpriteBrowser", "Stop", nullptr));
        buttonSetSpeed->setText(QApplication::translate("SpriteBrowser", "x1", nullptr));
        groupBox_2->setTitle(QApplication::translate("SpriteBrowser", "Info", nullptr));
        labelAnimationInfo->setText(QApplication::translate("SpriteBrowser", "<<info>>", nullptr));
        groupBox_5->setTitle(QApplication::translate("SpriteBrowser", "Size", nullptr));
        groupBox_6->setTitle(QApplication::translate("SpriteBrowser", "Other", nullptr));
        checkBox->setText(QApplication::translate("SpriteBrowser", "Bounding box", nullptr));
        pushButton->setText(QApplication::translate("SpriteBrowser", "Ok", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SpriteBrowser: public Ui_SpriteBrowser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPRITEBROWSER_H
