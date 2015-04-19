//----------------------------------------------------------------------
/// Filename: AntiAlisedImageStrategy.h
/// Author:   Markus Krallinger 0630748
/// Group:    20
/// \brief Shoots a ray linewise in the scene
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef ANTIALISEDIMAGESTRATEGY_H_
#define ANTIALISEDIMAGESTRATEGY_H_

#define AMOUNT_THREADS 1

#include "RayShootingStrategy.h"
#include "CalculateColorStrategy.h"
#include "Image.h"
#include "Ray.h"

#include <boost/thread/thread.hpp>

struct Thread 
{
  CalculateColorStrategy &m_strategy;
  Vec3 m_camera;  
  int m_depth;
  Image &m_image;
  int m_width;
  int m_heigth;
  float m_delta;
  int m_start;
  int m_end;

  Thread (CalculateColorStrategy &strategy, 
          Vec3 camera, 
          int depth, 
          Image &image,
          int width,
          int heigth,
          float delta,          
          int start,
          int end) :
          m_strategy(strategy), 
          m_camera(camera),
          m_depth(depth),
          m_image(image),
          m_width(width),
          m_heigth(heigth),
          m_delta(delta),
          m_start(start),
          m_end(end)
  {};
  
  void operator()()
  {
    int anti_aliasing_factor = 3;
    int anti_aliasing_start = 0 - ((anti_aliasing_factor - 1) / 2);
    int anti_aliasing_end   = 0 + ((anti_aliasing_factor - 1) / 2);
    
    float sub_pixel_count = (anti_aliasing_factor * anti_aliasing_factor);
    
    for (int current_pixel = m_start; current_pixel < m_end; current_pixel++){
      int pixel_x = (current_pixel % m_width) - m_width / 2;
      int pixel_y = (current_pixel / m_width) - m_heigth / 2;
      
      Vec3 rgb;
      
      for (int anti_aliasing_x = anti_aliasing_start;
               anti_aliasing_x <= anti_aliasing_end;
               anti_aliasing_x ++){
        
        for (int anti_aliasing_y = anti_aliasing_start;
                 anti_aliasing_y <= anti_aliasing_end;
                 anti_aliasing_y ++){
          
          Vec3 startpoint = Vec3 ((pixel_x + anti_aliasing_x) * m_delta,
                                  (pixel_y + anti_aliasing_y) * m_delta,
                                   0.0);
          
          Vec3 direction = startpoint - m_camera;
              
          Ray ray (startpoint, direction);

          Vec3 pixel = m_strategy.calcultateColor(ray, m_depth);
          
          pixel[0] = pixel[0] > 1.0f ? 1.0f : pixel[0];
          pixel[1] = pixel[1] > 1.0f ? 1.0f : pixel[1];
          pixel[2] = pixel[2] > 1.0f ? 1.0f : pixel[2];
          
          pixel[0] = pixel[0] < 0.0f ? 0.0f : pixel[0];
          pixel[1] = pixel[1] < 0.0f ? 0.0f : pixel[1];
          pixel[2] = pixel[2] < 0.0f ? 0.0f : pixel[2];

          if (anti_aliasing_x == 0 && anti_aliasing_y == 0){
            pixel = pixel * 0.5f;
          } else {
             pixel = pixel * (0.5f / (sub_pixel_count - 1));
          }
          
          rgb += pixel;
        }
      }
      
      rgb[0] = rgb[0] > 1.0f ? 1.0f : rgb[0];
      rgb[1] = rgb[1] > 1.0f ? 1.0f : rgb[1];
      rgb[2] = rgb[2] > 1.0f ? 1.0f : rgb[2];
      
      rgb[0] = rgb[0] < 0.0f ? 0.0f : rgb[0];
      rgb[1] = rgb[1] < 0.0f ? 0.0f : rgb[1];
      rgb[2] = rgb[2] < 0.0f ? 0.0f : rgb[2];
      
      m_image.setPixel(pixel_x + (m_width / 2), pixel_y + (m_heigth / 2),
                       static_cast<unsigned char> (rgb[0] * 255) ,
                       static_cast<unsigned char> (rgb[1] * 255) ,
                       static_cast<unsigned char> (rgb[2] * 255));
    }
  }
};

class LineShooting : public RayShootingStrategy
{
public:
  //-------------------------------------------------------------------
  ///  \param strategy strategy to calculate the color

    LineShooting ( CalculateColorStrategy &strategy )
        : RayShootingStrategy ( strategy )
    {};
    
  //-------------------------------------------------------------------

    virtual ~LineShooting(){};

  //-------------------------------------------------------------------
  ///  \brief shoots a ray in the scenne
  ///  \param image image to create
  ///  \param depth recursion depth
  ///  \param fov 
  ///  \param antialising the antialiasing factor 
  ///  \camera position of the camera 

  Image &shootRay ( 
    Image& image, int depth, int fov, int antialising, Vec3 &camera)
  {
    
    int width  = image.getWidth ();  
    int height = image.getHeight();

    float world_width  = 2 * tan(0.5f * fov * to_radian);
    float delta = world_width / static_cast<float> (width);
    int amount_pixel = (width * height);
    int interval = amount_pixel / AMOUNT_THREADS;
    
    int start = 0;
    
    boost::thread threads[AMOUNT_THREADS];
    
    for (int i = 0; i < AMOUNT_THREADS; i++){
      threads[i] = boost::thread(
                          Thread(m_color_strategy,
                                 camera,
                                 depth,
                                 image,
                                 width,
                                 height,
                                 delta,
                                 start,
                                 std::min(amount_pixel, start+interval)));
      start += interval;
    }
        
    for (int i = 0; i < AMOUNT_THREADS; i++){
      threads[i].join();
    }
    return image;
  };
private:
  //calculate scaling factors
  float pi        = 2 * acos(0.0f);
  float to_radian = 2 * pi / 360.0f;

};

#endif
