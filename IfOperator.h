//----------------------------------------------------------------------
/// \author Group:    20
/// \brief The operator for the addf function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef IFOPERATOR_H_
#define IFOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

class IfOperator : public GMLOperator
{
public:
  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter
  ///  \param array_ function stack of the interpreter
  ///  \param g_interpreter_ interpreter object

  IfOperator(std::vector<GMLToken> &stack,
    std::vector<std::vector<GMLToken> > &array_,
    GMLInterpreter &g_interpreter_) :
    GMLOperator(stack), m_array(array_),
    gml_interpreter_(g_interpreter_)
  {
    m_name = "if";
  }
  ;

  //------------------------------------------------------------------

  ~IfOperator()
  {};

  //------------------------------------------------------------------
  /// \brief execution of the token

  void execute() const
  {
    if (m_stack.size() < 3)
      throw std::runtime_error("ERROR if: Too few arguments on the stack");

    GMLToken operand1 = m_stack.back();
    m_stack.pop_back();
    GMLToken operand2 = m_stack.back();
    m_stack.pop_back();
    GMLToken operand3 = m_stack.back();
    m_stack.pop_back();

    if (operand1.m_type != FUNCTION)
      throw std::runtime_error( "ERROR if: no valid function");
    if (operand2.m_type != FUNCTION)
      throw std::runtime_error( "ERROR if: no valid function");
    if (operand3.m_type != INTEGER || !(operand3.m_int[0] == 1
        || operand3.m_int[0] == 0))
      throw std::runtime_error( "ERROR if: no valid TRUE or False");

    if (operand3.m_int[0] == 1)
    {
      std::vector<GMLToken> &array = m_array[operand2.m_int[0]];

      for (unsigned int i = (array.size()); i > 0; i--)
      {
        gml_interpreter_.execute(array[i-1]);
      }
    }
    else
    {
      std::vector<GMLToken> &array = m_array[operand1.m_int[0]];

      for (unsigned int i = (array.size()); i > 0; i--)
      {
        gml_interpreter_.execute(array[i-1]);
      }
    }
  };

  //------------------------------------------------------------------

private:
  std::vector<std::vector<GMLToken> > &m_array;
  GMLInterpreter &gml_interpreter_;
};

#endif  // IFOPERATOR_H_

