//
//  Hand.cpp
//  Assignment1
//
//  Created by rick gessner on 10/12/20.
//

#include "Hand.hpp"
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <deque>

namespace ECE17 {
	using CardList = std::deque<Card>;
  using CardCountMap = std::map<Faces, size_t>;
using HandAnalyzer = bool (*)(CardList);
  Hand::Hand() {
  }

  Hand::Hand(const Hand &aCopy) {
    *this=aCopy;
  }

  Hand::~Hand() {}

  Hand& Hand::operator=(const Hand& aCopy) {
    cards=aCopy.cards;
    return *this;
  }

  bool Hand::operator<(const Hand& aHand) const {
		HandRanks theRank = determineRank();
		HandRanks otherRank = aHand.determineRank();
		if(theRank==otherRank){
			 return (highCard() < aHand.highCard());
		}
		return theRank < otherRank;
  }
	
bool Hand::operator==(const Hand& aHand) const {
	return (int)determineRank() == (int)aHand.determineRank();
}

/*
 std::fstream theStream;
 theStream.open("filename", std::ios::read | std::ios::read | std::ios::read);
 */

  bool Hand::addCard(const Card &aCard) {
		size_t size =cards.size();
		cards.push_back(aCard);
		if((size+=1)==cards.size()){
			return true;
		}
		else{
			return false;
		}
  }

  CardOpt Hand::discard(Faces aFace, Suits aSuit) {
		int i=0;
			for(Card theCard: cards){
				if(theCard.getFace() == aFace && theCard.getSuit()==aSuit){
					cards.erase(cards.begin(),cards.begin()+i);
					return theCard;
				}
				i++;
			}
			//if does not return theCard
			return std::nullopt;
  }
CardOpt Hand::discard(CardOpt aCard) {
	int i=0;
		for(Card theCard: cards){
			if(theCard ==aCard){
				cards.erase(cards.begin(),cards.begin()+i);
				return theCard;
			}
			i++;
		}
		//if does not return theCard
		return std::nullopt;
}


  size_t Hand::count() const {
    return cards.size();    
  }

  bool Hand::contains(const Card &aCard) const {
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

  std::ostream& operator<<(std::ostream &anOutput, const Hand &aHand) {
    for(auto theCard : aHand.cards) {
      anOutput << theCard << " ";
    }
    return anOutput;
  }

  //what is the highest card in the hand?
  Faces Hand::highCard() const {
    Faces holder=Faces::two;
		for(Card theCard: cards){
			if((int)theCard.getFace()>(int)holder){
				holder = theCard.getFace();
			}
		}
		return holder;
  }

  //Determine the kind of hand (rank) we have, given a set of cards...
  HandRanks Hand::determineRank() const {
		if(determinePrimeVolts(cards)){
			return HandRanks::prime_volts;
		}
		else if(determineRoyalFlush(cards)){
			return HandRanks::royal_flush;
		}
		else if(determineStraightFlush(cards)){
			return HandRanks::straight_flush;
		}
		else if(determineFourOfKind(cards)==2){
			return HandRanks::straight_flush;
		}
		else if(determineFourOfKind(cards)==1){
			return HandRanks::four_kind;
		}
		
		else if(determineFullHouse(cards)==2){
			return HandRanks::four_kind;
		}
		else if(determineFullHouse(cards)==1){
			return HandRanks::full_house;
		}

		else if(determinePrimeFlush(cards)){
			return HandRanks::prime_flush;
		}
		else if(determineFlush(cards)){
			return HandRanks::flush;
		}
		else if(determinePrime(cards)){
			return HandRanks::prime;
		}
		else if(determineStraight(cards)){
			return HandRanks::straight;
		}
		else if(determineThreeOfAKind(cards)==2){
			return HandRanks::straight;
		}
		else if(determineThreeOfAKind(cards)==1){
			return HandRanks::three_kind;
		}
		else if(determineTwoPair(cards)==2){
			return HandRanks::three_kind;
		}
		else if(determineTwoPair(cards)==1){
			return HandRanks::two_pair;
		}
		else if(determinePair(cards)==2){
			return HandRanks::two_pair;
		}
		else if(determinePair(cards)==1){
			return HandRanks::one_pair;
		}
		else{
			return HandRanks::high_card;
		}
  }
  //Helper methods

	bool Hand::determineStraight(CardList myHand) const{
		if(myHand.empty()){
			return false;
		}
		std::sort(myHand.begin(),myHand.end());
		for(size_t i=0; i<myHand.size()-1;i++){
			if((int) myHand[i].getFace()-(int) myHand[i+1].getFace() != -1){
				return false;
			}
		}
		return true;
	}
	

	bool Hand::determineFlush(CardList myHand) const{
		if(myHand.empty()){
			return false;
		}
		ECE17::Suits theSuit = myHand[0].getSuit();
		for(size_t i=1;i<myHand.size();i++){
			if(myHand[i].getSuit() != theSuit){
				return false;
			}
		}
		return true;
	}

	bool Hand::determineVolts(CardList myHand) const{
		if(myHand.empty()){
			return false;
		}
		
		ECE17::Suits theSuit = static_cast<Suits>('V');
		for(size_t i=0;i<myHand.size();i++){
			if(myHand[i].getSuit() != theSuit){
				return false;
			}
		}
		return true;
	}


	bool Hand::determinePrime(CardList myHand) const{
		if(myHand.empty()){
			return false;
		}
		
		static std::vector<int> primes = {2, 3, 5, 7, 11,12, 13,14,15} ;
		for(size_t i=0;i<myHand.size();i++){
				size_t flag = std::count(myHand.cbegin(), myHand.cend(), myHand[i].getFace());
			if(flag==0){
				return false;
			}
		}
		return true;
	}

	bool Hand::determineStraightFlush(CardList myHand) const{
		if(myHand.empty()){
			return false;
		}
		return determineStraight(myHand) && determineFlush(myHand);
	}

bool Hand::determinePrimeFlush(CardList myHand) const{
	if(myHand.empty()){
		return false;
	}
	return determinePrime(myHand) && determineFlush(myHand);
}

	bool Hand::determinePrimeVolts(CardList myHand) const{
		if(myHand.empty()){
			return false;
		}
		return determinePrime(myHand) && determineVolts(myHand);
	}


	int Hand::determinePair(CardList myHand) const{
		if(myHand.empty()){
			return 0;
		}
		ECE17::Suits theSuit = static_cast<Suits>('V');
		std::sort(myHand.begin(),myHand.end());
		for(size_t i=0; i<myHand.size()-1;i++){
			if((int) myHand[i].getFace() == (int) myHand[i+1].getFace()){
				if(myHand[i].getSuit() ==theSuit || myHand[i+1].getSuit() ==theSuit){
					return 2;
				}
				return 1;
			}
		}
		return 0;
	}

	int Hand::determineTwoPair(CardList myHand) const{
		if(myHand.empty()){
			return false;
		}
		int flag=0;
		ECE17::Suits theSuit = static_cast<Suits>('V');
		size_t count = 0;
		std::sort(myHand.begin(),myHand.end());
		for(size_t k=0;k<myHand.size()-1; k++){
			if((int) myHand[k].getFace() == (int) myHand[k+1].getFace()){
				count++;
				if(myHand[k].getSuit() == theSuit ||myHand[k+2].getSuit() == theSuit){
					flag=1 ;}																																	
			}
			if(count==2){
				if(flag==1)	{
					return 2;
			}																					
				return 1;
			}
		}
		return 0;
	}
//2, 3, 5, 7, 11, 13, 17, 19, 23 and 29

	int Hand::determineThreeOfAKind(CardList myHand) const{
		if(myHand.empty()){
			return false;
		}
		ECE17::Suits theSuit = static_cast<Suits>('V');
		for(size_t i=0; i<myHand.size()-2; i++) {
			if((int) myHand[i].getFace() == (int) myHand[i+1].getFace()){
				if((int) myHand[i].getFace() == (int) myHand[i+2].getFace()){
					if(myHand[i].getSuit() == theSuit ||
						 myHand[i+1].getSuit() == theSuit ||
						 myHand[i+2].getSuit() == theSuit){
							 return 2;}
					return 1;
				}
			}
		}
		return 0;
	}

	int Hand::determineFullHouse(CardList myHand) const{ 
		if(myHand.empty()){
			return false;
		}
		ECE17::Suits theSuit = static_cast<Suits>('V');
		size_t i = 0;
		std::sort(myHand.begin(),myHand.end());
		if((int) myHand[i].getFace() == (int) myHand[i+2].getFace()){ //
			if((int) myHand[i+3].getFace() == (int) myHand[i+4].getFace()){
			 if(myHand[i].getSuit() == theSuit ||
				myHand[i+1].getSuit() == theSuit ||
					myHand[i+2].getSuit() == theSuit ||
					myHand[i+3].getSuit() == theSuit ||
				myHand[i+4].getSuit() == theSuit){
				return 2;}
				return 1;																					 
			}
		}
		else if((int) myHand[i+2].getFace() == (int) myHand[i+4].getFace()){
			if((int) myHand[i].getFace() == (int) myHand[i+1].getFace()){
				if(myHand[i].getSuit() == theSuit ||
				myHand[i+1].getSuit() == theSuit ||
				myHand[i+2].getSuit() == theSuit ||
				myHand[i+3].getSuit() == theSuit ||
				myHand[i+4].getSuit() == theSuit){
				return 2;}
				return 1;	
			}
		}
		return 0;
	}


	int Hand::determineFourOfKind(CardList myHand) const{
		if(myHand.empty()){
			return false;
		}
		ECE17::Suits theSuit = static_cast<Suits>('V');
		std::sort(myHand.begin(),myHand.end());
		for(size_t i=0; i<myHand.size()-3; i++) {
			if((int) myHand[i].getFace() == (int) myHand[i+1].getFace()){
				if((int) myHand[i+1].getFace() == (int) myHand[i+2].getFace()){
					if((int) myHand[i+2].getFace() == (int) myHand[i+3].getFace()){
						if(myHand[i].getSuit() == theSuit ||
						myHand[i+1].getSuit() == theSuit ||
						myHand[i+2].getSuit() == theSuit ||
							myHand[i+3].getSuit() == theSuit ||
							myHand[i+4].getSuit() == theSuit){
							return 2;}
						return 1;																				 
					}
				}
			}
		}
		return 0;
	}
	
	bool Hand::determineRoyalFlush(CardList myHand) const {
		if(myHand.empty()){
			return false;
		}
		std::sort(myHand.begin(),myHand.end());
		if(!determineFlush(myHand)){
			return false;
		}
		//make sure all same Suit
		if((int) myHand[0].getFace() != 10){
			return false;
		} //makes sure lowest one is 10
		// by now it should be 10,J,Q,K,A
		return determineStraight(myHand);
	}

	bool Hand::determineHighCard(CardList myHand) const{
		int holder = 0;
		for(Card theCard: myHand){
			if((int)theCard.getFace()>holder){
				holder = (int)theCard.getFace();
			}
		}
		return holder;
	}

	CardOpt Hand::findBadCards() {
		size_t flag = 0;
		std::sort(cards.begin(),cards.end());
			for(size_t i=0; i<cards.size()-1;i++){
				if((int) cards[i].getFace()-(int) cards[i+1].getFace() < -1){
					flag++;
					if(flag==2){
						return cards[i];
					}
				}
				else{
					flag=0;
				}
				
			}
		return std::nullopt;
		}


//std::map<std::string, HandAnalyzer> theFunctions = {
//	{"high-card", HanddetermineHighCard},
//	{"one-pair", determinePair},
//	{"two-pair", determineTwoPair},
//	{"three-of-kind", determineThreeOfAKind},
//	{"straight", determineStraight},
//	{"flush", determineFlush},
//	{"full-house", determineFullHouse},
//	{"four-of-kind", determineFourOfKind},
//	{"straight-flush", determineStraightFlush},
//	{"royal-flush", determineRoyalFlush},
//	{"unknown"},
//};

}
