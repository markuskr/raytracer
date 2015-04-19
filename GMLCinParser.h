//----------------------------------------------------------------------
/// \author Markus Krallinger 0630748, Group: 20
/// \brief Reads an input from stdin an creates the corresponding tokens
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef GMLCINPARSER_H_
#define GMLCINPARSER_H_

#include <string>
#include <iostream>
#include <fstream>

#include "GMLToken.h"
#include "GMLParser.h"

class GMLCinParser : public GMLParser 
{
typedef std::set<std::string>::iterator it;

public:
	GMLCinParser(std::istream &input);
	GMLToken parse();
	~GMLCinParser(){};
	
private:
	std::string  gml_program;
    std::istream &stream;
};


#endif /*GMLCINPARSER_H_*/
