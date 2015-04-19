//----------------------------------------------------------------------
/// \author Group:    20
/// \brief The operator for the lessi function.
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef LIGHTOPERATOR_H_
#define LIGHTOPERATOR_H_

#include "GMLToken.h"
#include "GMLOperator.h"
#include "SceneDescription.h"
#include "Vec3.h"
#include "DirectionalLight.h"
#include "TokenTypes.h"

class LightOperator : public GMLOperator
{

public:
  //-------------------------------------------------------------------
  ///  \param stack execution stack of the interpreter
  ///  \scene SceneDescription were the light is added

  LightOperator(std::vector<GMLToken> &stack, SceneDescription &scene) :
    GMLOperator(stack), m_scene(scene)
  {
    m_name = "light";
  };

  //-------------------------------------------------------------------

  ~LightOperator()
  {};

  //-------------------------------------------------------------------
  /// \brief execution of the token

  void execute() const
  {
    GMLToken color = m_stack.back();
    m_stack.pop_back();
    GMLToken direction = m_stack.back();
    m_stack.pop_back();

    Vec3 vec_color(color.m_float[0], color.m_float[1], color.m_float[2]);
    Vec3 vec_direction(direction.m_float[0], direction.m_float[1], direction.m_float[2]);

    Light *direct_light = new DirectionalLight(vec_color, vec_direction);

    int index = m_scene.addLight(direct_light);

    GMLToken token;
    token.m_type = LIGHT;
    token.m_int[0]= index;

    m_stack.push_back(token);

  };

private:
  SceneDescription &m_scene;

};

#endif

