/********************************************************************************
** Form generated from reading UI file 'CorposEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CORPOSEDITOR_H
#define UI_CORPOSEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QMdiArea *mdiArea;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menuHelp;
    QMenu *menuView;
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
            CorposEditorClass->setObjectName(QStringLiteral("CorposEditorClass"));
        CorposEditorClass->resize(1031, 797);
        CorposEditorClass->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        actionNew_Map = new QAction(CorposEditorClass);
        actionNew_Map->setObjectName(QStringLiteral("actionNew_Map"));
        actionLoad_Map = new QAction(CorposEditorClass);
        actionLoad_Map->setObjectName(QStringLiteral("actionLoad_Map"));
        actionRecent = new QAction(CorposEditorClass);
        actionRecent->setObjectName(QStringLiteral("actionRecent"));
        actionExit = new QAction(CorposEditorClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionOptions = new QAction(CorposEditorClass);
        actionOptions->setObjectName(QStringLiteral("actionOptions"));
        actionInfo = new QAction(CorposEditorClass);
        actionInfo->setObjectName(QStringLiteral("actionInfo"));
        actionRun_map = new QAction(CorposEditorClass);
        actionRun_map->setObjectName(QStringLiteral("actionRun_map"));
        actionTile_browser = new QAction(CorposEditorClass);
        actionTile_browser->setObjectName(QStringLiteral("actionTile_browser"));
        actionTile_browser->setCheckable(true);
        actionTile_browser->setChecked(true);
        actionEntity_list = new QAction(CorposEditorClass);
        actionEntity_list->setObjectName(QStringLiteral("actionEntity_list"));
        actionEntity_list->setCheckable(true);
        actionEntity_list->setChecked(true);
        actionOutput_window = new QAction(CorposEditorClass);
        actionOutput_window->setObjectName(QStringLiteral("actionOutput_window"));
        actionOutput_window->setCheckable(true);
        actionOutput_window->setChecked(true);
        actionSprite_browser = new QAction(CorposEditorClass);
        actionSprite_browser->setObjectName(QStringLiteral("actionSprite_browser"));
        actionSave = new QAction(CorposEditorClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave->setEnabled(false);
        centralWidget = new QWidget(CorposEditorClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));
        mdiArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        mdiArea->setViewMode(QMdiArea::TabbedView);
        mdiArea->setDocumentMode(true);
        mdiArea->setTabsClosable(true);
        mdiArea->setTabsMovable(true);

        gridLayout->addWidget(mdiArea, 0, 0, 1, 1);

        CorposEditorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CorposEditorClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1031, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        CorposEditorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CorposEditorClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CorposEditorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CorposEditorClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CorposEditorClass->setStatusBar(statusBar);
        tileDock = new QDockWidget(CorposEditorClass);
        tileDock->setObjectName(QStringLiteral("tileDock"));
        tileDock->setFloating(false);
        tileDock->setFeatures(QDockWidget::AllDockWidgetFeatures);
        tileDock->setAllowedAreas(Qt::AllDockWidgetAreas);
        dockWidgetContents_12 = new QWidget();
        dockWidgetContents_12->setObjectName(QStringLiteral("dockWidgetContents_12"));
        verticalLayout = new QVBoxLayout(dockWidgetContents_12);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        browseTileToolbox = new QGroupBox(dockWidgetContents_12);
        browseTileToolbox->setObjectName(QStringLiteral("browseTileToolbox"));
        verticalLayout_2 = new QVBoxLayout(browseTileToolbox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tileListWidget = new QListWidget(browseTileToolbox);
        tileListWidget->setObjectName(QStringLiteral("tileListWidget"));

        verticalLayout_2->addWidget(tileListWidget);

        label = new QLabel(browseTileToolbox);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        lineEdit_TileFilter = new QLineEdit(browseTileToolbox);
        lineEdit_TileFilter->setObjectName(QStringLiteral("lineEdit_TileFilter"));

        verticalLayout_2->addWidget(lineEdit_TileFilter);


        verticalLayout->addWidget(browseTileToolbox);

        tileDock->setWidget(dockWidgetContents_12);
        CorposEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), tileDock);
        entityDock = new QDockWidget(CorposEditorClass);
        entityDock->setObjectName(QStringLiteral("entityDock"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout_4 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        groupBox = new QGroupBox(dockWidgetContents);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_5 = new QVBoxLayout(groupBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        listView_2 = new QListView(groupBox);
        listView_2->setObjectName(QStringLiteral("listView_2"));

        verticalLayout_5->addWidget(listView_2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_5->addWidget(label_2);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout_5->addWidget(lineEdit);


        verticalLayout_4->addWidget(groupBox);

        entityDock->setWidget(dockWidgetContents);
        CorposEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), entityDock);
        consoleDock = new QDockWidget(CorposEditorClass);
        consoleDock->setObjectName(QStringLiteral("consoleDock"));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        horizontalLayout = new QHBoxLayout(dockWidgetContents_2);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        consoleText = new QTextEdit(dockWidgetContents_2);
        consoleText->setObjectName(QStringLiteral("consoleText"));
        consoleText->setReadOnly(true);

        horizontalLayout->addWidget(consoleText);

        consoleDock->setWidget(dockWidgetContents_2);
        CorposEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(8), consoleDock);

        menuBar->addAction(menuFile->menuAction());
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
        menuTools->addAction(actionOptions);
        menuHelp->addAction(actionInfo);
        menuView->addAction(actionTile_browser);
        menuView->addAction(actionEntity_list);
        menuView->addAction(actionOutput_window);

        retranslateUi(CorposEditorClass);
        QObject::connect(actionExit, SIGNAL(triggered()), CorposEditorClass, SLOT(close()));
        QObject::connect(actionOptions, SIGNAL(triggered()), CorposEditorClass, SLOT(showOptionsForms()));
        QObject::connect(actionTile_browser, SIGNAL(toggled(bool)), tileDock, SLOT(setVisible(bool)));
        QObject::connect(tileDock, SIGNAL(visibilityChanged(bool)), actionTile_browser, SLOT(setChecked(bool)));
        QObject::connect(actionEntity_list, SIGNAL(toggled(bool)), entityDock, SLOT(setVisible(bool)));
        QObject::connect(consoleDock, SIGNAL(visibilityChanged(bool)), actionOutput_window, SLOT(setChecked(bool)));
        QObject::connect(actionOutput_window, SIGNAL(toggled(bool)), consoleDock, SLOT(setVisible(bool)));
        QObject::connect(entityDock, SIGNAL(visibilityChanged(bool)), actionEntity_list, SLOT(setChecked(bool)));
        QObject::connect(actionSprite_browser, SIGNAL(triggered()), CorposEditorClass, SLOT(showSpriteBrowserForms()));
        QObject::connect(actionLoad_Map, SIGNAL(triggered()), CorposEditorClass, SLOT(loadMap()));
        QObject::connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)), CorposEditorClass, SLOT(loadTileDefinitions(QMdiSubWindow*)));
        QObject::connect(actionSave, SIGNAL(triggered()), CorposEditorClass, SLOT(saveMap()));
        QObject::connect(actionNew_Map, SIGNAL(triggered()), CorposEditorClass, SLOT(newMap()));
        QObject::connect(tileListWidget, SIGNAL(itemPressed(QListWidgetItem*)), CorposEditorClass, SLOT(tileSelected(QListWidgetItem*)));
        QObject::connect(lineEdit_TileFilter, SIGNAL(textChanged(QString)), CorposEditorClass, SLOT(tileFilter(QString)));

        QMetaObject::connectSlotsByName(CorposEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *CorposEditorClass)
    {
        CorposEditorClass->setWindowTitle(QApplication::translate("CorposEditorClass", "CorposEditor", Q_NULLPTR));
        actionNew_Map->setText(QApplication::translate("CorposEditorClass", "New", Q_NULLPTR));
        actionLoad_Map->setText(QApplication::translate("CorposEditorClass", "Load", Q_NULLPTR));
        actionRecent->setText(QApplication::translate("CorposEditorClass", "Recent", Q_NULLPTR));
        actionExit->setText(QApplication::translate("CorposEditorClass", "Exit", Q_NULLPTR));
        actionOptions->setText(QApplication::translate("CorposEditorClass", "Options", Q_NULLPTR));
        actionInfo->setText(QApplication::translate("CorposEditorClass", "Info", Q_NULLPTR));
        actionRun_map->setText(QApplication::translate("CorposEditorClass", "Run map", Q_NULLPTR));
        actionTile_browser->setText(QApplication::translate("CorposEditorClass", "Tile browser", Q_NULLPTR));
        actionEntity_list->setText(QApplication::translate("CorposEditorClass", "Entity list", Q_NULLPTR));
        actionOutput_window->setText(QApplication::translate("CorposEditorClass", "Output window", Q_NULLPTR));
        actionSprite_browser->setText(QApplication::translate("CorposEditorClass", "Sprite browser", Q_NULLPTR));
        actionSave->setText(QApplication::translate("CorposEditorClass", "Save", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("CorposEditorClass", "File", Q_NULLPTR));
        menuTools->setTitle(QApplication::translate("CorposEditorClass", "Tools", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("CorposEditorClass", "Help", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("CorposEditorClass", "View", Q_NULLPTR));
        tileDock->setWindowTitle(QApplication::translate("CorposEditorClass", "Tile browser", Q_NULLPTR));
        browseTileToolbox->setTitle(QApplication::translate("CorposEditorClass", "Browse tile", Q_NULLPTR));
        label->setText(QApplication::translate("CorposEditorClass", "Search:", Q_NULLPTR));
        entityDock->setWindowTitle(QApplication::translate("CorposEditorClass", "Entity list", Q_NULLPTR));
        groupBox->setTitle(QString());
        label_2->setText(QApplication::translate("CorposEditorClass", "Search:", Q_NULLPTR));
        consoleDock->setWindowTitle(QApplication::translate("CorposEditorClass", "Output", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CorposEditorClass: public Ui_CorposEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CORPOSEDITOR_H
