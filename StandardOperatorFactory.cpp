//----------------------------------------------------------------------
/// Filename: StandardOperatorFactory.cpp
/// Group:    20
/// \brief : factory for producing the standard operators
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#include "StandardOperatorFactory.h"
#include "AddiOperator.h"
#include "AddfOperator.h"
#include "SubiOperator.h"
#include "SubfOperator.h"
#include "SqrtOperator.h"
#include "MuliOperator.h"
#include "MulfOperator.h"
#include "DiviOperator.h"
#include "DivfOperator.h"
#include "ArrayOperator.h"
#include "NegiOperator.h"
#include "NegfOperator.h"
#include "LessiOperator.h"
#include "LessfOperator.h"
#include "AcosOperator.h"
#include "ModiOperator.h"
#include "EqiOperator.h"
#include "EqfOperator.h"
#include "AsinOperator.h"
#include "ClampfOperator.h"
#include "SinOperator.h"
#include "CosOperator.h"
#include "FloorOperator.h"
#include "FracOperator.h"
#include "RealOperator.h"
#include "ArrayOperator.h"
#include "FunctionOperator.h"
#include "DupOperator.h"
#include "WhileOperator.h"
#include "PointOperator.h"
#include "GetxOperator.h"
#include "GetyOperator.h"
#include "GetzOperator.h"
#include "ApplyOperator.h"
#include "LengthOperator.h"
#include "GetOperator.h"
#include "IfOperator.h"

using std::string;



//----------------------------------------------------------------------
StandardOperatorFactory::StandardOperatorFactory(GMLInterpreter &interpreter) 
: GMLOperatorFactory(interpreter)
{
}

//----------------------------------------------------------------------
int StandardOperatorFactory::createOperator(const string &gml_operator)
{
  if (gml_operator.compare("acos") == 0)
  {
    return m_interpreter.registerOperator(new AcosOperator(m_interpreter.m_stack) );
  }
  else if (gml_operator.compare("addf") == 0)
  {
    return m_interpreter.registerOperator(new AddfOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("addi") == 0)
  {
    return m_interpreter.registerOperator(new AddiOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("dup") == 0) 
  {
    return m_interpreter.registerOperator(new DupOperator(m_interpreter.m_stack) );
  }
  else if (gml_operator.compare("asin") == 0)
  {
    return m_interpreter.registerOperator(new AsinOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("clampf") == 0)
  {
    return m_interpreter.registerOperator(new ClampfOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("cos") == 0)
  {
    return m_interpreter.registerOperator(new CosOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("divf") == 0)
  {
    return m_interpreter.registerOperator(new DivfOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("divi") == 0)
  {
    return m_interpreter.registerOperator(new DiviOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("eqf") == 0)
  {
    return m_interpreter.registerOperator(new EqfOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("eqi") == 0)
  {
    return m_interpreter.registerOperator(new EqiOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("floor") == 0)
  {
    return m_interpreter.registerOperator(new FloorOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("frac") == 0)
  {
    return m_interpreter.registerOperator(new FracOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("lessf") == 0)
  {
    return m_interpreter.registerOperator(new LessfOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("lessi") == 0) 
  {
  return m_interpreter.registerOperator(new LessiOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("modi") == 0) 
  {
    return m_interpreter.registerOperator(new ModiOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("mulf") == 0)
  {
    return m_interpreter.registerOperator(new MulfOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("muli") == 0)
  {
    return m_interpreter.registerOperator(new MuliOperator(m_interpreter.m_stack));
  }
    else if (gml_operator.compare("negf") == 0)
  {
    return m_interpreter.registerOperator(new NegfOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("negi") == 0)
  {
    return m_interpreter.registerOperator(new NegiOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("real") == 0) 
  {
    return m_interpreter.registerOperator(new RealOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("sin") == 0)
  {
    return m_interpreter.registerOperator(new SinOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("sqrt") == 0)
  {
    return m_interpreter.registerOperator(new SqrtOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("subf") == 0)
  {
    return m_interpreter.registerOperator(new SubfOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("subi") == 0)
  {
    return m_interpreter.registerOperator(new SubiOperator(m_interpreter.m_stack));
  }
  else if (gml_operator.compare("]") == 0)
  {
    return m_interpreter.registerOperator(new ArrayOperator(m_interpreter.m_stack, m_interpreter.m_arrays) );
  }
  else if (gml_operator.compare("}") == 0) 
  {
    return m_interpreter.registerOperator(new FunctionOperator(m_interpreter.m_stack, m_interpreter.m_arrays) );
  }
  else if (gml_operator.compare("while") == 0)
  {
    return m_interpreter.registerOperator(new WhileOperator(m_interpreter.m_stack, m_interpreter.m_arrays, m_interpreter.m_operators, m_interpreter) );
  }
  else if (gml_operator.compare("point") == 0)
  {
    return m_interpreter.registerOperator(new PointOperator(m_interpreter.m_stack ));
  }
  else if (gml_operator.compare("getx") == 0)
  {
    return m_interpreter.registerOperator(new GetxOperator(m_interpreter.m_stack ));
  }
  else if (gml_operator.compare("gety") == 0) 
  {
    return m_interpreter.registerOperator(new GetyOperator(m_interpreter.m_stack ));
  }
  else if (gml_operator.compare("getz") == 0) 
  {
    return m_interpreter.registerOperator(new GetzOperator(m_interpreter.m_stack ));
  }
  else if (gml_operator.compare("apply") == 0)
  {
    return m_interpreter.registerOperator(new ApplyOperator(m_interpreter.m_stack, m_interpreter.m_arrays, m_interpreter) );
  }
  else if (gml_operator.compare("length") == 0)
  {
    return m_interpreter.registerOperator(new LengthOperator(m_interpreter.m_stack, m_interpreter.m_arrays, m_interpreter) );
  }
  else if (gml_operator.compare("get") == 0)
  {
    return m_interpreter.registerOperator(new GetOperator(m_interpreter.m_stack, m_interpreter.m_arrays) );
  }
  else if (gml_operator.compare("if") == 0)
  {
    return m_interpreter.registerOperator(new IfOperator(m_interpreter.m_stack, m_interpreter.m_arrays, m_interpreter) );
  }
  return -1;

}
//----------------------------------------------------------------------
void StandardOperatorFactory::init()
{

}

