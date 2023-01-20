//
//  Game.hpp
//  assignment2
//
//  Created by rick gessner on 10/6/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <map>
#include "Player.hpp"

namespace ECE17 {
      
  class Round; //forward declare...

  using Players = std::map<Player*, float>;

  //student -- declare the Game class here...
  class Game {
  public:
            Game(size_t aCardCount=5, float aMinimumBet=5.0);
            Game(const Game &aCopy);
            ~Game();
            Game& operator=(const Game &aCopy);

    bool    addPlayer(Player &aPlayer);
   
    bool    willStartGame();
    bool    run(float anAnte, std::ostream &anOutput);
    bool    didRun(bool aRunStatus,const std::string &aGameOutput);
                           
  protected:
          
    Game&   payWinner(const std::string &aPlayerName);

    Players players;    
    float   minBet;
    size_t  cardCount;
        
  };

}

#endif /* Game_hpp */
