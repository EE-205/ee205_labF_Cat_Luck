///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab D - Lucky Cat - EE 205 (Object Oriented Programming) - Spr 2024
//
//  Cats make their own luck
//
/// Declare the Game class
///
/// @file   Game.h
/// @author TODO <TODO@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <cassert>    // For assert
#include <cstdint>    // For uint8_t
#include <stdexcept>  // For invalid_argument

#include "config.h"   // For application-level tools


#define MIN_BALLS   (  1)  ///< The minimum number of balls in any game
#define MAX_BALLS   (250)  ///< The maximum number of balls in any game
#define MAX_DRAWS   ( 16)  ///< The maximum number of balls drawn in any game


/// Represents a single Lottery game.  Once the initial paramters of the game
/// are established, they can't be changed.  The game, however, can be payed
/// repeatedly.
class Game {

private:  // /////////////////////// Private Members ///////////////////////////
   uint8_t       balls;        ///< The number of balls in this Game
   uint8_t       draws;        ///< The number of balls retrieved in each Draw
   unsigned long tickets;      ///< The number of customers who buy a lottery ticket
   Draw*         winningDraw;  ///< Pointer to the winning Draw


public:  // ///////////////////////// Static Methods ///////////////////////////
   static bool validateBalls( uint8_t newBalls );
   static bool validateDraws( uint8_t newBalls, uint8_t newDraws );
   static bool validateTickets( [[maybe_unused]] unsigned long newTickets );


public:  // /////////////////// Constructors & Destructors /////////////////////
   Game( uint8_t newBalls, uint8_t newDraws, unsigned long newTickets );
   ~Game();


public:  // /////////////////////// Getters & Setters //////////////////////////
   /// @return The number of balls in this Game
   uint8_t       getBalls()   const { return balls;   };

   /// @return The number of balls retrieved in each Draw
   uint8_t       getDraws()   const { return draws;   };

   /// @return The number of customers who buy a lottery ticket
   unsigned long getTickets() const { return tickets; };


public:  // ///////////////////////// Public Methods ///////////////////////////
   void buyAllLotteryTickets();
   void makeWinningDraw();

   bool validate() const;
   void dump() const;

};
