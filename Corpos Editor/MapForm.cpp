#include "MapForm.h"
#include "game\utility\Logger.hpp"
#include "CorposEditor.h"
MapForm::MapForm(QWidget *parent, std::string mapLocation)
	: QWidget(parent)
{
	ui.setupUi(this);
	setMinimumSize(800, 800);

	QWidget::setWindowTitle(QString::fromStdString(mapLocation));

	mapView = new MapView(this, QPoint(0, 0), QSize(1000, 1000));

	mapView->adjustSize();
	mapView->loadMap(mapLocation);
	onResize();

	timer.setInterval(50);
	connect(&timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
	timer.start();

	this->setMouseTracking(true);
	mapView->update();
}

MapForm::MapForm(QWidget * parent, unsigned int x, unsigned int y, std::string name) : QWidget(parent)
{
	ui.setupUi(this);
	QWidget::setWindowTitle(QString::fromStdString("New map"));

	mapView = new MapView(this, QPoint(0, 0), QSize(1000, 1000));

	mapView->adjustSize();
	mapView->createMap(x, y);
	mapView->setMapName(name);
	onResize();

	timer.setInterval(50);
	connect(&timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
	timer.start();

	this->setMouseTracking(true);
	mapView->update();
}

MapForm::~MapForm()
{
	if (mapView != nullptr)
	{
		delete mapView;
	}
}

void MapForm::mouseMoveEvent(QMouseEvent * e)
{
	if (isRightMouseMoving)
	{
		int moveX = (lastMousePos.x - e->x())*viewSize;
		int moveY = (lastMousePos.y - e->y())*viewSize;

		mapView->view.move(sf::Vector2f(moveX, moveY));
		mapView->setView(mapView->view);

		lastMousePos.x = e->x();
		lastMousePos.y = e->y();

		mapView->update();
	}
	if (isLeftMouseMoving)
	{
		mapView->setTileAtMousePosition(CorposEditor::selectedTileset, CorposEditor::selectedTile);
	}
	if (isLeftShiftMouseMoving)
	{
		mapView->update();
	}
	e->setAccepted(false);
}

void MapForm::mousePressEvent(QMouseEvent * e)
{
	if (e->button() == Qt::RightButton)
	{
		lastMousePos.x = e->x();
		lastMousePos.y = e->y();
		isRightMouseMoving = true;
	}
	if (e->button() == Qt::LeftButton)
	{
		if (QGuiApplication::keyboardModifiers().testFlag(Qt::KeyboardModifier::ShiftModifier))
		{
			isLeftShiftMouseMoving = true;
			mapView->startDrawingSelection();
		}
		else
		{
			isLeftMouseMoving = true;
			mapView->setTileAtMousePosition(CorposEditor::selectedTileset, CorposEditor::selectedTile);
		}
	}
	e->setAccepted(false);
}

void MapForm::mouseReleaseEvent(QMouseEvent * e)
{
	if (e->button() == Qt::RightButton)
	{
		isRightMouseMoving = false;
	}
	if (e->button() == Qt::LeftButton)
	{
		if (isLeftShiftMouseMoving)
		{
			mapView->createTilesAtSelectedArea(CorposEditor::selectedTileset, CorposEditor::selectedTile);
		}
		isLeftMouseMoving = false;
		isLeftShiftMouseMoving = false;
	}
	mapView->update();
	e->setAccepted(false);

}

void MapForm::wheelEvent(QWheelEvent * e)
{
	e->setAccepted(false);
	if (!((viewSize < 0.2 &&  e->angleDelta().y() < 0) || (viewSize >= 4) && e->angleDelta().y() > 0))
		viewSize += e->angleDelta().y() / 1000.f;
	else return;
	if (viewSize < 0.2)viewSize = 0.16;
	if ((viewSize >= 4))viewSize = 4;
	mapView->setViewSize(viewSize);
	mapView->update();

}

std::vector<VertexTileMap>& MapForm::getVertexTileMap()
{
	return mapView->getVertexTileMap();
}

bool MapForm::saveToFile(std::string location)
{
	return mapView->saveToFile(location);
}

void MapForm::onResize()
{
	auto a = this->ui.centralWidget->QWidget::size();
	mapView->setFixedSize(a);
	mapView->setSize(sf::Vector2u(a.rwidth(), a.rheight()));
	mapView->onResize();
}

void MapForm::timerUpdate()
{
	onResize();
}