//----------------------------------------------------------------------
/// \autor Group:    20
/// \brief The operator for the cos function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef COSOPERATOR_H_
#define COSOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <cmath>
#include <vector>
#include <string>
#include <memory>

#include <iostream>

class CosOperator : public GMLOperator
{
public:

  ///-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter

  CosOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)
  {
    m_name = "cos";
  };
  
  ///-------------------------------------------------------------------
  ~CosOperator()
  {};

  ///-------------------------------------------------------------------
  /// \brief execution of the token
  
  void execute() const
  {

    GMLToken operand1;
    if (m_stack.empty())
      throw std::runtime_error("ERROR cos: Stack is empty");

    operand1 = m_stack.back();
    m_stack.pop_back();

    if (operand1.m_type == FLOAT)
    {
      float result = static_cast<float>(cos(operand1.m_float[0]*(2.0
          * acos(-1.0)/360.0)));
      GMLToken token;
      token.m_type = FLOAT;
      token.m_float[0] = result;

      m_stack.push_back(token);
    }
    else if (operand1.m_type == INTEGER)
    {
      float result = static_cast<float>(cos(operand1.m_int[0]*(2.0
          * acos(-1.0)/360.0)));
      GMLToken token;
      token.m_type = FLOAT;
      token.m_float[0] = result;

      m_stack.push_back(token);
    }
    else
      throw std::runtime_error("ERROR cos: something went wrong");

  };
};

#endif /*COSOPERATOR_H_*/

