#include "MapView.h"
#include "options.h"

MapView::MapView(QWidget * Parent, const QPoint & Position, const QSize & Size) : QSFMLCanvas(Parent, Position, Size)
{
	setMinimumSize(800, 800);

	selectRectangle.setPointCount(4);
	selectRectangle.setOutlineColor(sf::Color(200, 0, 0, 200));
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
	update();
}
void MapView::OnUpdate()
{
	// Clear screen
	clear(sf::Color(0, 128, 0));

	// Draw it
	world.drawBackground(*this);
	world.draw(*this);
	world.drawDebug(*this);
	if (drawSelectedArea)
	{
		//get tile id at mouse position
		auto mousepos = sf::Mouse::getPosition(*this);
		auto pos = this->mapPixelToCoords(mousepos);
		auto id = world.getTileId(pos);

		//snap position to grid
		pos.x = id.x * 32 + 31;
		pos.y = id.y * 32 + 31;

		// snap position 2 to grid
		auto pos2 = sf::Vector2f();
		pos2.x = startingSelectionTile.x * 32;
		pos2.y = startingSelectionTile.y * 32;

		// move a little
		if (pos.x > pos2.x)pos2.x += 1;
		else
		{
			pos2.x -= 1;
			pos.x -= 32;
		}

		if (pos.y > pos2.y)pos2.y += 1;
		else
		{
			pos2.y -= 1;
			pos.y -= 32;
		}

		//set select rectangle
		selectRectangle.setPoint(0, pos2);

		selectRectangle.setPoint(1, sf::Vector2f(pos.x, selectRectangle.getPoint(0).y));
		selectRectangle.setPoint(2, pos);
		selectRectangle.setPoint(3, sf::Vector2f(selectRectangle.getPoint(0).x, pos.y));

		this->draw(selectRectangle);
	}
}

void MapView::onResize()
{
	sf::Vector2f size(getSize().x * viewSize, getSize().y * viewSize);

	view.setSize(size);
	this->setView(view);
	update();
}

void MapView::loadMap(std::string mapLocation)
{
	world.loadTileset(Options::tilesetLocation);
	world.loadMap(TextFileData(mapLocation).getFirst("TILEMAP"));
}

void MapView::createMap(int x, int y)
{
	world.loadTileset(Options::tilesetLocation);
	world.createMap(sf::Vector2i(x,y));
}

void MapView::setMapName(std::string name)
{
	//worldmap.setName(name);
}

void MapView::setTileAtMousePosition(std::string tileset, std::string tile)
{
	if (tile == "")return;

	std::shared_ptr<TileDefinition> t = nullptr;
	if (!((tile == "0" || tile == "air") && tileset == ""))
	{
		t = world.tilesets[0].getTileDefinition(tile);
	}

	auto mousepos = sf::Mouse::getPosition(*this);
	auto pos = this->mapPixelToCoords(mousepos);
	auto id = world.getTileId(pos);

	if (id.x < 0 || id.y < 0)return;
	world.setTile(id,t->name);
	//worldmap.refreashTile(id.x, id.y);
	//worldmap.refreashNearTiles(id.x, id.y);
	//worldmap.refreashBackgroundTile(id.x, id.y);
	//worldmap.
	world.debugRefreshMap();
	update();
}

void MapView::startDrawingSelection()
{
	drawSelectedArea = true;
	auto mousepos = sf::Mouse::getPosition(*this);
	auto pos = this->mapPixelToCoords(mousepos);
	auto id = world.getTileId(pos);
	startingSelectionTile = id;
}

void MapView::createTilesAtSelectedArea(std::string tileset, std::string tile)
{
	drawSelectedArea = false;

	if (tile == "")return;

	std::shared_ptr<TileDefinition> t = nullptr;
	if (!(tile == "0"&&tileset == ""))
	{
		t = world.tilesets.at(0).getTileDefinition(tile);
	}

	auto mousepos = sf::Mouse::getPosition(*this);
	auto pos = this->mapPixelToCoords(mousepos);
	auto startid = world.getTileId(pos);
	auto endId = world.getTileId(selectRectangle.getPoint(0));

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
			world.setTile(sf::Vector2i(x,y),t->name);
			//worldmap.refreashTile(x, y);
			//worldmap.refreashBackgroundTile(x, y);
		}
	}

	world.debugRefreshMap();
	update();
}

bool MapView::saveToFile(std::string location)
{
	TextFileData map;
	map["TILEMAP"] = world.asTextElement();
	return map.saveToFile(location);
}

void MapView::setViewSize(float s)
{
	viewSize = s;
	sf::Vector2f size(getSize().x * viewSize, getSize().y * viewSize);

	view.setSize(size);
	this->setView(view);
	update();
}