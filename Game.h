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

#include <cstdint>    // For uint8_t

#include "config.h"   // For application configuration

#include "Draw.h"     // For Draw


/// Represents a single Lottery game.  Once the initial parameters of the game
/// are established, they can't be changed.
class Game {
private:  // /////////////////////// Private Class ///////////////////////////

   /// A Draw Node stored in a Binary Search Tree within Game
   ///
   /// If a Game has multiple tickets with the same Draw, count indicates how
   /// many
   class Node : public Draw {
   friend Game;  ///< The Game class is a friend of Node

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
      /// Add a Node to a Binary Search Tree (BST)
      ///
      /// @param tryAddingHere Try to add the node here using BST
      void add( Node& tryAddingHere ) {
         if( *this == tryAddingHere ) {
            tryAddingHere.count++;
//          printf( "Found duplicate... increment the Node\n" );
         } else if ( *this < tryAddingHere ) {
            if( tryAddingHere.left == nullptr ) {
               tryAddingHere.left = this;
//             printf( "Attach to the left\n" );
            } else {
//             printf( "Descend down the left branch\n" );
               add( *tryAddingHere.left );
            }
         } else {
            if( tryAddingHere.right == nullptr ) {
               tryAddingHere.right = this;
//             printf( "Attach to right\n" );
            } else {
//             printf( "Descend down the right branch\n" );
               add( *tryAddingHere.right );
            }
         }
      }

      /// Dump a single Node
      ///
      /// Sample output:
      ///
      ///     Object              class               Game::Node
      ///     Object              this                0x601eb437c900
      ///     Node                count               1
      ///     Node                left                0
      ///     Node                right               0
      ///     Object              class               Draw
      ///     Object              this                0x601eb437c900
      ///     Draw                draw                 22  49  56  61  62
      ///
      void dump() {
         PRINT_CLASS_FOR_DUMP();
         FORMAT_LINE_FOR_DUMP( "Node", "count" ) << count << '\n' ;
         FORMAT_LINE_FOR_DUMP( "Node", "left" ) << left << '\n' ;
         FORMAT_LINE_FOR_DUMP( "Node", "right" ) << right << '\n' ;
         Draw::dump();
      }

      /// Dump the Node objects using a BST in-order traversal
      void dumpInOrder() {
         if( left != nullptr ) {
            left->dumpInOrder();
         }
         Node::dump();
         if( right != nullptr ) {
            right->dumpInOrder();
         }
      }

      /// Delete all Nodes in a Binary Search Tree
      void deleteAllNodes() {
         if( left == nullptr && right == nullptr ) {
            return;
         }
         if( left != nullptr ) {
            left->deleteAllNodes();
            // printf( "Delete left\n" );
            delete left;
            left = nullptr;
         }
         if( right != nullptr ) {
            right->deleteAllNodes();
            // printf( "Delete right\n" );
            delete right;
            right = nullptr;
         }
      }

      /// Find a Node/Draw in a BST.
      ///
      /// @param findThisDraw The Draw to search for
      /// @return If the Draw is in the BST, return a pointer to the Node that owns it.  If it's not in the BST, return `nullptr`.
      Node* getNode( Draw& findThisDraw ) {
         if( *this == findThisDraw ) {
            return this;
         }

         if( *this < findThisDraw ) {
            if( right == nullptr ) {
               return nullptr;
            }
            return( right->getNode( findThisDraw ) );
         }

         // *this > findThisDraw
         if( left == nullptr ) {
            return nullptr;
         }
         return( left->getNode( findThisDraw ) );
      }
   };

private:  // /////////////////////// Private Members ///////////////////////////
   uint8_t       balls;        ///< The number of balls in this Game
   uint8_t       draws;        ///< The number of balls retrieved in each Draw
   unsigned long tickets;      ///< The number of customers who buy a lottery ticket
   Node*         head;         ///< Pointer to the head of a BST containing all tickets
   Draw*         winningDraw;  ///< Pointer to the winning Draw
   unsigned long showProgress; ///< Print `.` after this number of tickets.
public:
   unsigned long getShowProgress() const;

   void setShowProgress( const unsigned long showProgress);
   ///< During buyAllLotteryTickets(), print a `.` every #Game::showProgress draws.  If `0`, then don't show any progress.

public:  // ///////////////////////// Static Methods ///////////////////////////
   static bool validateBalls( uint8_t newBalls );
   static bool validateDraws( uint8_t newBalls, uint8_t newDraws );
   static bool validateTickets( [[maybe_unused]] unsigned long newTickets );


public:  // /////////////////// Constructors & Destructors /////////////////////
   Game( uint8_t newBalls, uint8_t newDraws, unsigned long newTickets );
   virtual ~Game();


public:  // /////////////////////// Getters & Setters //////////////////////////
   /// @return The number of balls in this Game
   uint8_t       getBalls()   const { return balls;   };

   /// @return The number of balls retrieved in each Draw
   uint8_t       getDraws()   const { return draws;   };

   /// @return The number of customers who buy a lottery ticket
   unsigned long getTickets() const { return tickets; };


public:  // ///////////////////////// Public Methods ///////////////////////////
   void         buyAllLotteryTickets();
   void         makeWinningDraw();
   unsigned int countWinningTickets() const;

   bool validate() const;
   void dump()     const;

};
