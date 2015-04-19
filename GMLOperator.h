//----------------------------------------------------------------------
/// \author Group 20
/// \brief Interface for the operators
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef GMLOPERATOR_
#define GMLOPERATOR_

#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "GMLToken.h"

class GMLOperator
{
public:
  std::string& getName()
  {
    return m_name;
  };

  GMLOperator(std::vector<GMLToken> &stack) :
    m_stack(stack)
  {};

  virtual void execute() const = 0;
  virtual ~GMLOperator()
  {};

protected:
  std::string m_name;
  std::vector<GMLToken> &m_stack;

};

#endif /*GMLOPERATOR_*/

