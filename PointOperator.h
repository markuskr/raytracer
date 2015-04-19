//----------------------------------------------------------------------
/// Filename: PointOperator.h
/// Group:    20
/// \brief : point operator
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef POINTOPERATOR_H_
#define POINTOPERATOR_H_

#include "GMLOperator.h"
#include "GMLToken.h"
#include "TokenTypes.h"

#include <vector>
#include <string>
#include <memory>

#include <iostream>

class PointOperator  : public GMLOperator 
{
public:
  PointOperator(std::vector<GMLToken> &stack) 
		:
    GMLOperator(stack)    
  {
    m_name = "point";
  };

  ~PointOperator(){};

//----------------------------------------------------------------------
  void execute() const
  {
    if(m_stack.size() < 3 )
      throw std::runtime_error("ERROR point: too few arguments");

    GMLToken token;
    for (int i = 0; i < 3; i++)
    {
      GMLToken tempToken = m_stack.back();               
      if (tempToken.m_type != FLOAT)
        throw std::runtime_error("ERROR point: wrong argument type");
      token.m_float[2-i] = tempToken.m_float[0];
      m_stack.pop_back();
	  }
    token.m_type   = POINT;
    m_stack.push_back(token);        
  };
};


#endif /*POINTOPERATOR_H_*/

