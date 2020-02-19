#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class testFont{
private:
    sf::RenderWindow window{ sf::VideoMode{ 640, 840 }, "SFML window" };
    sf::Text text;
    sf::Font font;

public:
    void test(){
        if (!font.loadFromFile("Roboto-Black.ttf")){
            std::cout<<"error loading font\n";
        }
        
        int number = 0;
        text.setFont(font);
        text.setCharacterSize(24);
        //text.setPosition(sf::Vector2f(200,400) );

        while ( window.isOpen() ) {
            window.clear();

            text.setString(std::to_string(number));
            number++;
            window.draw(text);

            window.display();

            sf::sleep( sf::milliseconds( 10 ));
            sf::Event event;
            while( window.pollEvent(event) ){
                if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    window.close();
                }
            }
        }
    }
};