//----------------------------------------------------------------------
/// Filename: DupOperator.h
/// Group:    20
/// \brief The operator for the dup function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef EQFOPERATOR_H_
#define EQFOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <vector>
#include <string>

#include <stdexcept>

class EqfOperator : public GMLOperator
{
public:
  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter

  EqfOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)
  {
    m_name = "eqf";
  };

  //-------------------------------------------------------------------

  ~EqfOperator()
  {};

  //-------------------------------------------------------------------
  /// \brief execution of the token

  void execute() const
  {

    if (m_stack.empty())
      throw std::runtime_error("Error eqf: Stack is empty");

    GMLToken operand1 = m_stack.back();
    m_stack.pop_back();

    if (m_stack.empty())
      throw std::runtime_error( "ERROR eqf: Stack is empty");

    GMLToken operand2 = m_stack.back();
    m_stack.pop_back();

    if ((operand1.m_type == FLOAT) && (operand2.m_type == FLOAT))
    {
      int result = 0;

      if (operand1.m_float[0] == operand2.m_float[0])
        result = 1;
      else
        result = 0;

      GMLToken token;
      token.m_type = INTEGER;
      token.m_int[0] = result;

      m_stack.push_back(token);
    }
    else
      throw std::runtime_error( "ERROR eqf: wrong operand-type" );

  }
  ;
};

#endif /*EQIOPERATOR_H_*/


