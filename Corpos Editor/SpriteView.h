#ifndef SPRITEVIEW_H
#define SPRITEVIEW_H
#include "qsfmlcanvas.h"
#include <SFML/Graphics.hpp>
#include <game\graphics\GameSprite.hpp>
class SpriteView : public QSFMLCanvas
{
public:
	SpriteView(QWidget* Parent, const QPoint& Position, const QSize& Size);
	void OnInit();
	void OnUpdate();
	void setSprite(GameSprite & sprite);
	void onResize();
	void setViewSize(float size);
private:
	float size = 1;
	sf::View view;
	GameSprite * sprite;
};
#endif // MYCANVAS_H