//----------------------------------------------------------------------
/// \author Group: 20
/// \brief The operator for the negi function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------


#ifndef NEGIOPERATOR_H_
#define NEGIOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"


#include <vector>
#include <string>
#include <memory>

#include <iostream>

class NegiOperator  : public GMLOperator 
{
public:
  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter

  NegiOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)		
  {
    m_name = "negi";
  };

  //-------------------------------------------------------------------
	
  ~NegiOperator(){};

  //-------------------------------------------------------------------
  /// \brief execution of the token

  void execute() const
  {
    if(m_stack.empty())
	throw std::runtime_error("ERROR negi: Stack is empty");
	
    GMLToken operand1;
    operand1 = m_stack.back();
    m_stack.pop_back();

    if (( operand1.m_type == INTEGER) && operand1.m_int[0] != 0)
    {
      int result = operand1.m_int[0] * -1;
	
      GMLToken token;
	token.m_type   = INTEGER;
	token.m_int[0] = result;

      m_stack.push_back(token);	    	
    }		
    else
      throw std::runtime_error("ERROR negi: wrong operand-type");
  };
};


#endif /*NEGIOPERATOR_H_*/

