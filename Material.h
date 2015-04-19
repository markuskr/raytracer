//----------------------------------------------------------------------
/// \author Group: 20
/// \brief calculates the material
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <exception>
#include "GMLInterpreter.h"
#include "GMLToken.h"
#include "TokenTypes.h"
#include "ResultIntersect.h"
#include "MaterialResult.h"
#include <stdexcept>

#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>

using std::exception;



class Material
{
public:

  
  
  //-----------------------------------------------------------------
  /// \param token function token for material
  /// \param m_interpreter interpreter object
  
  Material(GMLToken &token, GMLInterpreter& m_interpreter) :
    m_interpreter_(m_interpreter)
  {
    token_.m_int[0] = token.m_int[0];
    token_.m_int[1] = token.m_int[1];
    token_.m_int[2] = token.m_int[2];

    token_.m_type = token.m_type;

    if (token.m_type != FUNCTION)
      throw std::runtime_error("Error Material: No function token");
  }
  ;
  //-----------------------------------------------------------------

  virtual ~Material()
  {} ;

  //-----------------------------------------------------------------
  /// \brief calculates the material parameters
  /// \param u texture parameter u
  /// \param v texture parameter v
  /// \param face texture parameter face

  MaterialResult getMaterialParameters(float u, float v, int face)
  {
    GMLToken u_token;
    GMLToken v_token;
    GMLToken face_token;

    u_token.m_type = FLOAT;
    u_token.m_float[0] = u;

    v_token.m_type = FLOAT;
    v_token.m_float[0] = v;

    face_token.m_type = INTEGER;
    face_token.m_int[0] = face;

    m_interpreter_.m_stack.push_back(face_token);
    m_interpreter_.m_stack.push_back(u_token);
    m_interpreter_.m_stack.push_back(v_token);

    std::vector<GMLToken> &array =
        m_interpreter_.m_arrays[token_.m_int[0]];
    std::vector<GMLToken>::reverse_iterator it = array.rbegin();

    float ks_float = 0, n_float = 0, kd_float = 0;

    for (; it < array.rend(); it++)
    {
      m_interpreter_.execute( (*it));
    }

    GMLToken n = m_interpreter_.m_stack.back();
    m_interpreter_.m_stack.pop_back();

    if (n.m_type != FLOAT)
      throw std::runtime_error("Error Material: n wrong type");
    else
      n_float = n.m_float[0];

    GMLToken ks = m_interpreter_.m_stack.back();
    m_interpreter_.m_stack.pop_back();

    if (ks.m_type != FLOAT)
      throw std::runtime_error("Error Material: ks wrong type");
    else
      ks_float = ks.m_float[0];

    GMLToken kd = m_interpreter_.m_stack.back();
    m_interpreter_.m_stack.pop_back();
    if (kd.m_type != FLOAT)
      throw std::runtime_error("Error Material: kd wrong type");
    else
      kd_float = kd.m_float[0];

    GMLToken color = m_interpreter_.m_stack.back();
    m_interpreter_.m_stack.pop_back();

    if (color.m_type != POINT)
      throw std::runtime_error("Error Material: color wrong type");
    Vec3 colorVector(color.m_float[0], color.m_float[1],
        color.m_float[2]);
    
    MaterialResult material(colorVector, ks_float, kd_float, n_float);
    
    return material;

  };
  
  //-----------------------------------------------------------------
  /// \brief overloading of operator=
  /// \brief from material to be assigned

  Material & operator=(const Material &from)
  {
    token_ = from.token_;
    m_interpreter_ = from.m_interpreter_;
    return *this;
  };


private:
  GMLToken token_;
  GMLInterpreter& m_interpreter_;
};

#endif /*MATERIAL_H_*/


