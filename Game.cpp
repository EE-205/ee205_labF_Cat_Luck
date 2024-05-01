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

#include <cassert>    // For assert
#include <cstdint>    // For uint8_t
#include <ostream>    // For endl
#include <stdexcept>  // For invalid_argument

#include "Game.h"

#include "Draw.h"

using namespace std;


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
Game::Game( const uint8_t newBalls
           ,const uint8_t newDraws
           ,const unsigned long newTickets ) : head { nullptr }
                                             , winningDraw { nullptr } {
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


/// Destructor for Game
Game::~Game() {
   if( winningDraw != nullptr ) {
      delete winningDraw;
      winningDraw = nullptr;
   }
}


/// Draw a special ticket
void Game::makeWinningDraw() {
   if( winningDraw != nullptr ) {
      throw logic_error( "Attempt to repeat a winning draw.  Each Game gets only one draw!" );
   }
   winningDraw = new Draw( *this );
};



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
///
/// @todo balls & draws are not printing
///
///     Object              class               Game
///     Object              this                0x7ffc6260c718
///     Game                balls               16
///     Game                draws               8
///     Game                tickets             1000
///
void Game::dump() const {
   PRINT_CLASS_FOR_DUMP();
   FORMAT_LINE_FOR_DUMP( "Game", "balls" )   << +balls   << '\n' ;
   FORMAT_LINE_FOR_DUMP( "Game", "draws" )   << +draws   << '\n' ;
   FORMAT_LINE_FOR_DUMP( "Game", "tickets" ) << +tickets << '\n' ;
   if( winningDraw == nullptr ) {
      FORMAT_LINE_FOR_DUMP( "Game", "winningDraw" ) << "--" << '\n' ;
   } else {
      FORMAT_LINE_FOR_DUMP( "Game", "winningDraw" ) << " " << '\n' ;
      winningDraw->dump();
   }
}


/// Make a random Draw for each lottery ticket and store it in a data structure
void Game::buyAllLotteryTickets() {
   assert( validate() );
   
   if( winningDraw != nullptr ) {
      throw logic_error( "Attempt to buy lottery tickets after the draw!" );
   }

   for( unsigned long i = 0 ; i < tickets ; i++ ) {
      Node* xx = new Node();
      assert( xx->validate() );
      xx->left = nullptr;
      xx->right = nullptr;
      printf( "." );
   }   
}
