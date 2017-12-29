#ifndef OPTIONSFORMS_H
#define OPTIONSFORMS_H

#include <QWidget>
#include "ui_OptionsForms.h"
#include "Options.h"
#include <windows.h>
#include <iostream>
class OptionsForms : public QWidget
{
	Q_OBJECT

public:
	OptionsForms(QWidget *parent = Q_NULLPTR);
	~OptionsForms();

private:

	Ui::OptionsForms ui;
public slots:
	void browseGameExe();
	void saveOptions();
};
#endif