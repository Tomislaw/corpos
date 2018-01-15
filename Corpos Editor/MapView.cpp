#include "MapView.h"
#include "options.h"


MapView::MapView(QWidget * Parent, const QPoint & Position, const QSize & Size) : QSFMLCanvas(Parent, Position, Size)
{

	worldmap.getFunctionGetTexture() = std::bind(&GameDataHolder::getTexture, GameDataHolder::getInstance(), std::placeholders::_1);

	selectRectangle.setPointCount(4);
	selectRectangle.setOutlineColor(sf::Color(200,0,0,200));
	selectRectangle.setFillColor(sf::Color(100, 0, 0, 100));
	selectRectangle.setOutlineThickness(2);
	selectRectangle.setPosition(0, 0);
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
	if (drawSelectedArea)
	{
		auto mousepos = sf::Mouse::getPosition(*this);
		auto pos = this->mapPixelToCoords(mousepos);

		selectRectangle.setPoint(1, sf::Vector2f(pos.x, selectRectangle.getPoint(0).y));
		selectRectangle.setPoint(2, pos);
		selectRectangle.setPoint(3, sf::Vector2f( selectRectangle.getPoint(0).x, pos.y ));

		this->draw(selectRectangle);
	}
	
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

void MapView::createMap(int x, int y)
{
	worldmap.loadTileset(Options::tilesetLocation);
	worldmap.createMap(x,y);
}

void MapView::setMapName(std::string name)
{
	//worldmap.setName(name);
}

void MapView::setTileAtMousePosition(std::string tileset, std::string tile)
{

	if (tile == "")return;

	TileDefinition* t = nullptr;
	if (!(tile == "0"&&tileset == ""))
	{
		t = worldmap.getTileDefinition(tile, tileset);
	}

	auto mousepos = sf::Mouse::getPosition(*this);
	auto pos = this->mapPixelToCoords(mousepos);
	auto id = worldmap.getTileId(pos);

	if (id.x < 0 || id.y < 0)return;
	worldmap.setTile(t,id.x,id.y);
	worldmap.refreashTile(id.x,id.y);
	worldmap.refreashNearTiles(id.x,id.y);
	worldmap.refreashBackgroundTile(id.x, id.y);
	//worldmap.
	update();
}

void MapView::startDrawingSelection()
{
	drawSelectedArea = true;
	auto mousepos = sf::Mouse::getPosition(*this);
	auto pos = this->mapPixelToCoords(mousepos);
	//auto id = worldmap.getTileId(pos);
	selectRectangle.setPoint(0, pos);
}

void MapView::createTilesAtSelectedArea(std::string tileset, std::string tile)
{
	drawSelectedArea = false;

	if (tile == "")return;

	TileDefinition* t = nullptr;
	if (!(tile == "0"&&tileset == ""))
	{
		t = worldmap.getTileDefinition(tile, tileset);
	}

	auto mousepos = sf::Mouse::getPosition(*this);
	auto pos = this->mapPixelToCoords(mousepos);
	auto startid = worldmap.getTileId(pos);
	auto endId = worldmap.getTileId(selectRectangle.getPoint(0));

	if (startid.x > endId.x)
	{
		float buffor = startid.x;
		startid.x = endId.x;
		endId.x = buffor;
	}
	if (startid.y > endId.y)
	{
		float buffor = startid.y;
		startid.y = endId.y;
		endId.y = buffor;
	}

	for (int x = startid.x; x <= endId.x; x++)
	{
		for (int y = startid.y; y <= endId.y; y++)
		{
			if (x < 0 || y < 0)continue;
			worldmap.setTile(t,x,y);
			worldmap.refreashTile(x, y);
			worldmap.refreashBackgroundTile(x, y);
		}
	}


	//worldmap.
	update();

}

bool MapView::saveToFile(std::string location)
{
	TextFileData map;
	std::vector<TextElement> items;
	items.push_back(worldmap.generateTextElement());
	map.setElements(items);
	return map.saveToFile(location);
}
