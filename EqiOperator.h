//----------------------------------------------------------------------
/// Filename: EqiOperator.h
/// Group:    20
/// \brief The operator for the eqi function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef EQIOPERATOR_H_
#define EQIOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <vector>
#include <string>
#include <stdexcept>


class EqiOperator : public GMLOperator
{
public:
  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter

  EqiOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)
  {
    m_name = "eqi";
  };

  //-------------------------------------------------------------------

  ~EqiOperator()
  {};

  //-------------------------------------------------------------------
  /// \brief execution of the token

  void execute() const
  {

    if (m_stack.empty())
      throw std::runtime_error("Error eqi: Stack is empty");

    GMLToken operand1 = m_stack.back();
    m_stack.pop_back();

    if (m_stack.empty())
      throw std::runtime_error("ERROR eqi: Stack is empty");

    GMLToken operand2 = m_stack.back();
    m_stack.pop_back();

    if ((operand1.m_type == INTEGER) && (operand2.m_type == INTEGER))
    {
      int result = 0;

      if (operand1.m_int[0] == operand2.m_int[0])
        result = 1;
      else
        result = 0;

      GMLToken token;
      token.m_type = INTEGER;
      token.m_int[0] = result;

      m_stack.push_back(token);
    }
    else
      throw std::runtime_error("ERROR modi: wrong operand-type");

  }
  ;
};

#endif /*EQIOPERATOR_H_*/


