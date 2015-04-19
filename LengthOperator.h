//----------------------------------------------------------------------
/// \author Group:    20
/// \brief The operator for the length function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef LENGTHOPERATOR_H_
#define LENGTHOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <vector>
#include <string>
#include <memory>
#include <iostream>

class LengthOperator : public GMLOperator
{
public:

  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter
  ///  \param array_ function stack of the interpreter
  ///  \param g_interpreter_ interpreter object

  LengthOperator(std::vector<GMLToken> &stack,
    std::vector<std::vector<GMLToken> > &array_,
    GMLInterpreter &g_interpreter_) :
    GMLOperator(stack), m_array(array_)
  {
    m_name = "length";
  };

  //------------------------------------------------------------------

  ~LengthOperator()
  {};

  //------------------------------------------------------------------
  /// \brief execution of the token

  void execute() const
  {
    if (m_stack.empty())
      throw std::runtime_error("ERROR length: stack is empty");

    GMLToken functionToken = m_stack.back();
    m_stack.pop_back();

    if (functionToken.m_type != ARRAY)
      throw std::runtime_error("ERROR length: no valid Array");

    GMLToken token;
    token.m_type = INTEGER;
    token.m_int[0] = m_array[functionToken.m_int[0]].size();
    
    std::cout << token.m_int[0] << std::endl;
    
    m_stack.push_back(token);
    
  };

  //------------------------------------------------------------------

private:
  std::vector<std::vector<GMLToken> > &m_array;
};

#endif  // LENGTHOPERATOR
