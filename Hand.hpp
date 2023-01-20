//
//  Hand.hpp
//  assignment2
//
//  Created by rick gessner on 10/6/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#ifndef Hand_hpp
#define Hand_hpp

#include <stdio.h>
#include "Card.hpp"
#include <deque>
#include <map>

namespace ECE17 {
	using CardList = std::deque<Card>;
	using CardCountMap = std::map<Faces, size_t>;
	using HandAnalyzer = bool (*)(CardList);
  enum class HandRanks {
		unknown=0, high_card, one_pair, two_pair, three_kind, straight, prime,
				flush, prime_flush, full_house, four_kind, straight_flush, royal_flush, prime_volts
  };
        
  class Hand {
  public:
    //STUDENT: implement this class from assigment...
    //         You can't change the methods given,
    //         but you can add any other you want...
        
    Hand();
    Hand(const Hand &aCopy);
    ~Hand();
    Hand& operator=(const Hand &aHand);
    bool  operator<(const Hand &aHand) const;
		bool operator==(const Hand& aHand) const;
        
    bool    addCard(const Card &aCard);
		CardOpt discard(Faces aFace, Suits aSuit);
    
    bool    contains(const Card &aCard) const;
    size_t  count() const;
    
    HandRanks determineRank() const;
    Faces     highCard() const;
		
		bool determineRoyalFlush(CardList myHand) const;
		bool determineStraightFlush(CardList myHand) const;
		int determineFourOfKind(CardList myHand) const;
		int determineFullHouse(CardList myHand) const;
		bool determineFlush(CardList myHand) const;
		bool determineStraight(CardList myHand) const;
		int determineThreeOfAKind(CardList myHand) const;
		int determineTwoPair(CardList myHand) const;
		int determinePair(CardList myHand) const;
		bool determinePrimeVolts(CardList myHand) const;
		bool determinePrime(CardList myHand) const;
		bool determinePrimeFlush(CardList myHand) const;
		bool determineVolts(CardList myHand) const;
		
		
		bool determineHighCard(CardList myHand) const;
		CardOpt discard(CardOpt aCard);
		CardOpt findBadCards();
		
		

    //this will show a hand on the console...
    friend std::ostream& operator<<(std::ostream &anOutput, const Hand &aHand);

  protected:

    std::deque<Card> cards; //Deque required; DO NOT CHANGE!
  };


}

#endif /* Hand_hpp */
