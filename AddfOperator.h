//----------------------------------------------------------------------
/// \autor Group:    20
/// \brief The operator for the addf function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef ADDFOPERATOR_H_
#define ADDFOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <exception>
#include <stdexcept>
#include <vector>
#include <string>
#include <memory>
#include <string>
#include <iostream>

class AddfOperator : public GMLOperator
{
public:
  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter
  
  AddfOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)
  {
    m_name = "addf";
  };

  //-------------------------------------------------------------------
  
  ~AddfOperator()
  {};

  //-------------------------------------------------------------------
  /// \brief execution of the token
  
  void execute() const
  {
    GMLToken operand1;
    GMLToken operand2;

    if (m_stack.empty())
      throw std::runtime_error("ERROR addf: Stack is empty");

    operand1 = m_stack.back();
    m_stack.pop_back();

    if (m_stack.empty())
      throw std::runtime_error("ERROR addf: Stack is empty");

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
    
    if ((operand1.m_type == FLOAT) && (operand2.m_type == FLOAT))
    {
      float result = operand1.m_float[0] + operand2.m_float[0];
      GMLToken token;
      token.m_type = FLOAT;
      token.m_float[0] = result;

      m_stack.push_back(token);
    }

  };
};

#endif /*ADDFOPERATOR_H_*/

