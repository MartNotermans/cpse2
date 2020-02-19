#include "factory.hpp"

sf::Color factory::getColor(std::string string, std::shared_ptr<drawable> object){
    int colorStart = 0;
    int colorEnd = 0;
    for(long unsigned int i = string.size(); i > 0 ; i-- ){
        if(string[i] == '('){
            colorStart = i;
            break;
        }
        if(string[i] == ')'){
            colorEnd = i;
        }
    }

    std::string color = string.substr(colorStart+1, colorEnd - colorStart - 1);
    object->rememberColor(color);


    if(color == "Black"){
        return sf::Color::Black;
    }
    else if(color == "White"){
        return sf::Color::White;
    }
    else if(color == "Red"){
        return sf::Color::Red;
    }
    else if(color == "Green"){
        return sf::Color::Green;
    }
    else if(color == "Blue"){
        return sf::Color::Blue;
    }
    else if(color == "Yellow"){
        return sf::Color::Yellow;
    }
    else if(color == "Magenta"){
        return sf::Color::Magenta;
    }
    else if(color == "Cyan"){
        return sf::Color::Cyan;
    }
    else if(color == "Transparent"){
        return sf::Color::Transparent;
    }
    else{
        return sf::Color::White;
    }
}