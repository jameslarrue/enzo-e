// $Id$
// See LICENSE_CELLO file for license and copyright information

#ifndef FIELD_HPP
#define FIELD_HPP

/// @file     field.hpp
/// @author   James Bordner (jobordner@ucsd.edu)
/// @date     2009-11-17
/// @brief    Include file for the \ref Field component

//----------------------------------------------------------------------
// System includes
//----------------------------------------------------------------------

#include <map>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

//----------------------------------------------------------------------
// Component dependencies
//----------------------------------------------------------------------

#include "error.hpp"
#include "disk.hpp"
#include "mesh.hpp"

//----------------------------------------------------------------------
// Component class includes
//----------------------------------------------------------------------

class FieldBlock;
class FieldFaces;

#include "field_FieldDescr.hpp"
#include "field_FieldBlock.hpp"
#include "field_FieldFaces.hpp"
#include "field_FacesGroup.hpp"

#endif /* FIELD_HPP */

