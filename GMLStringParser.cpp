//----------------------------------------------------------------------
/// \autor Group:    20
/// \brief tokenize an GMLString 
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#include "GMLStringParser.h"

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <math.h>
#include <exception>
#include <stdexcept>
#include "TokenTypes.h"

using std::string;

GMLStringParser::GMLStringParser (const string& program_to_parse)
{
  gml_program = program_to_parse;
}
  
GMLToken GMLStringParser::parse()
{	
  string single_token;
  std::stringstream program(gml_program);   

  while (getline(program, single_token, ' '))
  {   
    string::iterator it = single_token.begin();
    for (; it < single_token.end(); it ++)
    {
      if ( (*it) == ' ') 
        single_token.erase(it);
    }

    if (single_token.length() > 0)
      m_program.push_back(getTokenFromString(single_token));
  }  
  GMLToken token;
    
  token.m_type = FUNCTION;
  token.m_int[0] = 0;
    
  return token;
}

