#include "MapForm.h"
#include "game\utility\Logger.hpp"
MapForm::MapForm(QWidget *parent, std::string mapLocation) 
	: QWidget(parent)
{
	ui.setupUi(this);
	QWidget::setWindowTitle(QString::fromStdString(mapLocation));

	mapView = new MapView(this, QPoint(0,0),QSize(1000,1000));


	mapView->adjustSize();
	mapView->loadMap(mapLocation);
	onResize();
	mapView->OnUpdate();


	timer.setInterval(50);
	connect(&timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
	timer.start();

	this->setMouseTracking(true);
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
	if (!isMouseMoving)return;

	int moveX = lastMousePos.x - e->x();
	int moveY = lastMousePos.y - e->y();

	mapView->view.move(sf::Vector2f(moveX, moveY));
	mapView->setView(mapView->view);

	lastMousePos.x = e->x();
	lastMousePos.y = e->y();

	mapView->update();
	//e->accept();
}

void MapForm::mousePressEvent(QMouseEvent * e)
{
	if (e->button() == Qt::RightButton)
	{

	lastMousePos.x = e->x();
	lastMousePos.y = e->y();
	isMouseMoving = true;
	}
	//e->accept();
}

void MapForm::mouseReleaseEvent(QMouseEvent * e)
{
	isMouseMoving = false;
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
