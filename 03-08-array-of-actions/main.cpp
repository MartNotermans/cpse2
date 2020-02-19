//############################################################################################################
//############################################################################################################
//game loop patern
//############################################################################################################
//############################################################################################################


#include <iostream>
#include <functional>
#include <SFML/Graphics.hpp>

#include <chrono>

#include "ball.hpp"
#include "rectangle.hpp"

class action {
private:
	std::function< bool() > condition;
	std::function< void() > work;
public:
	action(
	   std::function< bool() > condition, 
	   std::function< void() > work
	) : condition( condition ), 
		work( work ) 
	{}

	action(
		sf::Keyboard::Key key,
		std::function< void() > work
	) :
		condition(
			[ key ]()->bool { return sf::Keyboard::isKeyPressed( key ); }
		),
		work(work)
	{}

	action(
		sf::Mouse::Button button,
		std::function< void() > work
	) :
		condition(
			[ button ]()->bool { return sf::Mouse::isButtonPressed( button ); }
		),
		work(work)
	{}

	action(
		std::function< void() > work
	):
		condition(
			[]()->bool {return true;}
		),
		work(work)
	{}

	void operator()(){
		if( condition() ){
			work();
		}
	}
};

int main( int argc, char *argv[] ){
	std::cout << "Starting application 01-05 array of actions\n";

	sf::RenderWindow window{ sf::VideoMode{ 640, 480 }, "SFML window" };
	ball my_ball{ sf::Vector2f{ 320.0, 240.0 } };
	rectangle my_square{ sf::Vector2f{ 70.0, 70.0 },  sf::Vector2f{ 80.0, 80.0 } };

	rectangle wall_up   { sf::Vector2f{ 0.0, 0.0 },  sf::Vector2f{ 640.0, 5.0 } };
	rectangle wall_down { sf::Vector2f{ 0.0, 475.0 },  sf::Vector2f{ 640.0, 5.0 } };
	rectangle wall_left { sf::Vector2f{ 0.0, 0.0 },  sf::Vector2f{ 5.0, 480.0 } };
	rectangle wall_right{ sf::Vector2f{ 635.0, 0.0 },  sf::Vector2f{ 5.0, 480.0 } };

	sf::IntRect result;

	action actions[] = {
		action( sf::Keyboard::Left,  [&](){ my_square.move( sf::Vector2f( -1.0,  0.0 )); }),
		action( sf::Keyboard::Right, [&](){ my_square.move( sf::Vector2f( +1.0,  0.0 )); }),
		action( sf::Keyboard::Up,    [&](){ my_square.move( sf::Vector2f(  0.0, -1.0 )); }),
		action( sf::Keyboard::Down,  [&](){ my_square.move( sf::Vector2f(  0.0, +1.0 )); }),
		action( sf::Mouse::Left,     [&](){ my_square.jump( sf::Mouse::getPosition( window )); }),
		action(						 [&](){ my_ball.move( my_ball.getSpeed() ); }),
	};

	auto previous = std::chrono::system_clock::now();
    auto lag = 0.0;

	while (window.isOpen()) {

		auto current = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsed = current - previous;
        previous = current;
        lag += elapsed.count();

		window.clear();
		
		while (lag >= elapsed.count()) {

			for( auto & action : actions ){
				action();
			}

			my_ball.Bounce(wall_up, window);
			my_ball.Bounce(wall_left, window);
			my_ball.Bounce(wall_right, window);
			my_ball.Bounce(wall_down, window);

			my_ball.Bounce(my_square, window);

			lag -= elapsed.count();
		}

		//draw screen objects
		//window clear stond hier
		my_ball.draw(window);
		my_square.draw(window);
		wall_up.draw(window);
		wall_left.draw(window);
		wall_right.draw(window);
		wall_down.draw(window);
		window.display();

		sf::sleep( sf::milliseconds( 3 ));

        sf::Event event;		
	    while( window.pollEvent(event)){
			if( event.type == sf::Event::Closed ){
				window.close();
			}
		}	
	}

	std::cout << "Terminating application\n";
	return 0;
}

