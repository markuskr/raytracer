//----------------------------------------------------------------------
/// \author Group: 20
/// \brief The operator for the lessi function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------


#ifndef LESSIOPERATOR_H_
#define LESSIOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <vector>
#include <string>
#include <memory>

#include <stdexcept>

class LessiOperator : public GMLOperator
{
public:
  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter

  LessiOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)
  {
    m_name = "lessi";
  };

  //-------------------------------------------------------------------

  ~LessiOperator()
  {};

  //-------------------------------------------------------------------
  /// \brief execution of the token

  void execute() const
  {
    GMLToken operand1;
    GMLToken operand2;

    if (m_stack.empty())
      throw std::runtime_error("ERROR lessf: Stack is empty");

    operand1 = m_stack.back();
    m_stack.pop_back();

    if (m_stack.empty())
      throw std::runtime_error("ERROR lessf: Stack is empty");

    operand2 = m_stack.back();
    m_stack.pop_back();

    if ((operand1.m_type == INTEGER) && (operand2.m_type == INTEGER))
    {
      int result = 0;
      if (operand2.m_int[0] < operand1.m_int[0])
        result = 1;
      else
        result = 0;

      GMLToken token;
      token.m_type = INTEGER;
      token.m_int[0] = result;

      m_stack.push_back(token);

    }
    else
      throw std::runtime_error("ERROR lessi: wrong operand-type");
  };

};

#endif /*LESSIOPERATOR_H_*/

