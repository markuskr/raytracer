//----------------------------------------------------------------------
/// \autor Group:    20
/// \brief The operator for the clampf function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef CLAMPFOPERATOR_H_
#define CLAMPFOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <cmath>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

#include <iostream>

class ClampfOperator : public GMLOperator
{
public:

  ///-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter
  
  ClampfOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)
  {
    m_name = "clampf";
  };

  ///-------------------------------------------------------------------
  ~ClampfOperator()
  {
  };

  ///-------------------------------------------------------------------
  /// \brief execution of the token
  
  void execute() const
  {

    GMLToken operand1;
    if (m_stack.empty())
      throw std::runtime_error("ERROR clampf: Stack is empty");

    operand1 = m_stack.back();
    m_stack.pop_back();

    if (operand1.m_type == FLOAT)
    {
      GMLToken token;
      token.m_type = FLOAT;
      if (operand1.m_float[0] < 0.0)
      {
        token.m_float[0] = 0.0;

      }
      else if (operand1.m_float[0] > 1.0)
      {
        token.m_float[0] = 1.0;
      }
      else
        token.m_float[0] = operand1.m_float[0];

      m_stack.push_back(token);
    }
    else if (operand1.m_type == INTEGER)
    {
      GMLToken token;
      token.m_type = INTEGER;
      if (operand1.m_int[0] < 0)
      {
        token.m_float[0] = 0.0;

      }
      else if (operand1.m_int[0] >=1)
      {
        token.m_float[0] = 1.0;
      }
      else
        token.m_float[0] = static_cast<float>(operand1.m_int[0]);

      m_stack.push_back(token);
    }
    else
      throw std::runtime_error("ERROR clampf: wrong operand-type");
  };
};

#endif /*CLAMPFOPERATOR_H_*/

