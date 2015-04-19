//----------------------------------------------------------------------
/// \author Group: 20
/// \brief The operator for the modi function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------


#ifndef MODIOPERATOR_H_
#define MODIOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"



#include <vector>
#include <string>
#include <memory>

#include <iostream>

class ModiOperator  : public GMLOperator 
{
public:
  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter

  ModiOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)		
  {
    m_name = "modi";
  };

  //-------------------------------------------------------------------

  ~ModiOperator(){};

  //-------------------------------------------------------------------
  /// \brief execution of the token

  void execute() const
  {
    if(m_stack.empty())
      throw std::runtime_error("Error modi: Stack is empty");
          
    GMLToken operand1 = m_stack.back();
    m_stack.pop_back();

    if(m_stack.empty())
      throw std::runtime_error("ERROR modi: Stack is empty");
                  
    GMLToken operand2 = m_stack.back();
    m_stack.pop_back();	

   if (( operand1.m_type == INTEGER) && ( operand2.m_type == INTEGER))
   {
     int result = operand2.m_int[0] % operand1.m_int[0];

     GMLToken token;
     token.m_type   = INTEGER;
     token.m_int[0] = result;
            
     m_stack.push_back(token);	    	
   }
   else
     throw std::runtime_error("ERROR modi: wrong operand-type");
  };

};


#endif /*MODIOPERATOR_H_*/

