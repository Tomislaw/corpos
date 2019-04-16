#pragma once

#include <QWidget>
#include "ui_SpriteBrowser.h"
#include "SpriteView.h"
class SpriteBrowser : public QWidget
{
	Q_OBJECT

public:
	SpriteBrowser(QWidget *parent = Q_NULLPTR);
	~SpriteBrowser();

	void loadSprites();

public slots:
	void filterChanged(QString);
	void spriteSelected(int);
	void animationSelected(int);
	void timerUpdate();
	void timerStart();
	void timerStop();
	void sliderChanged(int);
	void sizeSliderChanged(int);
	void animationSpeedChanged();
	void onResize();
private:
	Ui::SpriteBrowser ui;
	std::vector<std::string> spritesIdList;
	GameSprite selectedSprite;
	SpriteView * view = nullptr;
	QTimer animationTimer;
	float timerInterval = 0;
	void resizeEvent(QResizeEvent *e);
	bool sfmlInitialized = false;
};
