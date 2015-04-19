//----------------------------------------------------------------------
/// \author Markus Krallinger 0630748, Group: 20
/// \brief registers commands and executes an GML- Program
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------


#ifndef GMLINTERPRETER_
#define GMLINTERPRETER_

#include <map>
#include <vector>
#include <memory>

#include "GMLToken.h"
#include "GMLParser.h"

class GMLParser;

class GMLInterpreter
{

public:
  //--------------------------------------------------------------------
  /// \param GMLToken the token to execute
  /// \return true if executing was successful 

  bool execute(const GMLToken &);
  bool executeOnStack(const GMLToken &, std::vector<GMLToken> & stack);

  //--------------------------------------------------------------------
  /// \param GMLOperator operator to register
  /// \return index of the function token

  int registerOperator(GMLOperator*);

  //--------------------------------------------------------------------
  /// \param start start of the program
  /// \return program program to be executed
  /// \return true if execution was successful

  bool interpretGML(GMLToken start, std::vector<GMLToken> program);

  GMLInterpreter() :
    m_opterator_id(0), m_deferred_mode(0), m_deferred_count(0)
  {};

  ~GMLInterpreter()
  {
    std::map<int, GMLOperator*>::iterator it = m_operators.begin();
    
    for (; it != m_operators.end(); it++)
      delete (*it).second;
  };
  
  /// \brief the execution stack of the program
  std::vector <GMLToken>               m_stack;
  /// \brief the arrays in the program
  std::vector <std::vector<GMLToken> > m_arrays;
  /// \brief mapping operator -> index
  std::map <int, GMLOperator*>         m_operators;

private:

  std::map <int, GMLToken> m_environment;

  int m_opterator_id;
  bool m_deferred_mode;
  int m_deferred_count;

  typedef std::vector <GMLToken>::iterator token_iterator;

};

#endif /*GMLINTERPRETER_*/
