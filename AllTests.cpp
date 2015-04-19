#include "GMLParser.h"
#include "GMLOperator.h"
#include "GMLToken.h"
#include "GMLInterpreter.h"
#include "GMLStringParser.h"

#include "StandardOperatorFactory.h"
#include "RaytraceOperatorFactory.h"
#include "TokenTypes.h"

#include "SceneDescription.h"

//Operators
#include "AddiOperator.h"
#include "AddfOperator.h"
#include "AcosOperator.h"
#include "ClampfOperator.h"
#include "CosOperator.h"
#include "AsinOperator.h"
#include "DiviOperator.h"
#include "DivfOperator.h"
#include "FloorOperator.h"
#include "FracOperator.h"
#include "ModiOperator.h"
#include "MuliOperator.h"
#include "MulfOperator.h"
#include "NegiOperator.h"
#include "NegfOperator.h"
#include "RealOperator.h"
#include "SinOperator.h"
#include "SqrtOperator.h"
#include "SubiOperator.h"
#include "SubfOperator.h"



#include "Primitive.h"

#include "Material.h"

#include <vector>

#include <iostream>
#include <string>
#include <assert.h>
#include <exception>
#include <memory>

#include <cmath>

using std::vector;
using std::cout;
using std::endl;
using std::string;

void pushIntToken  (int);
void pushFloatToken(float);

GMLToken createIntToken(int);
GMLToken createFloatToken(float);
GMLToken createPointToken (float, float, float);

void printStack();
void printStack(vector<GMLToken> &);

vector<GMLToken> stack;
static const float FLOAT_DIFF = 0.0001f;

class TestProgram
{
public:
  string program;
  GMLToken result;
  TestProgram(const string &progr, const GMLToken &token)
  {
    program = progr;
    result = token;
  }
};

//---------------------------------------------------------------------
void testIntOperator(GMLToken result, GMLOperator* op)
{
  cout << "Before: " << endl;
  printStack();
  op->execute();
  cout << "After: " << endl;
  printStack();  



  assert(result.m_type == stack.back().m_type);

  for (int i = 0; i < 3; i++)
  {
    if (result.m_type == INTEGER)
      assert(result.m_int[i]   == stack.back().m_int[i]);
    else if (result.m_type == FLOAT)
    {
      float f_result = abs(result.m_float[i] - stack.back().m_float[i]);
      assert( f_result < FLOAT_DIFF);
    }
  }
  stack.pop_back();
  
  delete op;
}

//---------------------------------------------------------------------
void testCompareValue(GMLToken result)
{
  cout << "After: " << endl;
  printStack();  

  assert(result.m_type == stack.back().m_type);

  for (int i = 0; i < 3; i++)
  {
    if (result.m_type == INTEGER)
      assert(result.m_int[i]   == stack.back().m_int[i]);
    else if (result.m_type == FLOAT)
    {
      float f_result = abs(result.m_float[i] - stack.back().m_float[i]);
      assert( f_result < FLOAT_DIFF);
    }
  }
  stack.pop_back();
}

//---------------------------------------------------------------------
int main____()
{	
  /*
  //Addi
  pushIntToken(1); pushIntToken(1);
  testIntOperator(createIntToken(2), new AddiOperator(stack)); 

  pushIntToken(-1); pushIntToken(-1);
  testIntOperator(createIntToken(-2), new AddiOperator(stack));

  //Addf
  pushFloatToken(1.0); pushFloatToken(2.5);
  testIntOperator(createFloatToken(3.5), new AddfOperator(stack)); 

  pushFloatToken(-1.0); pushFloatToken(-2.5);
  testIntOperator(createFloatToken(-3.5), new AddfOperator(stack));  

  //Acos
  pushFloatToken(-1.0);
  testIntOperator(createFloatToken(180), new AcosOperator(stack));  

  pushFloatToken(1.0);
  testIntOperator(createFloatToken(0), new AcosOperator(stack));  
 
  pushFloatToken(5.0);
  try { testIntOperator(createFloatToken(0), new AcosOperator(stack));}
  catch (std::exception &e) {};

  //Asin
  pushFloatToken(-1.0);
  testIntOperator(createFloatToken(-90), new AsinOperator(stack));  

  pushFloatToken(1.0);
  testIntOperator(createFloatToken(90), new AsinOperator(stack));  
 
  pushFloatToken(5.0);
  try { testIntOperator(createFloatToken(0), new AsinOperator(stack));}
  catch (std::exception &e) {};

  //Clampf
  pushFloatToken(5.0);
  testIntOperator(createFloatToken(1.0), new ClampfOperator(stack)); 

  pushFloatToken(-5.0);
  testIntOperator(createFloatToken(0.0), new ClampfOperator(stack));

  pushFloatToken(0.3);
  testIntOperator(createFloatToken(0.3), new ClampfOperator(stack));

  //Cos
  pushFloatToken(90);
  testIntOperator(createFloatToken(0), new CosOperator(stack));  

  pushFloatToken(0);
  testIntOperator(createFloatToken(1.0), new CosOperator(stack));  
 
  pushFloatToken(15.6);
  testIntOperator(createFloatToken(0.963162), new CosOperator(stack));

  //Divi 
  pushIntToken(90); pushIntToken(30);
  testIntOperator(createIntToken(3), new DiviOperator(stack));  

  pushIntToken(90); pushIntToken(33);
  testIntOperator(createIntToken(2), new DiviOperator(stack)); 
 
  pushFloatToken(90); pushIntToken(0);
  try { testIntOperator(createIntToken(0), new DiviOperator(stack));}
  catch (std::exception &e) {};

  //Divf
  pushFloatToken(90); pushFloatToken(30);
  testIntOperator(createFloatToken(3), new DivfOperator(stack));  

  pushFloatToken(90); pushFloatToken(33);
  testIntOperator(createFloatToken(2.727272), new DivfOperator(stack)); 
 
  pushFloatToken(90); pushFloatToken(0);
  try { testIntOperator(createFloatToken(0), new DivfOperator(stack));}
  catch (std::exception &e) {};

  //Eqi

  //Eqf

  //Floor
  pushFloatToken(1.2554);
  testIntOperator(createIntToken(1), new FloorOperator(stack));

  pushFloatToken(-1.2554);
  testIntOperator(createIntToken(-2), new FloorOperator(stack));
  
  //Frac
  pushFloatToken(1.2554);
  testIntOperator(createFloatToken(0.2554), new FracOperator(stack));

  pushFloatToken(-1.2554);
  testIntOperator(createFloatToken(-0.2554), new FracOperator(stack));

  //Lessi

  //Lessf

  //Modi
  pushIntToken(90); pushIntToken(30);
  testIntOperator(createIntToken(0), new ModiOperator(stack));  

  pushIntToken(93); pushIntToken(30);
  testIntOperator(createIntToken(3), new ModiOperator(stack));

  //Muli
  pushIntToken(90); pushIntToken(30);
  testIntOperator(createIntToken(2700), new MuliOperator(stack));  

  pushIntToken(90); pushIntToken(-30);
  testIntOperator(createIntToken(-2700), new MuliOperator(stack));

  pushIntToken(90); pushIntToken(0);
  testIntOperator(createIntToken(0), new MuliOperator(stack));

  //Mulf
  pushFloatToken(90); pushFloatToken(30);
  testIntOperator(createFloatToken(2700), new MulfOperator(stack));  

  pushFloatToken(90); pushFloatToken(-30);
  testIntOperator(createFloatToken(-2700), new MulfOperator(stack));

  pushFloatToken(90); pushFloatToken(0);
  testIntOperator(createFloatToken(0), new MulfOperator(stack));

  //Negi
  pushIntToken(90);
  testIntOperator(createIntToken(-90), new NegiOperator(stack));  

  pushIntToken(-90); 
  testIntOperator(createIntToken(90), new NegiOperator(stack));

  //Negf
  pushFloatToken(90);
  testIntOperator(createFloatToken(-90), new NegfOperator(stack));  

  pushFloatToken(-90); 
  testIntOperator(createFloatToken(90), new NegfOperator(stack));

  //Real
  pushIntToken(90);
  testIntOperator(createFloatToken(90), new RealOperator(stack));  

  //Sin
  pushFloatToken(90);
  testIntOperator(createFloatToken(1), new SinOperator(stack));  

  pushFloatToken(0);
  testIntOperator(createFloatToken(0), new SinOperator(stack));  
 
  pushFloatToken(15.6);
  testIntOperator(createFloatToken(0.268919), new SinOperator(stack));

  //Sqrt
  pushFloatToken(90);
  testIntOperator(createFloatToken(9.486832), new SqrtOperator(stack));  

  pushFloatToken(-1);
  try { testIntOperator(createFloatToken(0), new SqrtOperator(stack));}
  catch (std::exception &e) {};

  //Subi

  //Subf
  */


  

  vector<TestProgram> test_programs;

  /*test_programs.push_back(TestProgram( " 3 3 eqi { 1 } { 2 } if ", createIntToken(1) ));
 // test_programs.push_back(TestProgram( " -1.2 0.0 lessf { -1.2 -1 mulf } { 2 } if ", createFloatToken(1.2) ));
  test_programs.push_back(TestProgram( " { 1 addi } /inc 1 inc apply inc apply inc apply inc apply inc apply", createIntToken(6)  ));
  //test_programs.push_back(TestProgram( " [ 1 9 ] /bla bla bla [ 2 ] /blub blub blub blub bla bla bla 1 get", createIntToken(9))); 
  test_programs.push_back(TestProgram( "{ dup muli } /sq 4 sq apply", createIntToken(16) ));
  test_programs.push_back(TestProgram( 
    "{ /p p getx negf p gety negf p getz negf point } /negp 1.0 1.0 1.0 point negp apply", 
    createPointToken(-1.0, -1.0, -1.0 )));
  test_programs.push_back(TestProgram( "{ 20 muli } /f 12 f apply 20 f apply", createIntToken(400) ));
 // test_programs.push_back(TestProgram( 
 //   "{ { sin } { 1.0 addf } if } /g 45.0 1 g apply ", createFloatToken(0.707107) ));
  test_programs.push_back(TestProgram( 
    "{ { sin } { 1.0 addf } if } /g 45.0 0 g apply ", createFloatToken(46.0) ));
  test_programs.push_back(TestProgram( 
    "10 /x { 20 /x } /f -1 x f apply x 30 /x x -2 ", createIntToken(-2) ));
  test_programs.push_back(TestProgram( 
    "10 4 { /k 2 muli k 1 subi /k k 1 k lessi } while ", createIntToken(0) ));*/

  string program = " 1.0 0.5 0.0 point /orange ";
  program.append(  " 0.0 0.5 0.0 point /green ");
  program.append(  " 0.0 0.0 1.0 point /blue ");
  program.append(  " 1.0 0.0 0.0 point /red ");
  program.append(  " 1.0 1.0 1.0 point /white ");
  program.append(  " 1.0 1.0 0.0 point /yellow ");
  
  program.append(  " [ ");
  program.append(  " [ orange green orange ] ");
  program.append(  " [ green orange green ] "); 
  program.append(  " [ orange green orange ] "); 
  program.append(  " ] /texture ");

  program.append(  " [ ");
  program.append(  " [ yellow green yellow ] ");
  program.append(  " [ green yellow green ] "); 
  program.append(  " [ yellow green yellow ] "); 
  program.append(  " ] /texture2 ");

  program.append(  " [ ");
  program.append(  " [ blue red blue ] "); 
  program.append(  " [ red blue red ] "); 
  program.append(  " [ blue red blue ] "); 
  program.append(  " ] /texture1 ");
 
  program.append(  " [ ");
  program.append(  " [ blue white ] ");
  program.append(  " [ white blue ] ");
  program.append(  " ] /bavaria ");

 
                          
  program.append(  " { /v /u /face ");
  program.append(  " green ");
  /*program.append(  " v 0.0 lessf { v -1.0 mulf } { v } if ");
  program.append(  " floor 3 modi get ");
  program.append(  " u 0.0 lessf { u -1.0 mulf } { u } if ");
  program.append(  " floor 3 modi get ");*/
  program.append(  " 1.0 0.5 10.0 ");
  program.append(  " } plane 0.0 0.0 12.0 translate ");  
  program.append(  " 180.0 rotatez /pl ");
  program.append(  " pl pl 180.0 rotatez union /pl ");
  //program.append(  " pl -90.0 rotatez ");
 // program.append(  " union /pl "); 
  
  program.append(  " { /v /u /face ");   
  program.append(  " red ");
  program.append(  " 0.2 1.0 5.0 ");
  program.append(  " } sphere /sp ");

 
  program.append(  " { /v /u /face ");   
  program.append(  " orange ");
  program.append(  " 0.9 0.3 5.0 ");
  program.append(  " } sphere /sp_ "); 


  program.append(  " sp 1.0 0.5 5.5 translate /sp1 ");
  program.append(  " sp 2.0 2.0 5.0 translate /sp2 ");
  program.append(  " sp 2.0 -2.0 5.0 translate /sp3 ");
  program.append(  " sp -2.0 2.0 5.0 translate /sp4 ");

  program.append(  " sp_ -4.0 -4.0 6.0 translate /sp_1 ");
  program.append(  " sp_ 4.0 4.0 6.0 translate /sp_2 ");
  program.append(  " sp_ 4.0 -4.0 6.0 translate /sp_3 ");
  program.append(  " sp_ -4.0 4.0 6.0 translate /sp_4 ");
  
  program.append(  " sp2 sp1 union /bla1 ");
  program.append(  " sp3 sp4 union /bla2 ");
  program.append(  " bla1 bla2 union /bla3 ");  

  program.append(  " sp_2 sp_1 union /blub1 ");
  program.append(  " sp_3 sp_4 union /blub2 ");
  program.append(  " blub1 blub2 union /blub ");  
  
  program.append(  " bla3 blub union /bla ");
  program.append(  " pl bla union /bla ");
  program.append(  " [ 0.0 0.0 -4.0 point ");
  program.append(  " 1.0 1.0 1.0 point ");
  program.append(  " pointlight ");
  /*program.append(  " 0.0 2.0 -2.0 point ");
  program.append(  " white ");
  program.append(  " light ");
  program.append(  " 4.0 4.0 6.0 point ");
  program.append(  " white ");
  program.append(  " light ");
  program.append(  " [ 4.0 0.0 4.0 point ");
  program.append(  " white pointlight");*/
  program.append(  " ] /lights ");
  program.append(  " 0.5 0.5 0.5 point lights bla 10 90 200 200 render ");

 

program = " { /v /u /face ";
program.append(  " 1.0 0.0 0.0 point ");
program.append(  " 0.8 0.5 70.0 ");
program.append(  " } sphere -0.75 -0.75 1.0 translate");
program.append(  " /redSphere ");

program.append( " { /v /u /face ");
program.append(  " 0.0 1.0 0.0 point ");
program.append(  " 0.8 0.5 60.0 ");
program.append(  " } cube  1.5 uscale -0.75 -0.75 0.0 translate  ");
program.append(  " /greenSphere ");

program.append( " { /v /u /face ");
program.append(  " 0.0 0.5 1.0 point ");
program.append(  " 0.8 0.5 80.0 ");
program.append(  " } sphere");
program.append(  " /blueSphere ");

program.append( " { /v /u /face ");
program.append(  " 1.0 0.5 0.0 point ");
program.append(  " 0.8 0.5 100.0 ");
program.append(  " } plane ");
program.append(  " 90.0 rotatez  0.0 0.0 3.0 translate /pl ");
program.append(  " pl pl 180.0 rotatez union /pl ");
 

program.append(  " redSphere -2.5 -1.5 3.0 translate ");
program.append(  " greenSphere 0.0 -1.5 3.0 translate ");
program.append(  " blueSphere 2.5 -1.5 3.0 translate ");
program.append(  " union union /bla ");

program.append(  " redSphere -2.5 1.5 3.0 translate ");
program.append(  " greenSphere 0.0 1.5 3.0 translate ");
program.append(  " blueSphere 2.5 1.5 3.0 translate ");
program.append(  " union union /bla1 ");

program.append(  " bla bla1 union /scene ");

program.append(  " bla bla1 union /scene ");

program.append(  " scene 30.0 rotatez /scene ");
			
program.append(  " 0.0 0.0 2.0 point ");
program.append(  " 1.0 1.0 1.0 point pointlight /l ");

program.append(  " 2.0 2.0 2.0 point ");
program.append(  " 0.3 0.3 0.3 point light /l1 ");

program.append(  " 0.25 0.25 0.25 point ");
program.append(  " [ l ] ");
program.append(  " scene ");
program.append(  " 15 ");
program.append(  " 90 ");
program.append(  " 200 200 ");
program.append(  " test.pnm ");
program.append(  " render ");

/*

  test_programs.push_back(TestProgram( program, createIntToken(1)));

  vector<TestProgram>::iterator it = test_programs.begin();

  for (; it < test_programs.end(); it ++)
  {
    cout << (*it).program << "\n ------ \n" << endl;
    std::auto_ptr<GMLParser> parser ( new GMLStringParser((*it).program));  
    GMLInterpreter interpreter (parser.get());
    SceneDescription scene;
    std::auto_ptr<StandardOperatorFactory> fact(new StandardOperatorFactory(interpreter));
    std::auto_ptr<RaytraceOperatorFactory> rayt(new RaytraceOperatorFactory(interpreter, scene));
    parser->addFactory(fact.get());
    parser->addFactory(rayt.get());
    GMLToken start = parser->parse();
    interpreter.interpretGML( parser->getProgram(), start);
    stack = interpreter.m_stack;
   // testCompareValue((*it).result);
  }*/


  //

	return 0;
}
//---------------------------------------------------------------------
void pushIntToken (int value)
{
	GMLToken token;

	token.m_type   = INTEGER;
	token.m_int[0] = value;

  stack.push_back(token);
}
//---------------------------------------------------------------------
GMLToken createIntToken (int value)
{
	GMLToken token;

	token.m_type   = INTEGER;
	token.m_int[0] = value;

  return token;
}
//---------------------------------------------------------------------
GMLToken createPointToken (float value1, float value2, float value3)
{
	GMLToken token;

	token.m_type     = POINT;
	token.m_float[0] = value1;
  token.m_float[1] = value2;
  token.m_float[2] = value3;

  return token;
}
//---------------------------------------------------------------------
void pushFloatToken(float value)
{
  GMLToken token;

	token.m_type     = FLOAT;
	token.m_float[0] = value;

  stack.push_back(token);
}

//---------------------------------------------------------------------
GMLToken createFloatToken (float value)
{
	GMLToken token;

	token.m_type     = FLOAT;
	token.m_float[0] = value;

	return token;
}
//---------------------------------------------------------------------
void printStack()
{
  printStack(stack);
}
//---------------------------------------------------------------------
void printStack(vector<GMLToken> &print_stack)
{
  vector<GMLToken>::iterator it = print_stack.begin();
  
  string type = "";

  for (; it < print_stack.end(); it ++)
  {
    switch ((*it).m_type)
    {
    case INTEGER:
      type = "INTEGER";
      break;
    case FLOAT:
      type = "FLOAT";
      break;
    } 

    cout << "--------- \n Token: \n " + type << 
    "\n Int : ";
    for (int i = 0; i < 3; i ++)
      cout << (*it).m_int[i] << " ";
    cout << endl;

    cout << " Float: ";
    for (int i = 0; i < 3; i ++)
      cout << (*it).m_float[i] << " ";
    cout << "\n" << endl;;
  }
}

