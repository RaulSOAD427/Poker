//
//  Round.hpp
//  assignment7
//
//  Created by rick gessner on 11/23/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//
#ifndef Round_h
#define Round_h
#include "Game.hpp"
#include "Deck.hpp"
#include "Hand.hpp"
#include <vector>
#include <iomanip>
namespace ECE17 {
			
	//using Hands = std::map<ECE17::Player*, Hand>;
	static std::map<HandRanks, const char*> gHandNames = {
		{HandRanks::high_card, "high-card"},
		{HandRanks::one_pair, "one-pair"},
		{HandRanks::two_pair, "two-pair"},
		{HandRanks::three_kind, "three-of-kind"},
		{HandRanks::straight, "straight"},
		{HandRanks::flush, "flush"},
		{HandRanks::full_house, "full-house"},
		{HandRanks::four_kind, "four-of-kind"},
		{HandRanks::straight_flush, "straight-flush"},
		{HandRanks::royal_flush, "royal-flush"},
		{HandRanks::unknown, "unknown"},
	};
	class Round {
	public:
		Round(Players &aPlayers, size_t aCardCount=5, float anAnte=5.0)
		: players(aPlayers), cardCount(aCardCount), ante(anAnte), pot{0.0} {
			round=1;
			state=false;
		}
							
		//give each player a turn to drop/add cards.
		//return # of players who are still in this round
		Round& drawCards(Deck &aDeck, std::ostream &anOutput) {
			static const size_t kEndCardCount{5};
			for(auto thePlayer: rPlayers) {
				size_t theCount=thePlayer->getHand().count();
				thePlayer->discardUnwanted();
				size_t theCount2=thePlayer->getHand().count();
				if(theCount2<theCount) {
					anOutput << "    " << thePlayer->getName()
						<< " dropped " << theCount-theCount2 << " cards.\n";
				}
				thePlayer->drawCards(aDeck, kEndCardCount);
			}
			return *this;
		}
		
		Round& dealCards(Deck &aDeck) {
			//shuffle the deck, and deal the cards to your players...
			aDeck.shuffle();
			for(auto thePlayer: rPlayers) {
				thePlayer->setHand(Hand());
				thePlayer->drawCards(aDeck, cardCount);
			}
			return *this;
		}
		
		//Get bets from each player; some may "fold" (quit hand)
		//return # of players who are still in this round
		size_t placeBets(float aMinBet, std::ostream &anOutput) {
			for(auto &thePair: players) {
				auto thePlayer=rPlayers.begin();
				auto theEnd=rPlayers.end();
				while(thePlayer!=theEnd) {
					if(*thePlayer==thePair.first) {
						if(!thePair.first->isFolding(thePair.second)) {
							float theBet=thePair.first->placeBet(thePair.second, aMinBet);
							if(theBet<=thePair.second && theBet>=aMinBet) {
								pot+=theBet;
								anOutput << "  " << thePair.first->getName()
									<< "($" << thePair.second << ") "
									<< " bet $" << theBet << "\n";
								thePair.second-=theBet;
							}
							else {
								rPlayers.erase(thePlayer);
								anOutput << thePair.first->getName()
									<< " made illegal bet " << theBet << "\n";
								state=false;
							}
						}
						else {
							rPlayers.erase(thePlayer);
							anOutput << "\n    " << thePair.first->getName()
											 << " folded\n";
						}
						break;// end the loop
					}
					thePlayer++;
				}
			}
						
			return rPlayers.size();
		}
				
		//rank the hand of each player, and give the winning hand the pot...
		bool payWinner(std::ostream &anOutput) {
			if(!rPlayers.size()) {
				anOutput << "\t No winner\n";
				return false;
			}
			
			Player *theWinner=nullptr;
			for(auto thePlayer : rPlayers) {
				if(theWinner) {
					const auto &theWHand=theWinner->getHand();
					const auto &thePHand=thePlayer->getHand();
					if(theWHand<thePHand) {
						theWinner=thePlayer;
					}
				}
				else theWinner=thePlayer;
			}
			auto theRank=theWinner->getHand().determineRank();
			for(auto &thePair : players) {
				if(theWinner==thePair.first) {
					thePair.second+=pot;
				}
				anOutput << "\t" << thePair.first->getName()
					<< " " << thePair.first->getHand();
				if(theWinner==thePair.first) {
					anOutput << "\n\t\t won " << pot
						<< " with " << gHandNames[theRank];
				}
				anOutput << "\n";
			}
			return true;
		}
		
		bool willRun() {
			pot=0.0;
			state=true;
			rPlayers.clear();
			for(auto thePair : players) {
				if(thePair.second>=ante) {
					thePair.first->setHand(Hand()); //empty?
					players[thePair.first]=thePair.second-ante;
					rPlayers.push_back(thePair.first);
					pot+=ante;
				}
			}
			return state && rPlayers.size()>1;
		}
		
		bool didRun(bool runStatus) {
			ante+=1.0; //increment every round...
			round++;
			return runStatus;
		}
		bool run(float aMinBet, std::ostream &anOutput) {
			Deck theDeck;
			dealCards(theDeck);
			anOutput << "\nRound " << round
				<< std::fixed << std::setprecision(0)
				<< " -- ante ($" << ante << ")\n";
			if(placeBets(aMinBet, anOutput)>0) {
				drawCards(theDeck, anOutput).placeBets(aMinBet, anOutput);
			}
			return payWinner(anOutput);
		}
				
	protected:
		Players &players; //game players
		std::vector<Player*> rPlayers; //per-round version...
		size_t  cardCount;
		float   ante;
		float   pot;
		size_t  round;
		bool    state;
	};
}
#endif /* Round_h */
