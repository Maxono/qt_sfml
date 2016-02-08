#ifndef PARTICLEGENERATOR_H
#define PARTICLEGENERATOR_H

#define GETTER(TYPE, VAR, NAME) TYPE get##NAME() { return m_##VAR; }
#define SETTER(TYPE, VAR, NAME) void set##NAME(TYPE value) { m_##VAR = value; }

#define PROPERTY(TYPE, VAR, NAME) \
    private: \
    TYPE m_##VAR; \
    public: \
    SETTER(TYPE, VAR, NAME) \
    GETTER(TYPE, VAR, NAME)

#include <SFML/Graphics.hpp>

class ParticleGenerator : public sf::Drawable, public sf::Transformable
{
public:
    ParticleGenerator(int count);

    void setEmitter(sf::Vector2f pos);
    void getEmitter(float& x, float& y)
    {
        x = m_emitter.x;
        y = m_emitter.y;
    }

    void setColor(uint8_t red, uint8_t green, uint8_t blue);
    void getColor(uint8_t& red, uint8_t& green, uint8_t& blue)
    {
        red = m_color.r;
        green = m_color.g;
        blue = m_color.b;
    }
    void update(sf::Time elapsed);
    void setAmount(int amount);
    int getAmount() { return m_amount; }
    void setLife(int value);
    int getLife() { return m_lifetime.asSeconds(); }

#if 1
    SETTER(int, range, Range)
    GETTER(int, range, Range)

    SETTER(int, rotation, Rotation)
    GETTER(int, rotation, Rotation)

    SETTER(int, speed, Speed)
    GETTER(int, speed, Speed)
#else
    PROPERTY(int, range, Range)
    PROPERTY(int, rotation, Rotation)
    PROPERTY(int, speed, Speed)
#endif

    void clearParticles();

private:
    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };

    void resetParticle(std::size_t index);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Vector2f m_emitter;
    int m_amount;
    sf::Color m_color;
#if 1
    int m_range;
    int m_rotation;
    int m_speed;
#endif
    sf::Time m_lifetime;
};

#endif // PARTICLEGENERATOR_H
