//----------------------------------------------------------------------
/// \author Markus Krallinger 0630748, Group: 20
/// \brief Pops an function token off the stack an executes it.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef APPLYOPERATOR_H_
#define APPLYOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

#include <iostream>

class ApplyOperator : public GMLOperator
{
public:

  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter
  /// \param array_  array of GML-Token arrays 
  /// \param g_interpreter
  
  ApplyOperator(std::vector<GMLToken> &stack,
      std::vector<std::vector<GMLToken> > &array_,
      GMLInterpreter &g_interpreter_) :
    GMLOperator(stack), m_array(array_),
    gml_interpreter_(g_interpreter_)
  {
    m_name = "apply";
  };

  //------------------------------------------------------------------

  ~ApplyOperator()
  {
  };

  //------------------------------------------------------------------
  /// \brief execution of the token
  
  void execute() const
  {

    if (m_stack.empty())
      throw std::runtime_error("ERROR apply: stack is empty");

    GMLToken functionToken = m_stack.back();
    m_stack.pop_back();

    if(functionToken.m_type != FUNCTION){
      std::cout << functionToken.m_type << std::endl;
      throw std::runtime_error("ERROR apply: no valid function");
    }
    std::vector<GMLToken> &array = m_array[functionToken.m_int[0]];

    std::vector<GMLToken>::reverse_iterator it = array.rbegin();

    for (; it < array.rend(); it++)
    {
      gml_interpreter_.execute( (*it));
    }
  };
  
  //------------------------------------------------------------------
  
private:

  std::vector<std::vector<GMLToken> > &m_array;
  GMLInterpreter &gml_interpreter_;
};

#endif  // APPLYOPERATOR

