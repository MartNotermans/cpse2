#include <vector>

#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

#include <map>
#include <string>

class txtvector{
private:
std::vector<char> charVector = {};
char tempChar;

public:
    txtvector(std::string fileName){
        std::ifstream readFile;
        readFile.open(fileName);
        if (readFile.is_open()) {
            while (readFile.get(tempChar) ) {
                charVector.push_back(tempChar);
            }
        }else{
            std::cout<<"unable to open file\n";
        }
    }
    //return number of characters
    int nChar(){
        return charVector.size();
    }

    //return number of lines
    int nLines(){
        return count(charVector.begin(), charVector.end(), '\n');
    }

    //return number of alphabetic characters
    int nAlphabet(){
        int n = 0;
        for(unsigned int i = 0; i < charVector.size(); i++){
            if(std::isalpha(charVector[i]) ){
                n++;
            }
        }
        return n;
    }

    //turn all characters to small case
    void smallCase(){
        std::for_each( charVector.begin(), charVector.end(), [](char &c) { return c = std::tolower(c); } );
    }

    void alphabet(){
        int count[26] = {0};
        std::for_each( charVector.begin(), charVector.end(), [&count](char &c) {
            if(std::isalpha(c) ){
                count[c - 'a'] += 1;
            }
        } );
        
        for(int i = 0; i < 26; i++){
            char temp = i+'a';
            std::cout<<temp<<" "<<count[i]<<std::endl;
        }
    }



    void method(int n){
        std::cout<<n<<" test\n";
    }

    void tenMostWords(){
        std::map<std::string, int> mapWords;
        std::string tempString = "";
        for(unsigned int i = 0; i < charVector.size(); i++){
            if(std::isalpha(charVector[i]) ){
                tempString += charVector[i];
            }else if(tempString != ""){
                //is the current tempstring in mapWords
                if(mapWords.find(tempString) ==  mapWords.end() ){
                    //no? add it with value 1
                    mapWords.insert ( std::pair<std::string,int> (tempString, 1) );
                    tempString = "";
                }else{
                    //yes? up the value by 1
                    mapWords[tempString] += 1;
                    tempString = "";
                }
            }
        }

        std::pair <std::string, int> tenWords[10];
        for(int i = 0; i < 10; i++){
            tenWords[i].first = "";
            tenWords[i].second = 0;

            //std::cout<<tenWords[i].first<<" "<<tenWords[i].second<<std::endl;
        }

        //iterate through the map
        for(std::map<std::string, int>::iterator it = mapWords.begin(); it != mapWords.end(); ++it){
            //std::cout<<it->second<<" "<<it->first<<std::endl;
            for(int i = 0; i < 10; i++){
                if(it->second > tenWords[i].second){
                    for(int j = 8; j > i; j--){
                        tenWords[j+1].second = tenWords[j].second; //geen error meer, gaat het goed?
                    }
                    tenWords[i].first  = it->first;
                    //std::cout<<tenWords[i].first<<" | "<<it->first<<std::endl;

                    tenWords[i].second = it->second;
                    //std::cout<<tenWords[i].second<<" | "<<it->second<<std::endl;
                    break;
                }
            }
        }

        for(int i = 0; i < 10; i++){
            std::cout<<tenWords[i].first<<" "<<tenWords[i].second<<std::endl;
        }
    }

    


    void printVector(){
        for(unsigned int i = 0; i < charVector.size(); i++){
            std::cout<<charVector[i];
        }
        std::cout<<std::endl;
    }
};