#include <iostream>
#include <vector>
#include <string>

#include "interface.hpp"

class ticTacToe{
private:
    bool sfOrTxt; //false = sfml, true = txt

    std::vector<move> movesList = {};

    //for testing
    // std::vector<move> movesList = {
    //     move {true, 5},
    //     move {false, 2}
    // };

    bool turn = true; //false = O, true = X

    // 123
    // 456
    // 789
    // the place where the next move is placed
    int placeNextMove; 


    txtInterface txtinterface;
    sfmlInterface sfml;

public:
    ticTacToe(bool sfOrTxt):
    sfOrTxt(sfOrTxt)
    {       
        game();
    }

    void game(){

        //update board
        if(sfOrTxt){
            txtinterface.printBoard(movesList);
        }else{
            placeNextMove = sfml.drawBoard(movesList, false, turn);
        }

        if(movesList.size() != 0){
            turn = !( movesList.back().owner );
        }


        if(sfOrTxt){
            txtinterface.printInstruction(turn);
        }else{
            //sfml
        }
        
        //get input
        if(sfOrTxt){
            placeNextMove = txtinterface.getTxtInput(movesList);
        }else{
            //placeNextMove = sfml.getInput(movesList);
        }

        //undo
        if(placeNextMove == 0){
            if(movesList.size() != 0){ //needs testing
                movesList.pop_back();
                game();
            }else{
                game();
            }
        }

        move newMove(turn, placeNextMove);
        movesList.push_back(newMove);

        //did someone win?
        if( win() ){
            if(sfOrTxt){
                txtinterface.printBoard(movesList);
                if( movesList.back().owner ){
                    std::cout<<"x wins\n";
                }else{
                    std::cout<<"O wins\n";
                }
            }else{
                sfml.drawBoard(movesList, true, turn);
            }
            return;
        }; 

        game(); //runs game again for the next move
    }


    bool win(){

        int lastMovePlace = movesList.back().place;
        bool lastMoveOwner = movesList.back().owner;

        // 012
        // 345
        // 678
        //true is a move from the last player
        bool testArr[9] = {};
        

        for(unsigned int i = 0; i < movesList.size(); i++){
            testArr[ movesList[i].place - 1 ] = (movesList[i].owner == lastMoveOwner);
        }

        //test rows
        int startRow = (lastMovePlace-1)/3*3; //0, 3, 6
        if(testArr[startRow] && testArr[startRow+1] && testArr[startRow+2]){
            return true;
        }
        
        //test columns
        int startColumn = (lastMovePlace-1)%3; //0, 1, 2
        if(testArr[startColumn] && testArr[startColumn+3] && testArr[startColumn+6]){
            return true;
        }
        
        //test digonals
        if(testArr[0] && testArr[4] && testArr[8]){
            return true;
        }
        if(testArr[2] && testArr[4] && testArr[6]){
            return true;
        }
        
        return false;
    }

};