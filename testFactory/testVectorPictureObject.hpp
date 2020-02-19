#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>

#include <memory> //std::shared_ptr


class drawable{
public:
    virtual void draw(sf::RenderWindow & window) = 0;
};

class pictureObject: public drawable{
private:
    sf::Texture texture;
    sf::Sprite sprite;
public:
    pictureObject(){
        texture.loadFromFile("sfmlLogo.jpg");
        sprite.setTexture(texture);
        sprite.setPosition(100.0,300.0);
    }

    ~pictureObject(){
        std::cout<<"destructor pictureObject\n";
    }

    void draw(sf::RenderWindow & window){
        window.draw(sprite);
    }
};

class vectorclass{
    std::vector<std::shared_ptr<drawable> >objects;

public:

    void makeObjects(){
        std::shared_ptr<pictureObject> picture(new pictureObject() );

        objects.push_back(picture);
    }


    void drawObjects(){
        sf::RenderWindow window{ sf::VideoMode{ 800, 600 }, "SFML window" };
        while ( window.isOpen() ) {
            window.clear();

            objects[0]->draw(window);

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