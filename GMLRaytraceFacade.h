//----------------------------------------------------------------------
/// Filename: GMLRaytraceFacade.h
/// Author:   Markus Krallinger 0630748
/// Group:    20
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef GMLRAYTRACEFACADE_H_
#define GMLRAYTRACEFACADE_H_

#include "GMLInterpreter.h"
#include "StandardOperatorFactory.h"
#include "RaytraceOperatorFactory.h"
#include "GMLCinParser.h"
#include "SceneDescription.h"
#include "GMLToken.h"

#include "LineShooting.h"
#include "RaycastingStrategy.h"

#include <memory>
#include <vector>
#include <iostream>
#include <fstream>



class GMLRaytraceFacade
{
public:
  GMLRaytraceFacade(std::string filename) : shooting(color)
  {
    operators .reset( new StandardOperatorFactory( interpreter ));
    raytracing.reset( new RaytraceOperatorFactory( interpreter, scene, color, shooting )); 

    
    input.open(filename, std::fstream::in);

    if (!input.good())
    {
      std::cout << "Problem reading file: " << filename << std::endl;
      exit(-1);
    }
    
    parser.reset(new GMLCinParser(input));

  };
  
  void run()
  {
    try
    {
      parser->addFactory( operators .get() );  
      parser->addFactory( raytracing.get() );  
      
      GMLToken start                = parser->parse();
      std::vector<GMLToken> program = parser->getProgram();
      interpreter.interpretGML(start, program);
    }
    catch (std::exception &e)
    {
      std::cout <<  e.what() << std::endl;
    }     
  }
  
private:
  GMLInterpreter          interpreter;
  std::auto_ptr <StandardOperatorFactory> operators;
  std::auto_ptr <RaytraceOperatorFactory> raytracing;  
  std::auto_ptr <GMLParser>               parser;
  SceneDescription        scene;
  RaycastingStrategy      color;
  LineShooting            shooting;
  std::ifstream           input;
};

#endif /*GMLRAYTRACEFACADE_H_*/
