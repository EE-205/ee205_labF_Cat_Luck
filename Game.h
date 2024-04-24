///////////////////////////////////////////////////////////////////////////////
//   University of Hawaii, College of Engineering
//   Lab D - Lucky Cat - EE 205 (Object Oriented Programming) - Spr 2024
//
//   Cats make their own luck
//
/// @file   Game.h
/// @author TODO <TODO@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////


#include <cstdint>    // For uint8_t
#include <stdexcept>  // For invalid_argument


using namespace std;


#define MIN_BALLS (  1)   ///< The minimum number of balls in any game
#define MAX_BALLS (250)   ///< The maximum number of balls in any game


class Game {
private:
   uint8_t       balls;    ///< The number of balls in this Game
   uint8_t       draws;    ///< The number of balls retrieved in each draw
   unsigned long tickets;  ///< The number of customers who buy a lottery ticket

protected:
   void setBalls( uint8_t newBalls ) {
      if( newBalls < MIN_BALLS ) {
         throw invalid_argument( "balls must be >= 1" ); 
      }
      if( newBalls > MAX_BALLS ) {
         throw invalid_argument( "Game.balls must be <= 250" );
      }
      
      balls = newBalls;
   }

public:
   Game( uint8_t newBalls, uint8_t newDraws, unsigned long newTickets ) {
      setBalls( newBalls );
      draws = newDraws;
      tickets = newTickets;
   }
};
