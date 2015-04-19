//----------------------------------------------------------------------
/// \autor Group:    20
/// \brief The operator for the getx function
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef GETXOPERATOR_H_
#define GETXOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <vector>
#include <string>
#include <memory>

#include <stdexcept>

class GetxOperator : public GMLOperator
{
public:
  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter

  GetxOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)
  {
    m_name = "getx";
  };

  //------------------------------------------------------------------

  ~GetxOperator()
  {};

  //------------------------------------------------------------------
  /// \brief execution of the token

  void execute() const
  {
    if (m_stack.empty())
      throw std::runtime_error("ERROR getx: stack is empty");
    GMLToken pointToken = m_stack.back();
    m_stack.pop_back();
    if (pointToken.m_type != POINT)
      throw std::runtime_error("ERROR getx: no name specified");
    GMLToken token;
    token.m_float[0] = pointToken.m_float[0];
    token.m_type = FLOAT;

    m_stack.push_back(token);
  };

};

#endif /*GETXOPERATOR_H_*/



