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
	void setTile(TileDefinition tiledef);
	void onResize();
	void setViewSize(float size);
private:
	float size = 1;
	sf::VertexArray tileDrawable;
	std::vector<sf::Vertex*> tilePtr;
	sf::View view;
	Tile tile;
};
#endif // MYCANVAS_H