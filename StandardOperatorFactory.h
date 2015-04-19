//----------------------------------------------------------------------
/// Filename: StandardOperatorFactory.h
/// Group:    20
/// \brief : factory for producing the standard operators
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef STANDARD_OPERATOR_FACTORY_
#define STANDARD_OPERATOR_FACTORY_

#include "GMLOperatorFactory.h"
#include <string>

class StandardOperatorFactory : public GMLOperatorFactory
{
public:
	int createOperator(const std::string &);

	StandardOperatorFactory(GMLInterpreter &interpreter);
	
  ~StandardOperatorFactory(){};
	
private:
	void init();
};

#endif

