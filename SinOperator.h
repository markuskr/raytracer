//----------------------------------------------------------------------
/// Filename: SinOperator.h
/// Group:    20
/// \brief : sin operator
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#ifndef SINOPERATOR_H_
#define SINOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"


#include <cmath>
#include <vector>
#include <string>
#include <memory>

#include <iostream>

class SinOperator  : public GMLOperator 
{
public:
  SinOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)		
  {
    m_name = "sin";
  };

  ~SinOperator(){};

  void execute() const
  {   
    GMLToken operand1;
    if(m_stack.empty())
      throw std::runtime_error("ERROR sin: Stack is empty");
    operand1 = m_stack.back();
    m_stack.pop_back();
    if ( operand1.m_type == FLOAT)
    {
      float result = static_cast<float>(sin(operand1.m_float[0]*(2.0 * acos (-1.0)/360.0)));
      GMLToken token;
      token.m_type   = FLOAT;
      token.m_float[0] = result;
      m_stack.push_back(token);
    }	
    else if ( operand1.m_type == INTEGER) 
    {
      float result = static_cast<float>(sin(operand1.m_int[0]*(2.0 * acos (-1.0)/360.0)));
      GMLToken token;
      token.m_type   = FLOAT;
      token.m_float[0] = result;
      m_stack.push_back(token);
    }	
    else 
      throw std::runtime_error("ERROR sin: something went wrong"); 
  };
};


#endif /*ACOSOPERATOR_H_*/

