///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab D - Lucky Cat - EE 205 (Object Oriented Programming) - Spr 2024
//
//  Cats make their own luck
//
/// Define the Sim class
///
/// @file   Sim.cpp
/// @author TODO <TODO@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "Game.h"

using namespace std;

/// Entry point for the program
///
/// @return The return value for the program
int main() {
   unsigned int  numRuns    =         52;  // One draw per week for 1 year

   unsigned long numTickets =  132000000;  // The size of a large PowerBall drawing
   int           numBalls   =         69;  // Powerball balls range from 1 to 69
   int           numDraws   =          5;  // Powerball draws 5 balls per game

   unsigned long numWinners =          0;  // Accumulate the number of winners here

   for( unsigned int i = 0 ; i < numRuns ; i++ ) {
      Game aGame = Game( numBalls, numDraws, numTickets );
      aGame.setShowProgress( 50000 );
      aGame.buyAllLotteryTickets();
      aGame.makeWinningDraw();
      numWinners += aGame.countWinningTickets();
      cout << '\n';
   }

   cout.imbue( locale("") );  // Print numbers with commas

   cout << numTickets << " people played an "
        << numDraws << "-draw lottery from a pool of "
        << numBalls << " numbers.\n";

   cout << "In " << numRuns << " games, there were "
        << numWinners << " winners.\n";

   return 0;
}
