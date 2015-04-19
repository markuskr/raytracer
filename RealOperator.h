//----------------------------------------------------------------------
/// Filename: RealOperator.h
/// Group:    20
/// \brief : real operator
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#ifndef REALOPERATOR_H_
#define REALOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <cmath>
#include <vector>
#include <string>
#include <memory>

#include <iostream>

class RealOperator : public GMLOperator
{
public:
  RealOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)
  {
    m_name = "real";
  };

  ~RealOperator()
  {
  };

//----------------------------------------------------------------------
  void execute() const
  {

    GMLToken operand1;
    if (m_stack.empty())
      throw std::runtime_error("ERROR real: Stack is empty");

    operand1 = m_stack.back();
    m_stack.pop_back();

    if (operand1.m_type == INTEGER)
    {
      float result = static_cast<float>(operand1.m_int[0]);
      GMLToken token;
      token.m_type = FLOAT;
      token.m_float[0] = result;

      m_stack.push_back(token);
    }
    else
      throw std::runtime_error("ERROR real: wrong operand-type");

  }
  ;
};

#endif /*REALOPERATOR_H_*/

