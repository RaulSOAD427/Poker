//
//  Card.hpp
//  Assignment1
//
//  Created by rick gessner on 10/12/20.
//

#ifndef Card_hpp
#define Card_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <optional>

namespace ECE17 {

  enum class Suits
    : char {clubs='C', diamonds='D', hearts='H', spades='S'};

  enum class Faces
    : int {noface=0, two=2, three, four, five, six, seven, eight,
           nine, ten, jack, queen, king, ace};

  class Card {
  public:
    
    Card(Faces aFace=Faces::ace, Suits aSuit=Suits::clubs);
    Card(const Card &aCopy);
    ~Card();
    
    Faces getFace() const {return face;}
    Suits getSuit() const {return suit;}
    
    Card& operator=(const Card& aCopy);
    bool  operator<(const Card& aCopy) const;
    bool  operator==(const Card& aCopy) const;
            
    //this method will print the card to output stream
    friend std::ostream& operator<<(std::ostream &anOutput,
                                    const Card &aCard);
    
  protected:
    Suits suit;
    Faces face;
  };

  using CardOpt = std::optional<Card>;

}

#endif /* Card_hpp */
