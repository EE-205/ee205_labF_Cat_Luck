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

#include "Draw.h"


/// Represents a single Lottery game.  Once the initial paramters of the game
/// are established, they can't be changed.  The game, however, can be payed
/// repeatedly.
class Game {
private:  // /////////////////////// Private Class ///////////////////////////

   /// A Draw Node stored in a Binary Search Tree within Game
   ///
   /// If a Game has multiple tickets with the same Draw, count indicates how
   /// many
   class Node : public Draw {
   friend Game;  ///< The Game class is a friend of Node @todo Test this when finished

   private:  // ///////////////////// Private Members /////////////////////////
      Node*        left;   ///< The left tree
      Node*        right;  ///< The right tree
      unsigned int count;  ///< The number of tickets with this Draw

   public:  // ///////////////// Constructors & Destructors ///////////////////
      /// Create a new Node
      ///
      /// @param newGame The Game for this node
      Node( Game& newGame ) : Draw( newGame )
                            , left{ nullptr }
                            , right{ nullptr }
                            , count{ 1 } {}

   public:  // /////////////////////// Public Methods /////////////////////////
      void add( Node& root ) {
         if( *this == root ) {
            count++;
//          printf( "Found duplicate... increment root\n" );
         } else if ( *this < root ) {
            if( root.left == nullptr ) {
               root.left = this;
//             printf( "Attach to root.left\n" );
            } else {
//             printf( "Descend down root.left\n" );
               add( *root.left );
            }
         } else {
            if( root.right == nullptr ) {
               root.right = this;
//             printf( "Attach to root.right\n" );
            } else {
//             printf( "Descend down root.right\n" );
               add( *root.right );
            }
         }
      }

      void dumpInOrder() {
         if( left != nullptr ) {
            left->dumpInOrder();
         }
         Draw::dump();
//       PRINT_CLASS_FOR_DUMP();
         FORMAT_LINE_FOR_DUMP( "Node", "count" ) << count << '\n' ;
         if( right != nullptr ) {
            right->dumpInOrder();
         }
      }
   };

private:  // /////////////////////// Private Members ///////////////////////////
   uint8_t       balls;        ///< The number of balls in this Game
   uint8_t       draws;        ///< The number of balls retrieved in each Draw
   unsigned long tickets;      ///< The number of customers who buy a lottery ticket
   Node*         head;         ///< Pointer to the head of a BST containing all tickets
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
   unsigned int countWinningTickets();

   bool validate() const;
   void dump() const;

};
