///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab D - Lucky Cat - EE 205 (Object Oriented Programming) - Spr 2024
//
//  Cats make their own luck
//
/// The main() program that drives the simulation
///
/// @file   Sim.cpp
/// @author TODO <TODO@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <cassert>   // For assert
#include <iostream>  // For cout
#include <locale>    // For locale

#include "Game.h"

using namespace std;

/// Entry point for the program
///
/// @return The return value for the program
int main() {

   assert( Draw::validate_static() );

   const unsigned int  numRuns      =      4;  /// - Three draws per week for 1 year
   const unsigned long showProgress =      50000;  /// - Print a `.` after this many tickets drawn
   const unsigned long numTickets   =   21417741;  /// - The size of an average PowerBall drawing:  https://lottoreport.com/ticketcomparison.htm
   const int           numBalls     =         69;  /// - Powerball balls range from 1 to 69
   const int           numDraws     =          5;  /// - Powerball draws 5 balls per game

   unsigned long       numWinners   =          0;  //  Accumulate the number of winners here

   cout << "Game"
        << "  balls: "   << numBalls
        << "  draws: "   << numDraws
        << "  tickets: " << numTickets
        << "  runs: "    << numRuns
        << '\n';

   for( unsigned int i = 0 ; i < numRuns ; i++ ) {
      Game aGame = Game( numBalls, numDraws, numTickets );
      aGame.setShowProgress( showProgress );
      aGame.buyAllLotteryTickets();
      aGame.makeWinningDraw();
      // aGame.dump();
      numWinners += aGame.countWinningTickets();
      if( showProgress != 0 ) {
         cout << '\n';
      }
   }

   cout.imbue( locale("") );  // Print numbers with commas

   cout << numTickets << " people played a "
        << numDraws << "-draw lottery from a pool of "
        << numBalls << " numbers.\n";

   cout << "In " << numRuns << " games, there were "
        << numWinners << " winners.\n";

   return 0;
}
