#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CorposEditor.h"
#include <fstream>
#include "options.h"
#include "TileView.h"
#include "OptionsForms.h"
#include "NewMapForms.h"
#include "SpriteBrowser.h"
#include "MapForm.h"
#include <QMdiSubWindow>
#include <qmessagebox.h>
#include <TilesetEditor.h>
class CorposEditor : public QMainWindow
{
	Q_OBJECT

public:
	CorposEditor(QWidget *parent = Q_NULLPTR);

	~CorposEditor();

	static std::string selectedTileset;
	static std::string selectedTile;

	void createMap(int sizex, int sizey, std::string name);
private:
	Ui::CorposEditorClass ui;
	OptionsForms * optionsForm = nullptr;
	SpriteBrowser * spriteForm = nullptr;
	TilesetEditor * tilesetEditor = nullptr;
	NewMapForms * newMapforms = nullptr;
	void writeConsole(std::string info);

	QMdiSubWindow * windowPtr = nullptr;

public slots:
	void showOptionsForms();
	void showSpriteBrowserForms();
	void showTilesetEditor();
	void loadMap();
	void saveMap();
	void newMap();
	void loadTileDefinitions(QMdiSubWindow*);
	void loadMapEntities(QMdiSubWindow*);
	void tileSelected(QListWidgetItem*);
	void tileFilter(QString);
	void updateMenuView();
};
