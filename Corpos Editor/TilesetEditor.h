#pragma once

#include <QWidget>
#include "ui_TilesetEditor.h"
#include <QtWidgets/QMainWindow>
class TilesetEditor : public QMainWindow
{
	Q_OBJECT

public:
	TilesetEditor(QWidget *parent = Q_NULLPTR);
	~TilesetEditor();

private:
	Ui::TilesetEditor ui;
};
