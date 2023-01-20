//
//  main.cpp
//  Assignment1
//
//  Created by rick gessner on 10/12/20.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "AboutMe.hpp"
#include "Testing.hpp"

int playGame(std::ostream &anOutput) {
  ECE17::Game theGame;

  srand((unsigned)time(NULL));
  
  //STUDENT: Add players here...
  ECE17::Player thePlayer1("Player1");
  ECE17::Player thePlayer2("Player2");

  theGame.addPlayer(thePlayer1);
  theGame.addPlayer(thePlayer2);

  if(theGame.willStartGame()) {
    const float kStartAnte = 5.0;
    std::stringstream theOutput;
    bool theResult=theGame.run(kStartAnte,theOutput);
    theResult=theGame.didRun(theResult,theOutput.str());
    anOutput << theOutput.str() << "\n";
    return theResult ? kSuccess : !kSuccess;
  }
  return 0;
}

int main(int argc, const char * argv[]) {
      
  srand(static_cast<uint32_t>(time(0))); //randomize...

  if(argc>1) {
      
    std::string temp(argv[1]);
    std::stringstream theStream;
    
    static const char* theMsgs[]={"FAIL","PASS"};
    int theResult=0;
    
    //const char* theMsg=theMsgs[0];
    if("Compile"==temp) {
      ECE17::AboutMe theStudent;
      if(theStudent.getPID()!="Your PID") {
        if(theStudent.getName()!="Your name") {
          theResult=kSuccess;
        }
      }
    }
    else if("Cards"==temp) {
      theResult=ECE17::testCards(theStream);
    }
    else if ("Hand"==temp) {
      theResult=ECE17::testHand(theStream);
    }
    else if ("Deck"==temp) {
      theResult=ECE17::testDeck(theStream);
    }
    else if ("Game"==temp) {
      theResult=playGame(theStream);
    }
  
    std::cout << temp << " test " << theMsgs[theResult==0] <<"\n";
    std::cout << theStream.str() << "\n"; //output whatever user provided
    return theResult;
  }
  
  else {
    playGame(std::cout);
    return 0;
  }
      
  return 0;
}
