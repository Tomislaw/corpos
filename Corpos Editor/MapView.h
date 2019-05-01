#ifndef MAPVIEW_H
#define MAPVIEW_H
#include "qsfmlcanvas.h"
#include <SFML/Graphics.hpp>
#include <game\graphics\GameSprite.hpp>
#include <game\map\Tilemap.hpp>
#include "game/engine/World.hpp"
class MapView :
	public QSFMLCanvas
{
public:
	TileMap world;
	EntityList entities;

	MapView(QWidget* Parent, const QPoint& Position, const QSize& Size);
	~MapView();
	void OnInit();
	void OnUpdate();
	void onResize();
	void loadMap(std::string mapLocation);
	void createMap(int x, int y);
	void setMapName(std::string name);

	sf::View view;
	void setTileAtMousePosition(std::string tileset, std::string tile);
	void startDrawingSelection();
	void createTilesAtSelectedArea(std::string tileset, std::string tile);
	bool saveToFile(std::string location);
	void setViewSize(float size);
private:

	float viewSize = 1;

	sf::ConvexShape selectRectangle;
	bool drawSelectedArea = false;

	sf::Vector2i startingSelectionTile;
};
#endif