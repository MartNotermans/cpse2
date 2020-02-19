#include <iostream>
#include <vector>

#include "ticTacToe.hpp"

class txtInterface{
private:
    ticTacToe game;
    bool running = true;
public:

    txtInterface(){
        while(running){
                printInstruction(game.getTurn() );
                printBoard(game.getMovesList() );
                getTxtInput();
            if(game.win() ){
                winMessage(game.getMovesList() );
            }
        }
    }

    void printInstruction(bool turn){
        std::cout<<"it is ";
        if(turn){ //false = O, true = X
            std::cout<<"x's turn\n";
        }else{
            std::cout<<"O's turn\n";
        }
        std::cout<<"type 1 - 9 to make a move\npess 0 for undo\n";
    }

    void printBoard(std::vector<move> movesList){
                                    //          123    456    789
            std::string boardString = ("#####\n#___#\n#___#\n#___#\n#####\n");
                                    //  012345 678901 234567 890123 45678901 2
                                    //             10          20         30

            int loopUpTable[10] = {-1,7,8,9,13,14,15,19,20,21};
            for(unsigned int i = 0; i < movesList.size(); i++){
                if(movesList[i].owner){
                    boardString[ loopUpTable[ movesList[i].place ] ] = 'X';
                }else{
                    boardString[ loopUpTable[ movesList[i].place ] ] = 'O';
                }
            }

            std::cout<<boardString;
        }

    void getTxtInput(){
        char tempChar; 
        std::cin>>tempChar;

        if(isdigit(tempChar ) ){
            int placeNextMove = tempChar - '0';
            if(game.newMove(placeNextMove) ){
                std::cout<<"valit input\n";
                return;
            }else{
                std::cout<<"input not valit, please try again\n";
                return getTxtInput();
            }
        }
        std::cout<<"input not valit, please try again\n";
        return getTxtInput();
    }

    void winMessage(std::vector<move> movesList){
        printBoard(movesList);
        std::cout<<"The winner is: ";
        if(movesList.back().owner){
            //X
            std::cout<<"X\n";
        }else{
            //O
            std::cout<<"O\n";
        }
        std::cout<<"--- X: "<<game.getXScore()<<"   O: "<<game.getOScore()<<" ---\n";
        
        std::cout<<"new game? press 1 for yes, 0 for no\n";
        char tempChar; 
        std::cin>>tempChar;
        if(tempChar == '1'){
            game.newGame();
        }else{
            running = false;
        }
    }
};