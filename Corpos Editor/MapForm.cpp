#include "MapForm.h"
#include "game\utility\Logger.hpp"
#include "CorposEditor.h"
MapForm::MapForm(QWidget *parent, std::string mapLocation) 
	: QWidget(parent)
{
	ui.setupUi(this);
	setMinimumSize(800, 800);

	QWidget::setWindowTitle(QString::fromStdString(mapLocation));

	mapView = new MapView(this, QPoint(0,0),QSize(1000,1000));


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
	mapView->createMap(x,y);
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
	int moveX = lastMousePos.x - e->x();
	int moveY = lastMousePos.y - e->y();

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
	//e->accept();
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
	//e->accept();
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
	//e->accept();
}

void MapForm::wheelEvent(QWheelEvent * e)
{




	viewSize += e->angleDelta().y() / 1000.f;



	Logger::i(std::to_string(viewSize));
	mapView->view.zoom(0.5f);
	mapView->setView(mapView->view);

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
