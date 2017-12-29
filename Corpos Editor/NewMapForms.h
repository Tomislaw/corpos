#pragma once

#include <QWidget>
#include "ui_NewMapForms.h"

class NewMapForms : public QWidget
{
	Q_OBJECT

public:
	NewMapForms(QWidget *parent = Q_NULLPTR);
	~NewMapForms();

private:
	Ui::NewMapForms ui;
};
