//
//  Deck.cpp
//  PA1_rg
//
//  Created by rick gessner on 9/26/21.
//

#include "Deck.hpp"
#include <algorithm>
#include <random>

namespace ECE17 {

  Deck::Deck() {
    char theSuitList[]={'C','D','H','S'};
    for(auto theSuit : theSuitList) {
      Faces theFace=Faces::two;
      while(theFace<=Faces::ace) {
        Card theCard{theFace,static_cast<Suits>(theSuit)};
        cards.push_back(theCard);
        theFace=(Faces)((int)theFace+1);
      }
    }
  }

  Deck::Deck(const Deck &aCopy) {
		*this = aCopy;
  }

  Deck& Deck::operator=(const Deck &aDeck) {
		cards= aDeck.cards;
		return *this;
  }

  Deck::~Deck() {
		//student implement this
  }

  size_t Deck::count() {return cards.size();}
  
  Deck& Deck::shuffle() {
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(cards.begin(), cards.end(), g);
		//took from devdocs.io
    return *this;
  }

  CardOpt Deck::take() {
		if(cards.empty()){
			return std::nullopt;
		}
		Card ans = cards.front();
		cards.pop_front();
		return ans;
    return std::nullopt;
  }


  bool Deck::contains(const Card &aCard) const {
		if(cards.empty()){
			return false;
		}
		for(Card theCard: cards){
			if(theCard==aCard){
				return true;
			}
		}
		return false;
  }
  
  //put card back on bottom of deck
  bool Deck::discard(const Card &aCard) {
		cards.push_back(aCard);
		if(aCard == cards.back()){
			return true;
		}
		else{
			return false;
		}
  }

  std::ostream& operator<<(std::ostream &anOutput, const Deck &aDeck) {
		for(Card theCard: aDeck.cards){
		anOutput << theCard<< " ";
		}
		anOutput << "\n";
		return anOutput;
	}
}
