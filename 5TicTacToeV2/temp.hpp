int newPos = -1;
bool selectingInput = true;
while(selectingInput){
    //get input
    sf::Vector2i mousePos;
    if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) ){
        mousePos = sf::Mouse::getPosition( window );
        
        while( sf::Mouse::isButtonPressed( sf::Mouse::Left ) ){
            sf::sleep( sf::milliseconds( 10 ));
        }
    }
    
    //vergelijk met positions
    for(unsigned int i = 0; i < positions.size(); i++){
        if(mousePos.x > positions[i].x && mousePos.x < positions[i].x+200 &&
        mousePos.y > positions[i].y && mousePos.y < positions[i].y+200)
        {
            newPos = i;
            std::cout<<newPos<<"\n";
            for(unsigned int j = 0; j < game.getMovesList().size(); j++){
                if(game.getMovesList()[j].place == newPos){
                    std::cout<<"input not valit, please try again\n";
                    continue;
                }
            }
            selectingInput = false;
        }
    }
}
game.newMove(newPos);