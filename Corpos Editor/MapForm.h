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
	MapForm(QWidget *parent, std::string mapName);
	~MapForm();

	void mouseMoveEvent(QMouseEvent * e) override;
	void mousePressEvent(QMouseEvent * e) override;
	void mouseReleaseEvent(QMouseEvent * e) override;
	void wheelEvent(QWheelEvent * event) override;

	std::vector<VertexTileMap>& getVertexTileMap();
public slots:
	void timerUpdate();
	void onResize();
private:
	Ui::MapForm ui;
	MapView * mapView;
	double viewSize = 1;
	QTimer timer;
	sf::Vector2f lastMousePos;
	bool isMouseMoving = false;
};

#endif