#ifndef _DRAWABLE_HPP
#define _DRAWABLE_HPP

#include <SFML/Graphics.hpp>

class drawable{
protected:
    sf::Vector2f position;
public:
    drawable(sf::Vector2f position):
    position(position)
    {}

    virtual void draw(sf::RenderWindow & window) const = 0;
    virtual void move(sf::Vector2f delta) = 0;
    virtual void jump( sf::Vector2f target ) = 0; //float
	virtual void jump( sf::Vector2i target ) = 0; //int
};

#endif