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
	for (int i = 0; i < 26; i++)
	{
		tilePtr.push_back(&tileDrawable[i]);
	}
}
void TileView::OnInit()
{
	view.setCenter(0, 0);
	onResize();
}
void TileView::OnUpdate()
{
	// Clear screen
	clear(sf::Color(0, 0, 0));
	if (!tile.getTileDefinition())return;
	draw(tileDrawable,tile.getTileDefinition()->texture);
}

void TileView::setTile(TileDefinition tiledef)
{
	this->tile.changeTile(&tiledef, tilePtr, sf::Vector2f());
}

void TileView::onResize()
{
	sf::Vector2f size(getSize().x*size, getSize().y*size);

	view.setSize(size);
	this->setView(view);
}

void TileView::setViewSize(float size)
{
	this->size = size;
	onResize();
}
