//----------------------------------------------------------------------
/// \autor Group:    20
/// \brief The operator for the function closure "}"
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef FUNCTIONOPERATOR_H_
#define FUNCTIONOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <vector>
#include <string>
#include <memory>
#include <iostream>


class FunctionOperator  : public GMLOperator 
{
public:
  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter
  ///  \param array_ function stack of the interpreter

  FunctionOperator(std::vector<GMLToken> &stack, 
    std::vector<std::vector<GMLToken> > &array_) :
    GMLOperator(stack), m_array(array_)
    {
      m_name = "}";
    };
	
  //------------------------------------------------------------------
	
  ~FunctionOperator()
  {};
	
  //------------------------------------------------------------------
  /// \brief execution of the token

  void execute() const
  {
    std::vector <GMLToken> array_;
 
    while( m_stack.back().m_type != FMARKER )
    {
      GMLToken token = m_stack.back();
      array_.push_back(token);
      m_stack.pop_back();
    } 		
	
    m_stack.pop_back();
    m_array.push_back(array_);
			
    GMLToken token;
    token.m_type  = FUNCTION;
    token.m_int[0]= m_array.size() - 1;			
			
    m_stack.push_back(token);
			
  };

//------------------------------------------------------------------

private:
  std::vector<std::vector<GMLToken> > &m_array;

};

#endif  // FUNCTIONOPERATOR

