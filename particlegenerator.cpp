#include "particlegenerator.h"

ParticleGenerator::ParticleGenerator(int count) :
        m_amount(count),
        m_particles(count),
        m_vertices(sf::Points, count),
        m_lifetime(sf::seconds(3)),
        m_emitter(0,0),
        m_range(360),
        m_rotation(0),
        m_color(sf::Color(255, 255, 255)),
        m_speed(100)
{
}

void ParticleGenerator::setEmitter(sf::Vector2f pos)
{
    m_emitter = pos;
}


void ParticleGenerator::setColor(uint8_t red, uint8_t green, uint8_t blue)
{
    m_color = sf::Color(red, green, blue);
}

void ParticleGenerator::update(sf::Time elapsed)
{
   for(std::size_t i=0; i<m_particles.size(); i++)
   {
       Particle& p = m_particles[i];
       p.lifetime -= elapsed;

       if (p.lifetime <= sf::Time::Zero)
           resetParticle(i);

       m_vertices[i].position += p.velocity * elapsed.asSeconds();

       float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
       m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
   }
}

void ParticleGenerator::setAmount(int amount)
{
    m_amount = amount;
    m_particles.resize(amount);
    m_vertices.resize(amount);
}

void ParticleGenerator::setLife(int amount)
{
    m_lifetime = sf::seconds(amount);
}

void ParticleGenerator::clearParticles()
{
    for(std::size_t i=0; i<m_particles.size(); i++)
    {
       resetParticle(i);
    }
}

void ParticleGenerator::resetParticle(std::size_t index)
{
    float angle = ((std::rand() % (m_range)) + (360 - m_rotation)) * 3.14f / 180.0f;
    float speed = (std::rand() % m_speed);
    m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
    m_particles[index].lifetime = sf::milliseconds((std::rand() % m_lifetime.asMilliseconds()) + 1000);
    m_vertices[index].color = m_color;

    m_vertices[index].position = m_emitter;
}

void ParticleGenerator::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    states.texture = nullptr;

    target.draw(m_vertices, states);
}
