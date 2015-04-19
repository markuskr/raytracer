//----------------------------------------------------------------------
/// \author Markus Krallinger 0630748, Group: 20
/// \brief Cube primitive 
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef CUBEPRIMITIVE_H_
#define CUBEPRIMITIVE_H_
#include <cmath>

#include "Material.h"
#include "Primitive.h"
#include "ResultIntersect.h"
#include "Vec3.h"

using namespace std;

class CubePrimitive : public Primitive
{
public:

  //--------------------------------------------------------------------
  
  ~CubePrimitive()
  {
    delete &m_material;
  };

  //--------------------------------------------------------------------
  /// \param material The material of the cube 
    
  CubePrimitive(Material &material) :
    Primitive(material)
  {

    // create corners
    
    corners.reserve(8);
    corners.push_back(Vec3( 0.0f, 0.0f, 0.0f) );
    corners.push_back(Vec3( 1.0f, 0.0f, 0.0f) );
    corners.push_back(Vec3( 1.0f, 0.0f, 1.0f) );
    corners.push_back(Vec3( 0.0f, 0.0f, 1.0f) );
    corners.push_back(Vec3( 0.0f, 1.0f, 0.0f) );
    corners.push_back(Vec3( 1.0f, 1.0f, 0.0f) );
    corners.push_back(Vec3( 1.0f, 1.0f, 1.0f) );
    corners.push_back(Vec3( 0.0f, 1.0f, 1.0f) );
  };
  
  //--------------------------------------------------------------------
  /// \brief Intersects the ray with the cube
  /// \param ray The ray shoot in the scene
  /// \return    A ResultIntersect with the corresponding values

  ResultIntersect intersect(Ray &ray)
  {
    results.clear();

    Vec3 normal_1( 0, 0, -1.0f);
    Vec3 normal_2( 0, 0, 1.0f);
    Vec3 normal_3(-1.0f, 0, 0);
    Vec3 normal_4( 1.0f, 0, 0);
    Vec3 normal_5( 0, 1.0f, 0);
    Vec3 normal_6( 0, -1.0f, 0);

    intersectPlane(ray, normal_1, 1, 0, 1, 0); //front
    intersectPlane(ray, normal_2, 7, 0, 1, 1); //back
    intersectPlane(ray, normal_3, 1, 1, 2, 2); //left
    intersectPlane(ray, normal_4, 7, 1, 2, 3); //right
    intersectPlane(ray, normal_5, 7, 0, 2, 4); //top
    intersectPlane(ray, normal_6, 1, 0, 2, 5); //bottom   

    if (!results.empty())
    {
      std::vector<ResultIntersect>::iterator it = results.begin();

      float min_length = (*it).hitpoint_.length();
      
      ResultIntersect *nearest = &(*it);
      it++;
     
      //find nearest hitpoint
      for (; it < results.end(); it++)
        if ((*it).hitpoint_.length() < min_length)
        {
          nearest = &(*it);
          min_length = (*it).hitpoint_.length() ;
        }

      return ResultIntersect( *nearest) ;
    }
    ResultIntersect empty(m_material);
    empty.hit_ = false;
    return empty;

  };

  //--------------------------------------------------------------------
private:
  
  std::vector<Vec3> corners;
  std::vector<ResultIntersect> results;


  //--------------------------------------------------------------------
  /// \brief   get one specific corner
  /// \param corner the number of the corner to return
  /// \return the corner

  Vec3 &getCorner(int corner)
  {
    return corners.at(corner - 1);
  };

  //--------------------------------------------------------------------
  /// \brief helpfunction for intersect() - calculates
  ///             intersections between the ray and one plane of the cube
  /// \param ray                  the ray
  /// \param normal             normal vector of the plane
  /// \param corner_id       the id of the corner
  /// \param axis1, axis 2   the affected axis 
  /// \param face                 the affected side of the cube
  
  void intersectPlane(Ray &ray, Vec3 &normal, int corner_id,
      int axis1, int axis2, int face)
  {
    std::vector<ResultIntersect> intersections;
    if ( (ray.d * normal) != 0.0) //is ray parallel ?
    {
      Vec3 &corner = getCorner(corner_id);

      //calculate distance
      double distance = ((corner * normal - ray.p[0] * normal[0]
          - ray.p[1] * normal[1] - ray.p[2] * normal[2] )
          / (normal[0] * ray.d[0] + normal[1] * ray.d[1] + normal[2]
              * ray.d[2] ));

      if (distance > 0.0000001)
      {

        Vec3 direction = ray.d * static_cast<float>(distance);
        Vec3 intersect = ray.p + direction;

        if (intersect[axis1] >= 0.0f && intersect[axis1] <= 1.0f
            && intersect[axis2] >= 0.0f && intersect[axis2] <= 1.0f)
        {
          float u, v;
          switch (face)
          {
          case 0:
          case 1:
            u = intersect[0];
            v = intersect[1];
            break;
          case 2:
          case 3:
            u = intersect[1];
            v = intersect[2];
            break;
          case 4:
          case 5:
            u = intersect[0];
            v = intersect[2];
            break;
          default:
              u = 0.0f;
              v = 0.0f;
          }
          u = u < 0.0f ? 0.0f : u;
          u = u > 1.0f ? 1.0f : u;
          v = v < 0.0f ? 0.0f : v;
          v = v > 1.0f ? 1.0f : v;
              
          ResultIntersect result(intersect, face, u, v,
              normal, m_material);

          result.hit_ = true;

          results.push_back(result );
        }
      }
    }
  }
  ;

};

#endif

