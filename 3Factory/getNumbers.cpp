#include "factory.hpp"

std::pair<int, int> factory::getNumbers(std::string string, int n){
    int numberStart = 0;
    int numberMiddle = 0;
    int numberEnd = 0;
    int nBracket = 0;
    for(long unsigned int i = 0; i < string.size(); i++ ){
        if(nBracket > n){
            break;
        }
        if(string[i] == '('){
            numberStart = i;
        }
        if(string[i] == ','){
            numberMiddle = i;
        }
        if(string[i] == ')'){
            numberEnd = i;
            nBracket++;
        }
    }
    
    int firstNumber;
    int secondNumber;
    //std::cout<<numberStart<<" , "<<numberMiddle<<" , "<<numberEnd<<std::endl;
    if(numberMiddle > numberStart && numberEnd > numberMiddle){
        //std::cout<<"if\n";
        firstNumber  = std::stoi( string.substr(numberStart+1, numberMiddle-numberStart-1) );
        secondNumber = std::stoi( string.substr(numberMiddle+1, numberEnd-numberMiddle-1 ) );
    }else{
        //std::cout<<"else\n";
        firstNumber  = std::stoi( string.substr(numberStart+1, numberEnd-numberStart-1) );
        secondNumber = firstNumber;
    }
    //std::cout<<'('<<firstNumber<<','<<secondNumber<<std::endl;
    return std::pair<int, int>(firstNumber, secondNumber);
}