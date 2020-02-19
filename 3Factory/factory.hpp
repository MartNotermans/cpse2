#ifndef _FACTORY_HPP
#define _FACTORY_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory> //std::shared_ptr

#include "objectsClass.hpp"

class factory{
private:
    std::string fileName;

    std::vector<std::string> objectVector;

    std::vector< std::shared_ptr<drawable> > drawables;
    unsigned int windowWith = 0;
    unsigned int windowHight = 0;

public:
    factory(std::string fileName):
    fileName(fileName)
    {
        readingFile();
        indicateObjects();
    }

    //factory.cpp
    void readingFile();

    void indicateObjects();

    //getNumbers.cpp
    std::pair<int, int> getNumbers(std::string string, int n);

    //getColor.cpp
    sf::Color getColor(std::string color, std::shared_ptr<drawable> object);

    void makeWindow(std::string windowString){
        std::pair<int, int> numbers = getNumbers(windowString, 0);
        windowWith = numbers.first;
        windowHight = numbers.second;
    }

    void makeRectangle(std::string rectangleString, std::shared_ptr<rectangleObject> rectangle){
        std::pair<int, int> position = getNumbers(rectangleString, 0);
        float positionX = position.first;
        float positionY = position.second;

        std::pair<int, int> size = getNumbers(rectangleString, 1);
        float sizeX = size.first;
        float sizeY = size.second;

        rectangle->setPosition(positionX, positionY);
        rectangle->setSize(sizeX, sizeY);
        rectangle->setColor( getColor(rectangleString, rectangle) );
    }

    void makeCircle(std::string circleString, std::shared_ptr<circleObject> circle){
        std::pair<int, int> position = getNumbers(circleString, 0);
        float positionX = position.first;
        float positionY = position.second;

        std::pair<int, int> tempSize = getNumbers(circleString, 1);
        float size = tempSize.first;

        circle->setPosition(positionX, positionY);
        circle->setRadius(size);
        circle->setColor(getColor(circleString, circle) );

    }
    void makeLine(std::string lineString, std::shared_ptr<lineObject> line){
        std::pair<int, int> position1 = getNumbers(lineString, 0);
        float position1X = position1.first;
        float position1Y = position1.second;

        std::pair<int, int> position2 = getNumbers(lineString, 1);
        float position2X = position2.first;
        float position2Y = position2.second;

        line->setStart(position1X, position1Y);
        line->setEnd(position2X, position2Y);
        line->setColor( getColor(lineString, line) );
    }



    void makePicture(std::string pictureString, std::shared_ptr<pictureObject> picture){
        std::pair<int, int> position = getNumbers(pictureString, 0);
        float positionX = position.first;
        float positionY = position.second;



        int fileStart = 0;
        int fileEnd = 0;
        for(long unsigned int i = pictureString.size(); i > 0; i-- ){
            if(pictureString[i] == '('){
                fileStart = i;
                break;
            }
            if(pictureString[i] == ')'){
                fileEnd = i;
            }
        }
        std::string fileName = pictureString.substr(fileStart+1, fileEnd - fileStart - 1);

        picture->setPicture(fileName);
        picture->setPosition(positionX, positionY); 
    }

    void drawObjects(){
        sf::RenderWindow window{ sf::VideoMode{ windowWith, windowHight }, "SFML window" };
        while (window.isOpen()) {

            window.clear();

            sf::Vector2i mousePos = sf::Mouse::getPosition( window );

            for(unsigned int i = 0; i < drawables.size(); i++){
                if(drawables[i]->contains(mousePos) && sf::Mouse::isButtonPressed( sf::Mouse::Left ) ){
                    drawables[i]->jump(mousePos);
                }
                drawables[i]->draw(window);
            }

            window.display();

            sf::sleep( sf::milliseconds( 10 ));

            sf::Event event;		
            while( window.pollEvent(event) ){
                if( event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                    window.close();

                    std::ofstream targetFile (fileName, std::ios::out | std::ios::trunc);
                    if(targetFile.is_open() ){
                        targetFile<<"window("<<windowWith<<","<<windowHight<<")\n";
                        targetFile.close();
                    }
                    for(unsigned int i = 0; i < drawables.size(); i++){
                        std::ofstream targetFile (fileName, std::ios::out | std::ios::app);
                        if(targetFile.is_open() ){
                            targetFile<<drawables[i]->getData()<<"\n";
                            targetFile.close();
                        }


                        //std::cout<<drawables[i]->getData()<<std::endl;
                    }
                }
            }	
        }
    }
};

#endif

// window(800,600)
// rectangle(70,70)(80,80)(Green)
// rectangle(620,90)(150,60)(Blue)
// circle(300,180)(50)(Cyan)
// line(100,200)(250,250)(Yellow)
// picture(100,300)(sfmlLogo.jpg)
