#include <SFML/Graphics.hpp>
#include "ball.hpp"
#include "rectangle.hpp"
#include "iostream"

ball::ball( sf::Vector2f position, float size ) :
	drawable (position),
	size{ size }
{}

void ball::draw( sf::RenderWindow & window ) const {
	sf::CircleShape circle;
	circle.setRadius(size);
	circle.setPosition(position);
	window.draw(circle);
}

void ball::move( sf::Vector2f delta ){
	position += delta;
}

void ball::jump( sf::Vector2f target ){
	position = target;
}

void ball::jump( sf::Vector2i target ){
	jump( sf::Vector2f( 
		static_cast< float >( target.x ), 
		static_cast< float >( target.y )
	));
}

void ball::Bounce(rectangle target, sf::RenderWindow & window){
	sf::Rect targetRect( target.getPosition(), target.getSize() );


	//corners as vector2f
	sf::Vector2f leftTop =     {position.x, position.y};
	sf::Vector2f rightTop =    {position.x+diameter, position.y};
	sf::Vector2f leftBottom =  {position.x, position.y+diameter};

	sf::Vector2f horizontalSize = {1, diameter};
		sf::Rect topSide   ( sf::Vector2f{position.x+1, position.y} , horizontalSize);
			sf::RectangleShape topRectangle;
			topRectangle.setPosition(leftTop);
			topRectangle.setSize(horizontalSize);
			topRectangle.setFillColor(sf::Color::Red);
			window.draw(topRectangle);

		sf::Rect bottomSide(leftBottom, horizontalSize);
			sf::RectangleShape bottomRectangle;
			bottomRectangle.setPosition(leftBottom);
			bottomRectangle.setSize(horizontalSize);
			bottomRectangle.setFillColor(sf::Color::Red);
			window.draw(bottomRectangle);

	sf::Vector2f verticalSize = {diameter, 1};
		sf::Rect rightSide(rightTop, verticalSize);
			sf::RectangleShape rightRectangle;
			rightRectangle.setPosition(rightTop);
			rightRectangle.setSize(verticalSize);
			rightRectangle.setFillColor(sf::Color::Red);
			window.draw(rightRectangle);

		sf::Rect leftSide(leftTop, verticalSize);
			sf::RectangleShape leftRectangle;
			leftRectangle.setPosition(leftTop);
			leftRectangle.setSize(verticalSize);
			leftRectangle.setFillColor(sf::Color::Red);
			window.draw(leftRectangle);

	if( topSide.intersects(targetRect) ){ //top
		speed.y *= -1;
	}
	else if( rightSide.intersects(targetRect) ){ //right
		speed.x *= -1;
	}
	else if( leftSide.intersects(targetRect) ){ //left
		speed.x *= -1;
	}
	else if( bottomSide.intersects(targetRect) ){ //bottom
		speed.y *= -1;
	}
}