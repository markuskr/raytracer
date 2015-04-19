//----------------------------------------------------------------------
/// Filename: TokenTypes.h
/// Group:    20
/// \brief : describes the constants of the token types
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------

#ifndef TOKENTYPES_H_
#define TOKENTYPES_H_

static const unsigned short int INTEGER         = 0;
static const unsigned short int FLOAT 	 	    = 1;
static const unsigned short int POINT 		    = 2;
static const unsigned short int OPERATION 	    = 3;
static const unsigned short int MARKER 		    = 4;
static const unsigned short int ARRAY 		    = 5;
static const unsigned short int FUNCTION        = 6;
static const unsigned short int NAME 	        = 7;
static const unsigned short int NAMEDEFINITION  = 8;
static const unsigned short int FMARKER         = 9;
static const unsigned short int FUNCTIONMARKER  = 10;
static const unsigned short int BOOLEAN         = 11;


static const unsigned short int PRIMITIVE       = 12; //TODO should be dynamic
static const unsigned short int LIGHT           = 13; //TODO should be dynamic
static const unsigned short int FILENAME        = 14;
#endif /*TOKENTYPES_H_*/

