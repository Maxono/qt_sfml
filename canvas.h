#ifndef MYCANVAS_H
#define MYCANVAS_H
#include "qsfmlcanvas.h"
#include <SFML/Graphics.hpp>
#include "particlegenerator.h"
#include <QMouseEvent>
#include <qjsonobject.h>
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qfile.h>
#include <qdebug.h>
#include <qobject.h>

#define SET(name, type, var) \
    void set##name(type var) { m_particles.set##name(var); }

class Canvas : public QSFMLCanvas
{
    Q_OBJECT
public :

    Canvas(QWidget* Parent);
    void OnInit();
    void OnUpdate();

    SET(Range, int, range)
    SET(Rotation, int, angle)
    SET(Amount, int, amount)
    SET(Speed, int, speed)
    SET(Life, int, life)

    void setColor(uint8_t red, uint8_t green, uint8_t blue)
    {
        m_particles.setColor(red, green, blue);
    }

    QColor getColor()
    {
        uint8_t red, green, blue;
        m_particles.getColor(red, green, blue);
        return QColor(red, green, blue);
    }

    bool saveJson(QString filename);
    bool openJson(QString filename);
    void clearParticles() { m_particles.clearParticles(); }

signals:
    void rangeChanged(int range);
    void rotationChanged(int rotation);
    void amountChanged(int amount);
    void speedChanged(int speed);
    void lifeChanged(int life);

    void emitterChanged(int x, int y);
    void colorChanged(uint8_t red, uint8_t green, uint8_t blue);

protected:
    void mousePressEvent(QMouseEvent *e);

private :
    inline void setEmitter(sf::Vector2f pos);
    sf::Clock myClock;
    ParticleGenerator m_particles;

    int m_width;
    int m_height;
};

#undef SET
#endif // MYCANVAS_H
