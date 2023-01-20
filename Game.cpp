//
//  Game.cpp
//  assignment2
//
//  Created by rick gessner on 10/6/19.
//  Copyright © 2019 rick gessner. All rights reserved.
//

#include "Round.hpp"
#include <sstream>
#include <algorithm>

namespace ECE17 {
  
  const float kStartingBalance=1000.00;

  Game::Game(size_t aCardCount, float aMinBet) {
    cardCount=aCardCount;
    minBet=aMinBet;
  }

  Game::Game(const Game &aCopy)  {
    std::cout << "Game ctor(copy)\n";
  }

  Game& Game::operator=(const Game &aCopy) {
    return *this;
  }

  Game::~Game() {
  }

  bool Game::addPlayer(Player &aPlayer) {
    players[&aPlayer]=kStartingBalance;
    return true;
  }
  
  bool Game::willStartGame() {
    return players.size()>1; //gotta have 2 or more players...
  }

  bool Game::run(float anAnte, std::ostream &anOutput) {
    Round  theRound(players, cardCount, anAnte);
    while(theRound.willRun()) {
      theRound.didRun(theRound.run(minBet, anOutput));
    }
    anOutput << "\nENDING GAME\n";
    return true;
  }
  
  const char* verifyRounds(const std::string &aGameOutput,
                           float aMinBet) {
    std::stringstream theInput(aGameOutput);
    std::string theWords[2];
    bool        theState{false};
    size_t      theBets{0};
    size_t      theDrops{0};
    size_t      theFolds{0};
    
  //std::cout << anOutput << "\n";  //DEBUG
    
    const char* theResult="Verified";

    while(theInput >> theWords[theState]) {
        //std::cout << "while loop executed\n";
      if(theWords[!theState]=="bet") {
        if(theWords[theState][0]=='$')
          theWords[theState].erase(0,1); //remove $
        float theBet=stof(theWords[theState]);
        if(theBet!=aMinBet) theBets++;
        //std::cout << "BET " << theWords[theState] << "\n";
      }
      else if(theWords[!theState]=="dropped") {
        size_t theDrop=stoi(theWords[theState]);
        if(theDrop!=0) theDrops++;
        //std::cout << "DROPPED " << theWords[theState] << "\n";
      }
      else if(theWords[!theState]=="folded") {
        theFolds++;
      }
      theState=!theState;
    }

    if(!theBets) {
      std::cout << "Insufficient non-min. bets\n";
      theResult="Unverified";
    }
    if(!theDrops) {
      std::cout  << "Insufficient drops\n";
      theResult="Unverified";
    }
    if(!theFolds) {
      std::cout  << "Insufficient folds\n";
      theResult="Unverified";
    }
 
    return theResult;
  }

  bool Game::didRun(bool aRunStatus,
                    const std::string &aGameOutput) {

    //find player with most cash...
    Player *theWinner=nullptr;
    float  theBalance{0.00};
    for(auto thePair : players) {
      if(!theWinner) {
        theWinner=thePair.first;
        theBalance=thePair.second;
      }
      else {
        if(theBalance<thePair.second) {
          theWinner=thePair.first;
          theBalance=thePair.second;
        }
      }
    }
    
    if(theWinner) {
      std::string theVerify=verifyRounds(aGameOutput,minBet);
      std::cout << theVerify
        << " winner is " << theWinner->getName()
        << " ($" << theBalance << ")\n";
      return theVerify=="Verified";
    }

    std::cout << "Winner unknown, something is wrong!\n";
    return false;
  }

}
