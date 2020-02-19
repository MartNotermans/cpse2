#include <SFML/Graphics.hpp>
#include "rectangle.hpp"

rectangle::rectangle(sf::Vector2f position, sf::Vector2f size):
    drawable (position), size(size)
    {}

void rectangle::draw(sf::RenderWindow & window ) const {
    sf::RectangleShape rectangle;
    rectangle.setSize(size);
    rectangle.setPosition(position);
    window.draw(rectangle);
}

void rectangle::move( sf::Vector2f delta ){
	position += delta;
}

void rectangle::jump( sf::Vector2f target ){
	position = target;
}

void rectangle::jump( sf::Vector2i target ){
	jump( sf::Vector2f( 
		static_cast< float >( target.x ), 
		static_cast< float >( target.y )
	));
}
