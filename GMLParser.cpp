#include "GMLParser.h"

#include "TokenTypes.h"
#include <sstream>
#include <boost/lexical_cast.hpp>

using boost:: lexical_cast; 
using boost::bad_lexical_cast;
//----------------------------------------------------------------------
std::vector<GMLToken> &GMLParser::getProgram()
{
  return m_program;
}

//----------------------------------------------------------------------
void GMLParser::addKeyword(const std::string& keyword)
{
  m_valid_keywords.insert(keyword);
}
//----------------------------------------------------------------------
int GMLParser::getCommandType(const std::string &gml_command)
{
  int operator_id = 0;
  for (factory_iterator it = m_factories.begin(); it
      < m_factories.end(); it++)
  {
    if ((operator_id = (*it)->createOperator(gml_command)) > 0)
      return operator_id;
  }
  return -1;

}

//----------------------------------------------------------------------
bool GMLParser::is_number(const std::string& s)
{
  return !s.empty() && std::find_if(s.begin(),
                                    s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

//----------------------------------------------------------------------
GMLToken GMLParser::getTokenFromString(const std::string &command)
{

  std::stringstream numeric_values(command);

  if (command.find("\"") != std::string::npos)
  {
    std::string help;
    numeric_values >> help;
    std::string* filename = new std::string(help.substr(1, help.length() - 2 ));
    GMLToken token;
    token.m_type = FILENAME;
    token.m_int[0] = reinterpret_cast<uintptr_t>(filename); //TODO very dirty
    return token;
  }

  if (command.find(".") != std::string::npos)
  {
      try
      {
          float float_value = lexical_cast<float>(command);
          GMLToken token;
          token.m_type = FLOAT;
          token.m_float[0] = float_value;
          return token;
      }
      catch(const bad_lexical_cast &)
      {}
  }
  if (is_number(command))
  {
    try
    {
      int int_value = lexical_cast<int>(command);
      GMLToken token;
      token.m_type = INTEGER;
      token.m_int[0] = int_value;
      return token;
    }
    catch(const bad_lexical_cast &)
    {}
  }
  //NameDefinition
  if (command[0] == '/')
  {
    std::string name = command.substr(1, command.size() - 1);
    m_ivs_to_name.push_back(name);
    m_name_to_ivs[name] = m_ivs_to_name.size();
    GMLToken token;
    token.m_type = NAMEDEFINITION;
    token.m_int[0] = m_ivs_to_name.size();
    return token;
  }

  //Name
  if (m_name_to_ivs.count(command) > 0)
  {
    GMLToken token;
    token.m_type = NAME;
    token.m_int[0] = m_name_to_ivs[command];
    return token;
  }

  //Marker
  if (command[0] == '[')
  {
    GMLToken token;
    token.m_type = MARKER;
    return token;
  }
  if (command[0] == '{')
  {
    GMLToken token;
    token.m_type = FMARKER;
    return token;
  }

  int operator_type = 0;

  //Operation
  if ((operator_type = getCommandType(command)) > 0)
  {

    GMLToken token;
    token.m_type = OPERATION;
    token.m_int[0] = operator_type;
    return token;
  }
  GMLToken empty;
  return empty;
}

