#include "canvas.h"
#include <iostream>
#include <string>
#include <QDir>
Canvas::Canvas(QWidget* Parent) : QSFMLCanvas(Parent),
    m_particles(100000)
{
}
void Canvas::OnInit()
{
    m_particles.setEmitter(sf::Vector2f(width()/2, height()/2));
    myClock.restart();
}
void Canvas::OnUpdate()
{
    int widgetWidth = width();
    int widgetHeight = height();

    // detect resize
    if (widgetWidth != m_width || widgetHeight != m_height)
    {
        m_width = widgetWidth;
        m_height = widgetHeight;
        int widgetX, widgetY;
        widgetX = x();
        widgetY = y();
        QRect rect = QRect();
        rect.setX(widgetX);
        rect.setY(widgetY);
        rect.setWidth(widgetWidth);
        rect.setHeight(widgetHeight);
        setGeometry(rect);

        // set new size/view
        RenderWindow::setView(sf::View(sf::FloatRect(widgetX, widgetY, m_width, m_height)));
        RenderWindow::setSize(sf::Vector2u(m_width, m_height));
    }

    // update
    RenderWindow::clear(sf::Color::Black);
    sf::Time elapsed = myClock.restart();
    m_particles.update(elapsed);
    RenderWindow::draw(m_particles);
}

bool Canvas::saveJson(QString filename)
{
    QJsonObject json;

    float emitter_x, emitter_y;
    m_particles.getEmitter(emitter_x, emitter_y);

    QJsonArray emitter;
    emitter.append((int)emitter_x);
    emitter.append((int)emitter_y);

    uint8_t red, green, blue;
    m_particles.getColor(red, green, blue);
    QJsonArray color;
    color.append(red);
    color.append(green);
    color.append(blue);

    json["emitter"] = emitter;
    json["range"] = m_particles.getRange();
    json["rotation"] = m_particles.getRotation();
    json["amount"] = m_particles.getAmount();
    json["speed"] = m_particles.getSpeed();
    json["lifespan"] = m_particles.getLife();
    json["color"] = color;

    QFile file(filename);
    QJsonDocument doc = QJsonDocument(json);

    if (!file.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open the save file");
        return false;
    }

    file.write(doc.toJson());
    return true;
}

bool Canvas::openJson(QString filename)
{
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly))
        return false;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    QJsonObject json = doc.object();

    if (json.isEmpty())
        return false;

    int range = json["range"].toInt();
    int rotation = json["rotation"].toInt();
    int amount = json["amount"].toInt();
    int speed = json["speed"].toInt();
    int life = json["lifespan"].toInt();

    auto color = json["color"];
    if (color.isArray())
    {
        uint8_t red, green, blue;
        auto array = json["color"].toArray();
        red = array.at(0).toInt();
        green = array.at(1).toInt();
        blue = array.at(2).toInt();

        emit colorChanged(red, green, blue);
    }

    auto emitter = json["emitter"];
    if (emitter.isArray())
    {
        float x, y;
        auto array = emitter.toArray();
        x = (float)array.at(0).toDouble();
        y = (float)array.at(1).toDouble();
        sf::Vector2f pos = sf::Vector2f(x, y);
        setEmitter(pos);
    }
    emit rangeChanged(range);
    emit rotationChanged(rotation);
    emit amountChanged(amount);
    emit speedChanged(speed);
    emit lifeChanged(life);

    m_particles.clearParticles();
    return true;
}

void Canvas::setEmitter(sf::Vector2f pos)
{
    qDebug() << "x: " << pos.x << " y: " << pos.y;
    m_particles.setEmitter(pos);
}

void Canvas::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        sf::Vector2f pos = RenderWindow::mapPixelToCoords(sf::Vector2i(e->pos().x(), e->pos().y()));
        setEmitter(pos);
    }
}
