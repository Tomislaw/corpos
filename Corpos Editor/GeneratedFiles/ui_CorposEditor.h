/********************************************************************************
** Form generated from reading UI file 'CorposEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CORPOSEDITOR_H
#define UI_CORPOSEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CorposEditorClass
{
public:
    QAction *actionNew_Map;
    QAction *actionLoad_Map;
    QAction *actionRecent;
    QAction *actionExit;
    QAction *actionOptions;
    QAction *actionInfo;
    QAction *actionRun_map;
    QAction *actionTile_browser;
    QAction *actionEntity_list;
    QAction *actionOutput_window;
    QAction *actionSprite_browser;
    QAction *actionSave;
    QAction *actionRefresh;
    QAction *actionTileset_editor;
    QAction *actionSprite_editor;
    QAction *actionCorposFile_editor;
    QAction *actionHelp;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QMdiArea *mdiArea;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menuHelp;
    QMenu *menuView;
    QMenu *menuMap;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *tileDock;
    QWidget *dockWidgetContents_12;
    QVBoxLayout *verticalLayout;
    QGroupBox *browseTileToolbox;
    QVBoxLayout *verticalLayout_2;
    QListWidget *tileListWidget;
    QLabel *label;
    QLineEdit *lineEdit_TileFilter;
    QDockWidget *entityDock;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_5;
    QListView *listView_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QDockWidget *consoleDock;
    QWidget *dockWidgetContents_2;
    QHBoxLayout *horizontalLayout;
    QTextEdit *consoleText;

    void setupUi(QMainWindow *CorposEditorClass)
    {
        if (CorposEditorClass->objectName().isEmpty())
            CorposEditorClass->setObjectName(QString::fromUtf8("CorposEditorClass"));
        CorposEditorClass->resize(1031, 797);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/CorposEditor/Resources/icons/corposSpace.png"), QSize(), QIcon::Normal, QIcon::Off);
        CorposEditorClass->setWindowIcon(icon);
        CorposEditorClass->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        actionNew_Map = new QAction(CorposEditorClass);
        actionNew_Map->setObjectName(QString::fromUtf8("actionNew_Map"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/CorposEditor/Resources/icons/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew_Map->setIcon(icon1);
        actionLoad_Map = new QAction(CorposEditorClass);
        actionLoad_Map->setObjectName(QString::fromUtf8("actionLoad_Map"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/CorposEditor/Resources/icons/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad_Map->setIcon(icon2);
        actionRecent = new QAction(CorposEditorClass);
        actionRecent->setObjectName(QString::fromUtf8("actionRecent"));
        actionExit = new QAction(CorposEditorClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionOptions = new QAction(CorposEditorClass);
        actionOptions->setObjectName(QString::fromUtf8("actionOptions"));
        actionInfo = new QAction(CorposEditorClass);
        actionInfo->setObjectName(QString::fromUtf8("actionInfo"));
        actionRun_map = new QAction(CorposEditorClass);
        actionRun_map->setObjectName(QString::fromUtf8("actionRun_map"));
        actionRun_map->setEnabled(false);
        actionRun_map->setIcon(icon);
        actionTile_browser = new QAction(CorposEditorClass);
        actionTile_browser->setObjectName(QString::fromUtf8("actionTile_browser"));
        actionTile_browser->setCheckable(true);
        actionTile_browser->setChecked(true);
        actionEntity_list = new QAction(CorposEditorClass);
        actionEntity_list->setObjectName(QString::fromUtf8("actionEntity_list"));
        actionEntity_list->setCheckable(true);
        actionEntity_list->setChecked(true);
        actionOutput_window = new QAction(CorposEditorClass);
        actionOutput_window->setObjectName(QString::fromUtf8("actionOutput_window"));
        actionOutput_window->setCheckable(true);
        actionOutput_window->setChecked(true);
        actionSprite_browser = new QAction(CorposEditorClass);
        actionSprite_browser->setObjectName(QString::fromUtf8("actionSprite_browser"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/CorposEditor/Resources/icons/spriteBrowser.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSprite_browser->setIcon(icon3);
        actionSave = new QAction(CorposEditorClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/CorposEditor/Resources/icons/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon4);
        actionRefresh = new QAction(CorposEditorClass);
        actionRefresh->setObjectName(QString::fromUtf8("actionRefresh"));
        actionTileset_editor = new QAction(CorposEditorClass);
        actionTileset_editor->setObjectName(QString::fromUtf8("actionTileset_editor"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/CorposEditor/Resources/icons/tilesetEditor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTileset_editor->setIcon(icon5);
        actionSprite_editor = new QAction(CorposEditorClass);
        actionSprite_editor->setObjectName(QString::fromUtf8("actionSprite_editor"));
        actionSprite_editor->setEnabled(false);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/CorposEditor/Resources/icons/spriteEditor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSprite_editor->setIcon(icon6);
        actionCorposFile_editor = new QAction(CorposEditorClass);
        actionCorposFile_editor->setObjectName(QString::fromUtf8("actionCorposFile_editor"));
        actionCorposFile_editor->setEnabled(false);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/CorposEditor/Resources/icons/corposFileEditor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCorposFile_editor->setIcon(icon7);
        actionHelp = new QAction(CorposEditorClass);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        centralWidget = new QWidget(CorposEditorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QString::fromUtf8("mdiArea"));
        mdiArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        mdiArea->setViewMode(QMdiArea::TabbedView);
        mdiArea->setDocumentMode(true);
        mdiArea->setTabsClosable(true);
        mdiArea->setTabsMovable(true);

        gridLayout->addWidget(mdiArea, 0, 0, 1, 1);

        CorposEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CorposEditorClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1031, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuMap = new QMenu(menuBar);
        menuMap->setObjectName(QString::fromUtf8("menuMap"));
        CorposEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CorposEditorClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        CorposEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CorposEditorClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        CorposEditorClass->setStatusBar(statusBar);
        tileDock = new QDockWidget(CorposEditorClass);
        tileDock->setObjectName(QString::fromUtf8("tileDock"));
        tileDock->setFloating(false);
        tileDock->setFeatures(QDockWidget::AllDockWidgetFeatures);
        tileDock->setAllowedAreas(Qt::AllDockWidgetAreas);
        dockWidgetContents_12 = new QWidget();
        dockWidgetContents_12->setObjectName(QString::fromUtf8("dockWidgetContents_12"));
        verticalLayout = new QVBoxLayout(dockWidgetContents_12);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        browseTileToolbox = new QGroupBox(dockWidgetContents_12);
        browseTileToolbox->setObjectName(QString::fromUtf8("browseTileToolbox"));
        verticalLayout_2 = new QVBoxLayout(browseTileToolbox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tileListWidget = new QListWidget(browseTileToolbox);
        tileListWidget->setObjectName(QString::fromUtf8("tileListWidget"));

        verticalLayout_2->addWidget(tileListWidget);

        label = new QLabel(browseTileToolbox);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        lineEdit_TileFilter = new QLineEdit(browseTileToolbox);
        lineEdit_TileFilter->setObjectName(QString::fromUtf8("lineEdit_TileFilter"));

        verticalLayout_2->addWidget(lineEdit_TileFilter);


        verticalLayout->addWidget(browseTileToolbox);

        tileDock->setWidget(dockWidgetContents_12);
        CorposEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), tileDock);
        entityDock = new QDockWidget(CorposEditorClass);
        entityDock->setObjectName(QString::fromUtf8("entityDock"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout_4 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox = new QGroupBox(dockWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_5 = new QVBoxLayout(groupBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        listView_2 = new QListView(groupBox);
        listView_2->setObjectName(QString::fromUtf8("listView_2"));

        verticalLayout_5->addWidget(listView_2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_5->addWidget(label_2);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout_5->addWidget(lineEdit);


        verticalLayout_4->addWidget(groupBox);

        entityDock->setWidget(dockWidgetContents);
        CorposEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), entityDock);
        consoleDock = new QDockWidget(CorposEditorClass);
        consoleDock->setObjectName(QString::fromUtf8("consoleDock"));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        horizontalLayout = new QHBoxLayout(dockWidgetContents_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        consoleText = new QTextEdit(dockWidgetContents_2);
        consoleText->setObjectName(QString::fromUtf8("consoleText"));
        consoleText->setReadOnly(true);

        horizontalLayout->addWidget(consoleText);

        consoleDock->setWidget(dockWidgetContents_2);
        CorposEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(8), consoleDock);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuMap->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew_Map);
        menuFile->addAction(actionLoad_Map);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionRun_map);
        menuFile->addSeparator();
        menuFile->addAction(actionRecent);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuTools->addAction(actionSprite_browser);
        menuTools->addSeparator();
        menuTools->addAction(actionSprite_editor);
        menuTools->addAction(actionTileset_editor);
        menuTools->addAction(actionCorposFile_editor);
        menuTools->addSeparator();
        menuTools->addAction(actionOptions);
        menuHelp->addAction(actionInfo);
        menuHelp->addAction(actionHelp);
        menuView->addAction(actionTile_browser);
        menuView->addAction(actionEntity_list);
        menuView->addAction(actionOutput_window);
        menuMap->addAction(actionRefresh);
        mainToolBar->addAction(actionNew_Map);
        mainToolBar->addAction(actionLoad_Map);
        mainToolBar->addAction(actionSave);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionRun_map);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSprite_browser);
        mainToolBar->addAction(actionTileset_editor);
        mainToolBar->addAction(actionSprite_editor);
        mainToolBar->addAction(actionCorposFile_editor);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionHelp);
        mainToolBar->addAction(actionInfo);

        retranslateUi(CorposEditorClass);
        QObject::connect(actionExit, SIGNAL(triggered()), CorposEditorClass, SLOT(close()));
        QObject::connect(actionOptions, SIGNAL(triggered()), CorposEditorClass, SLOT(showOptionsForms()));
        QObject::connect(actionTile_browser, SIGNAL(toggled(bool)), tileDock, SLOT(setVisible(bool)));
        QObject::connect(actionEntity_list, SIGNAL(toggled(bool)), entityDock, SLOT(setVisible(bool)));
        QObject::connect(actionOutput_window, SIGNAL(toggled(bool)), consoleDock, SLOT(setVisible(bool)));
        QObject::connect(actionSprite_browser, SIGNAL(triggered()), CorposEditorClass, SLOT(showSpriteBrowserForms()));
        QObject::connect(actionLoad_Map, SIGNAL(triggered()), CorposEditorClass, SLOT(loadMap()));
        QObject::connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), CorposEditorClass, SLOT(loadTileDefinitions(QMdiSubWindow*)));
        QObject::connect(actionSave, SIGNAL(triggered()), CorposEditorClass, SLOT(saveMap()));
        QObject::connect(actionNew_Map, SIGNAL(triggered()), CorposEditorClass, SLOT(newMap()));
        QObject::connect(tileListWidget, SIGNAL(itemPressed(QListWidgetItem*)), CorposEditorClass, SLOT(tileSelected(QListWidgetItem*)));
        QObject::connect(lineEdit_TileFilter, SIGNAL(textChanged(QString)), CorposEditorClass, SLOT(tileFilter(QString)));
        QObject::connect(actionTileset_editor, SIGNAL(triggered()), CorposEditorClass, SLOT(showTilesetEditor()));

        QMetaObject::connectSlotsByName(CorposEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *CorposEditorClass)
    {
        CorposEditorClass->setWindowTitle(QApplication::translate("CorposEditorClass", "CorposEditor", nullptr));
        actionNew_Map->setText(QApplication::translate("CorposEditorClass", "New", nullptr));
        actionLoad_Map->setText(QApplication::translate("CorposEditorClass", "Load", nullptr));
        actionRecent->setText(QApplication::translate("CorposEditorClass", "Recent", nullptr));
        actionExit->setText(QApplication::translate("CorposEditorClass", "Exit", nullptr));
        actionOptions->setText(QApplication::translate("CorposEditorClass", "Options", nullptr));
        actionInfo->setText(QApplication::translate("CorposEditorClass", "Info", nullptr));
        actionRun_map->setText(QApplication::translate("CorposEditorClass", "Run map", nullptr));
        actionTile_browser->setText(QApplication::translate("CorposEditorClass", "Tile browser", nullptr));
        actionEntity_list->setText(QApplication::translate("CorposEditorClass", "Entity list", nullptr));
        actionOutput_window->setText(QApplication::translate("CorposEditorClass", "Output window", nullptr));
        actionSprite_browser->setText(QApplication::translate("CorposEditorClass", "Sprite browser", nullptr));
        actionSave->setText(QApplication::translate("CorposEditorClass", "Save file", nullptr));
        actionRefresh->setText(QApplication::translate("CorposEditorClass", "Refresh", nullptr));
        actionTileset_editor->setText(QApplication::translate("CorposEditorClass", "Tileset editor", nullptr));
        actionSprite_editor->setText(QApplication::translate("CorposEditorClass", "Sprite editor", nullptr));
        actionCorposFile_editor->setText(QApplication::translate("CorposEditorClass", "CorposFile editor", nullptr));
        actionHelp->setText(QApplication::translate("CorposEditorClass", "Help", nullptr));
        menuFile->setTitle(QApplication::translate("CorposEditorClass", "File", nullptr));
        menuTools->setTitle(QApplication::translate("CorposEditorClass", "Tools", nullptr));
        menuHelp->setTitle(QApplication::translate("CorposEditorClass", "Help", nullptr));
        menuView->setTitle(QApplication::translate("CorposEditorClass", "View", nullptr));
        menuMap->setTitle(QApplication::translate("CorposEditorClass", "Map", nullptr));
        tileDock->setWindowTitle(QApplication::translate("CorposEditorClass", "Tile browser", nullptr));
        browseTileToolbox->setTitle(QApplication::translate("CorposEditorClass", "Browse tile", nullptr));
        label->setText(QApplication::translate("CorposEditorClass", "Search:", nullptr));
        entityDock->setWindowTitle(QApplication::translate("CorposEditorClass", "Entity list", nullptr));
        groupBox->setTitle(QString());
        label_2->setText(QApplication::translate("CorposEditorClass", "Search:", nullptr));
        consoleDock->setWindowTitle(QApplication::translate("CorposEditorClass", "Output", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CorposEditorClass: public Ui_CorposEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CORPOSEDITOR_H
