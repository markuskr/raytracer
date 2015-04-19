//----------------------------------------------------------------------
/// \author Group: 20
/// \brief The operator for the muli function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef MULIOPERATOR_H_
#define MULIOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <vector>
#include <string>
#include <memory>

#include <iostream>

class MuliOperator : public GMLOperator
{
public:
  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter

  MuliOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)
  {
    m_name = "muli";
  };

  //-------------------------------------------------------------------

  ~MuliOperator()
  {};

  //-------------------------------------------------------------------
  /// \brief execution of the token

  void execute() const
  {
    GMLToken operand1;
    GMLToken operand2;

    if (m_stack.empty())
      throw std::runtime_error("ERROR muli: Stack is empty");

    operand1 = m_stack.back();
    m_stack.pop_back();

    if (m_stack.empty())
      throw std::runtime_error("ERROR muli: Stack is empty");

    operand2 = m_stack.back();
    m_stack.pop_back();

    if ((operand1.m_type == INTEGER) && (operand2.m_type == INTEGER))
    {
      int result = operand1.m_int[0] * operand2.m_int[0];
      GMLToken token;
      token.m_type = INTEGER;
      token.m_int[0] = result;

      m_stack.push_back(token);
      return;
    }
    else
      throw std::runtime_error("ERROR muli: wrong operand-type");
  };
};

#endif /*MULIOPERATOR_H_*/

