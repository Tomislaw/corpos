#include "CorposEditor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CorposEditor w;
	w.show();
	return a.exec();
}