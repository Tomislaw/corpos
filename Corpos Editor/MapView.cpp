#include "MapView.h"
#include "options.h"


MapView::MapView(QWidget * Parent, const QPoint & Position, const QSize & Size) : QSFMLCanvas(Parent, Position, Size)
{

	worldmap.getFunctionGetTexture() = std::bind(&GameDataHolder::getTexture, GameDataHolder::getInstance(), std::placeholders::_1);
}

MapView::~MapView()
{
}


void MapView::OnInit()
{
	view.setCenter(50, 50);
	onResize();
}
void MapView::OnUpdate()
{
	// Clear screen
	clear(sf::Color(0, 128, 0));



	// Draw it
	worldmap.drawBackground(*this);
	worldmap.draw(*this);
	worldmap.drawEditor(*this);
}


void MapView::onResize()
{
	sf::Vector2f size(getSize().x, getSize().y);

	view.setSize(size);
	this->setView(view);
}


void MapView::loadMap(std::string mapLocation)
{


	TextFileData file;
	file.load_file(mapLocation);
	auto tm = file.get_first_element_by_name("TILEMAP");
	worldmap.loadTileset(Options::tilesetLocation);
	worldmap.loadMap(tm);

}
