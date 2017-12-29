#include "SpriteView.h"

#include "GameDataHolder.h"
#include "spriteview.h"
#include <iostream>
#include <string>
#include <QDir>
SpriteView::SpriteView(QWidget* Parent, const QPoint& Position, const QSize& Size) : QSFMLCanvas(Parent, Position, Size)
{

}
void SpriteView::OnInit()
{
	view.setCenter(50, 50);
	onResize();
}
void SpriteView::OnUpdate()
{
	// Clear screen
	clear(sf::Color(0, 128, 0));



	// Draw it
	if(sprite!= nullptr)
	draw(sprite->GetSprite());;
}

void SpriteView::setSprite(GameSprite & sprite)
{
	this->sprite = &sprite;
}

void SpriteView::onResize()
{
	sf::Vector2f size(getSize().x*size, getSize().y*size);

	view.setSize(size);
	this->setView(view);
}

void SpriteView::setViewSize(float size)
{
	this->size = size;
	onResize();
}
