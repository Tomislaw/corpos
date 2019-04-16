#ifndef MAPFORM_H
#define MAPFORM_H

#include <QWidget>
#include "ui_MapForm.h"
#include "MapView.h"
#include "game\map\Tilemap.hpp"
#include <QMouseEvent>
class MapForm : public QWidget
{
	Q_OBJECT

public:
	MapView * mapView;

	MapForm(QWidget *parent, std::string mapName);
	MapForm(QWidget *parent, unsigned int x, unsigned int y, std::string name);
	~MapForm();

	void mouseMoveEvent(QMouseEvent * e) override;
	void mousePressEvent(QMouseEvent * e) override;
	void mouseReleaseEvent(QMouseEvent * e) override;
	void wheelEvent(QWheelEvent * event) override;

	bool saveToFile(std::string location);

public slots:
	void timerUpdate();
	void onResize();
private:
	Ui::MapForm ui;
	float viewSize = 1;
	QTimer timer;
	sf::Vector2f lastMousePos;
	sf::Vector2f startShiftMousePos;
	bool isRightMouseMoving = false;
	bool isLeftMouseMoving = false;
	bool isLeftShiftMouseMoving = false;
};

#endif