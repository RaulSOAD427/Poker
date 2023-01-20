# SP22-Assignment6
#### Due Saturday, June 4, 2022 -- 11:30pm

Let's play cards!


### Preparing to build a Five-Card Poker Game

## Introduction

You've come a long way towards being able to program with objects in C++. Now it's time to put these techniques to work. In this assignment, you are going to build a working game of 5-card poker. The players in the game will be `Player` objects you build, that can respond to the rules of the game, and driven by the process defined in your `Game` object (described below). 

The `Game` object drives the process of game-play.  During each round (hand), your `Player` class will analyze the cards it has received, and choose whether to fold, stand pat, or place a virtual bet. This part of this exercise is really fun (and many students get very competitive!). 

> Note: You're permitted to reuse your code from your earlier assignments (e.g. #1), if that can save you some time.

--- 

## Rules of Five-Card Poker Game

Two (or more) players join the game. Each game is made up of a sequence of rounds (or hands). Rounds continue until all but one player has withdrawn from the game (usually by running out of money/chips).

### 1. The Ante
At the start of each round, every player pays an "ante" -- a small fee to participate in the round. The proceeds from player anties are kept in a central "pot" by the game, and these funds get disbursed at the end of the round to the winner of the round.

### 2. Dealing the Cards
The game shuffles a full deck of 52 cards. Each player is dealt a "hand" of five cards - by the game.  In your code, a `Hand` object will hold the five `Cards` that each `Player` receives.  Players are free to examine their own cards, which are kept out of the view of other players. 

### 3. First Bet 

After receiving their starting "hand", each `Player` has three options:

1. It can fold their hand, and relinquish the money it put in the pot, and await the start of the next round. 
2. It can "stand pat" -- and not make an anticipatory bet (usually because they don't have a very strong hand)
3. It can place a bet (0<bet<balance)

If _any_ player places a bet at this point, then _every_ player must match that bet, or elect to fold. To make our game a little simpler, players are not permitted to raise any bet. A player can either match a bet, or fold. 

If more than one player remains after that first round of betting, there follows a round of "drawing" new cards. If only 1 player is left, they immediately win the pot, and the next round begins. 

> Note: The game engine should _not_ allow the "last" player in a round to fold, even if that `Player` elects to do so. The last player in a round automatically wins the pot.

### 4. Drawing Cards (discard/add)

Each `Player` still in the round is given the opportunity to discard from 0 to 4 cards. After discarding N cards, the game will ask the `Player` to draw new cards to fill out the hand (to a total of 5 cards) again.

### 5. Final Bet -- 

As before, each player is again given the option to fold, hold, or bet. As before, if any player choose to bet, then every player who wants to remain in the round must match that bet, or they may fold.

### 6. Winning the Round 
Cards for all players are now revealed (you will show the cards in the hand for each player in the terminal), and the game determines which player has the winning hand, and how much they won in the pot (also shown in the terminal -- see below). The winning player receives all the money from the pot for this round. The game then continues back at step one in the process with a new shuffled `Deck`. 

```
Round 1 --
Player1Name : {8♥ 7♥ 6♥ 5♥ 4♥}
Player2Name : {A♦, K♦, Q♦, J♦, 10♦} WINS $20
```

---

## Hands you can achieve in Five-Card Poker (best to worst)

### 1. Royal flush
A sequence of 5 highest cards (all in the same suit).  Example: `{A♦, K♦, Q♦, J♦, 10♦}` (shown in order for clarity)

### 2. Straight flush
Five cards in a sequence, all in the same suit.  Examples : `{8♥ 7♥ 6♥ 5♥ 4♥}`, or `{7♦ 8♦ 9♦ 10♦ J♦}`

### 3. Four of a kind
All four cards of the same face value (suit doesn't matter). Example: `{K-K-K-K 3}`

### 4. Full house
Three cards with the same face value.  `{T T T 9 9}`

### 5. Flush
Any five cards with the same suit, but not in a sequence.  Example:  `{4♦ J♦ 8♦ 2♦ 9♦}`

### 6. Straight
Five cards in a sequence, regardless of suit. Example: `{5 6 7 8 9}`

### 7. Three of a kind
Three cards of the same rank, regardless of suit.  `{Q-Q-Q 2 3}`

### 8. Two pair
Two pairs of two cards with same face value.  Example: `{K-K 7-7 2}`

### 9. One Pair
Two cards of the same face value.  Example: `{A-A 5 2 8}`

### 10. High Card
When you can't make any of the hands above, your highest card is the only play. 

--- 

## Your Deliverables for This Assignment

### Challenge 1. Implement the Core Classes 

#### The `Card` class  (given)

The `Card` class represents a given card (suit, face) in a deck. As usual, there are 4 suits, with 13 faces in each, for a total of 52 cards.  This is implemented for you.

<hr> 

In order to get your game to work, you'll need to implement the classes described below. 

#### 1. The `Hand` class

A `Hand` will represent the 5 cards that each player will have during each round of the game. Generally speaking, your `Hand` class should have a data member that contains N `Card` objects (N is usually 5).  In addition to the OCF methods, you MUST also implement the following methods for the `Hand` class. You're free to add other methods or data you need to this class.  You can reuse logic from earlier assignment too -- but don't change this API.

```cpp
    Hand& operator=(const Hand &aHand);
    bool  operator<(const Hand &aHand) const;
    bool  operator==(const Hand& aHand) const;
        
    bool    addCard(const Card &aCard);
    CardOpt discard(Faces aFace, Suits aSuit);
    
    bool    contains(const Card &aCard) const;
    size_t  count() const;
    
    HandRanks determineRank() const;
    Faces     highCard() const;

    friend std::ostream& operator<<(std::ostream &anOutput, const Hand &aHand);    
```

It's essential that you implement `determineRank()` correctly. Given a `Hand` object that contains 5 cards, this method will analyze the collection of cards to determine the "best-match" logical hand the cards represent. See "Hands you can achieve" (above). Your game will rely on this method working in order to choose a winning `Hand` from reach round.

It is also essential that you implement comparison operators corrected `bool Hand::operator<()` and `bool Hand::operator==()`. These methods compare the rank of two `Hand` objects. If the ranks are different, the winner is the `Hand` with the highest ordinal value.  The the ranks are the same, then the winner is determine by analysis of the individual cards as outline above (See "Hands you can achieve in Five-Card Poker").  For many students, this method presents one of the most interesting challenges. These are dependent upon `determineRank`. 


#### 2. The `Deck` class

The `Deck` class will initially hold 52 distinct (non-repeating) `Card` objects in an internal data structure. You're free to build your `Deck` class any way you like, but you must implement the methods listed below (along with the OCF methods). Again, you can reuse `Deck` logic from a previous assignment if you wish. You're welcome to add any additional methods or data members you like to the `Deck` class as well.

```cpp
    CardOpt take(); //remove top card from deck...
    bool    discard(const Card &aCard); //push card back to bottom of deck
        
    size_t  count(); //retrieve #cards in deck...
    bool    contains(const Card &aCard) const; //determine if card is in deck
    Deck&   shuffle();
        
    friend std::ostream& operator<<(std::ostream &anOutput, const Deck &aDeck);
```

It's essential that your `shuffle` method works well, and that after calling this method, the cards are in a well-sorted, random order. Be careful to ensure that the cards in your `Deck` are in a **unique**, random order each time `shuffle` is called.  Fortunately, you've already implemented this in a previous assignment.

#### 3. The `Player` class

Your `Player` class will act like a virtual player, and respond to calls made by the `Game` object to iterate through rounds until a winner emerges (with all the money!). Your player will contain a `Hand` object, a name, and a balance (and you can add other data as necessary).  You are required to implement the existing methods (including OCF), and may freely add your own.

```cpp
    const Hand&   getHand() const;
    void          setHand(const Hand &aHand);

    const std::string&  getName() const;
    
    bool          isFolding(float aBalance) const;
    float         placeBet(float aBalance, float aMinBet);
    size_t        discardUnwanted();
    
    bool          drawCards(Deck &aDeck, size_t aMaxCount);
    
    friend std::ostream& operator<<(std::ostream &anOut, const Player &anObj); 
```

`Player:drawCards` and `Player::discardUnwanted` are automatically called during each round. In `drawCards` you will retrieve cards from the given `Deck` to complete your hand. This happens when the round first begins, and later if the players chooses to discard cards to improve their hand.  In the `DiscardUnwanted` method, you have a chance to analyze your hand, and estimate the most likely "best" hand you can achieve. Then, drop cards that aren't helpful to you, in hopes that when you draw new cards, you can get a winning hand.  This process may require that you write your own custom methods that help you analyze your and try to set a goal (target hand). 

An important part of playing Poker is to know when to "fold" your hand (forfeit a round). If you think your opponent has better cards than you do, you can either bluff (bet as if you have a good hand), or "fold" (forfeit). The `Player::isFolding` method is your opportunity to fold. If you return `true` from this call, the game will presume you have forfeited the round. It is essential that you player class use this method when necessary. No player plays very long without folding, and your `Player` class must fold on occasion as well to preserve your money for betting in other rounds.

It's also important your player vary the bet you place, based on the quality of your hand. If you don't the autograder will reduce the points you are awarded for this assignment.

### Challenge 2. Effectively play the game

This challenge involves getting your player to act in accordancee with the game rules. That means, when asked to do so, your player class can:

1.  Draw cards as necessary
2.  Place varied bets
3.  Determine the rank of your hand
4.  Use the rank to choose when to fold

### Challenge 3. System Design

In this week's engineering notebook -- describe the design of the Game system. In particular, answer the following questions:
1. How do the `Game` and `Round` objects work together to move the game foward?
2. How does the design of the system reduce the potential for cheating? Are there still opportunities to cheat?
3. We discussed several patterns for algorithm design.  Describe which method you used for your "hand ranking" method.
4. How does the game verification code work?

## Grading

The grading for this assignment follows this rubric:

1. Compiles (10pts) 
2. Hand test (20pts)
3. Deck test (15pts)
4. Game playing (challenge 2) (35pts)
5. System description pdf (20pts)


## Submitting Your Work - Due Saturday, June 4, 2022 -- 11:30pm

Good luck, and good gaming!
