#ifndef _RECTANGLE_HPP
#define _RECTANGLE_HPP

#include <SFML/Graphics.hpp>
#include "drawable.hpp"

class rectangle: public drawable {
private:
	sf::Vector2f size; //not bottom right corner

public:
    rectangle(sf::Vector2f position, sf::Vector2f size);

    void draw( sf::RenderWindow & window ) const override;

    void move( sf::Vector2f delta ) override;

    void jump( sf::Vector2f target ) override; //float
	void jump( sf::Vector2i target ) override; //int

    sf::Vector2f getPosition(){return position;}
    sf::Vector2f getSize(){return size;}
};

#endif