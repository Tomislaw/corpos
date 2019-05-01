#include "SpriteBrowser.h"
#include "game\utility\Logger.hpp"
SpriteBrowser::SpriteBrowser(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	loadSprites();
	view = new SpriteView(ui.widgetSFML, QPoint(), QSize());

	//Timer setup
	timerInterval = 50;
	animationTimer.setInterval(timerInterval);
	connect(&animationTimer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
	//animationTimer.start();
}

SpriteBrowser::~SpriteBrowser()
{
	//delete view;
}

void SpriteBrowser::loadSprites()
{
	auto list = corpos::GameAssetsManager::getInstance()->gameSprites;
	if (list.size() == 0)
	{
		corpos::Logger::e("Can't add any sprites to sprite browser.");
		return;
	}
	this->ui.listSprites->clear();
	spritesIdList.clear();
	for (auto & item : list) {
		this->ui.listSprites->addItem(QString::fromStdString(item.first));
		spritesIdList.push_back(item.first);
	}

	//this->ui.listSprites->clear();
}

void SpriteBrowser::spriteSelected(int id)
{
	if (sfmlInitialized == false)
	{
		onResize();
		sfmlInitialized = true;
	}
	if (id < 0)return;
	else
	{
		this->selectedSprite = corpos::GameSprite(corpos::GameAssetsManager::getInstance()->gameSprites[spritesIdList[id]]);

		auto anims = &selectedSprite.getAnimationSheet();
		this->ui.listAnimations->clear();
		for (size_t i = 0; i < anims->size(); i++)
		{
			auto a = anims->at(i).GetName();
			this->ui.listAnimations->addItem(QString::fromStdString(a));
		}
		if (anims->size() > 0)
		{
			this->ui.listAnimations->item(0)->setSelected(true);
			animationSelected(0);
		}
		else
		{
			animationSelected(-1);
		}
		view->update();
	}
}

void SpriteBrowser::animationSelected(int id)
{
	selectedSprite.update(0);
	if (id < 0)
	{
		this->ui.labelAnimationInfo->setText("<<info>>");
		this->ui.sliderFrame->setRange(0, 0);
	}
	else
	{
		auto anims = &selectedSprite.getAnimationSheet();
		auto a = anims->at(id);
		this->ui.labelAnimationInfo->setText(QString::fromStdString(a.toString()));
		selectedSprite.setAnimation(a.GetName());
		view->update();
		this->ui.sliderFrame->setRange(0, a.getFrameCount() - 1);
	}
}

void SpriteBrowser::timerUpdate()
{
	selectedSprite.update(timerInterval / 1000);
	if (selectedSprite.getCurrentAnimation() != nullptr)
	{
		this->ui.sliderFrame->setSliderPosition(selectedSprite.getCurrentAnimation()->getCurrentFrameId());
	}
	else
	{
		this->ui.sliderFrame->setSliderPosition(0);
	}
	view->update();
}

void SpriteBrowser::timerStart()
{
	if (selectedSprite.getCurrentAnimation() == nullptr)return;;
	if (selectedSprite.getCurrentAnimation()->is_finished())
		selectedSprite.getCurrentAnimation()->reset();

	animationTimer.start();
}

void SpriteBrowser::timerStop()
{
	animationTimer.stop();
}

void SpriteBrowser::sliderChanged(int i)
{
	if (selectedSprite.getCurrentAnimation() != nullptr)
	{
		selectedSprite.setRectangle(selectedSprite.getCurrentAnimation()->getRectangle(i));
		view->update();
	}
}

void SpriteBrowser::sizeSliderChanged(int current)
{
	float size = (int)current;
	size = size / 50;
	view->setViewSize(size);
	view->update();
}

void SpriteBrowser::animationSpeedChanged()
{
	if (timerInterval > 24)
	{
		if (timerInterval > 49)
		{
			if (timerInterval > 99)
			{
				this->ui.buttonSetSpeed->setText("x0.5");
				timerInterval = 25;
			}
			else
			{
				this->ui.buttonSetSpeed->setText("x2");
				timerInterval = 101;
			}
		}
		else
		{
			this->ui.buttonSetSpeed->setText("x1");
			timerInterval = 50;
		}
	}
	else
	{
		this->ui.buttonSetSpeed->setText("x0.5");
		timerInterval = 25;
	}
}

void SpriteBrowser::onResize()
{
	if (view == nullptr)return;
	auto a = this->ui.widgetSFML->QWidget::size();

	view->setFixedSize(a);
	view->setSize(sf::Vector2u(a.rwidth(), a.rheight()));
	view->setSprite(selectedSprite);
}

void SpriteBrowser::filterChanged(QString str)
{
	;
	auto list = corpos::GameAssetsManager::getInstance()->gameSprites;
	if (list.size() == 0)
	{
		corpos::Logger::e("Can't add any sprites to sprite browser.");
		return;
	}
	this->ui.listSprites->clear();
	spritesIdList.clear();

	for (auto & item : list) {
		std::string name = item.first;
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);
		if (name.find(str.toLower().toStdString()) != -1) {
			this->ui.listSprites->addItem(QString::fromStdString(name));
			spritesIdList.push_back(name);
		}
	}
}

void SpriteBrowser::resizeEvent(QResizeEvent *e)
{
	QWidget::resizeEvent(e);
	onResize();
}