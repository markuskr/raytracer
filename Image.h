//----------------------------------------------------------------------
/// \author  Group: 20
/// \brief Image class, took from AG02
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef __IMAGE_H_
#define __IMAGE_H_


class Image 
{
private:
  int width;
  int height;
  unsigned char *values;
  inline int getOffset(int x, int y)
  {
    return (y*(width) + (x))*3;
  }

public:
  //-------------------------------------------------------------------
  ///  \param w width of the image
  ///  \param h height of the image

  Image(int w, int h) : width(w), height(h)
  {
    values = new unsigned char[w * h * 3];
  }

  //-------------------------------------------------------------------

  ~Image()
  {
    delete[] values;
  }

  //-------------------------------------------------------------------

  inline int getWidth()
  {
    return width;
  }

  //-------------------------------------------------------------------

  inline int getHeight()
  {
    return height;
  }

  //-------------------------------------------------------------------

  inline unsigned char * getValues()
  {
    return values;
  }

  //-------------------------------------------------------------------
  ///  \brief set a pixel in the image

  inline void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) 
  {
    values[getOffset(x,y) + 0] = r;
    values[getOffset(x,y) + 1] = g;
    values[getOffset(x,y) + 2] = b;
  }

  //-------------------------------------------------------------------
  ///  \brief get the color of a pixel of the image

  inline void getPixel(int x, int y, unsigned char &r, unsigned char &g, unsigned char &b)
  {
    r = values[getOffset(x,y) + 0];
    g = values[getOffset(x,y) + 1];
    b = values[getOffset(x,y) + 2];
  }

};

#endif

