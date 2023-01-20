//
//  Tester.hpp
//  RGAssignment1
//
//  Created by rick gessner on 10/12/20.
//
#ifndef Tester_h
#define Tester_h
#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <typeinfo>
#include <string>
#include <initializer_list>
#include "Card.hpp"
#include "Deck.hpp"
#include "Player.hpp"
#include "Game.hpp"
const int kDeckSize{52};
const int kSuccess{0};
const int kCompareError{50};
const int kShuffleError{75};
const int kConstructorError{100};
const int kCopyConstructorError{200};
const int kAssignmentError{300};
const int kContainsError{400};
const int kCountError{500};
const int kRankingError{600};
const int kHighCardError{700};
const int kHighSingleCardError{750};
const int kPairRankingError{800};
const int kTripleRankingError{900};
const int kAddCardError{1000};
namespace ECE17 {
	//this class only exists so we can test Card class...
	class MockCard : public Card {
	public:
		MockCard(Faces aFace=Faces::ace, Suits aSuit=Suits::clubs)
		: Card(aFace, aSuit) {}
		MockCard(const Card &aCopy) : Card(aCopy) {}
		
		bool matches(const MockCard &aCard) {
			return suit==aCard.suit && face==aCard.face;
		}
	};
	int compareCards(std::ostream &anOutput) {
		srand((unsigned)time(NULL));
		for(int i=0;i<1000;i++) {
			size_t theRand1=2+((rand() % 8));
			size_t theRand2=8+((rand() % 7));
			Faces theFace1=static_cast<Faces>(theRand1);
			Faces theFace2=static_cast<Faces>(theRand2);
			Card theCard1(theFace1, Suits::hearts);
			Card theCard2(theFace2, Suits::clubs);
			if(theRand1<theRand2) {
				if(theCard1<theCard2) {}
				else {
					anOutput << "Comparison error: (" << theRand1 << "," << theRand2 << ")\
n";
					return kCompareError;
				}
			}
			else {
				if(theCard1==theCard2) {
					anOutput << "Comparison error: (" << theRand1 << "," << theRand2 << ")\
n";
					return kCompareError;
				}
			}
		}
			
		return kSuccess;
	}
	int testCards(std::ostream &anOutput) {
		MockCard theCard1; //default ctor, should be ace of clubs
		MockCard theCard2{Faces::ace, Suits::clubs}; //non-default ctor
		
		if(!theCard1.matches(theCard2))
			return kConstructorError;
			
		MockCard theCard3{theCard2}; //copy ctor...
		if(!theCard1.matches(theCard2))
			return kCopyConstructorError;
		MockCard theCard4{Faces::ace, Suits::hearts}; //ctor
		theCard3=theCard4;
		
		if(!theCard3.matches(theCard4))
			return kAssignmentError;
		
		return compareCards(anOutput);
	}
	//----------------------------------------------
	//this class only exists so we can test Deck class...
	class MockDeck : public Deck {
	public:
		MockDeck() : Deck() {}
		MockDeck(const MockDeck &aCopy) : Deck(aCopy) {}
		
		//bool matches(const MockHand &aDeck) {return true;}
	};
	int testDeck(std::ostream &anOutput) {
		
		Deck theDeck1;
		auto theCard=theDeck1.take();
						
		size_t theSize=theDeck1.count();
		if(1!=kDeckSize-theSize) {
			std::cout << "deck initialization error\n";
			return kCountError;
		}
		
		Deck theDeck2(theDeck1);
		
		std::stringstream theOut1;
		theOut1 << theDeck1;
		std::string theStr1=theOut1.str();
		
		if(theStr1.size()<100) {
			std::cout << "Deck::operator<< error\n";
			return kCountError;
		}
		std::stringstream theOut2;
		theOut2 << theDeck2;
		std::string theStr2=theOut2.str();
		if((theStr1!=theStr2)|| (kDeckSize-theDeck2.count()!=1)) {
			std::cout << "deck copy-ctor error\n";
			return kCopyConstructorError;
		}
		
		Deck theDeck3;
		theDeck3=theDeck1;
		if(theDeck1.count()!=theDeck3.count()) {
			std::cout << "deck assignment error\n";
			return kAssignmentError;
		}
		
		std::stringstream theOut3;
		theDeck1.shuffle();
		theOut3 << theDeck1;
		std::string theStr3=theOut3.str();
		std::stringstream theOut4;
		theDeck1.shuffle();
		theOut4 << theDeck2;
		std::string theStr4=theOut4.str();
		if(theStr3==theStr4) {
			std::cout << "shuffle not working\n";
			return kShuffleError;
		}
		
		std::stringstream theOut5;
		theDeck1.shuffle();
		theOut5 << theDeck1;
		std::string theStr5=theOut4.str();
		if(theStr5==theStr3) {
			std::cout << "shuffle not working\n";
			return kShuffleError;
		}
		return kSuccess;
	}
	//----------------------------------------------
	Hand getRandomHand(Deck &aDeck) {
		Hand theHand;
		for(int i=0;i<5;i++) {
			theHand.addCard(*aDeck.take());
		}
		return theHand;
	}
	Hand makeHand(const std::initializer_list<Card> &aList) {
		Hand theHand;
		for(auto &theCard : aList) {
			theHand.addCard(theCard);
		}
		return theHand;
	}
	Hand getHighCard(bool aState=false) {
		Hand theHand;
		theHand.addCard(Card(Faces::two,Suits::hearts));
		theHand.addCard(Card(Faces::four,Suits::diamonds));
		theHand.addCard(Card(Faces::seven, Suits::spades));
		theHand.addCard(Card(Faces::nine, Suits::clubs));
		theHand.addCard(Card(Faces::jack, Suits::hearts));
		return theHand;
	}
	Hand getOnePair(bool aState=false) {
		Hand theHand;
		Faces theFace = static_cast<Faces>(2 + (rand() % 2));
		theHand.addCard(Card(theFace, Suits::hearts));
		theHand.addCard(Card(theFace, Suits::diamonds));
		theHand.addCard(Card(Faces::seven, Suits::spades));
		theHand.addCard(Card(Faces::nine, Suits::clubs));
		theHand.addCard(Card(Faces::jack, Suits::hearts));
		return theHand;
	}
	Hand getOnePairAlt(bool aState=false) {
		Hand theHand;
		Faces theFace = static_cast<Faces>(5 + (rand() % 5));
		theHand.addCard(Card(theFace, Suits::hearts));
		theHand.addCard(Card(theFace, Suits::diamonds));
		theHand.addCard(Card(Faces::two, Suits::clubs));
		theHand.addCard(Card(Faces::four, Suits::diamonds));
		theHand.addCard(Card(Faces::queen, Suits::clubs));
		return theHand;
	}
	Hand getTwoPair() {
		Hand theHand;
		static Faces theFaces[]={Faces::two, Faces::four};
		Faces theFace = static_cast<Faces>(theFaces[rand() % 2]);
		theHand.addCard(Card(theFace, Suits::hearts));
		theHand.addCard(Card(theFace, Suits::clubs));
		theHand.addCard(Card(Faces::six, Suits::spades));
		theHand.addCard(Card(Faces::six, Suits::diamonds));
		theHand.addCard(Card(Faces::queen,  Suits::hearts));
		return theHand;
	}
	Hand getTwoPairAlt() {
		Hand theHand;
		static Faces theFaces1[]={Faces::six, Faces::eight};
		Faces theFace1 = static_cast<Faces>(theFaces1[rand() % 2]);
		theHand.addCard(Card(theFace1, Suits::hearts));
		theHand.addCard(Card(theFace1, Suits::clubs));
		
		static Faces theFaces2[]={Faces::ten, Faces::queen};
		Faces theFace2 = static_cast<Faces>(theFaces2[rand() % 2]);
		theHand.addCard(Card(theFace2, Suits::spades));
		theHand.addCard(Card(theFace2, Suits::diamonds));
		theHand.addCard(Card(Faces::king,  Suits::hearts));
		return theHand;
	}
	Hand getThreeOfAKind(bool aState=false) {
		Hand theHand;
		Faces theFace = static_cast<Faces>(4 + (rand() % 2));
		theHand.addCard(Card(theFace, Suits::hearts));
		theHand.addCard(Card(theFace, Suits::diamonds));
		theHand.addCard(Card(theFace, Suits::spades));
		theHand.addCard(Card(Faces::nine,Suits::clubs));
		theHand.addCard(Card(Faces::jack, Suits::clubs));
		return theHand;
	}
	Hand getThreeOfAKindAlt(bool aState=false) {
		Hand theHand;
		Faces theFace = static_cast<Faces>(7 + (rand() % 3));
		theHand.addCard(Card(theFace, Suits::hearts));
		theHand.addCard(Card(theFace, Suits::diamonds));
		theHand.addCard(Card(theFace, Suits::spades));
		theHand.addCard(Card(Faces::three,Suits::clubs));
		theHand.addCard(Card(Faces::queen, Suits::clubs));
		return theHand;
	}
	Hand getStraight(bool aState=false) {
		Hand theHand;
		theHand.addCard(Card(Faces::five, Suits::hearts));
		theHand.addCard(Card(Faces::six, Suits::diamonds));
		theHand.addCard(Card(Faces::seven, Suits::spades));
		theHand.addCard(Card(Faces::eight, Suits::clubs));
		theHand.addCard(Card(Faces::nine, Suits::hearts));
		return theHand;
	}
	Hand getFlush(Suits aSuit=Suits::clubs, bool aState=false) {
		Hand theHand;
		theHand.addCard(Card(Faces::two, aSuit));
		theHand.addCard(Card(Faces::five, aSuit));
		theHand.addCard(Card(Faces::eight, aSuit));
		theHand.addCard(Card(Faces::jack, aSuit));
		theHand.addCard(Card(Faces::ace, aSuit));
		return theHand;
	}
	Hand getFullHouse(Faces aFace, bool aState=false) {
		Hand theHand;
		Faces theFace = static_cast<Faces>(2 + (rand() % 2));
		theHand.addCard(Card(theFace, Suits::clubs));
		theHand.addCard(Card(theFace, Suits::spades));
		theHand.addCard(Card(theFace, Suits::hearts));
		theHand.addCard(Card(aFace, Suits::clubs));
		theHand.addCard(Card(aFace, Suits::hearts));
		return theHand;
	}
	Hand getFullHouseAlt(Faces aFace, bool aState=false) {
		Hand theHand;
		Faces theFace = static_cast<Faces>(8 + (rand() % 2));
		theHand.addCard(Card(theFace, Suits::clubs));
		theHand.addCard(Card(theFace, Suits::spades));
		theHand.addCard(Card(theFace, Suits::hearts));
		theHand.addCard(Card(aFace, Suits::clubs));
		theHand.addCard(Card(aFace, Suits::hearts));
		return theHand;
	}
	Hand getFourOfAKind(bool aState=false) {
		Hand theHand;
		theHand.addCard(Card(Faces::five, Suits::hearts));
		theHand.addCard(Card(Faces::five, Suits::diamonds));
		theHand.addCard(Card(Faces::five, Suits::spades));
		theHand.addCard(Card(Faces::five, Suits::clubs));
		theHand.addCard(Card(Faces::seven, Suits::hearts));
		return theHand;
	}
	Hand getPrime(bool aState=false) {
		Hand theHand;
		theHand.addCard(Card(Faces::three, Suits::hearts));
		theHand.addCard(Card(Faces::five, Suits::hearts));
		theHand.addCard(Card(Faces::seven, Suits::spades));
		theHand.addCard(Card(Faces::jack, Suits::clubs));
		theHand.addCard(Card(Faces::king, Suits::hearts));
		return theHand;
	}
	Hand getStraightFlush(bool aState=false) {
		Hand theHand;
		theHand.addCard(Card(Faces::three, Suits::hearts));
		theHand.addCard(Card(Faces::four, Suits::hearts));
		theHand.addCard(Card(Faces::five, Suits::hearts));
		theHand.addCard(Card(Faces::six, Suits::hearts));
		theHand.addCard(Card(Faces::seven, Suits::hearts));
		return theHand;
	}
	Hand getRoyalFlush(bool aState=false) {
		Hand theHand;
		theHand.addCard(Card(Faces::ten, Suits::hearts));
		theHand.addCard(Card(Faces::jack, Suits::hearts));
		theHand.addCard(Card(Faces::queen, Suits::hearts));
		theHand.addCard(Card(Faces::king, Suits::hearts));
		theHand.addCard(Card(Faces::ace, Suits::hearts));
		return theHand;
	}
	//-----------------------------------------------------
	//make a hand that corresponds to the given type...
	bool validateRank(HandRanks aType, const Hand& aHand, const char *aMsg) {
		auto theRank=aHand.determineRank();
		if(aType!=theRank) {
			std::cout << "Determine rank for " << aMsg << " failed\n";
			return false;
		}
		return true;
	}
	int testRanks(std::ostream &anOutput) {
		const size_t theMax{1};
		
		for(int i=0;i<theMax;i++) {
			if(!validateRank(HandRanks::high_card, getHighCard(i), "high-card")) {
				return kRankingError;
			}
			if(!validateRank(HandRanks::one_pair,  getOnePair(i), "one-pair")) {
				return kPairRankingError;
			}
			if(!validateRank(HandRanks::two_pair,  getTwoPair(), "two-pair")) {
				return kPairRankingError;
			}
			
			if(!validateRank(HandRanks::three_kind, getThreeOfAKind(i),"three-kind")) {
				return kTripleRankingError;
			}
			if(!validateRank(HandRanks::straight,  getStraight(i),"straight")) {
				return kRankingError;
			}
			if(!validateRank(HandRanks::flush,  getFlush(Suits::clubs, i),"flush")) {
				return kRankingError;
			}
				
			if(!validateRank(HandRanks::full_house,
											 getFullHouse(Faces::nine, i),"full-house")) {
				return kRankingError;
			}
			if(!validateRank(HandRanks::four_kind,  getFourOfAKind(i),"four-kind")) {
				return kRankingError;
			}
			if(!validateRank(HandRanks::straight_flush,  getStraightFlush(i),"straight"))
{
				return kRankingError;
			}
	
			if(!validateRank(HandRanks::royal_flush,  getRoyalFlush(i),"royal-flush")) {
				std::cout << "Determine rank for royal-flush failed\n";
				return kRankingError;
			}
			
		}
		
		return kSuccess;
	}
	//test many scenarios of ranks, and high-card comparisons...
	int testHand(std::ostream &anOutput) {
		const size_t kHandSize{5};
		Deck theDeck;
		theDeck.shuffle();
		Hand theHand1;
		for(size_t i=0;i<kHandSize;i++) {
			if(auto theCard=theDeck.take()) {
				theHand1.addCard(*theCard);
			}
			else return kAddCardError;
		}
		std::stringstream theOut1;
		theOut1 << theHand1;
		std::string theStr1=theOut1.str();
	 // anOutput << theStr1;
		
		Hand theHand2(theHand1);
		std::stringstream theOut2;
		theOut2 << theHand2;
		std::string theStr2=theOut2.str();
		//anOutput << theStr2;
		if(theStr1!=theStr2) {
			anOutput << "hand copy-ctor error\n";
			return kCopyConstructorError;
		}
					
		Hand theHand3;
		theHand3=theHand1;
		std::stringstream theOut3;
		theOut3 << theHand3;
		std::string theStr3=theOut3.str();
		if(theStr1!=theStr3) {
			anOutput << "hand assignment error\n";
			return kCopyConstructorError;
		}
		if(kHandSize!=theHand1.count()) {
			anOutput << "hand count() error\n";
			return kCountError;
		}
		
		//make sure hand ranks high-card multiples correctly...
		Hand theHigh=getHighCard();
		if(Faces::jack!=theHigh.highCard()) {
			anOutput << "high-card error\n";
			return kHighSingleCardError;
		}
		
		//compare high-pairs...
		Hand theHighPair1a=getOnePair();
		Hand theHighPair1b=getOnePairAlt();
		
		if(Faces::jack!=theHighPair1a.highCard()) return kHighCardError;
		if(Faces::queen!=theHighPair1b.highCard()) return kHighCardError;
		HandRanks theRank1a=theHighPair1a.determineRank();
		HandRanks theRank1b=theHighPair1b.determineRank();
		if((theRank1b!=theRank1a) || theHighPair1b<theHighPair1a) {
			anOutput << "high-card error\n";
			return kHighSingleCardError;
		}
		Hand thePairA= makeHand({{Faces::two, Suits::hearts},{Faces::two, 
Suits::clubs},
			{Faces::five, Suits::diamonds},{Faces::seven, Suits::diamonds},{Faces::jack, 
Suits::spades},
		});
		Hand thePairB= makeHand({{Faces::two, Suits::hearts},{Faces::two, 
Suits::clubs},
			{Faces::five, Suits::diamonds},{Faces::seven, Suits::diamonds},{Faces::queen,
Suits::spades},
		});
		
		if(Faces::jack!=thePairA.highCard()) return kPairRankingError;
		if(Faces::queen!=thePairB.highCard()) return kPairRankingError;
		if(thePairB<thePairA) {
			return kPairRankingError;
		}
		
		//compare two pair high cards...
		Hand theHighPair2a=getTwoPair();
		Hand theHighPair2b=getTwoPairAlt();
		
		if(Faces::queen!=theHighPair2a.highCard()) return kHighCardError;
		if(Faces::king!=theHighPair2b.highCard()) return kHighCardError;
		HandRanks theRank2a=theHighPair2a.determineRank();
		HandRanks theRank2b=theHighPair2b.determineRank();
		if((theRank2b!=theRank2a) || theHighPair2b<theHighPair2a) {
			anOutput << "high-card pair error\n";
			return kPairRankingError;
		}
		
		Hand thePairsA= makeHand({{Faces::two, Suits::hearts},{Faces::two, 
Suits::clubs},
			{Faces::four, Suits::diamonds},{Faces::four, Suits::spades},{Faces::jack, 
Suits::clubs},
		});
		Hand thePairsB= makeHand({{Faces::two, Suits::diamonds},{Faces::two, 
Suits::spades},
			{Faces::four, Suits::clubs},{Faces::four, Suits::hearts},{Faces::ace, 
Suits::spades},
		});
		if(Faces::jack!=thePairsA.highCard()) return kHighCardError;
		if(Faces::ace!=thePairsB.highCard()) return kHighCardError;
		
		if(thePairsB<thePairsA) {
			return kPairRankingError;
		}
		
		//compare three pair high cards...
		Hand theHighPair3a=getThreeOfAKind();
		Hand theHighPair3b=getThreeOfAKindAlt();
		
		if(Faces::jack!=theHighPair3a.highCard()) return kHighCardError;
		if(Faces::queen!=theHighPair3b.highCard()) return kHighCardError;
	 
		HandRanks theRank3a=theHighPair3a.determineRank();
		HandRanks theRank3b=theHighPair3b.determineRank();
		if((theRank3b!=theRank3a) || theHighPair3b<theHighPair3a) {
			anOutput << "high-card triple error\n";
			return kRankingError;
		}
		
		if(theHighPair3a<thePairsB) {
			return kRankingError;
		}
		
		Hand theStraightA= makeHand({{Faces::two, Suits::hearts},{Faces::three, 
Suits::clubs},
			{Faces::four, Suits::spades},{Faces::five, Suits::hearts},{Faces::six, 
Suits::diamonds},
		});
		Hand theStraightB= makeHand({{Faces::seven, Suits::clubs},{Faces::eight, 
Suits::diamonds},
			{Faces::nine, Suits::hearts},{Faces::ten, Suits::hearts},{Faces::jack, 
Suits::spades},
		});
		
		if(Faces::six!=theStraightA.highCard()) return kHighCardError;
		if(Faces::jack!=theStraightB.highCard()) return kHighCardError;
		
		if(theStraightB<theStraightA) {
			return kPairRankingError;
		}
		if(theStraightB<theHighPair3a) {
			return kRankingError;
		}
		
		//---------------
		Hand theFlushA= makeHand({{Faces::two, Suits::hearts},{Faces::four, 
Suits::hearts},
			{Faces::six, Suits::hearts},{Faces::eight, Suits::hearts},{Faces::ten, 
Suits::hearts},
		});
		Hand theFlushB= makeHand({{Faces::three, Suits::diamonds},{Faces::five, 
Suits::diamonds},
			{Faces::seven, Suits::diamonds},{Faces::nine, Suits::diamonds},{Faces::jack, 
Suits::diamonds},
		});
		
		if(Faces::ten!=theFlushA.highCard()) return kHighCardError;
		if(Faces::jack!=theFlushB.highCard()) return kHighCardError;
		
		if(theFlushB<theFlushA) {
			return kPairRankingError;
		}
		if(theFlushA<theStraightB) {
			return kRankingError;
		}
		
			//compare full houses...
		Faces theFaceA=static_cast<Faces>(5 + (rand() % 2));
		Hand theFullA=getFullHouse(theFaceA, false);
		Faces theFaceB = static_cast<Faces>(11 + (rand() % 3));
		Hand theFullB=getFullHouseAlt(theFaceB, false);
		
		if(theFaceA!=theFullA.highCard()) return kHighCardError;
		if(theFaceB!=theFullB.highCard()) return kHighCardError;
		
		HandRanks theFullRankA=theFullA.determineRank();
		HandRanks theFullRankB=theFullB.determineRank();
		if((theFullRankA!=theFullRankB) || theFullB<theFullA) {
			anOutput << "full-house rank error\n";
			return kRankingError;
		}
	
		if(theFullA<theFlushA) {
			return kRankingError;
		}
		return testRanks(anOutput);
	}
	//----------------------------------------------
	int testPlayer(std::ostream &anOutput) {
		Player thePlayer1("Truong Nguyen");
		Player thePlayer2(thePlayer1);
		
		std::stringstream theOut1;
		theOut1 << thePlayer1;
		std::string theStr1=theOut1.str();
		std::stringstream theOut2;
		theOut2 << thePlayer2;
		if(theStr1!=theOut2.str()) {
			std::cout << "player copy-ctor error\n";
			return kCopyConstructorError;
		}
		
		Player thePlayer3;
		thePlayer3=thePlayer1;
		std::stringstream theOut3;
		theOut3 << thePlayer3;
		if(theStr1!=theOut3.str()) {
			std::cout << "player assignment error\n";
			return kAssignmentError;
		}
		
		return kSuccess;
	}
	//----------------------------------------------
	//this class only exists so we can test game class...
	class MockGame : public Game {
	public:
		MockGame() : Game() {}
		MockGame(const MockGame &aCopy) : Game(aCopy) {}
		
		bool matches(const MockGame &aGame) {
			return true;
		}
	};
	int testGame(std::ostream &anOutput) {
		return !kSuccess;
	}
	int compileTest(const ECE17::AboutMe &aStudent) {
		if(aStudent.getPID()!="Your PID") {
			if(aStudent.getName()!="Your name") {
				return kSuccess;
			}
		}
		return !kSuccess;
	}
}
#endif /* Tester_h */
