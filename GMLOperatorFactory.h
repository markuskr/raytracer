//----------------------------------------------------------------------
/// \author Markus Krallinger 0630748, Group: 20
/// \brief Interface for the Operator- factories
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef GMLOPERATORFACTORY_
#define GMLOPERATORFACTORY_

#include <memory>
#include <vector>
#include <string>
#include <map>

#include "GMLOperator.h"
#include "GMLInterpreter.h"


class GMLInterpreter;

class GMLOperatorFactory
{
public:
  virtual int createOperator(const std::string &) = 0;
  virtual ~GMLOperatorFactory(){};
  GMLOperatorFactory(GMLInterpreter &interpreter) : 
    m_interpreter(interpreter)
  {};
	
protected:
  GMLInterpreter	&m_interpreter;
  std::vector  <GMLOperator*> m_operators;
};


#endif /*GMLOPERATORFACTORY_*/

