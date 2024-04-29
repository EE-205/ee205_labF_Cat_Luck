///////////////////////////////////////////////////////////////////////////////
//  University of Hawaii, College of Engineering
//  Lab D - Lucky Cat - EE 205 (Object Oriented Programming) - Spr 2024
//
//  Cats make their own luck
//
/// Generic declarations for the entire simulation
///
/// @file   config.h
/// @author Mark Nelson <marknels@hawaii.edu>
///////////////////////////////////////////////////////////////////////////////


#include <iomanip>    // For setw() & setfill()
#include <ios>        // For left & boolalpha
#include <iostream>   // For cout & endl

#include <boost/core/typeinfo.hpp>  // For typeinfo()


/// A grammatically correct title for the program
#define PROGRAM_TITLE "Lottery Simulation"

/// A short-title for the program (used for console messages)
#define PROGRAM_NAME  "lottoSim"


class Draw;  // Forward declaration of the Draw object
class Game;  // Forward declaration of the Game object


/// this converts to string
#define STR_(X) #X

/// this makes sure the argument is expanded before converting to string
#define STR(X) STR_(X)


/// Format the heading for dumping members of a class to the console
///
/// Print =====================
#define PRINT_HEADING_FOR_DUMP                                                \
    /* Print =========================================================== */   \
    std::cout << std::setw(80) << std::setfill( '=' ) << "" << '\n'


/// Format a line for dumping the members of a class to the console.
/// Setup the fields for printing (space pad, left justify, etc.)
#define FORMAT_LINE_FOR_DUMP( className, member )         \
    std::cout << std::setfill( ' ' )  /** Space pad */    \
              << std::left            /** Left justify className */  \
              << std::boolalpha       /** Print `true` or `false` for `bool`s */ \
              << std::setw(20) << (className)             \
              << std::setw(20) << (member)                \
              << std::setw(40)        /** (data) */


/// Format dumping a class' object information
///
#define PRINT_CLASS_FOR_DUMP() \
      FORMAT_LINE_FOR_DUMP( "Object", "class" ) << boost::core::demangled_name( BOOST_CORE_TYPEID( *this )) << '\n' ; \
      FORMAT_LINE_FOR_DUMP( "Object", "this" )  << this  << '\n' 
