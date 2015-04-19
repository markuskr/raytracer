//----------------------------------------------------------------------
/// \author Markus Krallinger 0630748, Group: 20
/// \brief GMLParser
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef GMLPARSER_
#define GMLPARSER_

#include "GMLToken.h"
#include "GMLOperatorFactory.h"
#include <vector>
#include <string>
#include <map>
#include <set>

class GMLOperatorFactory;

class GMLParser
{

public:
  GMLParser()    
  {};

  virtual GMLToken parse() = 0;
  std::vector<GMLToken> &getProgram();

  void addKeyword(const std::string &);

  void addFactory(GMLOperatorFactory *factory)
  {
    m_factories.push_back(factory);
  };

  virtual ~GMLParser()
  {};
  
protected:
  std::vector<std::string>   m_ivs_to_name;
  std::map<std::string, int> m_name_to_ivs;
  std::vector<GMLToken>      m_program;
  std::set<std::string>      m_valid_keywords;

  std::vector<GMLOperatorFactory*> m_factories;

  int getCommandType(const std::string &gml_command);
  typedef std::vector<GMLOperatorFactory*>::iterator factory_iterator;

  GMLToken getTokenFromString(const std::string &command);

private:
  GMLParser(const GMLParser &);
  GMLParser &operator =(GMLParser const &);
  
  bool is_number(const std::string& s);
};

#endif /*GMLPARSER_*/

