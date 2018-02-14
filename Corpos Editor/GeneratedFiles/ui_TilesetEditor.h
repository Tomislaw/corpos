/********************************************************************************
** Form generated from reading UI file 'TilesetEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TILESETEDITOR_H
#define UI_TILESETEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TilesetEditor
{
public:
    QWidget *mainWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_9;
    QGridLayout *gridLayout_5;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *lineEdit_3;
    QToolButton *toolButton;
    QWidget *widget_5;
    QGridLayout *gridLayout_6;
    QSpinBox *spinBox_6;
    QSpinBox *spinBox_7;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_10;
    QLabel *label_9;
    QLineEdit *lineEdit_2;
    QLabel *label_5;
    QPushButton *pushButton_7;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_5;
    QTableWidget *tableWidget_2;
    QFrame *frame_5;
    QGridLayout *gridLayout_4;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboBox_2;
    QLineEdit *lineEdit;
    QSpinBox *spinBox_5;
    QCheckBox *checkBox;
    QLabel *label_4;
    QFrame *frame_4;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_AddTile;
    QPushButton *pushButton_DeleteFile;
    QPushButton *pushButton_DuplicateTile;
    QPushButton *pushButton_ChangeTile;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *tableWidget;
    QFrame *frame_3;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_3;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_8;
    QHBoxLayout *horizontalLayout_6;
    QComboBox *comboBox;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_4;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QGroupBox *groupBox_7;
    QHBoxLayout *horizontalLayout_5;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox_4;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout;
    QCheckBox *checkBox_LeftBottom;
    QCheckBox *checkBox_RightBottom;
    QCheckBox *checkBox_Bottom;
    QCheckBox *checkBox_Left;
    QCheckBox *checkBox_Right;
    QCheckBox *checkBox_RightTop;
    QCheckBox *checkBox_Top;
    QCheckBox *checkBox_LeftTop;
    QFrame *frame;
    QSpacerItem *verticalSpacer;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_6;
    QPushButton *pushButton_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TilesetEditor)
    {
        if (TilesetEditor->objectName().isEmpty())
            TilesetEditor->setObjectName(QStringLiteral("TilesetEditor"));
        TilesetEditor->resize(1067, 1052);
        TilesetEditor->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        mainWidget = new QWidget(TilesetEditor);
        mainWidget->setObjectName(QStringLiteral("mainWidget"));
        mainWidget->setContextMenuPolicy(Qt::DefaultContextMenu);
        mainWidget->setAcceptDrops(false);
        horizontalLayout = new QHBoxLayout(mainWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget = new QWidget(mainWidget);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox_9 = new QGroupBox(widget);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_9->sizePolicy().hasHeightForWidth());
        groupBox_9->setSizePolicy(sizePolicy1);
        gridLayout_5 = new QGridLayout(groupBox_9);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        widget_4 = new QWidget(groupBox_9);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        horizontalLayout_7 = new QHBoxLayout(widget_4);
        horizontalLayout_7->setSpacing(1);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        lineEdit_3 = new QLineEdit(widget_4);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        horizontalLayout_7->addWidget(lineEdit_3);

        toolButton = new QToolButton(widget_4);
        toolButton->setObjectName(QStringLiteral("toolButton"));

        horizontalLayout_7->addWidget(toolButton);


        gridLayout_5->addWidget(widget_4, 2, 1, 1, 1);

        widget_5 = new QWidget(groupBox_9);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        gridLayout_6 = new QGridLayout(widget_5);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setHorizontalSpacing(1);
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        spinBox_6 = new QSpinBox(widget_5);
        spinBox_6->setObjectName(QStringLiteral("spinBox_6"));

        gridLayout_6->addWidget(spinBox_6, 0, 0, 1, 1);

        spinBox_7 = new QSpinBox(widget_5);
        spinBox_7->setObjectName(QStringLiteral("spinBox_7"));

        gridLayout_6->addWidget(spinBox_7, 0, 1, 1, 1);


        gridLayout_5->addWidget(widget_5, 2, 2, 1, 1);

        label_6 = new QLabel(groupBox_9);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_5->addWidget(label_6, 0, 1, 1, 1);

        label_7 = new QLabel(groupBox_9);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_5->addWidget(label_7, 0, 2, 1, 1);

        label_8 = new QLabel(groupBox_9);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_5->addWidget(label_8, 1, 0, 1, 1);

        label_10 = new QLabel(groupBox_9);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_5->addWidget(label_10, 1, 2, 1, 1);

        label_9 = new QLabel(groupBox_9);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_5->addWidget(label_9, 1, 1, 1, 1);

        lineEdit_2 = new QLineEdit(groupBox_9);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout_5->addWidget(lineEdit_2, 2, 0, 1, 1);

        label_5 = new QLabel(groupBox_9);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_5->addWidget(label_5, 0, 0, 1, 1);

        pushButton_7 = new QPushButton(groupBox_9);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        gridLayout_5->addWidget(pushButton_7, 3, 2, 1, 1);


        verticalLayout->addWidget(groupBox_9);

        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        verticalLayout_5 = new QVBoxLayout(groupBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        tableWidget_2 = new QTableWidget(groupBox);
        if (tableWidget_2->columnCount() < 4)
            tableWidget_2->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_2->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget_2->setObjectName(QStringLiteral("tableWidget_2"));
        tableWidget_2->horizontalHeader()->setDefaultSectionSize(100);

        verticalLayout_5->addWidget(tableWidget_2);

        frame_5 = new QFrame(groupBox);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_5);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label = new QLabel(frame_5);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_4->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(frame_5);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_4->addWidget(label_2, 2, 0, 1, 1);

        label_3 = new QLabel(frame_5);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_4->addWidget(label_3, 3, 0, 1, 1);

        comboBox_2 = new QComboBox(frame_5);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        gridLayout_4->addWidget(comboBox_2, 2, 1, 1, 1);

        lineEdit = new QLineEdit(frame_5);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout_4->addWidget(lineEdit, 0, 1, 1, 1);

        spinBox_5 = new QSpinBox(frame_5);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));

        gridLayout_4->addWidget(spinBox_5, 3, 1, 1, 1);

        checkBox = new QCheckBox(frame_5);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout_4->addWidget(checkBox, 4, 1, 1, 1);

        label_4 = new QLabel(frame_5);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_4->addWidget(label_4, 4, 0, 1, 1);


        verticalLayout_5->addWidget(frame_5);

        frame_4 = new QFrame(groupBox);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_4);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        pushButton_AddTile = new QPushButton(frame_4);
        pushButton_AddTile->setObjectName(QStringLiteral("pushButton_AddTile"));

        gridLayout_3->addWidget(pushButton_AddTile, 1, 0, 1, 1);

        pushButton_DeleteFile = new QPushButton(frame_4);
        pushButton_DeleteFile->setObjectName(QStringLiteral("pushButton_DeleteFile"));

        gridLayout_3->addWidget(pushButton_DeleteFile, 2, 1, 1, 1);

        pushButton_DuplicateTile = new QPushButton(frame_4);
        pushButton_DuplicateTile->setObjectName(QStringLiteral("pushButton_DuplicateTile"));

        gridLayout_3->addWidget(pushButton_DuplicateTile, 1, 1, 1, 1);

        pushButton_ChangeTile = new QPushButton(frame_4);
        pushButton_ChangeTile->setObjectName(QStringLiteral("pushButton_ChangeTile"));

        gridLayout_3->addWidget(pushButton_ChangeTile, 2, 0, 1, 1);


        verticalLayout_5->addWidget(frame_4);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy2);
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        tableWidget = new QTableWidget(groupBox_2);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setMaximumSize(QSize(16777215, 16777215));
        tableWidget->setShowGrid(true);
        tableWidget->setSortingEnabled(true);
        tableWidget->horizontalHeader()->setDefaultSectionSize(60);
        tableWidget->horizontalHeader()->setMinimumSectionSize(49);
        tableWidget->verticalHeader()->setMinimumSectionSize(30);

        verticalLayout_4->addWidget(tableWidget);

        frame_3 = new QFrame(groupBox_2);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        pushButton_3 = new QPushButton(frame_3);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout_2->addWidget(pushButton_3, 0, 0, 1, 1);

        pushButton_4 = new QPushButton(frame_3);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout_2->addWidget(pushButton_4, 0, 1, 1, 1);

        pushButton_5 = new QPushButton(frame_3);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout_2->addWidget(pushButton_5, 1, 1, 1, 1);


        verticalLayout_4->addWidget(frame_3);


        verticalLayout->addWidget(groupBox_2);


        horizontalLayout->addWidget(widget);

        widget_2 = new QWidget(mainWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy3);
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_3 = new QGroupBox(widget_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy4);

        verticalLayout_2->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(widget_2);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_4);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        groupBox_8 = new QGroupBox(groupBox_4);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        horizontalLayout_6 = new QHBoxLayout(groupBox_8);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        comboBox = new QComboBox(groupBox_8);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_6->addWidget(comboBox);


        horizontalLayout_3->addWidget(groupBox_8);

        groupBox_5 = new QGroupBox(groupBox_4);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_5);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        spinBox = new QSpinBox(groupBox_5);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        sizePolicy3.setHeightForWidth(spinBox->sizePolicy().hasHeightForWidth());
        spinBox->setSizePolicy(sizePolicy3);

        horizontalLayout_4->addWidget(spinBox);

        spinBox_2 = new QSpinBox(groupBox_5);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));

        horizontalLayout_4->addWidget(spinBox_2);


        horizontalLayout_3->addWidget(groupBox_5);

        groupBox_7 = new QGroupBox(groupBox_4);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        horizontalLayout_5 = new QHBoxLayout(groupBox_7);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        spinBox_3 = new QSpinBox(groupBox_7);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));

        horizontalLayout_5->addWidget(spinBox_3);

        spinBox_4 = new QSpinBox(groupBox_7);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));

        horizontalLayout_5->addWidget(spinBox_4);


        horizontalLayout_3->addWidget(groupBox_7);


        verticalLayout_2->addWidget(groupBox_4);


        horizontalLayout->addWidget(widget_2);

        widget_3 = new QWidget(mainWidget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setMaximumSize(QSize(360, 16777215));
        verticalLayout_3 = new QVBoxLayout(widget_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox_6 = new QGroupBox(widget_3);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setMaximumSize(QSize(350, 300));
        groupBox_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        groupBox_6->setFlat(false);
        groupBox_6->setCheckable(false);
        gridLayout = new QGridLayout(groupBox_6);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
        checkBox_LeftBottom = new QCheckBox(groupBox_6);
        checkBox_LeftBottom->setObjectName(QStringLiteral("checkBox_LeftBottom"));

        gridLayout->addWidget(checkBox_LeftBottom, 2, 0, 1, 1);

        checkBox_RightBottom = new QCheckBox(groupBox_6);
        checkBox_RightBottom->setObjectName(QStringLiteral("checkBox_RightBottom"));

        gridLayout->addWidget(checkBox_RightBottom, 2, 2, 1, 1);

        checkBox_Bottom = new QCheckBox(groupBox_6);
        checkBox_Bottom->setObjectName(QStringLiteral("checkBox_Bottom"));

        gridLayout->addWidget(checkBox_Bottom, 2, 1, 1, 1);

        checkBox_Left = new QCheckBox(groupBox_6);
        checkBox_Left->setObjectName(QStringLiteral("checkBox_Left"));

        gridLayout->addWidget(checkBox_Left, 1, 0, 1, 1);

        checkBox_Right = new QCheckBox(groupBox_6);
        checkBox_Right->setObjectName(QStringLiteral("checkBox_Right"));

        gridLayout->addWidget(checkBox_Right, 1, 2, 1, 1);

        checkBox_RightTop = new QCheckBox(groupBox_6);
        checkBox_RightTop->setObjectName(QStringLiteral("checkBox_RightTop"));

        gridLayout->addWidget(checkBox_RightTop, 0, 2, 1, 1);

        checkBox_Top = new QCheckBox(groupBox_6);
        checkBox_Top->setObjectName(QStringLiteral("checkBox_Top"));

        gridLayout->addWidget(checkBox_Top, 0, 1, 1, 1);

        checkBox_LeftTop = new QCheckBox(groupBox_6);
        checkBox_LeftTop->setObjectName(QStringLiteral("checkBox_LeftTop"));

        gridLayout->addWidget(checkBox_LeftTop, 0, 0, 1, 1);

        frame = new QFrame(groupBox_6);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMinimumSize(QSize(100, 100));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frame, 1, 1, 1, 1);


        verticalLayout_3->addWidget(groupBox_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        frame_2 = new QFrame(widget_3);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton = new QPushButton(frame_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        pushButton_6 = new QPushButton(frame_2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        horizontalLayout_2->addWidget(pushButton_6);

        pushButton_2 = new QPushButton(frame_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);


        verticalLayout_3->addWidget(frame_2);


        horizontalLayout->addWidget(widget_3);

        TilesetEditor->setCentralWidget(mainWidget);
        menuBar = new QMenuBar(TilesetEditor);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1067, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        TilesetEditor->setMenuBar(menuBar);
        mainToolBar = new QToolBar(TilesetEditor);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        TilesetEditor->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(TilesetEditor);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        TilesetEditor->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addSeparator();
        menuFile->addSeparator();

        retranslateUi(TilesetEditor);

        QMetaObject::connectSlotsByName(TilesetEditor);
    } // setupUi

    void retranslateUi(QMainWindow *TilesetEditor)
    {
        TilesetEditor->setWindowTitle(QApplication::translate("TilesetEditor", "Tileset editor", Q_NULLPTR));
        mainWidget->setWindowTitle(QApplication::translate("TilesetEditor", "Tileset editor", Q_NULLPTR));
        groupBox_9->setTitle(QApplication::translate("TilesetEditor", "Tileset", Q_NULLPTR));
        toolButton->setText(QApplication::translate("TilesetEditor", "...", Q_NULLPTR));
        label_6->setText(QApplication::translate("TilesetEditor", "Texture:", Q_NULLPTR));
        label_7->setText(QApplication::translate("TilesetEditor", "Texture size:", Q_NULLPTR));
        label_8->setText(QApplication::translate("TilesetEditor", "none", Q_NULLPTR));
        label_10->setText(QApplication::translate("TilesetEditor", "0,0", Q_NULLPTR));
        label_9->setText(QApplication::translate("TilesetEditor", "none", Q_NULLPTR));
        label_5->setText(QApplication::translate("TilesetEditor", "Name:", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("TilesetEditor", "Change", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("TilesetEditor", "Tile", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_2->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("TilesetEditor", "Name", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_2->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("TilesetEditor", "Type", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_2->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("TilesetEditor", "Health", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_2->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("TilesetEditor", "SingleImage", Q_NULLPTR));
        label->setText(QApplication::translate("TilesetEditor", "Name: ", Q_NULLPTR));
        label_2->setText(QApplication::translate("TilesetEditor", "Type:", Q_NULLPTR));
        label_3->setText(QApplication::translate("TilesetEditor", "Health:", Q_NULLPTR));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("TilesetEditor", "tile", Q_NULLPTR)
         << QApplication::translate("TilesetEditor", "background", Q_NULLPTR)
         << QApplication::translate("TilesetEditor", "ladder", Q_NULLPTR)
        );
        checkBox->setText(QString());
        label_4->setText(QApplication::translate("TilesetEditor", "SingleImage:", Q_NULLPTR));
        pushButton_AddTile->setText(QApplication::translate("TilesetEditor", "Add", Q_NULLPTR));
        pushButton_DeleteFile->setText(QApplication::translate("TilesetEditor", "Delete", Q_NULLPTR));
        pushButton_DuplicateTile->setText(QApplication::translate("TilesetEditor", "Duplicate", Q_NULLPTR));
        pushButton_ChangeTile->setText(QApplication::translate("TilesetEditor", "Change", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("TilesetEditor", "Tile grid", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QApplication::translate("TilesetEditor", "Type", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QApplication::translate("TilesetEditor", "Position", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QApplication::translate("TilesetEditor", "Size", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("TilesetEditor", "Add", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("TilesetEditor", "Duplicate", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("TilesetEditor", "Delete", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("TilesetEditor", "Texture view", Q_NULLPTR));
        groupBox_4->setTitle(QString());
        groupBox_8->setTitle(QApplication::translate("TilesetEditor", "Type", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("TilesetEditor", "top-left", Q_NULLPTR)
         << QApplication::translate("TilesetEditor", "top", Q_NULLPTR)
         << QApplication::translate("TilesetEditor", "top-right", Q_NULLPTR)
         << QApplication::translate("TilesetEditor", "left", Q_NULLPTR)
         << QApplication::translate("TilesetEditor", "inner", Q_NULLPTR)
         << QApplication::translate("TilesetEditor", "right", Q_NULLPTR)
         << QApplication::translate("TilesetEditor", "bottom-left", Q_NULLPTR)
         << QApplication::translate("TilesetEditor", "bottom", Q_NULLPTR)
         << QApplication::translate("TilesetEditor", "bottom-right", Q_NULLPTR)
        );
        groupBox_5->setTitle(QApplication::translate("TilesetEditor", "Position", Q_NULLPTR));
        groupBox_7->setTitle(QApplication::translate("TilesetEditor", "Size", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("TilesetEditor", "Tile view", Q_NULLPTR));
        checkBox_LeftBottom->setText(QApplication::translate("TilesetEditor", "Left, Bottom", Q_NULLPTR));
        checkBox_RightBottom->setText(QApplication::translate("TilesetEditor", "Right, Bottom", Q_NULLPTR));
        checkBox_Bottom->setText(QApplication::translate("TilesetEditor", "Bottom", Q_NULLPTR));
        checkBox_Left->setText(QApplication::translate("TilesetEditor", "Left", Q_NULLPTR));
        checkBox_Right->setText(QApplication::translate("TilesetEditor", "Right", Q_NULLPTR));
        checkBox_RightTop->setText(QApplication::translate("TilesetEditor", "Right, Top", Q_NULLPTR));
        checkBox_Top->setText(QApplication::translate("TilesetEditor", "Top", Q_NULLPTR));
        checkBox_LeftTop->setText(QApplication::translate("TilesetEditor", "Left, Top", Q_NULLPTR));
        pushButton->setText(QApplication::translate("TilesetEditor", "Save", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("TilesetEditor", "Save as", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("TilesetEditor", "Cancel", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("TilesetEditor", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TilesetEditor: public Ui_TilesetEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TILESETEDITOR_H
