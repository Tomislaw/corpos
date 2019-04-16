#ifndef frameeditor_h
#define frameeditor_h
#include "qsfmlcanvas.h"
#include <SFML/Graphics.hpp>
#include <game\map\Tile.hpp>
#include <QMouseEvent>
class FrameEditor : public QSFMLCanvas
{
	Q_OBJECT
public:
	FrameEditor(QWidget* Parent, const QPoint& Position, const QSize& Size);
	void OnInit();
	void OnUpdate();
	void onResize();
	void setViewSize(float size);
	void setTexture(std::string textureName);

	void mouseMoveEvent(QMouseEvent * e) override;
	void mousePressEvent(QMouseEvent * e) override;
	void mouseReleaseEvent(QMouseEvent * e) override;
	void wheelEvent(QWheelEvent * event) override;

	bool isFrameMoving() { return isMovingFrame; }
	sf::View view;

	sf::Texture * getTexture() { return texture; };

public slots:
	void centerView();
	void setFrame(sf::IntRect frame);
	void moveFrame(sf::Vector2f move);

signals:
	void frameChanged(sf::IntRect);
private:
	float size = 1;
	sf::VertexArray textureVertex;
	sf::VertexArray frameVertex;
	sf::Texture * texture = nullptr;

	sf::IntRect frame;

	bool isRightMouseMoving = false;
	bool isLefttMouseMoving = false;
	bool isMovingFrame = false;
	sf::Vector2f lastMoveFrame;
	sf::Vector2f lastRightMousePos;
	sf::Vector2f lastLeftMousePos;
};
#endif // MYCANVAS_H