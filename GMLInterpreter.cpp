//----------------------------------------------------------------------
/// \author Markus Krallinger 0630748, Group: 20
/// \brief registers commands and executes an GML- Program
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#include "GMLInterpreter.h"
#include "TokenTypes.h"

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

//----------------------------------------------------------------------
int GMLInterpreter::registerOperator(GMLOperator *gml_operator)
{
  m_opterator_id ++;	
  m_operators[m_opterator_id] = gml_operator;		
  return m_opterator_id;
}

//----------------------------------------------------------------------
bool GMLInterpreter::interpretGML( GMLToken start, std::vector<GMLToken> program)
{  
  for( token_iterator it = program.begin() + start.m_int[0]; it < program.end(); it ++)
    execute( *(it) );		    
  return false;
}

//----------------------------------------------------------------------
bool GMLInterpreter::executeOnStack(const GMLToken & token, std::vector<GMLToken> & stack)
{
  switch (token.m_type)
  {
    case FLOAT:
      stack.push_back(token);
      break;
    case INTEGER:
      stack.push_back(token);
      break;
    case MARKER:
      stack.push_back(token);
      break;
    case FMARKER:
      stack.push_back(token);
      m_deferred_count++;
      m_deferred_mode = true;
      break;
    case POINT:
      m_stack.push_back(token);
      break;
    case OPERATION:
      if ((m_operators[token.m_int[0]]->getName()).compare("}") == 0 )
      {
        m_operators[token.m_int[0]]->execute();
        m_deferred_count--;
        if(m_deferred_count == 0)
          m_deferred_mode = false;
      }
      else if(!m_deferred_mode)
        m_operators[token.m_int[0]]->execute();
      else
      {
        stack.push_back(token);
      }
      break;
    case NAMEDEFINITION:
      if(!m_deferred_mode)
      {
        m_environment[token.m_int[0]] = m_stack.back();
        stack.pop_back();
      }
      else
        stack.push_back(token);
      break;
    case NAME:
      if(!m_deferred_mode)
      {
        long index = token.m_int[0];
        GMLToken &env_token =  m_environment[index];
        stack.push_back(env_token);
      }
      else
        stack.push_back(token);
      break;
    case FUNCTION:
      stack.push_back(token);
      break;
    case FILENAME:
      stack.push_back(token);
      break;
    default:
      return false;
  }
  return true;
}

//----------------------------------------------------------------------
bool GMLInterpreter::execute(const GMLToken &token)
{
  return executeOnStack(token, m_stack);
}

