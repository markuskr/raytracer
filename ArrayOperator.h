//----------------------------------------------------------------------
/// \author Markus Krallinger 0630748, Group: 20
/// \brief Pops an function token off the stack an executes it.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef ARRAYOPERATOR_H_
#define ARRAYOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"
#include "GMLInterpreter.h"

#include <exception>
#include <vector>
#include <string>
#include <memory>

#include <iostream>

class GMLInterpreter;

class ArrayOperator : public GMLOperator
{
public:

  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter
  /// \param array_  array of GML-Token arrays 

  ArrayOperator(std::vector<GMLToken> &stack,
      std::vector<std::vector<GMLToken> > &array_) :
    GMLOperator(stack), m_array(array_)
  {
    m_name = "]";
  };

  //------------------------------------------------------------------
  
  ~ArrayOperator()
  {};
  
  //------------------------------------------------------------------
  /// \brief execution of the token

  void execute() const
  {
    std::vector <GMLToken> array_;
    while (m_stack.back().m_type != MARKER)
    {
      GMLToken token = m_stack.back();
      array_.push_back(token);
      m_stack.pop_back();
    }
    m_stack.pop_back();
    m_array.push_back(array_);

    GMLToken token;
    token.m_type = ARRAY;
    token.m_int[0]= m_array.size() - 1;

    m_stack.push_back(token);
  };

  //------------------------------------------------------------------

  private:
  
  std::vector<std::vector<GMLToken> > &m_array;
  
};

#endif 

