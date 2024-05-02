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
   unsigned int  numRuns    =       52;
   unsigned long numWinners =        0;

   unsigned long numTickets =  100000;
   int           numBalls   =       10;
   int           numDraws   =        3;

//   cout << unitbuf;  // Print `.` incrementally using unbuffered output

   for( unsigned int i = 0 ; i < numRuns ; i++ ) {
      Game aGame = Game( numBalls, numDraws, numTickets );
      aGame.setShowProgress( 10000 );
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
