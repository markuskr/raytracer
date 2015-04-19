//----------------------------------------------------------------------
/// \autor Group:    20
/// \brief The operator for the frac function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef FRACOPERATOR_H_
#define FRACOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"


#include <exception>
#include <vector>
#include <string>
#include <memory>

#include <iostream>

class FracOperator  : public GMLOperator 
{
public:
  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter
	
  FracOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)		
  {
    m_name = "frac";
  };
  //------------------------------------------------------------------

  ~FracOperator()
  {};

  //-------------------------------------------------------------------
  /// \brief execution of the token

  void execute() const
  {
    GMLToken operand1;       

    if(m_stack.empty())
      throw std::runtime_error("ERROR frac: Stack is empty");
                 	
    operand1 = m_stack.back();
    m_stack.pop_back();	      
          
    double p = static_cast<double>(operand1.m_float[0]);
      
    float result=0.0;
             
    if(p>=0)
      result = operand1.m_float[0]-floor(operand1.m_float[0]);
    else if(p<0)
      result = operand1.m_float[0]-ceil(operand1.m_float[0]);
             
    GMLToken token;
    token.m_type   = FLOAT;
    token.m_float[0] = result;
      
    m_stack.push_back(token);	        

   };
};


#endif /*FRACOPERATOR_H_*/


