///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab D - Lucky Cat - EE 205 (Object Oriented Programming) - Spr 2024
//
//  Cats make their own luck
//
/// Declare the Draw class
///
/// @file   Draw.h
/// @author TODO <TODO@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <climits>    // For UCHAR_MAX
#include <cstdint>    // For uint8_t

#include "config.h"   // For application-level tools

#include "Game.h"     


/// Represents one Draw in a Game
class Draw {
private:  // /////////////////////// Private Members ///////////////////////////
   const Game& game;  ///< The game associated with this Draw

   /// The sorted set of numbers in the draw
   union alignas( 8 ) {
      uint8_t  each[MAX_DRAWS];  ///< Each individual draw
      uint64_t g8[MAX_DRAWS/8];  ///< A group of 8 draws
   } draw;
   

public:  // ///////////////////////// Static Methods ///////////////////////////
   static bool    validate_static();
   static uint8_t getRandom8( uint8_t balls );




public:  // /////////////////// Constructors & Destructors /////////////////////
   Draw( const Game& newGame );


public:  // ///////////////////////// Public Methods ///////////////////////////
   bool validate() const;
   void dump() const;

};
