#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H
#include <QWidget>
#include <SFML/Graphics.hpp>
#include <QTimer>
#include "particlegenerator.h"
#include <QRect>
#include <qobject.h>

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
    //Q_OBJECT
public:
    explicit QSFMLCanvas(QWidget *parent);
    virtual void showEvent(QShowEvent*);
    virtual QPaintEngine* paintEngine() const;
    virtual void paintEvent(QPaintEvent*);
    virtual ~QSFMLCanvas();
    virtual void OnInit();
    virtual void OnUpdate();
    virtual void setGeometry(QRect rect);
    virtual void setGeometry(int x, int y, int width, int height);

private:
    QTimer m_timer;
    bool m_myInitialized;
};
#endif // QSMLCANVAS_H
