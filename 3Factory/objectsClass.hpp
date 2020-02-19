#include <SFML/Graphics.hpp>

class drawable{
protected:
    sf::Vector2f position;

public:
    virtual bool contains(sf::Vector2i positionToCheck) = 0;
    virtual void jump(sf::Vector2i newPosition) = 0;
    virtual void draw(sf::RenderWindow & window) const = 0;
    virtual std::string getData() = 0;
    virtual void rememberColor(std::string colorPar) = 0;
    
};

class rectangleObject: public drawable{
private:
    sf::RectangleShape rectangle;
    sf::Vector2f size;

    sf::Color sfColor;
    std::string strColor;

public:    
    rectangleObject(){}

    void setPosition(float positionX, float positionY){
        position = {positionX, positionY};
        rectangle.setPosition(position);
    }

    void setSize(float sizeX, float sizeY){
        size = {sizeX, sizeY};
        rectangle.setSize( size );
    }

    void setColor(sf::Color colorPar){
        sfColor = colorPar;
        rectangle.setFillColor(sfColor);
    }

    void rememberColor(std::string colorPar){
        strColor = colorPar;
    }

    bool contains(sf::Vector2i positionToCheck)override{
        float tempX = positionToCheck.x;
        float tempY = positionToCheck.y;
        sf::Vector2f tempFloatToCheck(tempX,tempY);
        sf::Rect rectangleRect(position, size);
        return rectangleRect.contains(tempFloatToCheck);
    }

    void jump(sf::Vector2i newPosition)override{
        float tempX = newPosition.x;
        float tempY = newPosition.y;
        position = {tempX -(size.x/2), tempY - (size.y/2)};
        rectangle.setPosition(position);
    }

    void draw(sf::RenderWindow & window) const override{
        window.draw(rectangle);
    }

    std::string getData(){
        std::string returnString = "rectangle(";
        int intPositionX = position.x;
        int intPositionY = position.y;
        int intSizeX = size.x;
        int intSizeY = size.y;
        returnString += std::to_string(intPositionX);
        returnString += ',';
        returnString += std::to_string(intPositionY);
        returnString += ")(";
        returnString += std::to_string(intSizeX);
        returnString += ',';
        returnString += std::to_string(intSizeY);
        returnString += ")(";
        returnString += strColor;
        returnString += ")";
        return returnString;
    }
};

class circleObject: public drawable{
private:
    sf::CircleShape circle;
    float radius;

    sf::Color sfColor;
    std::string strColor;

public:    
    circleObject(){}

    void setPosition(float positionX, float positionY){
        position = {positionX, positionY};
        circle.setPosition( position );
    }

    void setRadius(float size){
        radius = size;
        circle.setRadius(radius);
    }

    void setColor(sf::Color colorPar){
        sfColor = colorPar;
        circle.setFillColor(sfColor);
    }

    void rememberColor(std::string colorPar){
        strColor = colorPar;
    }

    bool contains(sf::Vector2i positionToCheck)override{
        float tempX = positionToCheck.x;
        float tempY = positionToCheck.y;
        sf::Vector2f tempFloatToCheck(tempX,tempY);
        sf::Vector2f temp(radius*2, radius*2);
        sf::Rect circleRect(position, temp);
        return circleRect.contains(tempFloatToCheck);
    }

    void jump(sf::Vector2i newPosition)override{
        position = {newPosition.x-(radius), newPosition.y-(radius)};
        circle.setPosition(position);
    }

    void draw(sf::RenderWindow & window) const override{
        window.draw(circle);
    }

    std::string getData(){
        std::string returnString = "circle(";
        int intPositionX = position.x;
        int intPositionY = position.y;
        int intradius = radius;
        returnString += std::to_string(intPositionX);
        returnString += ',';
        returnString += std::to_string(intPositionY);
        returnString += ")(";
        returnString += std::to_string(intradius);
        returnString += ")(";
        returnString += strColor;
        returnString += ")";
        return returnString;
    }
};

class lineObject: public drawable{
private:
    sf::Vertex lineStart; // is drawable position
    sf::Vector2f endPosition;
    sf::Vertex lineEnd;
    sf::Vertex line[2];

    sf::Color sfColor;
    std::string strColor;

public:
    lineObject(){}

    void setStart(float positionX, float positionY){
        position = sf::Vector2f(positionX, positionY);
        lineStart.position = position;
    }
    void setEnd(float positionX, float positionY){
        endPosition = sf::Vector2f(positionX, positionY);
        lineEnd.position = endPosition;
    }

    void setColor(sf::Color colorPar){
        sfColor = colorPar;
        lineStart.color  = sfColor;
        lineEnd.color = sfColor;
    }

    void rememberColor(std::string colorPar){
        strColor = colorPar;
    }

    bool contains(sf::Vector2i positionToCheck)override{
        float tempX = positionToCheck.x;
        float tempY = positionToCheck.y;
        sf::Vector2f tempFloatToCheck(tempX,tempY);
        sf::Rect rectangleRect(position, sf::Vector2f( (endPosition.x - position.x), (endPosition.y - position.y) ) );
        return rectangleRect.contains(tempFloatToCheck);
    }

    void jump(sf::Vector2i newPosition)override{
        float with = endPosition.x-position.x;
        float hight = endPosition.y-position.y;

        float newX = newPosition.x;
        float newY = newPosition.y;
        position = {newX-(with/2), newY-(hight/2)};
        lineStart.position = position;

        endPosition = {position.x + with, position.y + hight};
        lineEnd.position = endPosition;
    }

    void draw(sf::RenderWindow & window) const override{
        sf::Vertex line[2] = {lineStart, lineEnd};
        window.draw(line, 2, sf::Lines);
    }

    std::string getData(){
        std::string returnString = "line(";
        int intPositionX = position.x;
        int intPositionY = position.y;
        int intEndPositionX = endPosition.x;
        int intEndPositionY = endPosition.x;
        returnString += std::to_string(intPositionX);
        returnString += ',';
        returnString += std::to_string(intPositionY);
        returnString += ")(";
        returnString += std::to_string(intEndPositionX);
        returnString += ',';
        returnString += std::to_string(intEndPositionY);
        returnString += ")(";
        returnString += strColor;
        returnString += ")";
        return returnString;
    }
};

class pictureObject: public drawable{
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f size = {0,0};

    std::string fileName;

    sf::Color sfColor = sf::Color::White;
    std::string strColor = "White";

public:    
    pictureObject(){}

    void setPosition(float positionX, float positionY){
        position = {positionX, positionY};
        sprite.setPosition(positionX, positionY);
    }

    void setPicture(std::string fileNamePar){
        fileName = fileNamePar;
        if (!texture.loadFromFile(fileName)){
            std::cout<<"could not load fom file\n";
        }
        sf::Vector2u temp = texture.getSize();
        size.x = temp.x;
        size.y = temp.y;
        sprite.setTexture(texture);
    }

    void rememberColor(std::string colorPar){
        strColor = colorPar;
    }

    bool contains(sf::Vector2i positionToCheck)override{
        float tempX = positionToCheck.x;
        float tempY = positionToCheck.y;
        sf::Vector2f tempFloatToCheck(tempX,tempY);
        sf::Rect rectangleRect(position, size);
        return rectangleRect.contains(tempFloatToCheck);
    }

    void jump(sf::Vector2i newPosition)override{
        float tempX = newPosition.x;
        float tempY = newPosition.y;
        position = {tempX -(size.x/2), tempY - (size.y/2)};
        sprite.setPosition(position);
    }

    void draw(sf::RenderWindow & window) const override{
        window.draw(sprite);
    }

    std::string getData(){
        std::string returnString = "picture(";
        int intPositionX = position.x;
        int intPositionY = position.y;
        returnString += std::to_string(intPositionX);
        returnString += ',';
        returnString += std::to_string(intPositionY);
        returnString += ")(";
        returnString += fileName;
        returnString += ")";
        return returnString;
    }
};