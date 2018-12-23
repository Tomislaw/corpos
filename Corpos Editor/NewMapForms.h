#pragma once

#include <QWidget>
#include "ui_NewMapForms.h"

class CorposEditor;

class NewMapForms : public QWidget
{
	Q_OBJECT

public:
	NewMapForms(CorposEditor * callback);
	~NewMapForms();

public slots:
	void createMap();
	void validate(QString);
private:
	CorposEditor * callback;
	Ui::NewMapForms ui;
};
