#include <vector>

#include "move.hpp"

class ticTacToe{
private:
    std::vector<move> movesList = {};
    bool startTurn = 0; //false = O, true = X
    bool turn = startTurn; //false = O, true = X

    int oScore = 0;
    int xScore = 0;

public:
    bool newMove(int place){ //0 = not valid, 1 is valid
        
        if(validMove(place)){
            if(place == 0){
                //undo
                std::cout<<"undo\n";
                movesList.pop_back();
                turn = !movesList.back().owner;
            }else{
                move newMove(turn, place);
                movesList.push_back(newMove);
                turn = !movesList.back().owner;
            }
            return 1;
        }
        return 0;
    }

    bool validMove(int place){ //0 = not valid, 1 is valid
        if(place >= 0 and place <= 9){
            for(unsigned int i = 0; i < movesList.size(); i++){
                if(place == movesList[i].place){
                    return 0;
                }
            }
        }
        return 1;
    }

    bool win(){
        if(movesList.empty() ){
            return false;
        }

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
            updateScore();
            return true;
        }
        
        //test columns
        int startColumn = (lastMovePlace-1)%3; //0, 1, 2
        if(testArr[startColumn] && testArr[startColumn+3] && testArr[startColumn+6]){
            updateScore();
            return true;
        }
        
        //test digonals
        if(testArr[0] && testArr[4] && testArr[8]){
            updateScore();
            return true;
        }
        if(testArr[2] && testArr[4] && testArr[6]){
            updateScore();
            return true;
        }
        
        return false;
    }

    bool getTurn(){
        return turn;
    }

    std::vector<move> getMovesList(){
        return movesList;
    }

    void newGame(){
        movesList.clear();
        startTurn = !startTurn;
        turn = startTurn;

    }

    void updateScore(){
        if(movesList.back().owner){ //== X
            xScore++;
        }else{
            oScore++;
        }
    }

    int getXScore(){
        return xScore;
    }
    int getOScore(){
        return oScore;
    }
};