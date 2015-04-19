//----------------------------------------------------------------------
/// Filename: FloorOperator.h
/// Group:    20
/// \brief The operator for the floor function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef FLOOROPERATOR_H_
#define FLOOROPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <vector>
#include <string>

#include <stdexcept>

class FloorOperator : public GMLOperator
{
public:
  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter

  FloorOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)
  {
    m_name = "floor";
  };

  //-------------------------------------------------------------------

  ~FloorOperator()
  {};

  //-------------------------------------------------------------------
  /// \brief execution of the token

  void execute() const
  {
    GMLToken operand1;

    if (m_stack.empty())
      throw std::runtime_error("ERROR floor: Stack is empty");

    operand1 = m_stack.back();
    m_stack.pop_back();

    signed int result = static_cast<int>(floor(operand1.m_float[0]));
    GMLToken token;
    token.m_type = INTEGER;
    token.m_int[0] = result;

    m_stack.push_back(token);
  };
};

#endif /*FLOOROPERATOR_H_*/


