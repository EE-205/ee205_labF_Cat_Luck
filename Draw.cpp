///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab D - Lucky Cat - EE 205 (Object Oriented Programming) - Spr 2024
//
//  Cats make their own luck
//
/// Define the Draw class
///
/// @file   Draw.cpp
/// @author TODO <TODO@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <cassert>    // For assert

#include "Draw.h"  // For obvious reasons

#include "Game.h"

using namespace std;


/// Create a new Draw for a Game
///
/// @param newGame The Game associated with this drawing
Draw::Draw( const Game& newGame ) : game( newGame ) {
}


/// Validate that the compiler is compatible with the assumptions
/// Draw makes about data sizes.  This really only needs to be run once.
///
/// Like the other `validate` functions, it either returns `true` or raises
/// an exception (in this case, it fails an assert()).
///
/// @return `true` if Draw's data structure will compile and work correctly.
bool Draw::validate_static() {
   static_assert( MAX_BALLS <= UCHAR_MAX );

   return true;
}


/// Validate the internal state of the Draw
///
/// @return `true` if the state is valid.  If not, throw an exception.
bool Draw::validate() const {
   game.validate();

   return true;
}


/// Print the internal state of the Draw
///
///     Object              class               Game                                    
///     Object              this                0x7ffc6260c718                          
///     Game                balls               16                                
///     Game                draws               8                                   
///     Game                tickets             1000  
///
void Draw::dump() const {
   PRINT_CLASS_FOR_DUMP();
   /// We choose not to print the entire Game each time we print a Draw
}
