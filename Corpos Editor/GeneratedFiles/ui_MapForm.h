/********************************************************************************
** Form generated from reading UI file 'MapForm.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPFORM_H
#define UI_MAPFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapForm
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *centralWidget;

    void setupUi(QWidget *MapForm)
    {
        if (MapForm->objectName().isEmpty())
            MapForm->setObjectName(QString::fromUtf8("MapForm"));
        MapForm->resize(400, 300);
        verticalLayout = new QVBoxLayout(MapForm);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        centralWidget = new QWidget(MapForm);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));

        verticalLayout->addWidget(centralWidget);


        retranslateUi(MapForm);

        QMetaObject::connectSlotsByName(MapForm);
    } // setupUi

    void retranslateUi(QWidget *MapForm)
    {
        MapForm->setWindowTitle(QApplication::translate("MapForm", "MapForm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MapForm: public Ui_MapForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPFORM_H
