/********************************************************************************
** Form generated from reading UI file 'NewMapForms.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWMAPFORMS_H
#define UI_NEWMAPFORMS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            NewMapForms->setObjectName(QStringLiteral("NewMapForms"));
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
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame_2 = new QFrame(NewMapForms);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        lineEditMapName = new QLineEdit(frame_2);
        lineEditMapName->setObjectName(QStringLiteral("lineEditMapName"));

        horizontalLayout_2->addWidget(lineEditMapName);


        verticalLayout->addWidget(frame_2);

        frame = new QFrame(NewMapForms);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        spinBoxWidth = new QSpinBox(frame);
        spinBoxWidth->setObjectName(QStringLiteral("spinBoxWidth"));
        spinBoxWidth->setMinimum(30);
        spinBoxWidth->setMaximum(500);

        horizontalLayout->addWidget(spinBoxWidth);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        spinBoxHeight = new QSpinBox(frame);
        spinBoxHeight->setObjectName(QStringLiteral("spinBoxHeight"));
        spinBoxHeight->setMinimum(30);
        spinBoxHeight->setMaximum(500);

        horizontalLayout->addWidget(spinBoxHeight);


        verticalLayout->addWidget(frame);

        frame_3 = new QFrame(NewMapForms);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButtonCreate = new QPushButton(frame_3);
        pushButtonCreate->setObjectName(QStringLiteral("pushButtonCreate"));
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
        NewMapForms->setWindowTitle(QApplication::translate("NewMapForms", "New map", Q_NULLPTR));
        label_3->setText(QApplication::translate("NewMapForms", "Map name:", Q_NULLPTR));
        label->setText(QApplication::translate("NewMapForms", "Width:", Q_NULLPTR));
        label_2->setText(QApplication::translate("NewMapForms", "Height", Q_NULLPTR));
        pushButtonCreate->setText(QApplication::translate("NewMapForms", "Create", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NewMapForms: public Ui_NewMapForms {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWMAPFORMS_H
