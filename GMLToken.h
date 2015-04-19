//----------------------------------------------------------------------
/// \author Group:    20
/// \brief GMLToken
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------


#ifndef GMLTOKEN_H_
#define GMLTOKEN_H_

#include <cstdint>

class GMLToken
{
public: 
  unsigned short int m_type;
  union { long m_int[3]; float m_float[3];};
  GMLToken() 
  {
    m_type = 0;
    m_int[0] = 0;
    m_int[1] = 0;
    m_int[2] = 0;
  };
};

#endif /*GMLTOKEN_H_*/
