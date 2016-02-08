#include "qsfmlcanvas.h"
#ifdef Q_WS_X11
#include <Qt/qx11info_x11.h>
#include <X11/Xlib.h>
#endif
#include <iostream>
QSFMLCanvas::QSFMLCanvas(QWidget* Parent) : QWidget(Parent),
    m_myInitialized (false)
{
    // Setup some states to allow direct rendering into the widget
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    // Set strong focus to enable keyboard events to be received
    setFocusPolicy(Qt::StrongFocus);
    // Setup the widget geometry
    m_timer.setInterval(30);
}
QSFMLCanvas::~QSFMLCanvas() {}
void QSFMLCanvas::showEvent(QShowEvent*)
{
    if (!m_myInitialized)
    {
        // Under X11, we need to flush the commands sent to the server to ensure that
        // SFML will get an updated view of the windows
#ifdef Q_WS_X11
        XFlush(QX11Info::display());
#endif
        // Create the SFML window with the widget handle
        RenderWindow::create((sf::WindowHandle) winId());
        RenderWindow::create((sf::WindowHandle) winId());
        // Let the derived class do its specific stuff
        OnInit();
        // Setup the timer to trigger a refresh at specified framerate
        connect(&m_timer, SIGNAL(timeout()), this, SLOT(repaint()));
        m_timer.start();
        m_myInitialized = true;
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
void QSFMLCanvas::OnInit()
{
}
void QSFMLCanvas::OnUpdate() {}

void QSFMLCanvas::setGeometry(QRect rect)
{
    int x, y, width, height;
    rect.getRect(&x, &y, &width, &height);
    move(QPoint(x,y));
    resize(QSize(width, height));
}

void QSFMLCanvas::setGeometry(int x, int y, int width, int height)
{
    move(QPoint(x,y));
    resize(QSize(width, height));
}
