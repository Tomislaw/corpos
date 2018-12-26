/********************************************************************************
** Form generated from reading UI file 'OptionsForms.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSFORMS_H
#define UI_OPTIONSFORMS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OptionsForms
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *gameExeLineText;
    QPushButton *browseGameConfButton;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *saveGameConfButton;

    void setupUi(QWidget *OptionsForms)
    {
        if (OptionsForms->objectName().isEmpty())
            OptionsForms->setObjectName(QString::fromUtf8("OptionsForms"));
        OptionsForms->setWindowModality(Qt::NonModal);
        OptionsForms->resize(400, 201);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(OptionsForms->sizePolicy().hasHeightForWidth());
        OptionsForms->setSizePolicy(sizePolicy);
        OptionsForms->setMinimumSize(QSize(400, 201));
        OptionsForms->setMaximumSize(QSize(400, 201));
        OptionsForms->setLayoutDirection(Qt::LeftToRight);
        verticalLayout = new QVBoxLayout(OptionsForms);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        tabWidget = new QTabWidget(OptionsForms);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setAutoFillBackground(false);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        groupBox->setMinimumSize(QSize(261, 70));
        groupBox->setMaximumSize(QSize(16777215, 70));
        groupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        gameExeLineText = new QLineEdit(groupBox);
        gameExeLineText->setObjectName(QString::fromUtf8("gameExeLineText"));

        horizontalLayout_2->addWidget(gameExeLineText);

        browseGameConfButton = new QPushButton(groupBox);
        browseGameConfButton->setObjectName(QString::fromUtf8("browseGameConfButton"));

        horizontalLayout_2->addWidget(browseGameConfButton);


        verticalLayout_2->addWidget(groupBox);

        frame = new QFrame(tab);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        saveGameConfButton = new QPushButton(frame);
        saveGameConfButton->setObjectName(QString::fromUtf8("saveGameConfButton"));
        saveGameConfButton->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout->addWidget(saveGameConfButton);


        verticalLayout_2->addWidget(frame);

        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(OptionsForms);
        QObject::connect(browseGameConfButton, SIGNAL(released()), OptionsForms, SLOT(browseGameExe()));
        QObject::connect(saveGameConfButton, SIGNAL(released()), OptionsForms, SLOT(saveOptions()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(OptionsForms);
    } // setupUi

    void retranslateUi(QWidget *OptionsForms)
    {
        OptionsForms->setWindowTitle(QApplication::translate("OptionsForms", "Options", nullptr));
        groupBox->setTitle(QApplication::translate("OptionsForms", "Game executable folder", nullptr));
        browseGameConfButton->setText(QApplication::translate("OptionsForms", "Browse", nullptr));
        saveGameConfButton->setText(QApplication::translate("OptionsForms", "Save", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("OptionsForms", "Game configurations", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OptionsForms: public Ui_OptionsForms {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSFORMS_H
