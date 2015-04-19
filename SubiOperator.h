//----------------------------------------------------------------------
/// \autor Group:    20
/// \brief The operator for the acos function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#ifndef SUBIOPERATOR_H_
#define SUBIOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"


#include <exception>
#include <vector>
#include <string>
#include <memory>

#include <iostream>

class SubiOperator  : public GMLOperator 
{
public:
  SubiOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)		
  {
    m_name = "subi";
  };

  ~SubiOperator(){};

  void execute() const
  {
    GMLToken operand1;
    GMLToken operand2;
    if(m_stack.empty())
      throw std::runtime_error("ERROR subi: Stack is empty");
    operand1 = m_stack.back();
    m_stack.pop_back();
    if(m_stack.empty())
      throw std::runtime_error("ERROR subi: Stack is empty");
    operand2 = m_stack.back();
    m_stack.pop_back();		

    if (( operand1.m_type == INTEGER) &&
      ( operand2.m_type == INTEGER))
    {
      int result = operand2.m_int[0] - operand1.m_int[0];
      GMLToken token;
      token.m_type   = INTEGER;
      token.m_int[0] = result;
      m_stack.push_back(token);	    	
    }	
    else
      throw std::runtime_error("ERROR subi: Somkething went wrong"); 
  };
};


#endif /*SUBIOPERATOR_H_*/


