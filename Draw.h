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
//   uint64_t blob;


public:  // ///////////////////////// Static Methods ///////////////////////////
   static bool validate_static();
   

public:  // /////////////////// Constructors & Destructors /////////////////////
   Draw( const Game& newGame );


public:  // ///////////////////////// Public Methods ///////////////////////////
   bool validate() const;
   void dump() const;

};
