#include "qsfmlcanvas.h"
#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
#endif
#include <iostream>
QSFMLCanvas::QSFMLCanvas(QWidget* Parent, const QPoint& Position, const QSize& Size, unsigned int FrameTime) : QWidget(Parent),
initialized(false)
{
	// Setup some states to allow direct rendering into the widget
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_OpaquePaintEvent);
	setAttribute(Qt::WA_NoSystemBackground);
	// Set strong focus to enable keyboard events to be received
	setFocusPolicy(Qt::StrongFocus);
	// Setup the widget geometry
	move(Position);
	resize(Size);
	// Setup the timer
	//timer.setInterval(FrameTime);
}
QSFMLCanvas::~QSFMLCanvas() {}
void QSFMLCanvas::showEvent(QShowEvent*)
{
	if (!initialized)
	{
		// Under X11, we need to flush the commands sent to the server to ensure that
		// SFML will get an updated view of the windows
#ifdef Q_WS_X11
		//XFlush(QX11Info::display());
#endif
		// Create the SFML window with the widget handle
		sf::RenderWindow::create((sf::WindowHandle) winId());

		// Let the derived class do its specific stuff
		OnInit();

		// Setup the timer to trigger a refresh at specified framerate
		//connect(&timer, SIGNAL(timeout()), this, SLOT(repaint()));
		//timer.start();
		//initialized = true;
	}
}
QPaintEngine* QSFMLCanvas::paintEngine() const
{
	return 0;
}
void QSFMLCanvas::paintEvent(QPaintEvent*)
{
	// Let the derived class do its specific stuff
	OnUpdate();
	// Display on screen
	RenderWindow::display();
}
void QSFMLCanvas::OnInit() {}
void QSFMLCanvas::OnUpdate() {}