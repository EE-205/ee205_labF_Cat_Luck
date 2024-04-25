///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab D - Lucky Cat - EE 205 (Object Oriented Programming) - Spr 2024
//
//  Cats make their own luck
//
/// Define the Game class
///
/// @file   Game.cpp
/// @author TODO <TODO@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////


#include "Game.h"


/// Validate the number of balls in this Game
///
/// @param newBalls A potential number of balls to set
///
/// @return `true` if `newBalls` is acceptable or throws an exception
/// @throws invalid_argument if `newBalls` is outside of legal values
bool Game::validateBalls( const uint8_t newBalls ) {
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
/// @param newBalls The proposed number of balls in this Game
/// @param newDraws The proposed number of draws
///
/// @return `true` if `newDraws` is acceptable or throws an exception
/// @throws invalid_argument if `newDraws` is outside of legal values
bool Game::validateDraws( const uint8_t newBalls, const uint8_t newDraws ) {
   assert( validateBalls( newBalls ) );

   if( newDraws > newBalls ) {
      throw invalid_argument( "Game.draws must be <= Game.balls" );
   }

   if( newDraws > MAX_DRAWS ) {
      throw invalid_argument( "Game.draws must be <= " STR( MAX_DRAWS ) );
   }

   return true;
}


/// Validate the number of tickets in the Game
///
/// This is actually bounds-checked by the datatype... The minimum number is
/// 0 and the maximum number is ULONG_MAX.
///
/// @param newTickets The proposed number of tickets issued in this Game
/// @return `true` if `newTickets` is acceptable
bool Game::validateTickets( [[maybe_unused]] const unsigned long newTickets ) {
   return true;
}


/// Create a new Game
///
/// @param newBalls   The number of balls (numbers) in this Game
/// @param newDraws   The number of draws in this Game
/// @param newTickets The number of people who will play the Game
Game::Game( const uint8_t newBalls, const uint8_t newDraws, const unsigned long newTickets ) {
   if( validateBalls( newBalls) ) {
      balls = newBalls;
   }
   if( validateDraws( balls, newDraws ) ) {
      draws = newDraws;
   }
   if( validateTickets( newTickets ) ) {
      tickets = newTickets;
   }
}


/// Validate the internal state of the Game
///
/// @return `true` if the state is valid.  If not, throw an exception.
bool Game::validate() const {
   validateBalls( balls );
   validateDraws( balls, draws );
   validateTickets( tickets );

   return true;
}


/// Print the internal state of the Game
void Game::dump() const {
      PRINT_CLASS_FOR_DUMP;
      FORMAT_LINE_FOR_DUMP( "Game", "balls" )  << balls  << std::endl ;
}
