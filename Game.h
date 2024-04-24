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


#define MIN_BALLS (  1)   ///< The minimum number of balls in any game
#define MAX_BALLS (250)   ///< The maximum number of balls in any game
#define MAX_DRAWS ( 16)   ///< The maximum number of balls drawn in any game

/// this converts to string
#define STR_(X) #X

/// this makes sure the argument is expanded before converting to string
#define STR(X) STR_(X)


class Game {
private:
   uint8_t       balls;    ///< The number of balls in this Game
   uint8_t       draws;    ///< The number of balls retrieved in each draw
   unsigned long tickets;  ///< The number of customers who buy a lottery ticket

public:
   
   /// Validate the number of balls in this Game
   ///
   /// @param newBalls A potential number of balls to set
   ///
   /// @return `true` if `newBalls` is acceptable or throws an exception
   /// @throws invalid_argument if `newBalls` is outside of legal values
   static bool validateBalls( uint8_t newBalls ) {
      if( newBalls < MIN_BALLS ) {
         throw invalid_argument( "balls must be >= " STR( MIN_BALLS ) ); 
      }
      if( newBalls > MAX_BALLS ) {
         throw invalid_argument( "Game.balls must be <= " STR( MAX_BALLS ) );
      }
      
      return true;
   }
   
   
   /// Validate the number of draws in this Game
   ///
   /// @param newDraws The proposed number of draws
   /// 
   /// @return `true` if `newDraws` is acceptable or throws an exception
   /// @throws invalid_argument if `newDraws` is outside of legal values
   static bool validateDraws( uint8_t newBalls, uint8_t newDraws ) {
      assert( validateBalls( newBalls ) );
      
      if( newDraws > newBalls ) { 
         throw invalid_argument( "Game.draws must be <= Game.balls" );
      }
      
      if( newDraws > MAX_DRAWS ) {
         throw invalid_argument( "Game.draws must be <= " STR( MAX_DRAWS ) );
      }

      return true;      
   }


   Game( uint8_t newBalls, uint8_t newDraws, unsigned long newTickets ) {
      if( validateBalls( newBalls) ) {
         balls = newBalls;
      }
      if( validateDraws( balls, newDraws ) ) {
         draws = newDraws;
      }
      tickets = newTickets;
   }
};
