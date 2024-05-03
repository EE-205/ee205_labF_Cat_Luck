///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab D - Lucky Cat - EE 205 (Object Oriented Programming) - Spr 2024
//
//  Cats make their own luck
//
/// Define the Game class
///
/// The Game can consume a lot of memory.  In C++, when `new` fails it should
/// throws a [bad_alloc](https://en.cppreference.com/w/cpp/memory/new/bad_alloc)
/// exception.
///
/// However, in modern C++ and certain operating systems (Like 64-bit Linux),
/// when systems run out of memory, the OS kills the process before an exception
/// can be thrown.  @see https://accu.org/journals/overload/31/176/wu/
///
/// Therefore, we do not make any attempt to try/catch nor recover from a Game
/// that exceeds the available physical memory + swap.
///
/// @file   Game.cpp
/// @author TODO <TODO@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <cassert>    // For assert
#include <cstdint>    // For uint8_t
#include <iostream>   // For cout
#include <stdexcept>  // For invalid_argument logic_error

#include "Game.h"     // For obvious reasons

#include "Draw.h"     // For Draw

using namespace std;


/// Validate the number of balls in this Game
///
/// @param newBalls A potential number of balls to set
///
/// @return `true` if `newBalls` is acceptable or throws an exception
/// @throws invalid_argument if `newBalls` is outside of legal values
bool Game::validateBalls( const uint8_t newBalls ) {
   if( newBalls < MIN_BALLS ) {
      throw invalid_argument( "Game.balls must be >= " STR( MIN_BALLS ) );
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

   if( newDraws < 1 ) {
      throw invalid_argument( "Game.draws must be >= 1" );
   }

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
/// 1 and the maximum number is ULONG_MAX.
///
/// @param newTickets The proposed number of tickets issued in this Game
/// @return `true` if `newTickets` is acceptable
/// @throws invalid_argument if `newTickets` is outside of legal values
bool Game::validateTickets( const unsigned long newTickets ) {
   if( newTickets < 1 ) {
      throw invalid_argument( "Game.tickets must be >= 1" );
   }
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
                                             , winningDraw { nullptr }
                                             , showProgress { 0 } {
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


/// Getter for #Game::showProgress
///
/// @return #Game::showProgress
unsigned long Game::getShowProgress() const {
   return showProgress;
}


/// Setter for #Game::showProgress
///
/// @param showProgress The value to set.  `0` (default) disables printing progress.
void Game::setShowProgress( unsigned long showProgress ) {
   Game::showProgress = showProgress;
}


/// Draw a special ticket
void Game::makeWinningDraw() {
   if( winningDraw != nullptr ) {
      /// @throws logic_error Attempt to repeat a winning draw.  Each Game gets only one draw.
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
   PRINT_HEADING_FOR_DUMP;

   PRINT_CLASS_FOR_DUMP();
   FORMAT_LINE_FOR_DUMP( "Game", "balls" )   << +balls   << '\n' ;
   FORMAT_LINE_FOR_DUMP( "Game", "draws" )   << +draws   << '\n' ;
   FORMAT_LINE_FOR_DUMP( "Game", "tickets" ) << +tickets << '\n' ;

   if( head == nullptr ) {
      FORMAT_LINE_FOR_DUMP( "Game", "head" ) << "--" << '\n' ;
   } else {
      FORMAT_LINE_FOR_DUMP( "Game", "head" ) << " " << '\n' ;
      head->dump();
   }

   if( winningDraw == nullptr ) {
      FORMAT_LINE_FOR_DUMP( "Game", "winningDraw" ) << "--" << '\n' ;
   } else {
      FORMAT_LINE_FOR_DUMP( "Game", "winningDraw" ) << " " << '\n' ;
      winningDraw->dump();
   }

   PRINT_HEADING_FOR_DUMP;

   if( head == nullptr ) {
      FORMAT_LINE_FOR_DUMP( "Game", "tickets" ) << "--" << '\n' ;
   } else {
      FORMAT_LINE_FOR_DUMP( "Game", "tickets" ) << " " << '\n' ;
      head->dumpInOrder();
   }

   PRINT_HEADING_FOR_DUMP;
}


/// Make a random Draw for each lottery ticket and store it in a data structure
void Game::buyAllLotteryTickets() {
   assert( validate() );

   if( winningDraw != nullptr ) {
      /// @throws logic_error Attempt to buy lottery tickets after the draw!
      throw logic_error( "Attempt to buy lottery tickets after the draw!" );
   }

   if( head != nullptr ) {
      /// @throws logic_error Attempt to buy more lottery tickets after buying them all already!
      throw logic_error( "Attempt to buy more lottery tickets after buying them all already!" );
   }

   /// Put the first lottery ticket in #Game.head
   head = new Node( *this );

   unsigned int progress = showProgress;

   for( unsigned long i = 1 ; i < tickets ; i++ ) {
      Node* ticket = new Node( *this );
      assert( ticket->validate() );

      ticket->add( *head );

      if( progress-- == 1 ) {   /// Print a `.` when showProgress is near `UINT_MAX`
         cout << '.' << flush;  /// Print progress incrementally
         progress = showProgress;
      }
   }

// head->dumpInOrder();
}


/// Get the number of winning tickets in the Game
///
/// @return The number of winning tickets (matching Draw objects) in the Game
unsigned int Game::countWinningTickets() const {
   if( winningDraw == nullptr ) {
      /// @throws logic_error Attempt to count winning tickets before drawing the winning ticket
      throw logic_error("Attempt to count winning tickets before drawing the winning ticket");
   }

   if( head == nullptr ) {
      /// @throws logic_error Attempt to count winning tickets before buying tickets
      throw logic_error("Attempt to count winning tickets before buying tickets");
   }

   Node *aNode = head->getNode(*winningDraw);
   if (aNode == nullptr) {
   Node *aNode = head->getNode( *winningDraw );
   if( aNode == nullptr ) {
      return 0;
   }
   return aNode->count;
}
