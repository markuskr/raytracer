//----------------------------------------------------------------------
/// Filename: WhileOperator.h
/// Group:    20
/// \brief :while operator
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef WHILEOPERATOR_H_
#define WHILEOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <exception>
#include <vector>
#include <string>
#include <memory>

#include <iostream>


class WhileOperator : public GMLOperator
{
public:
  WhileOperator(std::vector<GMLToken> &stack,
    std::vector<std::vector<GMLToken> > &array_,
    std::map <int, GMLOperator*> &interpreter_, 
    GMLInterpreter &g_interpreter_) : 
	  GMLOperator(stack), m_array(array_),
    gml_interpreter_(g_interpreter_)
  {
    m_name = "while";
  };

//------------------------------------------------------------------

  ~WhileOperator()
  {
  };

//------------------------------------------------------------------
  void execute() const
  {
    if (m_stack.empty())
	    throw std::runtime_error("ERROR while: stack is empty");

    GMLToken function_token = m_stack.back();
    m_stack.pop_back();

    if (function_token.m_type != FUNCTION)
	    throw std::runtime_error("ERROR while: no valid function");

    std::vector<GMLToken> f_array = m_array[function_token.m_int[0]];

    while (m_stack.back().m_int[0] != 0)
    {
	    std::vector<GMLToken>::reverse_iterator it = f_array.rbegin();

	    for (; it < f_array.rend(); it ++)
	    {
		    gml_interpreter_.execute( (*it));
	    }
     	m_stack.pop_back();
   }
 };
//------------------------------------------------------------------
private:
  std::vector<std::vector<GMLToken> > &m_array;
  GMLInterpreter &gml_interpreter_;
};

#endif /*WHILEOPERATOR_H_*/

