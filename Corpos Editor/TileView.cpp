#include "TileView.h"

#include "SpriteView.h"

#include "GameDataHolder.h"
#include "spriteview.h"
#include <iostream>
#include <string>
#include <QDir>
TileView::TileView(QWidget* Parent, const QPoint& Position, const QSize& Size) : QSFMLCanvas(Parent, Position, Size)
{
	tileDrawable.resize(16);
	for (int i = 0; i < 16; i++)
	{
		tilePtr.push_back(&tileDrawable[i]);
	}
	tileDrawable.setPrimitiveType(sf::PrimitiveType::Quads);
	setFixedSize(Size);
	update();
}
void TileView::OnInit()
{
	view.setCenter(0, 0);
	update();
}
void TileView::OnUpdate()
{
	// Clear screen
	clear(sf::Color(255,255,255));
	tile.setPosition(sf::Vector2f(16,16));

	if (!texture)return;
	draw(tileDrawable,texture);
}

void TileView::setTile(TileDefinition * tiledef)
{
	if (tiledef == nullptr)return;
	texture = GameDataHolder::getInstance()->getTexture(tiledef->texture_name);
	this->tile.changeTile(tiledef, tilePtr, sf::Vector2f(0,0));
	tile.setDisplayType(false, false, false,
						false,		  false, 
						false, false, false);
	update();
}

void TileView::onResize()
{
	sf::Vector2f Size(getSize().x * this->size, getSize().y*this->size);
	view.setSize(Size);
	view.setCenter(sf::Vector2f());
	this->setView(view);
}

void TileView::setViewSize(float size)
{
	this->size = size;
	onResize();
}
