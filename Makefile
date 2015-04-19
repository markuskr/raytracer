TITLE	= GMLRaytracer
#CC	= /usr/local/bin/g++-4.9
CC = g++
CFLAGS	= -O3 --std=gnu++11 -Wall 
LDFLAGS	= -I /usr/local/Cellar/boost/1.57.0/include -L /usr/local/Cellar/boost/1.57.0/ -l boost_system -l boost_thread-mt

# INCLUDE BASE DIRECTORY AND BOOST DIRECTORY FOR LIB FILES
# LLIBFLAGS = -L/usr/local/Cellar/boost/1.50.0/
#
# # SPECIFIY LINK OPTIONS
# LINKFLAGS = -l boost_thread-mt -lboost_system


OBJECTS = GMLCinParser.o \
  GMLParser.o \
  GMLStringParser.o \
  StandardOperatorFactory.o \
  GMLInterpreter.o \
  Matrix4x4.o \
  RaytraceOperatorFactory.o \
  $(TITLE).o

$(TITLE): $(OBJECTS)
	$(CC) -o $(TITLE) $(OBJECTS) $(LDFLAGS)

%.o: %.cpp %.h
	$(CC) $(CFLAGS) -c $<

$(TITLE).o: $(TITLE).cpp
	$(CC) $(CFLAGS) -c $<


all: $(TITLE)

run : $(TITLE)
	./$^

dbg : $(TITLE)
	ddd ./$^

valgrind: $(TITLE)
	$(CC) $(CFLAGS) -o $(TITLE) $(OBJECTS) $(LDFLAGS) -g

	valgrind -v --leak-check=full --show-leak-kinds=all --dsymutil=yes --tool=memcheck  ./$^  ../gml_files/cube_sphere_reflection_intersect.gml
	
video: $(TITLE)
	$(CC) $(CFLAGS) -o $(TITLE) $(OBJECTS) $(LDFLAGS)
	./$^ < gml_files/test-sphere.gml

  
test: $(TITLE)
	$(CC) $(CFLAGS) -o $(TITLE) $(OBJECTS) $(LDFLAGS)
	./$^ < gml_files/test-plane.gml
	./$^ < gml_files/black_white.gml
	./$^ < gml_files/cube.gml

clean:
	rm *.o $(TITLE)

