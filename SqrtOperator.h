//----------------------------------------------------------------------
/// Filename: SqrtOperator.h
/// Group:    20
/// \brief : sqrt operator
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#ifndef SQRTOPERATOR_H_
#define SQRTOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"


#include <cmath>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <exception>

#include <iostream>

class SqrtOperator  : public GMLOperator 
{
public:
  SqrtOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)		
  {
    m_name = "sqrt";
  };

  ~SqrtOperator(){};

  void execute() const
  {   
    GMLToken operand1;
    if(m_stack.empty())
      throw std::runtime_error("ERROR sqrt: Stack is empty");
    operand1 = m_stack.back();
    m_stack.pop_back();
    if ( operand1.m_type == FLOAT) 
    {
      if(operand1.m_float[0] < 0.0)
        throw std::runtime_error("ERROR sqrt: operand less zero");
    float result = sqrt(operand1.m_float[0]);
    GMLToken token;
    token.m_type   = FLOAT;
    token.m_float[0] = result;
    m_stack.push_back(token);	 
  } 
  else if ( operand1.m_type == INTEGER)
  {
    if(operand1.m_int[0] < 0)
      throw std::runtime_error("ERROR sqrt: operand less zero");
    float result = sqrt(static_cast<float>(operand1.m_int[0]));
    GMLToken token;
    token.m_type   = FLOAT;
    token.m_float[0] = result;
    m_stack.push_back(token);	 
  } 	
  else
    throw std::runtime_error("ERROR sqrt: something went wrong");
  };
};


#endif /*SQRTOPERATOR_H_*/

