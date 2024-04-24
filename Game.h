///////////////////////////////////////////////////////////////////////////////
//   University of Hawaii, College of Engineering
//   Lab D - Lucky Cat - EE 205 (Object Oriented Programming) - Spr 2024
//
//   Cats make their own luck
//
/// @file   Game.h
/// @author TODO <TODO@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////


#include <cassert>    // For assert
#include <cstdint>    // For uint8_t
#include <stdexcept>  // For invalid_argument


using namespace std;


#define MIN_BALLS   (  1)  ///< The minimum number of balls in any game
#define MAX_BALLS   (250)  ///< The maximum number of balls in any game
#define MAX_DRAWS   ( 16)  ///< The maximum number of balls drawn in any game


/// this converts to string
#define STR_(X) #X

/// this makes sure the argument is expanded before converting to string
#define STR(X) STR_(X)


/// Represents a single Lottery game.  Once the initial paramters of the game
/// are established, they can't be changed.  The game, however, can be payed
/// repeatedly.
class Game {
private:
   uint8_t       balls;    ///< The number of balls in this Game
   uint8_t       draws;    ///< The number of balls retrieved in each draw
   unsigned long tickets;  ///< The number of customers who buy a lottery ticket
   

public:  // ///////////////////////// Static Methods ///////////////////////////
   static bool validateBalls( uint8_t newBalls );
   static bool validateDraws( uint8_t newBalls, uint8_t newDraws );
   static bool validateTickets( [[maybe_unused]] unsigned long newTickets );


public:  // /////////////////// Constructors & Destructors /////////////////////
   Game( uint8_t newBalls, uint8_t newDraws, unsigned long newTickets );

};
