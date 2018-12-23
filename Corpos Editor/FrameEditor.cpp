#include "FrameEditor.h"

#include "SpriteView.h"

#include "GameDataHolder.h"
#include "spriteview.h"
#include <iostream>
#include <string>
#include <QDir>
FrameEditor::FrameEditor(QWidget* Parent, const QPoint& Position, const QSize& Size) : QSFMLCanvas(Parent, Position, Size)
{
	textureVertex.resize(4);
	textureVertex.setPrimitiveType(sf::PrimitiveType::Quads);
	frameVertex.resize(5);
	frameVertex[0].color = sf::Color(0, 0, 255, 100);
	frameVertex[1].color = sf::Color(0, 0, 255, 100);
	frameVertex[2].color = sf::Color(0, 0, 255, 100);
	frameVertex[3].color = sf::Color(0, 0, 255, 100);
	frameVertex[4].color = sf::Color(0, 0, 255, 100);

	view.setCenter(sf::Vector2f());
	sf::Vector2f Sizef(Size.width() * this->size, Size.height()*this->size);
	view.setSize(Sizef);
	this->setView(view);

	setSize(sf::Vector2u(Sizef.x, Sizef.y));
	//setFixedSize(Size);
	update();
}
void FrameEditor::OnInit()
{
	update();
}
void FrameEditor::OnUpdate()
{
	// Clear screen
	clear(sf::Color(255, 255, 255));

	if (!texture)return;
	draw(textureVertex, texture);

	frameVertex.setPrimitiveType(sf::PrimitiveType::Quads);
	draw(frameVertex);

	frameVertex.setPrimitiveType(sf::PrimitiveType::LinesStrip);
	draw(frameVertex);

	frameVertex.setPrimitiveType(sf::PrimitiveType::Points);
	draw(frameVertex);
}

void FrameEditor::onResize()
{
	//centerView();
}

void FrameEditor::setViewSize(float size)
{
	auto currentSize = QWidget::size();
	sf::Window::setSize(sf::Vector2u(currentSize.width(), currentSize.height()));

	sf::Vector2f Size(getSize().x * this->size, getSize().y*this->size);
	view.setSize(Size);
	this->setView(view);
	update();
}

void FrameEditor::setTexture(std::string textureName)
{
	texture = GameDataHolder::getInstance()->getTexture(textureName);
	if (!texture)
	{
		//handle texture not found here
	}
	else
	{
		textureVertex[0].texCoords = sf::Vector2f(0, 0);
		textureVertex[1].texCoords = sf::Vector2f(texture->getSize().x, 0);
		textureVertex[2].texCoords = sf::Vector2f(texture->getSize().x, texture->getSize().y);
		textureVertex[3].texCoords = sf::Vector2f(0, texture->getSize().y);

		textureVertex[0].position = sf::Vector2f(0, 0);
		textureVertex[1].position = sf::Vector2f(texture->getSize().x, 0);
		textureVertex[2].position = sf::Vector2f(texture->getSize().x, texture->getSize().y);
		textureVertex[3].position = sf::Vector2f(0, texture->getSize().y);

		setViewSize(1);
		centerView();
	}
}

void FrameEditor::setFrame(sf::IntRect frame)
{
	if (this->frame == frame)return;
	this->frame = frame;
	frameVertex[0].position = sf::Vector2f(frame.left, frame.top);
	frameVertex[1].position = sf::Vector2f(frame.left + frame.width, frame.top);
	frameVertex[2].position = sf::Vector2f(frame.left + frame.width, frame.top + frame.height);
	frameVertex[3].position = sf::Vector2f(frame.left, frame.top + frame.height);
	frameVertex[4].position = sf::Vector2f(frame.left, frame.top);
	lastMoveFrame = sf::Vector2f();
	update();
	emit frameChanged(frame);
}

void FrameEditor::moveFrame(sf::Vector2f move)
{
	lastMoveFrame += move;

	int moveX = (int)lastMoveFrame.x;
	int moveY = (int)lastMoveFrame.y;

	if (moveX == 0 && moveY == 0)return;

	lastMoveFrame.x -= moveX;
	lastMoveFrame.y -= moveY;

	frame.left += moveX;
	frame.top += moveY;
	frameVertex[0].position = sf::Vector2f(frame.left, frame.top);
	frameVertex[1].position = sf::Vector2f(frame.left + frame.width, frame.top);
	frameVertex[2].position = sf::Vector2f(frame.left + frame.width, frame.top + frame.height);
	frameVertex[3].position = sf::Vector2f(frame.left, frame.top + frame.height);
	frameVertex[4].position = sf::Vector2f(frame.left, frame.top);

	update();
	emit frameChanged(frame);
}

void FrameEditor::centerView()
{
	view.setCenter(sf::Vector2f());
	this->setView(view);
	update();
}

void FrameEditor::mouseMoveEvent(QMouseEvent * e)
{
	if (isRightMouseMoving)
	{
		float moveX = (lastRightMousePos.x - e->x())*size;
		float moveY = (lastRightMousePos.y - e->y())*size;

		view.move(sf::Vector2f(moveX, moveY));

		lastRightMousePos.x = e->x();
		lastRightMousePos.y = e->y();

		setViewSize(size);
	}
	if (isMovingFrame)
	{
		float moveX = -(lastLeftMousePos.x - e->x())*size;
		float moveY = -(lastLeftMousePos.y - e->y())*size;

		moveFrame(sf::Vector2f(moveX, moveY));

		lastLeftMousePos.x = e->x();
		lastLeftMousePos.y = e->y();
	}

	//e->accept();
}

void FrameEditor::mousePressEvent(QMouseEvent * e)
{
	if (e->button() == Qt::RightButton)
	{
		lastRightMousePos.x = e->x();
		lastRightMousePos.y = e->y();
		isRightMouseMoving = true;
	}
	if (e->button() == Qt::LeftButton)
	{
		isLefttMouseMoving = true;
		auto pos = this->mapPixelToCoords(sf::Mouse::getPosition(*this));
		if (!frame.contains(sf::Vector2i(pos.x, pos.y)))return;
		lastLeftMousePos.x = e->x();
		lastLeftMousePos.y = e->y();
		isMovingFrame = true;
	}
	//e->accept();
}

void FrameEditor::mouseReleaseEvent(QMouseEvent * e)
{
	if (e->button() == Qt::RightButton)
	{
		isRightMouseMoving = false;
	}
	if (e->button() == Qt::LeftButton)
	{
		isLefttMouseMoving = false;
		isMovingFrame = false;
		lastMoveFrame = sf::Vector2f();
	}
	update();
	//e->accept();
}

void FrameEditor::wheelEvent(QWheelEvent * e)
{
	if (!((size < 0.2 &&  e->angleDelta().y() < 0) || (size >= 4) && e->angleDelta().y() > 0))
		size += e->angleDelta().y() / 1000.f;
	else return;
	if (size < 0.2)size = 0.16;
	if ((size >= 4))size = 4;
	setViewSize(size);
}