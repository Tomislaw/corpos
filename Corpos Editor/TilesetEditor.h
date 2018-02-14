#ifndef TILESET_H
#define TILESET_H

#include <QWidget>
#include "ui_TilesetEditor.h"
#include <QtWidgets/QMainWindow>
#include "TileView.h"
class TilesetEditor : public QMainWindow
{
	Q_OBJECT

public:
	TilesetEditor(QWidget *parent = Q_NULLPTR);
	~TilesetEditor();

	public slots:
	void loadTileset();
	void loadTileGrid(QTreeWidgetItem*, int);

private:
	void changeTilesetData(std::string name, std::string texture, std::string size);
	void addTile(TextElement * e);

	Ui::TilesetEditor ui;

	TileView * tileView;




	std::vector<TileDefinition> tileDefinitions;

	std::string name;
	std::string texture;

};

#endif