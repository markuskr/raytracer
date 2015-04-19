//----------------------------------------------------------------------
/// \author Group: 20
/// \brief The operator for the negf function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------


#ifndef NEGFOPERATOR_H_
#define NEGFOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <vector>
#include <string>
#include <memory>

#include <iostream>

class NegfOperator  : public GMLOperator 
{
public:
  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter

  NegfOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)		
  {
    m_name = "negf";
  };
	
  //-------------------------------------------------------------------

  ~NegfOperator()
  {};

  //-------------------------------------------------------------------
  /// \brief execution of the token
	
  void execute() const
  {
    if(m_stack.empty())
      throw std::runtime_error("ERROR lessf: Stack is empty");
		
    GMLToken operand1 = m_stack.back();
    m_stack.pop_back();
				
    if (( operand1.m_type == FLOAT) && operand1.m_float[0] != 0.0)
    { 
      float result = static_cast<float>(operand1.m_float[0] * -1.0);

      GMLToken token;
      token.m_type   = FLOAT;
      token.m_float[0] = result;
      
      m_stack.push_back(token);	    	
    }
    else 
      throw std::runtime_error("ERROR negf: wrong operand-type");
  };
};


#endif /*NEGFOPERATOR_H_*/

