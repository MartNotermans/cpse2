#include "factory.hpp"

void factory::readingFile(){
    std::ifstream readFile;
    readFile.open(fileName);
    if (readFile.is_open()) {
        std::string tempString = "";
        char tempChar;
        while (readFile.get(tempChar) ) {
            if(tempChar == '\n'){
                objectVector.push_back(tempString);
                tempString = "";
            }else{
                tempString += tempChar;
            }
        }
        if(tempString != ""){
            objectVector.push_back(tempString);
            tempString = "";
        }
    }else{
        std::cout<<"unable to open file\n";
    }
}

void factory::indicateObjects(){
    for(unsigned int i = 0; i < objectVector.size(); i++){
        std::string tempName = "";
        for(long unsigned int j = 0; j < objectVector[i].size(); j++ ){
            if(std::isalpha(objectVector[i].at(j)) ){
                tempName += objectVector[i].at(j);
            }else{
                if(tempName == "window"){
                    makeWindow(objectVector[i]);
                }
                else if(tempName == "rectangle"){
                    std::shared_ptr<rectangleObject> rectangle(new rectangleObject() );
                    drawables.push_back(rectangle);
                    makeRectangle(objectVector[i], rectangle);
                }
                else if(tempName == "circle"){
                    std::shared_ptr<circleObject> circle(new circleObject() );
                    drawables.push_back(circle);
                    makeCircle(objectVector[i], circle);
                }
                else if(tempName == "line"){
                    std::shared_ptr<lineObject> line(new lineObject() );
                    drawables.push_back(line);
                    makeLine(objectVector[i], line);
                }
                else if(tempName == "picture"){
                    std::shared_ptr<pictureObject> picture(new pictureObject() );
                    drawables.push_back(picture);
                    makePicture(objectVector[i], picture);
                }
                else{
                    std::cout<<"unknown object\n";
                }
                tempName = "";
                j = -1; //gets updated to 0 by for loop at line 45
                i++; //to go to the next string
            }
        }
    }
}