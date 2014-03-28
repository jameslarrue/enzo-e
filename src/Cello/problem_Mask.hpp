// See LICENSE_CELLO file for license and copyright information

/// @file     problem_Mask.hpp
/// @author   James Bordner (jobordner@ucsd.edu)
/// @date     2014-03-28
/// @brief    [\ref Problem] Declaration of the Mask class
///

#ifndef PROBLEM_MASK_HPP
#define PROBLEM_MASK_HPP

class Mask {

  /// @class    Mask
  /// @ingroup  Problem
  /// @brief    [\ref Problem] 

public: // interface

  /// Constructor
  Mask() throw();

  /// Destructor
  ~Mask() throw();

  /// Copy constructor
  Mask(const Mask & Mask) throw();

  /// Assignment operator
  Mask & operator= (const Mask & Mask) throw();

  /// CHARM++ Pack / Unpack function
  inline void pup (PUP::er &p)
  {
    TRACEPUP;
    // NOTE: change this function whenever attributes change
  }

  virtual void evaluate
  (const Hierarchy * hierarchy,
   const CommBlock * comm_block,
   FieldBlock * field_block, 
   int index_field,  int index_value,
   std::string field_name, 
   const FieldDescr * field_descr,
   int n, bool * mask, bool * deflt,
   double * x, double * y, double * z, double t) throw () = 0;

  
private: // functions


private: // attributes

  // NOTE: change pup() function whenever attributes change

};

#endif /* PROBLEM_MASK_HPP */

