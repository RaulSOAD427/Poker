//
//  AutoPlayer.hpp
//  assignment7
//
//  Created by rick gessner on 11/23/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <string>
#include "Deck.hpp"

namespace ECE17 {
  
  class Player {
  public:
    
    Player(const std::string &aName="");
    Player(const Player &aPlayer);
    ~Player();
    Player& operator=(const Player &aPlayer);
      
    const Hand&   getHand() const;
    void          setHand(const Hand &aHand);

    const std::string&  getName() const;
    
    bool          isFolding(float aBalance) const;
    float         placeBet(float aBalance, float aMinBet);
		HandRanks        discardUnwanted(size_t aMaxCount);
    
    bool          drawCards(Deck &aDeck, size_t aMaxCount);
    
    friend std::ostream& operator<<(std::ostream &anOut, const Player &anObj);

  protected:
    std::string name;
    Hand        hand;
  };

}
 
#endif /* Player_hpp */
