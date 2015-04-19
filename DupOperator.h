//----------------------------------------------------------------------
/// Filename: DupOperator.h
/// Group:    20
/// \brief The operator for the dup function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef DUBOPERATOR_H_
#define DUBOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <cmath>
#include <vector>
#include <string>
#include <memory>

#include <iostream>

class DupOperator : public GMLOperator
{
public:
  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter
  
  DupOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)
  {
    m_name = "dup";
  };

  //-------------------------------------------------------------------

  ~DupOperator(){};

  //-------------------------------------------------------------------
  /// \brief execution of the token

  void execute() const
  {

    GMLToken operand1;
    if (m_stack.empty())
      throw std::runtime_error("ERROR dub: Stack is empty");

    operand1 = m_stack.back();
    m_stack.push_back(operand1);

  };
};

#endif /*DubOPERATOR_H_*/


