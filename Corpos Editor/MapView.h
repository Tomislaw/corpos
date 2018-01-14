#ifndef MAPVIEW_H
#define MAPVIEW_H
#include "qsfmlcanvas.h"
#include <SFML/Graphics.hpp>
#include <game\graphics\GameSprite.hpp>
#include <game\map\Tilemap.hpp>
#include "GameDataHolder.h"
class MapView :
	public QSFMLCanvas
{
public:
	MapView(QWidget* Parent, const QPoint& Position, const QSize& Size);
	~MapView();
	void OnInit();
	void OnUpdate();
	void onResize();
	void loadMap(std::string mapLocation);
	void createMap(int x, int y);
	void setMapName(std::string name);

	sf::View view;
	std::vector<VertexTileMap>& getVertexTileMap()
	{
		return worldmap.getVertexTileMapVector();
	}
	void setTileAtMousePosition(std::string tileset, std::string tile);

	bool saveToFile(std::string location);
private:


	Tilemap worldmap;

	
};
#endif