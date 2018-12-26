/********************************************************************************
** Form generated from reading UI file 'NewMapForms.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWMAPFORMS_H
#define UI_NEWMAPFORMS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewMapForms
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *lineEditMapName;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *spinBoxWidth;
    QLabel *label_2;
    QSpinBox *spinBoxHeight;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonCreate;

    void setupUi(QWidget *NewMapForms)
    {
        if (NewMapForms->objectName().isEmpty())
            NewMapForms->setObjectName(QString::fromUtf8("NewMapForms"));
        NewMapForms->resize(400, 182);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NewMapForms->sizePolicy().hasHeightForWidth());
        NewMapForms->setSizePolicy(sizePolicy);
        NewMapForms->setMinimumSize(QSize(400, 150));
        NewMapForms->setMaximumSize(QSize(400, 182));
        verticalLayout = new QVBoxLayout(NewMapForms);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_2 = new QFrame(NewMapForms);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        lineEditMapName = new QLineEdit(frame_2);
        lineEditMapName->setObjectName(QString::fromUtf8("lineEditMapName"));

        horizontalLayout_2->addWidget(lineEditMapName);


        verticalLayout->addWidget(frame_2);

        frame = new QFrame(NewMapForms);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        spinBoxWidth = new QSpinBox(frame);
        spinBoxWidth->setObjectName(QString::fromUtf8("spinBoxWidth"));
        spinBoxWidth->setMinimum(30);
        spinBoxWidth->setMaximum(500);

        horizontalLayout->addWidget(spinBoxWidth);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        spinBoxHeight = new QSpinBox(frame);
        spinBoxHeight->setObjectName(QString::fromUtf8("spinBoxHeight"));
        spinBoxHeight->setMinimum(30);
        spinBoxHeight->setMaximum(500);

        horizontalLayout->addWidget(spinBoxHeight);


        verticalLayout->addWidget(frame);

        frame_3 = new QFrame(NewMapForms);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButtonCreate = new QPushButton(frame_3);
        pushButtonCreate->setObjectName(QString::fromUtf8("pushButtonCreate"));
        pushButtonCreate->setEnabled(false);

        horizontalLayout_3->addWidget(pushButtonCreate);


        verticalLayout->addWidget(frame_3);


        retranslateUi(NewMapForms);
        QObject::connect(pushButtonCreate, SIGNAL(clicked()), NewMapForms, SLOT(createMap()));
        QObject::connect(lineEditMapName, SIGNAL(textChanged(QString)), NewMapForms, SLOT(validate(QString)));

        QMetaObject::connectSlotsByName(NewMapForms);
    } // setupUi

    void retranslateUi(QWidget *NewMapForms)
    {
        NewMapForms->setWindowTitle(QApplication::translate("NewMapForms", "New map", nullptr));
        label_3->setText(QApplication::translate("NewMapForms", "Map name:", nullptr));
        label->setText(QApplication::translate("NewMapForms", "Width:", nullptr));
        label_2->setText(QApplication::translate("NewMapForms", "Height", nullptr));
        pushButtonCreate->setText(QApplication::translate("NewMapForms", "Create", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewMapForms: public Ui_NewMapForms {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWMAPFORMS_H
