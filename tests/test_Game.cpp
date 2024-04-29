///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab D - Lucky Cat - EE 205 (Object Oriented Programming) - Spr 2024
//
//  Cats make their own luck
//
/// Comprehensive test of the Game class
///
/// @file test_Game.cpp
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////
/// @cond Suppress Doxygen warnings

#define BOOST_TEST_MODULE Lucky_Cat_Test_Suite
#include <boost/test/included/unit_test.hpp>

#include "../Game.h"

using namespace std;

BOOST_AUTO_TEST_SUITE( test_Game )

   BOOST_AUTO_TEST_CASE( test_validateBalls ) {
      BOOST_CHECK_THROW( Game::validateBalls( MIN_BALLS - 1 ), invalid_argument );
      BOOST_CHECK_NO_THROW( Game::validateBalls( MIN_BALLS ) );
      BOOST_CHECK_NO_THROW( Game::validateBalls( MAX_BALLS ) );
      BOOST_CHECK_THROW( Game::validateBalls( MAX_BALLS +1 ), invalid_argument );
   }

   BOOST_AUTO_TEST_CASE( test_validateDraws ) {
      BOOST_CHECK_THROW( Game::validateDraws( MIN_BALLS-1, MIN_BALLS-1 ), invalid_argument );
      BOOST_CHECK_THROW( Game::validateDraws( 5, 6 ), invalid_argument );
      BOOST_CHECK_NO_THROW( Game::validateDraws( MIN_BALLS, MIN_BALLS ) );
      BOOST_CHECK_NO_THROW( Game::validateDraws( MAX_BALLS, MIN_BALLS ) );
      BOOST_CHECK_NO_THROW( Game::validateDraws( MAX_BALLS, MAX_DRAWS ) );
      BOOST_CHECK_THROW( Game::validateDraws( MAX_BALLS, MAX_DRAWS+1 ), invalid_argument );
      BOOST_CHECK_THROW( Game::validateDraws( MAX_BALLS + 1, MAX_DRAWS ), invalid_argument );
   }

   BOOST_AUTO_TEST_CASE( test_validateTickets ) {
      /// No tests for validateTickets (for now)
   }

   BOOST_AUTO_TEST_CASE( test_validateDump ) {
      Game aGame( 16, 8, 1000 );
//    aGame.dump();
   }

   BOOST_AUTO_TEST_CASE( test_GameGetters ) {
      Game aGame( 16, 8, 1000 );
      BOOST_CHECK_EQUAL( aGame.getBalls(), 16 );
      BOOST_CHECK_EQUAL( aGame.getDraws(), 8 );
      BOOST_CHECK_EQUAL( aGame.getTickets(), 1000 );
   }

BOOST_AUTO_TEST_SUITE_END()

/// @endcond
