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
	file.loadFile(mapLocation);
	auto tm = file.getFirstElementByName("TILEMAP");
	worldmap.loadTileset(Options::tilesetLocation);
	worldmap.loadMap(tm);

}

void MapView::setTileAtMousePosition(std::string tileset, std::string tile)
{

	
	auto t =  worldmap.getTileDefinition(tile, tileset);

	auto mousepos = sf::Mouse::getPosition(*this);
	auto pos = this->mapPixelToCoords(mousepos);
	auto id = worldmap.getTileId(pos);
	Logger::i(std::to_string(id.x) + " " + std::to_string(id.y) );
	if (id.x < 0 || id.y < 0)return;
	worldmap.setTile(t,id.x,id.y);
	worldmap.refreashTile(id.x,id.y);
	worldmap.refreashNearTiles(id.x,id.y);
	worldmap.refreashBackgroundTile(id.x, id.y);
	//worldmap.
	update();
}
