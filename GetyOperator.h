//----------------------------------------------------------------------
/// \autor Group:    20
/// \brief The operator for the gety function
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef GETYOPERATOR_H_
#define GETYOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <vector>
#include <string>
#include <memory>

#include <stdexcept>

class GetyOperator  : public GMLOperator 
{
public:
  //------------------------------------------------------------------
  /// \brief execution of the token

  GetyOperator(std::vector<GMLToken> &stack) :
    GMLOperator(stack)		
  {
    m_name = "gety";
  };

  //-------------------------------------------------------------------

  ~GetyOperator()
  {};

  //-------------------------------------------------------------------
  /// \brief execution of the token

  void execute() const
  {
    if(m_stack.empty())
      throw std::runtime_error("ERROR gety: stack is empty");
    
    GMLToken pointToken = m_stack.back();
    m_stack.pop_back();
    
    if(pointToken.m_type != POINT)
     throw std::runtime_error("ERROR gety: no name specified");
    
    GMLToken token;
    token.m_float[0] = pointToken.m_float[1];
    token.m_type = FLOAT;
    m_stack.push_back(token);	    	
  };
   	
};

#endif /*GETYOPERATOR_H_*/



