//
//  AutoPlayer.cpp
//  assignment7
//
//  Created by rick gessner on 11/23/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "Player.hpp"

namespace ECE17 {

  Player::Player(const std::string &aName)
    : name(aName) {}
  
  Player::Player(const Player &aCopy) {*this=aCopy;}
   
  Player& Player::operator=(const Player &aCopy) {
    name=aCopy.name;
    hand=aCopy.hand;
    return *this;
  }

  Player::~Player() {}
  
  const Hand& Player::getHand() const {return hand;}

  void  Player::setHand(const Hand &aHand) {    
    hand=aHand;
  }

  const std::string& Player::getName() const  {return name;}

  bool Player::isFolding(float aBalance) const {
		HandRanks rank = hand.determineRank();
		size_t ans= (int)rank;
		if(ans<2){
			return true;
		}
		
		return false;
  }

  bool Player::drawCards(Deck &aDeck, size_t aMaxCount) {
		while(hand.count()!=aMaxCount){
			auto theCard = aDeck.take();
			if(theCard == std::nullopt){
				return false;
			}
			hand.addCard(*theCard);
		}
    return true;
  }

  float Player::placeBet(float aBalance, float aMinBet) {
		if(isFolding(aBalance)){
			return 0;
		}
		HandRanks rank = hand.determineRank();
		float ans;
			ans= 2*(float)rank *25;
		
			if(ans<aMinBet){
				return 0;
			}
		
    float theBet{ans}; 
    return theBet;
  }

  HandRanks Player::discardUnwanted(size_t aMaxCount) {
		HandRanks rank = hand.determineRank();
		CardOpt aCard;
		size_t count=0;
		if((float)rank > 5){
			return rank;
		}
		while(count<5){
			aCard = hand.findBadCards();
			if(aCard==std::nullopt){
				return rank;
			}
			//TODO: dont have time to find error :((
			hand.discard(aCard);
			count++;
		}
		if((float)rank ==1){
			return HandRanks::one_pair;
		}
		else if((float)rank ==2){
			return HandRanks::two_pair;
		}
		if((float)rank ==3){
			return HandRanks::three_kind;
		}
		if((float)rank ==4){
			return HandRanks::straight;
		}
		else return rank;
  }

  std::ostream& operator<<(std::ostream &anOut, const Player &aPlayer) {
    anOut << aPlayer;
    return anOut;
  }

}
