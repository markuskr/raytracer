//----------------------------------------------------------------------
/// \author Markus Krallinger 0630748, Group: 20
/// \brief Parses a string into GML Tokens
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef STRINGPARSER_H_
#define STRINGPARSER_H_

#include <string>
#include "GMLToken.h"
#include "GMLParser.h"

class GMLStringParser : public GMLParser 
{
typedef std::set<std::string>::iterator it;

public:
//----------------------------------------------------------------------
/// \param program_to_parse input string to be parsed

GMLStringParser(const std::string &);

//-------------------------------------------------------------------
/// \brief parse and tokenize the input
/// \param stack execution stack of the interpreter

GMLToken parse();

//-------------------------------------------------------------------

~GMLStringParser()
{};

//-------------------------------------------------------------------
	
private:
  std::string gml_program;
};

#endif /*STRINGPARSER_H_*/

