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
	sf::View view;
private:


	Tilemap worldmap;

	
};
#endif