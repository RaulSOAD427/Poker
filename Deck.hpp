//
//  Deck.hpp
//  assignment2
//
//  Created by rick gessner on 10/6/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef Deck_hpp
#define Deck_hpp

#include <stdio.h>
#include "Hand.hpp"

namespace ECE17 {

  class Deck  {
  public:
    //STUDENT: implement this class from assigment...
    Deck();
    Deck(const Deck &aDeck);
    Deck& operator=(const Deck &aDeck);
    ~Deck();

    CardOpt take(); //remove top card from deck...
    bool    discard(const Card &aCard);
        
    size_t  count(); //retrieve #cards in deck...
    bool    contains(const Card &aCard) const;
    Deck&   shuffle();
        
    friend std::ostream& operator<<(std::ostream &anOutput, const Deck &aDeck);

  protected:
    void initializeCards();
    std::deque<Card> cards; 

  };

}


#endif /* Deck_hpp */
