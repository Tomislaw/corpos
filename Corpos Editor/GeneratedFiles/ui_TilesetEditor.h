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
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TilesetEditor
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionClose;
    QAction *actionSave;
    QWidget *mainWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_5;
    QTreeWidget *treeWidget_Tiles;
    QFrame *frame_5;
    QGridLayout *gridLayout_4;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QLabel *label_4;
    QCheckBox *checkBox;
    QLineEdit *lineEdit;
    QSpinBox *spinBox_5;
    QLabel *label_8;
    QLineEdit *lineEdit_4;
    QFrame *frame_4;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_AddTile;
    QPushButton *pushButton_DeleteFile;
    QPushButton *pushButton_DuplicateTile;
    QPushButton *pushButton_ChangeTile;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QTreeWidget *treeWidget_tilesGrid;
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
    QLabel *label_7;
    QLabel *label_Texturesize;
    QLabel *label_Texture;
    QLabel *label_Name;
    QLabel *label_6;
    QPushButton *pushButton_7;
    QLabel *label_5;
    QLineEdit *lineEdit_2;
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
    QFrame *frameTileView;
    QSpacerItem *verticalSpacer;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TilesetEditor)
    {
        if (TilesetEditor->objectName().isEmpty())
            TilesetEditor->setObjectName(QStringLiteral("TilesetEditor"));
        TilesetEditor->resize(1067, 1107);
        QIcon icon;
        icon.addFile(QStringLiteral(":/CorposEditor/Resources/icons/tilesetEditor.png"), QSize(), QIcon::Normal, QIcon::Off);
        TilesetEditor->setWindowIcon(icon);
        TilesetEditor->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        actionNew = new QAction(TilesetEditor);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/CorposEditor/Resources/icons/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon1);
        actionOpen = new QAction(TilesetEditor);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/CorposEditor/Resources/icons/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon2);
        actionClose = new QAction(TilesetEditor);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionSave = new QAction(TilesetEditor);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/CorposEditor/Resources/icons/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon3);
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
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        verticalLayout_5 = new QVBoxLayout(groupBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        treeWidget_Tiles = new QTreeWidget(groupBox);
        treeWidget_Tiles->setObjectName(QStringLiteral("treeWidget_Tiles"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(treeWidget_Tiles->sizePolicy().hasHeightForWidth());
        treeWidget_Tiles->setSizePolicy(sizePolicy1);
        treeWidget_Tiles->header()->setDefaultSectionSize(70);

        verticalLayout_5->addWidget(treeWidget_Tiles);

        frame_5 = new QFrame(groupBox);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_5);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_3 = new QLabel(frame_5);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_4->addWidget(label_3, 4, 0, 1, 1);

        label = new QLabel(frame_5);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_4->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(frame_5);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_4->addWidget(label_2, 2, 0, 1, 1);

        comboBox_2 = new QComboBox(frame_5);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        gridLayout_4->addWidget(comboBox_2, 2, 1, 1, 1);

        label_4 = new QLabel(frame_5);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_4->addWidget(label_4, 5, 0, 1, 1);

        checkBox = new QCheckBox(frame_5);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        gridLayout_4->addWidget(checkBox, 5, 1, 1, 1);

        lineEdit = new QLineEdit(frame_5);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout_4->addWidget(lineEdit, 0, 1, 1, 1);

        spinBox_5 = new QSpinBox(frame_5);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));

        gridLayout_4->addWidget(spinBox_5, 4, 1, 1, 1);

        label_8 = new QLabel(frame_5);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_4->addWidget(label_8, 3, 0, 1, 1);

        lineEdit_4 = new QLineEdit(frame_5);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        gridLayout_4->addWidget(lineEdit_4, 3, 1, 1, 1);


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
        treeWidget_tilesGrid = new QTreeWidget(groupBox_2);
        treeWidget_tilesGrid->setObjectName(QStringLiteral("treeWidget_tilesGrid"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(treeWidget_tilesGrid->sizePolicy().hasHeightForWidth());
        treeWidget_tilesGrid->setSizePolicy(sizePolicy3);
        treeWidget_tilesGrid->header()->setDefaultSectionSize(70);

        verticalLayout_4->addWidget(treeWidget_tilesGrid);

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
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy4);
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_3 = new QGroupBox(widget_2);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);

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
        sizePolicy4.setHeightForWidth(spinBox->sizePolicy().hasHeightForWidth());
        spinBox->setSizePolicy(sizePolicy4);

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
        groupBox_9 = new QGroupBox(widget_3);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        QSizePolicy sizePolicy5(QSizePolicy::Ignored, QSizePolicy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(groupBox_9->sizePolicy().hasHeightForWidth());
        groupBox_9->setSizePolicy(sizePolicy5);
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


        gridLayout_5->addWidget(widget_4, 4, 1, 1, 1);

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


        gridLayout_5->addWidget(widget_5, 4, 2, 1, 1);

        label_7 = new QLabel(groupBox_9);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_5->addWidget(label_7, 0, 2, 1, 1);

        label_Texturesize = new QLabel(groupBox_9);
        label_Texturesize->setObjectName(QStringLiteral("label_Texturesize"));

        gridLayout_5->addWidget(label_Texturesize, 3, 2, 1, 1);

        label_Texture = new QLabel(groupBox_9);
        label_Texture->setObjectName(QStringLiteral("label_Texture"));

        gridLayout_5->addWidget(label_Texture, 3, 1, 1, 1);

        label_Name = new QLabel(groupBox_9);
        label_Name->setObjectName(QStringLiteral("label_Name"));

        gridLayout_5->addWidget(label_Name, 3, 0, 1, 1);

        label_6 = new QLabel(groupBox_9);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_5->addWidget(label_6, 0, 1, 1, 1);

        pushButton_7 = new QPushButton(groupBox_9);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        gridLayout_5->addWidget(pushButton_7, 5, 2, 1, 1);

        label_5 = new QLabel(groupBox_9);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_5->addWidget(label_5, 0, 0, 1, 1);

        lineEdit_2 = new QLineEdit(groupBox_9);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout_5->addWidget(lineEdit_2, 4, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_9);

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

        frameTileView = new QFrame(groupBox_6);
        frameTileView->setObjectName(QStringLiteral("frameTileView"));
        frameTileView->setMinimumSize(QSize(100, 100));
        frameTileView->setFrameShape(QFrame::Box);
        frameTileView->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frameTileView, 1, 1, 1, 1);


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
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave);

        retranslateUi(TilesetEditor);
        QObject::connect(actionOpen, SIGNAL(triggered()), TilesetEditor, SLOT(loadTileset()));
        QObject::connect(treeWidget_Tiles, SIGNAL(itemPressed(QTreeWidgetItem*,int)), TilesetEditor, SLOT(loadTileGrid(QTreeWidgetItem*,int)));

        QMetaObject::connectSlotsByName(TilesetEditor);
    } // setupUi

    void retranslateUi(QMainWindow *TilesetEditor)
    {
        TilesetEditor->setWindowTitle(QApplication::translate("TilesetEditor", "Tileset editor", Q_NULLPTR));
        actionNew->setText(QApplication::translate("TilesetEditor", "New", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("TilesetEditor", "Open", Q_NULLPTR));
        actionClose->setText(QApplication::translate("TilesetEditor", "Exit", Q_NULLPTR));
        actionSave->setText(QApplication::translate("TilesetEditor", "Save", Q_NULLPTR));
        mainWidget->setWindowTitle(QApplication::translate("TilesetEditor", "Tileset editor", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("TilesetEditor", "Tile", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget_Tiles->headerItem();
        ___qtreewidgetitem->setText(4, QApplication::translate("TilesetEditor", "SingleImage", Q_NULLPTR));
        ___qtreewidgetitem->setText(3, QApplication::translate("TilesetEditor", "Health", Q_NULLPTR));
        ___qtreewidgetitem->setText(2, QApplication::translate("TilesetEditor", "Background", Q_NULLPTR));
        ___qtreewidgetitem->setText(1, QApplication::translate("TilesetEditor", "Type", Q_NULLPTR));
        ___qtreewidgetitem->setText(0, QApplication::translate("TilesetEditor", "Name", Q_NULLPTR));
        label_3->setText(QApplication::translate("TilesetEditor", "Health:", Q_NULLPTR));
        label->setText(QApplication::translate("TilesetEditor", "Name: ", Q_NULLPTR));
        label_2->setText(QApplication::translate("TilesetEditor", "Type:", Q_NULLPTR));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("TilesetEditor", "tile", Q_NULLPTR)
         << QApplication::translate("TilesetEditor", "background", Q_NULLPTR)
         << QApplication::translate("TilesetEditor", "ladder", Q_NULLPTR)
        );
        label_4->setText(QApplication::translate("TilesetEditor", "SingleImage:", Q_NULLPTR));
        checkBox->setText(QString());
        label_8->setText(QApplication::translate("TilesetEditor", "Background:", Q_NULLPTR));
        pushButton_AddTile->setText(QApplication::translate("TilesetEditor", "Add", Q_NULLPTR));
        pushButton_DeleteFile->setText(QApplication::translate("TilesetEditor", "Delete", Q_NULLPTR));
        pushButton_DuplicateTile->setText(QApplication::translate("TilesetEditor", "Duplicate", Q_NULLPTR));
        pushButton_ChangeTile->setText(QApplication::translate("TilesetEditor", "Change", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("TilesetEditor", "Tile grid", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget_tilesGrid->headerItem();
        ___qtreewidgetitem1->setText(2, QApplication::translate("TilesetEditor", "Size", Q_NULLPTR));
        ___qtreewidgetitem1->setText(1, QApplication::translate("TilesetEditor", "Position", Q_NULLPTR));
        ___qtreewidgetitem1->setText(0, QApplication::translate("TilesetEditor", "Type", Q_NULLPTR));
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
        groupBox_9->setTitle(QApplication::translate("TilesetEditor", "Tileset", Q_NULLPTR));
        toolButton->setText(QApplication::translate("TilesetEditor", "...", Q_NULLPTR));
        label_7->setText(QApplication::translate("TilesetEditor", "Texture size:", Q_NULLPTR));
        label_Texturesize->setText(QApplication::translate("TilesetEditor", "0,0", Q_NULLPTR));
        label_Texture->setText(QApplication::translate("TilesetEditor", "none", Q_NULLPTR));
        label_Name->setText(QApplication::translate("TilesetEditor", "none", Q_NULLPTR));
        label_6->setText(QApplication::translate("TilesetEditor", "Texture:", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("TilesetEditor", "Change", Q_NULLPTR));
        label_5->setText(QApplication::translate("TilesetEditor", "Name:", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("TilesetEditor", "Tile view", Q_NULLPTR));
        checkBox_LeftBottom->setText(QApplication::translate("TilesetEditor", "Left, Bottom", Q_NULLPTR));
        checkBox_RightBottom->setText(QApplication::translate("TilesetEditor", "Right, Bottom", Q_NULLPTR));
        checkBox_Bottom->setText(QApplication::translate("TilesetEditor", "Bottom", Q_NULLPTR));
        checkBox_Left->setText(QApplication::translate("TilesetEditor", "Left", Q_NULLPTR));
        checkBox_Right->setText(QApplication::translate("TilesetEditor", "Right", Q_NULLPTR));
        checkBox_RightTop->setText(QApplication::translate("TilesetEditor", "Right, Top", Q_NULLPTR));
        checkBox_Top->setText(QApplication::translate("TilesetEditor", "Top", Q_NULLPTR));
        checkBox_LeftTop->setText(QApplication::translate("TilesetEditor", "Left, Top", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("TilesetEditor", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TilesetEditor: public Ui_TilesetEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TILESETEDITOR_H
