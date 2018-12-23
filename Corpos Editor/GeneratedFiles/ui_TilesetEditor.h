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
	QWidget *widget_7;
	QHBoxLayout *horizontalLayout_9;
	QSpinBox *spinBox_tileRectX;
	QSpinBox *spinBox_TilerectY;
	QSpinBox *spinBox_TilerectW;
	QSpinBox *spinBox_TilerectH;
	QLabel *label_2;
	QLabel *label_3;
	QComboBox *comboBox_tileType;
	QLabel *label;
	QLineEdit *lineEdit_tileName;
	QSpinBox *spinBox_health;
	QLabel *label_4;
	QLabel *label_8;
	QCheckBox *checkBox_singleImage;
	QLineEdit *lineEdit_background;
	QLabel *label_9;
	QLabel *label_10;
	QLineEdit *lineEdit_connectGroup;
	QFrame *frame_4;
	QGridLayout *gridLayout_3;
	QPushButton *pushButton_AddTile;
	QPushButton *pushButton_DuplicateTile;
	QPushButton *pushButton_ChangeTile;
	QPushButton *pushButton_DeleteFile;
	QGroupBox *groupBox_2;
	QVBoxLayout *verticalLayout_4;
	QTreeWidget *treeWidget_tilesGrid;
	QFrame *frame_3;
	QGridLayout *gridLayout_2;
	QPushButton *pushButton_AddFrame;
	QPushButton *pushButton_DuplicateFrame;
	QPushButton *pushButton_DeleteFrame;
	QWidget *widget_2;
	QVBoxLayout *verticalLayout_2;
	QGroupBox *groupBox_TextureView;
	QVBoxLayout *verticalLayout_6;
	QVBoxLayout *verticalLayout_TextureView;
	QGroupBox *groupBox_4;
	QHBoxLayout *horizontalLayout_3;
	QGroupBox *groupBox_8;
	QHBoxLayout *horizontalLayout_6;
	QComboBox *comboBox_frameType;
	QGroupBox *groupBox_5;
	QHBoxLayout *horizontalLayout_4;
	QSpinBox *spinBox_posX;
	QSpinBox *spinBox_posY;
	QGroupBox *groupBox_7;
	QHBoxLayout *horizontalLayout_5;
	QSpinBox *spinBox_sizeX;
	QSpinBox *spinBox_sizeY;
	QPushButton *pushButton_ChangeFrame;
	QSpacerItem *horizontalSpacer;
	QWidget *widget_3;
	QVBoxLayout *verticalLayout_3;
	QGroupBox *groupBox_9;
	QGridLayout *gridLayout_5;
	QLabel *label_Name;
	QLabel *label_Texture;
	QLineEdit *lineEdit_tilesetName;
	QLabel *label_6;
	QWidget *widget_4;
	QHBoxLayout *horizontalLayout_7;
	QLabel *label_Texturesize;
	QWidget *widget_5;
	QGridLayout *gridLayout_6;
	QSpinBox *spinBox_6;
	QSpinBox *spinBox_7;
	QLabel *label_5;
	QPushButton *pushButton_ChangeTileset;
	QLabel *label_7;
	QWidget *widget_6;
	QHBoxLayout *horizontalLayout_8;
	QLineEdit *lineEdit_Texture;
	QComboBox *comboBox_Texture;
	QGroupBox *groupBox_6;
	QGridLayout *gridLayout;
	QFrame *frameTileView;
	QCheckBox *checkBox_LeftBottom;
	QCheckBox *checkBox_RightBottom;
	QCheckBox *checkBox_Bottom;
	QCheckBox *checkBox_Left;
	QCheckBox *checkBox_Right;
	QCheckBox *checkBox_RightTop;
	QCheckBox *checkBox_Top;
	QCheckBox *checkBox_LeftTop;
	QPushButton *pushButton_Randomize;
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
		TilesetEditor->resize(1460, 1015);
		QIcon icon;
		icon.addFile(QStringLiteral(":/CorposEditor/Resources/icons/tilesetEditor.png"), QSize(), QIcon::Normal, QIcon::Off);
		TilesetEditor->setWindowIcon(icon);
		TilesetEditor->setDockOptions(QMainWindow::AllowNestedDocks | QMainWindow::AllowTabbedDocks | QMainWindow::AnimatedDocks);
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
		widget_7 = new QWidget(frame_5);
		widget_7->setObjectName(QStringLiteral("widget_7"));
		horizontalLayout_9 = new QHBoxLayout(widget_7);
		horizontalLayout_9->setSpacing(1);
		horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
		horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
		horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
		spinBox_tileRectX = new QSpinBox(widget_7);
		spinBox_tileRectX->setObjectName(QStringLiteral("spinBox_tileRectX"));
		spinBox_tileRectX->setMinimum(-99);

		horizontalLayout_9->addWidget(spinBox_tileRectX);

		spinBox_TilerectY = new QSpinBox(widget_7);
		spinBox_TilerectY->setObjectName(QStringLiteral("spinBox_TilerectY"));
		spinBox_TilerectY->setMinimum(-99);

		horizontalLayout_9->addWidget(spinBox_TilerectY);

		spinBox_TilerectW = new QSpinBox(widget_7);
		spinBox_TilerectW->setObjectName(QStringLiteral("spinBox_TilerectW"));
		spinBox_TilerectW->setMinimum(-99);

		horizontalLayout_9->addWidget(spinBox_TilerectW);

		spinBox_TilerectH = new QSpinBox(widget_7);
		spinBox_TilerectH->setObjectName(QStringLiteral("spinBox_TilerectH"));
		spinBox_TilerectH->setMinimum(-99);

		horizontalLayout_9->addWidget(spinBox_TilerectH);

		gridLayout_4->addWidget(widget_7, 6, 1, 1, 1);

		label_2 = new QLabel(frame_5);
		label_2->setObjectName(QStringLiteral("label_2"));

		gridLayout_4->addWidget(label_2, 2, 0, 1, 1);

		label_3 = new QLabel(frame_5);
		label_3->setObjectName(QStringLiteral("label_3"));

		gridLayout_4->addWidget(label_3, 4, 0, 1, 1);

		comboBox_tileType = new QComboBox(frame_5);
		comboBox_tileType->setObjectName(QStringLiteral("comboBox_tileType"));

		gridLayout_4->addWidget(comboBox_tileType, 2, 1, 1, 1);

		label = new QLabel(frame_5);
		label->setObjectName(QStringLiteral("label"));

		gridLayout_4->addWidget(label, 0, 0, 1, 1);

		lineEdit_tileName = new QLineEdit(frame_5);
		lineEdit_tileName->setObjectName(QStringLiteral("lineEdit_tileName"));

		gridLayout_4->addWidget(lineEdit_tileName, 0, 1, 1, 1);

		spinBox_health = new QSpinBox(frame_5);
		spinBox_health->setObjectName(QStringLiteral("spinBox_health"));
		spinBox_health->setMinimum(-1);
		spinBox_health->setMaximum(999999);

		gridLayout_4->addWidget(spinBox_health, 4, 1, 1, 1);

		label_4 = new QLabel(frame_5);
		label_4->setObjectName(QStringLiteral("label_4"));

		gridLayout_4->addWidget(label_4, 5, 0, 1, 1);

		label_8 = new QLabel(frame_5);
		label_8->setObjectName(QStringLiteral("label_8"));

		gridLayout_4->addWidget(label_8, 3, 0, 1, 1);

		checkBox_singleImage = new QCheckBox(frame_5);
		checkBox_singleImage->setObjectName(QStringLiteral("checkBox_singleImage"));

		gridLayout_4->addWidget(checkBox_singleImage, 5, 1, 1, 1);

		lineEdit_background = new QLineEdit(frame_5);
		lineEdit_background->setObjectName(QStringLiteral("lineEdit_background"));

		gridLayout_4->addWidget(lineEdit_background, 3, 1, 1, 1);

		label_9 = new QLabel(frame_5);
		label_9->setObjectName(QStringLiteral("label_9"));

		gridLayout_4->addWidget(label_9, 6, 0, 1, 1);

		label_10 = new QLabel(frame_5);
		label_10->setObjectName(QStringLiteral("label_10"));

		gridLayout_4->addWidget(label_10, 7, 0, 1, 1);

		lineEdit_connectGroup = new QLineEdit(frame_5);
		lineEdit_connectGroup->setObjectName(QStringLiteral("lineEdit_connectGroup"));

		gridLayout_4->addWidget(lineEdit_connectGroup, 7, 1, 1, 1);

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

		pushButton_DuplicateTile = new QPushButton(frame_4);
		pushButton_DuplicateTile->setObjectName(QStringLiteral("pushButton_DuplicateTile"));

		gridLayout_3->addWidget(pushButton_DuplicateTile, 1, 1, 1, 1);

		pushButton_ChangeTile = new QPushButton(frame_4);
		pushButton_ChangeTile->setObjectName(QStringLiteral("pushButton_ChangeTile"));

		gridLayout_3->addWidget(pushButton_ChangeTile, 2, 0, 1, 1);

		pushButton_DeleteFile = new QPushButton(frame_4);
		pushButton_DeleteFile->setObjectName(QStringLiteral("pushButton_DeleteFile"));

		gridLayout_3->addWidget(pushButton_DeleteFile, 2, 1, 1, 1);

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
		pushButton_AddFrame = new QPushButton(frame_3);
		pushButton_AddFrame->setObjectName(QStringLiteral("pushButton_AddFrame"));

		gridLayout_2->addWidget(pushButton_AddFrame, 0, 0, 1, 1);

		pushButton_DuplicateFrame = new QPushButton(frame_3);
		pushButton_DuplicateFrame->setObjectName(QStringLiteral("pushButton_DuplicateFrame"));

		gridLayout_2->addWidget(pushButton_DuplicateFrame, 0, 1, 1, 1);

		pushButton_DeleteFrame = new QPushButton(frame_3);
		pushButton_DeleteFrame->setObjectName(QStringLiteral("pushButton_DeleteFrame"));

		gridLayout_2->addWidget(pushButton_DeleteFrame, 1, 1, 1, 1);

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
		groupBox_TextureView = new QGroupBox(widget_2);
		groupBox_TextureView->setObjectName(QStringLiteral("groupBox_TextureView"));
		sizePolicy1.setHeightForWidth(groupBox_TextureView->sizePolicy().hasHeightForWidth());
		groupBox_TextureView->setSizePolicy(sizePolicy1);
		verticalLayout_6 = new QVBoxLayout(groupBox_TextureView);
		verticalLayout_6->setSpacing(6);
		verticalLayout_6->setContentsMargins(11, 11, 11, 11);
		verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
		verticalLayout_TextureView = new QVBoxLayout();
		verticalLayout_TextureView->setSpacing(6);
		verticalLayout_TextureView->setObjectName(QStringLiteral("verticalLayout_TextureView"));

		verticalLayout_6->addLayout(verticalLayout_TextureView);

		verticalLayout_2->addWidget(groupBox_TextureView);

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
		comboBox_frameType = new QComboBox(groupBox_8);
		comboBox_frameType->setObjectName(QStringLiteral("comboBox_frameType"));

		horizontalLayout_6->addWidget(comboBox_frameType);

		horizontalLayout_3->addWidget(groupBox_8);

		groupBox_5 = new QGroupBox(groupBox_4);
		groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
		horizontalLayout_4 = new QHBoxLayout(groupBox_5);
		horizontalLayout_4->setSpacing(6);
		horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
		horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
		spinBox_posX = new QSpinBox(groupBox_5);
		spinBox_posX->setObjectName(QStringLiteral("spinBox_posX"));
		sizePolicy4.setHeightForWidth(spinBox_posX->sizePolicy().hasHeightForWidth());
		spinBox_posX->setSizePolicy(sizePolicy4);
		spinBox_posX->setMinimumSize(QSize(50, 0));
		spinBox_posX->setMinimum(-9999);
		spinBox_posX->setMaximum(9999);

		horizontalLayout_4->addWidget(spinBox_posX);

		spinBox_posY = new QSpinBox(groupBox_5);
		spinBox_posY->setObjectName(QStringLiteral("spinBox_posY"));
		spinBox_posY->setMinimumSize(QSize(50, 0));
		spinBox_posY->setMinimum(-9999);
		spinBox_posY->setMaximum(99999);

		horizontalLayout_4->addWidget(spinBox_posY);

		horizontalLayout_3->addWidget(groupBox_5);

		groupBox_7 = new QGroupBox(groupBox_4);
		groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
		horizontalLayout_5 = new QHBoxLayout(groupBox_7);
		horizontalLayout_5->setSpacing(6);
		horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
		horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
		spinBox_sizeX = new QSpinBox(groupBox_7);
		spinBox_sizeX->setObjectName(QStringLiteral("spinBox_sizeX"));
		spinBox_sizeX->setMinimumSize(QSize(50, 0));
		spinBox_sizeX->setMinimum(-9999);
		spinBox_sizeX->setMaximum(9999);

		horizontalLayout_5->addWidget(spinBox_sizeX);

		spinBox_sizeY = new QSpinBox(groupBox_7);
		spinBox_sizeY->setObjectName(QStringLiteral("spinBox_sizeY"));
		spinBox_sizeY->setMinimumSize(QSize(50, 0));
		spinBox_sizeY->setMinimum(-9999);
		spinBox_sizeY->setMaximum(9999);

		horizontalLayout_5->addWidget(spinBox_sizeY);

		horizontalLayout_3->addWidget(groupBox_7);

		pushButton_ChangeFrame = new QPushButton(groupBox_4);
		pushButton_ChangeFrame->setObjectName(QStringLiteral("pushButton_ChangeFrame"));

		horizontalLayout_3->addWidget(pushButton_ChangeFrame);

		horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

		horizontalLayout_3->addItem(horizontalSpacer);

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
		label_Name = new QLabel(groupBox_9);
		label_Name->setObjectName(QStringLiteral("label_Name"));

		gridLayout_5->addWidget(label_Name, 0, 1, 1, 1);

		label_Texture = new QLabel(groupBox_9);
		label_Texture->setObjectName(QStringLiteral("label_Texture"));

		gridLayout_5->addWidget(label_Texture, 3, 1, 1, 1);

		lineEdit_tilesetName = new QLineEdit(groupBox_9);
		lineEdit_tilesetName->setObjectName(QStringLiteral("lineEdit_tilesetName"));

		gridLayout_5->addWidget(lineEdit_tilesetName, 0, 2, 1, 1);

		label_6 = new QLabel(groupBox_9);
		label_6->setObjectName(QStringLiteral("label_6"));

		gridLayout_5->addWidget(label_6, 3, 0, 1, 1);

		widget_4 = new QWidget(groupBox_9);
		widget_4->setObjectName(QStringLiteral("widget_4"));
		horizontalLayout_7 = new QHBoxLayout(widget_4);
		horizontalLayout_7->setSpacing(1);
		horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
		horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
		horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
		label_Texturesize = new QLabel(widget_4);
		label_Texturesize->setObjectName(QStringLiteral("label_Texturesize"));

		horizontalLayout_7->addWidget(label_Texturesize);

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

		label_5 = new QLabel(groupBox_9);
		label_5->setObjectName(QStringLiteral("label_5"));

		gridLayout_5->addWidget(label_5, 0, 0, 1, 1);

		pushButton_ChangeTileset = new QPushButton(groupBox_9);
		pushButton_ChangeTileset->setObjectName(QStringLiteral("pushButton_ChangeTileset"));

		gridLayout_5->addWidget(pushButton_ChangeTileset, 5, 2, 1, 1);

		label_7 = new QLabel(groupBox_9);
		label_7->setObjectName(QStringLiteral("label_7"));

		gridLayout_5->addWidget(label_7, 4, 0, 1, 1);

		widget_6 = new QWidget(groupBox_9);
		widget_6->setObjectName(QStringLiteral("widget_6"));
		horizontalLayout_8 = new QHBoxLayout(widget_6);
		horizontalLayout_8->setSpacing(1);
		horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
		horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
		horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
		lineEdit_Texture = new QLineEdit(widget_6);
		lineEdit_Texture->setObjectName(QStringLiteral("lineEdit_Texture"));

		horizontalLayout_8->addWidget(lineEdit_Texture);

		comboBox_Texture = new QComboBox(widget_6);
		comboBox_Texture->setObjectName(QStringLiteral("comboBox_Texture"));

		horizontalLayout_8->addWidget(comboBox_Texture);

		gridLayout_5->addWidget(widget_6, 3, 2, 1, 1);

		verticalLayout_3->addWidget(groupBox_9);

		groupBox_6 = new QGroupBox(widget_3);
		groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
		groupBox_6->setMaximumSize(QSize(350, 300));
		groupBox_6->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignVCenter);
		groupBox_6->setFlat(false);
		groupBox_6->setCheckable(false);
		gridLayout = new QGridLayout(groupBox_6);
		gridLayout->setSpacing(6);
		gridLayout->setContentsMargins(11, 11, 11, 11);
		gridLayout->setObjectName(QStringLiteral("gridLayout"));
		gridLayout->setSizeConstraint(QLayout::SetMinimumSize);
		frameTileView = new QFrame(groupBox_6);
		frameTileView->setObjectName(QStringLiteral("frameTileView"));
		frameTileView->setMinimumSize(QSize(100, 100));
		frameTileView->setFrameShape(QFrame::Box);
		frameTileView->setFrameShadow(QFrame::Raised);

		gridLayout->addWidget(frameTileView, 1, 1, 1, 1);

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

		pushButton_Randomize = new QPushButton(groupBox_6);
		pushButton_Randomize->setObjectName(QStringLiteral("pushButton_Randomize"));

		gridLayout->addWidget(pushButton_Randomize, 3, 2, 1, 1);

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
		menuBar->setGeometry(QRect(0, 0, 1460, 26));
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
		QObject::connect(treeWidget_Tiles, SIGNAL(itemPressed(QTreeWidgetItem*, int)), TilesetEditor, SLOT(onSelectedTileDefinition(QTreeWidgetItem*, int)));
		QObject::connect(checkBox_LeftTop, SIGNAL(toggled(bool)), TilesetEditor, SLOT(updateTileView()));
		QObject::connect(checkBox_Top, SIGNAL(toggled(bool)), TilesetEditor, SLOT(updateTileView()));
		QObject::connect(checkBox_RightTop, SIGNAL(toggled(bool)), TilesetEditor, SLOT(updateTileView()));
		QObject::connect(checkBox_Right, SIGNAL(toggled(bool)), TilesetEditor, SLOT(updateTileView()));
		QObject::connect(checkBox_RightBottom, SIGNAL(toggled(bool)), TilesetEditor, SLOT(updateTileView()));
		QObject::connect(checkBox_Bottom, SIGNAL(toggled(bool)), TilesetEditor, SLOT(updateTileView()));
		QObject::connect(checkBox_LeftBottom, SIGNAL(toggled(bool)), TilesetEditor, SLOT(updateTileView()));
		QObject::connect(checkBox_Left, SIGNAL(toggled(bool)), TilesetEditor, SLOT(updateTileView()));
		QObject::connect(pushButton_Randomize, SIGNAL(clicked()), TilesetEditor, SLOT(updateTileView()));
		QObject::connect(comboBox_Texture, SIGNAL(currentTextChanged(QString)), TilesetEditor, SLOT(selectedTexture(QString)));
		QObject::connect(pushButton_ChangeTileset, SIGNAL(clicked()), TilesetEditor, SLOT(changeTileset()));
		QObject::connect(treeWidget_tilesGrid, SIGNAL(itemPressed(QTreeWidgetItem*, int)), TilesetEditor, SLOT(onSelectedTileFrame(QTreeWidgetItem*, int)));
		QObject::connect(spinBox_posX, SIGNAL(valueChanged(int)), TilesetEditor, SLOT(updateFrameEditorData()));
		QObject::connect(spinBox_posY, SIGNAL(valueChanged(int)), TilesetEditor, SLOT(updateFrameEditorData()));
		QObject::connect(spinBox_sizeX, SIGNAL(valueChanged(int)), TilesetEditor, SLOT(updateFrameEditorData()));
		QObject::connect(spinBox_sizeY, SIGNAL(valueChanged(int)), TilesetEditor, SLOT(updateFrameEditorData()));
		QObject::connect(pushButton_ChangeFrame, SIGNAL(clicked()), TilesetEditor, SLOT(editFrame()));
		QObject::connect(actionSave, SIGNAL(triggered()), TilesetEditor, SLOT(saveTileset()));
		QObject::connect(pushButton_AddTile, SIGNAL(clicked()), TilesetEditor, SLOT(addTile()));
		QObject::connect(pushButton_ChangeTile, SIGNAL(clicked()), TilesetEditor, SLOT(editTile()));
		QObject::connect(pushButton_DuplicateTile, SIGNAL(clicked()), TilesetEditor, SLOT(duplicateTile()));
		QObject::connect(pushButton_AddFrame, SIGNAL(clicked()), TilesetEditor, SLOT(addFrame()));
		QObject::connect(pushButton_DuplicateFrame, SIGNAL(clicked()), TilesetEditor, SLOT(duplicateFrame()));
		QObject::connect(pushButton_DeleteFrame, SIGNAL(clicked()), TilesetEditor, SLOT(deleteFrame()));
		QObject::connect(pushButton_DeleteFile, SIGNAL(clicked()), TilesetEditor, SLOT(deleteTile()));

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
		___qtreewidgetitem->setText(6, QApplication::translate("TilesetEditor", "Connect group", Q_NULLPTR));
		___qtreewidgetitem->setText(5, QApplication::translate("TilesetEditor", "Nowa kolumna", Q_NULLPTR));
		___qtreewidgetitem->setText(4, QApplication::translate("TilesetEditor", "SingleImage", Q_NULLPTR));
		___qtreewidgetitem->setText(3, QApplication::translate("TilesetEditor", "Health", Q_NULLPTR));
		___qtreewidgetitem->setText(2, QApplication::translate("TilesetEditor", "Background", Q_NULLPTR));
		___qtreewidgetitem->setText(1, QApplication::translate("TilesetEditor", "Type", Q_NULLPTR));
		___qtreewidgetitem->setText(0, QApplication::translate("TilesetEditor", "Name", Q_NULLPTR));
		label_2->setText(QApplication::translate("TilesetEditor", "Type:", Q_NULLPTR));
		label_3->setText(QApplication::translate("TilesetEditor", "Health:", Q_NULLPTR));
		comboBox_tileType->clear();
		comboBox_tileType->insertItems(0, QStringList()
			<< QApplication::translate("TilesetEditor", "tile", Q_NULLPTR)
			<< QApplication::translate("TilesetEditor", "background", Q_NULLPTR)
			<< QApplication::translate("TilesetEditor", "ladder", Q_NULLPTR)
		);
		label->setText(QApplication::translate("TilesetEditor", "Name: ", Q_NULLPTR));
		label_4->setText(QApplication::translate("TilesetEditor", "SingleImage:", Q_NULLPTR));
		label_8->setText(QApplication::translate("TilesetEditor", "Background:", Q_NULLPTR));
		checkBox_singleImage->setText(QString());
		label_9->setText(QApplication::translate("TilesetEditor", "Size:", Q_NULLPTR));
		label_10->setText(QApplication::translate("TilesetEditor", "Group:", Q_NULLPTR));
		pushButton_AddTile->setText(QApplication::translate("TilesetEditor", "Add", Q_NULLPTR));
		pushButton_DuplicateTile->setText(QApplication::translate("TilesetEditor", "Duplicate", Q_NULLPTR));
		pushButton_ChangeTile->setText(QApplication::translate("TilesetEditor", "Change", Q_NULLPTR));
		pushButton_DeleteFile->setText(QApplication::translate("TilesetEditor", "Delete", Q_NULLPTR));
		groupBox_2->setTitle(QApplication::translate("TilesetEditor", "Tile grid", Q_NULLPTR));
		QTreeWidgetItem *___qtreewidgetitem1 = treeWidget_tilesGrid->headerItem();
		___qtreewidgetitem1->setText(2, QApplication::translate("TilesetEditor", "Size", Q_NULLPTR));
		___qtreewidgetitem1->setText(1, QApplication::translate("TilesetEditor", "Position", Q_NULLPTR));
		___qtreewidgetitem1->setText(0, QApplication::translate("TilesetEditor", "Type", Q_NULLPTR));
		pushButton_AddFrame->setText(QApplication::translate("TilesetEditor", "Add", Q_NULLPTR));
		pushButton_DuplicateFrame->setText(QApplication::translate("TilesetEditor", "Duplicate", Q_NULLPTR));
		pushButton_DeleteFrame->setText(QApplication::translate("TilesetEditor", "Delete", Q_NULLPTR));
		groupBox_TextureView->setTitle(QApplication::translate("TilesetEditor", "Texture view", Q_NULLPTR));
		groupBox_4->setTitle(QString());
		groupBox_8->setTitle(QApplication::translate("TilesetEditor", "Type", Q_NULLPTR));
		comboBox_frameType->clear();
		comboBox_frameType->insertItems(0, QStringList()
			<< QApplication::translate("TilesetEditor", "top-left", Q_NULLPTR)
			<< QApplication::translate("TilesetEditor", "top", Q_NULLPTR)
			<< QApplication::translate("TilesetEditor", "top-right", Q_NULLPTR)
			<< QApplication::translate("TilesetEditor", "left", Q_NULLPTR)
			<< QApplication::translate("TilesetEditor", "inner", Q_NULLPTR)
			<< QApplication::translate("TilesetEditor", "center", Q_NULLPTR)
			<< QApplication::translate("TilesetEditor", "right", Q_NULLPTR)
			<< QApplication::translate("TilesetEditor", "bottom-left", Q_NULLPTR)
			<< QApplication::translate("TilesetEditor", "bottom", Q_NULLPTR)
			<< QApplication::translate("TilesetEditor", "bottom-right", Q_NULLPTR)
			<< QApplication::translate("TilesetEditor", "inner-top-left", Q_NULLPTR)
			<< QApplication::translate("TilesetEditor", "inner-top-right", Q_NULLPTR)
			<< QApplication::translate("TilesetEditor", "inner-bottom-right", Q_NULLPTR)
			<< QApplication::translate("TilesetEditor", "inner-bottom-left", Q_NULLPTR)
		);
		groupBox_5->setTitle(QApplication::translate("TilesetEditor", "Position", Q_NULLPTR));
		groupBox_7->setTitle(QApplication::translate("TilesetEditor", "Size", Q_NULLPTR));
		pushButton_ChangeFrame->setText(QApplication::translate("TilesetEditor", "Change", Q_NULLPTR));
		groupBox_9->setTitle(QApplication::translate("TilesetEditor", "Tileset", Q_NULLPTR));
		label_Name->setText(QApplication::translate("TilesetEditor", "none", Q_NULLPTR));
		label_Texture->setText(QApplication::translate("TilesetEditor", "none", Q_NULLPTR));
		label_6->setText(QApplication::translate("TilesetEditor", "Texture:", Q_NULLPTR));
		label_Texturesize->setText(QApplication::translate("TilesetEditor", "0,0", Q_NULLPTR));
		label_5->setText(QApplication::translate("TilesetEditor", "Name:", Q_NULLPTR));
		pushButton_ChangeTileset->setText(QApplication::translate("TilesetEditor", "Change", Q_NULLPTR));
		label_7->setText(QApplication::translate("TilesetEditor", "Texture size:", Q_NULLPTR));
		groupBox_6->setTitle(QApplication::translate("TilesetEditor", "Tile view", Q_NULLPTR));
		checkBox_LeftBottom->setText(QApplication::translate("TilesetEditor", "Left, Bottom", Q_NULLPTR));
		checkBox_RightBottom->setText(QApplication::translate("TilesetEditor", "Right, Bottom", Q_NULLPTR));
		checkBox_Bottom->setText(QApplication::translate("TilesetEditor", "Bottom", Q_NULLPTR));
		checkBox_Left->setText(QApplication::translate("TilesetEditor", "Left", Q_NULLPTR));
		checkBox_Right->setText(QApplication::translate("TilesetEditor", "Right", Q_NULLPTR));
		checkBox_RightTop->setText(QApplication::translate("TilesetEditor", "Right, Top", Q_NULLPTR));
		checkBox_Top->setText(QApplication::translate("TilesetEditor", "Top", Q_NULLPTR));
		checkBox_LeftTop->setText(QApplication::translate("TilesetEditor", "Left, Top", Q_NULLPTR));
		pushButton_Randomize->setText(QApplication::translate("TilesetEditor", "Randomize", Q_NULLPTR));
		menuFile->setTitle(QApplication::translate("TilesetEditor", "File", Q_NULLPTR));
	} // retranslateUi
};

namespace Ui {
	class TilesetEditor : public Ui_TilesetEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TILESETEDITOR_H
