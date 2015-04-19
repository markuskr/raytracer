//----------------------------------------------------------------------
/// \author Group:    20
/// \brief The operator for the addf function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef ADDIOPERATOR_H_
#define ADDIOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"


#include <vector>
#include <string>
#include <memory>
#include <exception>
#include <iostream>

class AddiOperator  : public GMLOperator 
{
public:

  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter
  
    AddiOperator(std::vector<GMLToken> &stack) :
      GMLOperator(stack)
      {
          m_name = "addi";
      };

  //-------------------------------------------------------------------
  
      ~AddiOperator(){};

  //-------------------------------------------------------------------
  /// \brief execution of the token
  
      void execute() const
      {
          GMLToken operand1;
          GMLToken operand2;
          if(m_stack.empty())
            throw std::runtime_error("ERROR addi: Stack is empty");
          
           operand1 = m_stack.back();
           m_stack.pop_back();

           if(m_stack.empty())
             throw std::runtime_error("ERROR addi: Stack is empty");
           
           operand2 = m_stack.back();
           m_stack.pop_back();

           if (( operand1.m_type == INTEGER) &&
              ( operand2.m_type == INTEGER))
           {
              int result = operand1.m_int[0] + operand2.m_int[0];
              GMLToken token;
              token.m_type   = INTEGER;
              token.m_int[0] = result;
              m_stack.push_back(token);	  
              return;
            }
           else throw std::runtime_error("ERROR addi: wrong operand-type");
      };
};


#endif /*ADDIOPERATOR_H_*/




