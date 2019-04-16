#include "NewMapForms.h"
#include "CorposEditor.h"
#include "game\utility\Logger.hpp"
#include <QErrorMessage>

NewMapForms::NewMapForms(CorposEditor *callback)
	: QWidget()
{
	this->callback = callback;
	ui.setupUi(this);
}

NewMapForms::~NewMapForms()
{
}

void NewMapForms::validate(QString v)
{
	if (v.size() != 0)ui.pushButtonCreate->setEnabled(true);
	else ui.pushButtonCreate->setEnabled(false);
}

void NewMapForms::createMap()
{
	if (callback != nullptr)
	{
		callback->createMap(ui.spinBoxWidth->value(), ui.spinBoxHeight->value(),
			ui.lineEditMapName->text().toStdString());;
		this->setVisible(false);
	}
}