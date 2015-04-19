//----------------------------------------------------------------------
/// Filename: DivfOperator.h
/// Group:    20
/// \brief The operator for the divf function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef DIVFOPERATOR_H_
#define DIVFOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <exception>

#include <iostream>

class DivfOperator : public GMLOperator
{
public:

  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter
  
  DivfOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)
    {
      m_name = "divf";
    };

  //-------------------------------------------------------------------

  ~DivfOperator(){};

  //-------------------------------------------------------------------
  /// \brief execution of the token

  void execute() const
  {
    GMLToken operand1;
    GMLToken operand2;

    if (m_stack.empty())
      throw std::runtime_error("ERROR divf: Stack is empty");

    operand1 = m_stack.back();
    m_stack.pop_back();

    if (m_stack.empty())
      throw std::runtime_error("ERROR divf: Stack is empty");

    operand2 = m_stack.back();
    m_stack.pop_back();

    if ((operand1.m_type == FLOAT) && (operand2.m_type == FLOAT))
    {
      if (operand1.m_float[0] == 0.0)
        throw std::runtime_error("ERROR: Division through Zero");

      float result = operand2.m_float[0] / operand1.m_float[0];
      GMLToken token;
      token.m_type = FLOAT;
      token.m_float[0] = result;

      m_stack.push_back(token);
    }
    else
      throw std::runtime_error("ERROR divf: Wrong operand-type");
  }
  ;
};

#endif /*DIVFOPERATOR_H_*/



