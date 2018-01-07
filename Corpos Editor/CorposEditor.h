#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CorposEditor.h"
#include <fstream>
#include "options.h"

#include "OptionsForms.h"
#include "SpriteBrowser.h"
#include "MapForm.h"
#include <QMdiSubWindow>

class CorposEditor : public QMainWindow
{
	Q_OBJECT

public:
	CorposEditor(QWidget *parent = Q_NULLPTR);

	~CorposEditor();

	static std::string selectedTileset;
	static std::string selectedTile;
private:
	Ui::CorposEditorClass ui;
	OptionsForms * optionsForm = nullptr;
	SpriteBrowser * spriteForm = nullptr;
	void writeConsole(std::string info);


public slots:
void showOptionsForms();
void showSpriteBrowserForms();
void loadMap();
void loadTileDefinitions(QMdiSubWindow*);
void tileBrowserSelected(QTreeWidgetItem*, int);
};
