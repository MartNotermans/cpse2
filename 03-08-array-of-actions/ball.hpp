#ifndef _BALL_HPP
#define _BALL_HPP

#include <SFML/Graphics.hpp>
#include "drawable.hpp"
#include "rectangle.hpp"

class ball: public drawable {
private:
	float size;//radius
	float diameter = size;

	sf::Vector2f speed = {1.0, 1.0};

public:

	ball( sf::Vector2f position, float size = 30.0 );

	void draw( sf::RenderWindow & window ) const override;

	void move( sf::Vector2f delta ) override;

	void jump( sf::Vector2f target ) override; //float
	void jump( sf::Vector2i target ) override; //int

	void Bounce(rectangle target, sf::RenderWindow & window);

	sf::Vector2f getSpeed(){return speed;}
};
#endif
