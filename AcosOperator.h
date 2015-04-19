//----------------------------------------------------------------------
/// \autor Group:    20
/// \brief The operator for the acos function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef ACOSOPERATOR_H_
#define ACOSOPERATOR_H_

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

class AcosOperator : public GMLOperator
{
public:
  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter
  
  AcosOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)
  {
    m_name = "acos";
  };  

  //-------------------------------------------------------------------
  
  ~AcosOperator()
  {}; 
  
  //-------------------------------------------------------------------
  /// \brief execution of the token
   
  void execute() const
  {
    GMLToken operand1;
    if (m_stack.empty())
      throw std::runtime_error("ERROR Acos: Stack is empty");

    operand1 = m_stack.back();
    m_stack.pop_back();

    if ( (operand1.m_type == INTEGER) && ((operand1.m_int[0]==0)
        || (operand1.m_int[0] == 1) || (operand1.m_int[0]== -1 ) ))
    {
      operand1.m_float[0] = static_cast<float>(operand1.m_int[0]);
      operand1.m_type = FLOAT;
    }

    if (operand1.m_type == FLOAT)
    {
      if (operand1.m_float[0] >= -1.0 && operand1.m_float[0] <= 1.0)
      {
        float result = static_cast<float>(acos(operand1.m_float[0])
            * 360 / (2 * acos(-1.0)));
        
        GMLToken token;
        token.m_type = FLOAT;
        token.m_float[0] = result;

        m_stack.push_back(token);
      }
      else
        throw std::runtime_error("ERROR acos: out of range");
    }
    else
      throw std::runtime_error("ERROR Acos: Wrong operand type");
  };
};

#endif /*ACOSOPERATOR_H_*/

