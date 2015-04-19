//----------------------------------------------------------------------
/// Filename: DiviOperator.h
/// Group:    20
/// \brief The operator for the divi function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef DIVIOPERATOR_H_
#define DIVIOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <exception>

#include <iostream>

class DiviOperator : public GMLOperator
{
public:

  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter

  DiviOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)
  {
    m_name = "divi";
  };

  //-------------------------------------------------------------------

  ~DiviOperator(){};

  //-------------------------------------------------------------------
  /// \brief execution of the token
  
  void execute() const
  {
    GMLToken operand1;
    GMLToken operand2;

    if (m_stack.empty())
      throw std::runtime_error( "ERROR divi: Stack is empty" );

    operand1 = m_stack.back();
    m_stack.pop_back();

    if (m_stack.empty())
      throw std::runtime_error( "ERROR divi: Stack is empty" );

    operand2 = m_stack.back();
    m_stack.pop_back();

    if ((operand1.m_type == INTEGER) && (operand2.m_type == INTEGER))
    {
      if (operand1.m_int[0] == 0)
        throw std::runtime_error( "ERROR: Division through Zero" );

      int result = operand2.m_int[0] / operand1.m_int[0];
      GMLToken token;
      token.m_type = INTEGER;
      token.m_int[0] = result;

      m_stack.push_back(token);
    }
    else
      throw std::runtime_error("ERROR divi: Wrong operand-type");
  }
  ;
};

#endif /*DIVIOPERATOR_H_*/


