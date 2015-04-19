//----------------------------------------------------------------------
/// \author Markus Krallinger 0630748, Group: 20
/// \brief Reads an input from stdin an creates the corresponding tokens
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#include "GMLCinParser.h"

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <math.h>
#include <exception>
#include <stdexcept>
#include "TokenTypes.h"
#include <iostream>

using std::string;
using std::getline;

//----------------------------------------------------------------------

GMLCinParser::GMLCinParser(std::istream &input) : stream(input)
{}

//----------------------------------------------------------------------
//   /// \parse the input and returns a token

GMLToken GMLCinParser::parse()
{
    
    for (string line; std::getline(stream, line); ) {
        
        size_t pos = line.find("%");
        
        if(pos != string::npos)
            line = line.substr(0, pos);
        
        std::stringstream program(line);
        string single_token;
        
        while (program >> single_token)
        {            
            m_program.push_back(getTokenFromString(single_token));
        }
        
        
    }
 
 
  GMLToken token;
  token.m_type = FUNCTION;
  token.m_int[0] = 0;
    
  return token;
}

