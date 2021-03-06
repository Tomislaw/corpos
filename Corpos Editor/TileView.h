#ifndef TILEVIEW_HPP
#define TILEVIEW_HPP
#include "qsfmlcanvas.h"
#include <SFML/Graphics.hpp>
#include <game\map\Tile.hpp>
class TileView : public QSFMLCanvas
{
public:
	TileView(QWidget* Parent, const QPoint& Position, const QSize& Size);
	void OnInit();
	void OnUpdate();
	void setTile(corpos::TileDefinition * tiledef);
	void onResize();
	void setViewSize(float size);
	void setTileCollidables(bool a, bool b, bool c,
		bool d,	/*x*/	bool e,
		bool f, bool g, bool h);
	sf::View view;

private:
	float size = 1;
	sf::VertexArray tileDrawable;
	std::vector<sf::Vertex*> tilePtr;
	corpos::Tile tile;
	sf::Texture * texture = nullptr;
	//QLabel * label_info = nullptr;
};
#endif // MYCANVAS_H