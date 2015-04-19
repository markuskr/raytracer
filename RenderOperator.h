//----------------------------------------------------------------------
/// Filename: RenderOperator.h
/// Group:    20
/// \brief : render operator
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------
#ifndef RENDEROPERATOR_H_
#define RENDEROPERATOR_H_

#include "Raytracer.h"
#include "GMLToken.h"
#include "GMLInterpreter.h"
#include "Primitive.h"
#include "SceneDescription.h"
#include "Vec3.h"
#include "Image.h"

#include "CalculateColorStrategy.h"
#include "RayShootingStrategy.h"

class RenderOperator : public GMLOperator
{
  public:
  RenderOperator(GMLInterpreter &interpreter, SceneDescription &scene, 
    CalculateColorStrategy &color, RayShootingStrategy &shooting) :
    GMLOperator(interpreter.m_stack), m_scene(scene), m_interpreter(interpreter),
      m_color(color), m_shooting(shooting)
  {
    m_name = "render";
  };
  
  ~RenderOperator(){};

//----------------------------------------------------------------------
  void execute() const
  {
   
     GMLToken name    = m_stack.back(); m_stack.pop_back(); //empty    
     GMLToken height  = m_stack.back(); m_stack.pop_back();
     GMLToken width   = m_stack.back(); m_stack.pop_back();
     GMLToken fov     = m_stack.back(); m_stack.pop_back();
     GMLToken depth   = m_stack.back(); m_stack.pop_back();
     GMLToken object  = m_stack.back(); m_stack.pop_back();
     GMLToken lights  = m_stack.back(); m_stack.pop_back(); //Array
     GMLToken ambient = m_stack.back(); m_stack.pop_back();
    

     Vec3 camera;
     camera[0] = 0; camera[1] = 0; camera[2] = -1;
     std::string filename;
      
     if (name.m_type == FILENAME)
     {
       filename = *(string*) name.m_int[0]; //TODO; really dirty         
       delete (string*) name.m_int[0];        
     }
     std::vector<Light *> array_lights;
     std::vector<GMLToken>::iterator it = m_interpreter.m_arrays[lights.m_int[0]].begin();

     for (; it < m_interpreter.m_arrays[lights.m_int[0]].end(); it++)
     {
       array_lights.push_back(m_scene.getLight( (*it).m_int[0] ));
     }

     Primitive *prim_scene   = m_scene.getPrimitive(object.m_int [0]);
     Vec3 vec_ambient(ambient.m_float[0], ambient.m_float[1],ambient.m_float[2]);    
     m_color.setValues(vec_ambient, array_lights, prim_scene);
     Raytracer raytracer(m_shooting); 
     Image image( width.m_int[0], height.m_int[0]);
     raytracer.createImage(depth.m_int[0], fov.m_int[0], camera, image, filename);
  };

private:
  SceneDescription &m_scene;
  GMLInterpreter   &m_interpreter;
  
  CalculateColorStrategy &m_color;
  RayShootingStrategy    &m_shooting;

};

#endif

