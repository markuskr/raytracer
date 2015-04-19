//----------------------------------------------------------------------
/// \author Group: 20
/// \brief The operator for the mulf function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef MULFOPERATOR_H_
#define MULFOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <vector>
#include <string>
#include <memory>
#include <iostream>

class MulfOperator  : public GMLOperator 
{
public:
  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter

  MulfOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)		
  {
    m_name = "mulf";
  };
  
  //-------------------------------------------------------------------

  ~MulfOperator(){};

  //-------------------------------------------------------------------
  /// \brief execution of the token

  void execute() const
  {
    GMLToken operand1;
    GMLToken operand2;

    if(m_stack.empty())
      throw std::runtime_error("ERROR mulf: Stack is empty");
          		
    operand1 = m_stack.back();
    m_stack.pop_back();
          		
    if(m_stack.empty())
      throw std::runtime_error("ERROR mulff: Stack is empty");
          	
    operand2 = m_stack.back();
    m_stack.pop_back();

    if (operand1.m_type == INTEGER)
    {
      operand1.m_float[0] = (float)operand1.m_int[0];
      operand1.m_type = FLOAT;
    }
    if (operand2.m_type == INTEGER)
    {
       operand2.m_float[0] = (float)operand2.m_int[0];
       operand2.m_type = FLOAT;
    }
    if (( operand1.m_type == FLOAT) &&
        ( operand2.m_type == FLOAT))
    {
      float result = operand1.m_float[0] * operand2.m_float[0];

      GMLToken token;
      token.m_type   = FLOAT;
      token.m_float[0] = result;

      m_stack.push_back(token);	    	
    }
    else
      throw std::runtime_error("ERROR mulf: wrong operand-type");
    
  };
};


#endif /*MULFOPERATOR_H_*/

