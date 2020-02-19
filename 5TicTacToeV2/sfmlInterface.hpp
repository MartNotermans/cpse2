#include <SFML/Graphics.hpp>
#include <memory> //std::shared_ptr

#include "ticTacToe.hpp"

class object{
protected:
    sf::Vector2f position;
public:
    virtual void draw(sf::RenderWindow & window) const = 0;
};

class cross: public object{
private:

    sf::RectangleShape part1;

    sf::RectangleShape part2;

public:
    cross(sf::Vector2f newPosition){
        position = newPosition;

        part1.setPosition(position);
        part1.setSize(sf::Vector2f(200,50) );
        part1.setRotation(45.0);
        part1.move(45,10);
        part1.setFillColor(sf::Color::White);

        part2.setPosition(position);
        part2.setSize(sf::Vector2f(200,50) );
        part2.setRotation(135.0);
        part2.move(190,45);
        part2.setFillColor(sf::Color::White);
    }

    void draw(sf::RenderWindow & window) const{
        window.draw(part1);
        window.draw(part2);
    }
};

class circle: public object{
private:
    sf::CircleShape outer;
    sf::CircleShape inner;

public:
    circle(sf::Vector2f newPosition){
        position = newPosition;
        outer.setPosition(position);
        outer.setRadius(90);
        outer.move(10,10);
        outer.setFillColor(sf::Color::White);

        inner.setPosition(position);
        inner.setRadius(60);
        inner.move(40,40);
        inner.setFillColor(sf::Color::Black);


    }

    void draw(sf::RenderWindow & window) const override{
        window.draw(outer);
        window.draw(inner);
    }
};


class sfmlInterface{
private:
    float newOriginX = 0;
    float newOriginY = 200;

    unsigned int screenSizeX = 840;
    unsigned int screenSizeY = 840;
    float floatScreenSizeX = screenSizeX;



    std::vector<sf::Vector2f> positions = {
        sf::Vector2f {floatScreenSizeX-200,0},          //pos0
        sf::Vector2f {newOriginX, newOriginY},          //pos1
        sf::Vector2f {newOriginX+220, newOriginY},      //pos2
        sf::Vector2f {newOriginX+440, newOriginY},      //pos3
        sf::Vector2f {newOriginX, newOriginY+220},      //pos4
        sf::Vector2f {newOriginX+220, newOriginY+220},  //pos5
        sf::Vector2f {newOriginX+440, newOriginY+220},  //pos6
        sf::Vector2f {newOriginX, newOriginY+440},      //pos7
        sf::Vector2f {newOriginX+220, newOriginY+440},  //pos8
        sf::Vector2f {newOriginX+440, newOriginY+440}   //pos9
    };


    sf::RectangleShape ver1;
    sf::RectangleShape ver2;
    sf::RectangleShape hor1;
    sf::RectangleShape hor2;

    sf::RectangleShape undo;
    sf::Text undoText;

    sf::Text text;
    sf::Font font;


    ticTacToe game;

    sf::RenderWindow window{ sf::VideoMode{ screenSizeX, screenSizeY }, "SFML window" };

    //getInput
    bool inputPressed = false;
    int newPos = -1;

public:
    //int drawBoard(std::vector<move> movesList, bool win, bool turn){
    sfmlInterface(){


        initialiseObjects();

        
        

        while ( window.isOpen() ) {

            if(game.win() ){
                if(game.getTurn() ){
                        text.setString("X wins");
                    }else{
                        text.setString("O wins");
                    }
            }else{
                if(game.getTurn() ){
                    text.setString("O's turn");
                }else{
                    text.setString("X's turn");
                }
            }

            window.clear();

            window.draw(ver1);
            window.draw(ver2);
            window.draw(hor1);
            window.draw(hor2);

            window.draw(undo);
            
            window.draw(text);
            window.draw(undoText);

            for(unsigned int i = 0; i < game.getMovesList().size(); i++){
                if(game.getMovesList()[i].owner){
                    //x
                    cross object( positions[ game.getMovesList()[i].place ] );
                    object.draw(window);
                }else{
                    //O
                    circle object( positions[ game.getMovesList()[i].place ] );
                    object.draw(window);
                }
            }

            window.display();

            getInput();
            

            sf::sleep( sf::milliseconds( 10 ));


            sf::Event event;
            while( window.pollEvent(event) ){
                if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    window.close();
                }
            }
        }
    }

    void initialiseObjects(){
        ver1.setPosition(sf::Vector2f(newOriginX+200, newOriginY) );
        ver1.setSize(sf::Vector2f(20,640) );

        ver2.setPosition(sf::Vector2f(newOriginX+420, newOriginY) );
        ver2.setSize(sf::Vector2f(20,640) );

        hor1.setPosition(sf::Vector2f(newOriginX, newOriginY+200) );
        hor1.setSize(sf::Vector2f(640,20) );

        hor2.setPosition(sf::Vector2f(newOriginX, newOriginY+420) );
        hor2.setSize(sf::Vector2f(640,20) );

        undo.setPosition(sf::Vector2f(floatScreenSizeX-200, 0) );
        undo.setSize(sf::Vector2f(200,200) );

        //text
        if (!font.loadFromFile("Roboto-Black.ttf")){
            std::cout<<"error loading font\n";
        }

        text.setFont(font);
        text.setCharacterSize(100);
        text.setPosition(sf::Vector2f(20,0) );

        undoText.setString("undo");
        undoText.setFont(font);
        undoText.setCharacterSize(90);
        undoText.setFillColor(sf::Color::Black );
        undoText.setPosition(sf::Vector2f(floatScreenSizeX-200, 0) );
    }

    void getInput(){
        sf::Vector2i mousePos;
        if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && !inputPressed ){
            inputPressed = true;
            mousePos = sf::Mouse::getPosition( window );
        }
        if( !sf::Mouse::isButtonPressed(sf::Mouse::Left) && inputPressed){
            
            for(unsigned int i = 0; i < positions.size(); i++){
                if(
                    mousePos.x > positions[i].x &&
                    mousePos.x < positions[i].x+200 &&
                    mousePos.y > positions[i].y &&
                    mousePos.y < positions[i].y+200
                    )
                {
                    newPos = i;
                    std::cout<<newPos<<" newPos\n";
                }
            }
            std::cout<<newPos<<"\n";
            game.newMove(newPos);
            
            inputPressed = false;
            newPos = -1;
        }

    }

};
