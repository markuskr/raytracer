//----------------------------------------------------------------------
/// \author Markus Krallinger 0630748, Group: 20
/// \brief Interface to calculate one single pixel in an image
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef CALCULATECOLORSTRATEGY_H_
#define CALCULATECOLORSTRATEGY_H_

#include "Ray.h"
#include "Vec3.h"
#include "Primitive.h"
#include "GMLToken.h"
#include "Light.h"

#include <memory>
#include <vector>

using std::vector;
using std::auto_ptr;

class CalculateColorStrategy
{
public:
  //--------------------------------------------------------------------
  /// \param amibient The ambient light of the scene
  /// \param lights   An array of lights in the scene
  /// \param objects  A pointer to the scene
  
  CalculateColorStrategy ( 
    Vec3              ambient, 
    vector<Light*>    lights ,
    Primitive        *object ) 
   : 
    m_ambient(ambient) , 
    m_lights(lights)
  {
    m_objects = object;
  };

  CalculateColorStrategy ()
  {};

  void setValues ( Vec3 ambient,  vector<Light*> lights , Primitive *object )
  {
    m_ambient = ambient; 
    m_lights  = lights ;  
    m_objects = object;
  }
  
  //--------------------------------------------------------------------
  /// \brief   Calculates the color of the actual pixel
  /// \param ray      The ray, shoot in the scene
  /// \param depth    Recurisive depth 
  /// \return         Color of the pixel
    
  virtual Vec3 calcultateColor(Ray &ray, int depth) = 0;
  
  //--------------------------------------------------------------------
  virtual ~CalculateColorStrategy(){};
  
protected:

  Vec3                m_ambient ;
  vector<Light*>      m_lights  ;
  Primitive*          m_objects ;


};

#endif

