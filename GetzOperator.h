//----------------------------------------------------------------------
/// \autor Group:    20
/// \brief The operator for the getz function
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef GETZOPERATOR_H_
#define GETZOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <vector>
#include <string>
#include <memory>

#include <stdexcept>

class GetzOperator  : public GMLOperator 
{
public:
  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter

  GetzOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)		
  {
    m_name = "getz";
  };

  //-------------------------------------------------------------------

  ~GetzOperator()
  {};

  //------------------------------------------------------------------
  /// \brief execution of the token

  void execute() const
  {
    if(m_stack.empty())
      throw std::runtime_error("ERROR getz: stack is empty");
      
    GMLToken pointToken = m_stack.back();
    m_stack.pop_back();
    if(pointToken.m_type != POINT)
      throw std::runtime_error( "ERROR getz: no name specified");
    GMLToken token;
    token.m_float[0] = pointToken.m_float[2];
    token.m_type = FLOAT;
         
    m_stack.push_back(token);	    	
  };
    	
};

#endif /*GETZOPERATOR_H_*/


