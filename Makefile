CC = g++
CFLAGS = -Wall
PROG = scigl-viz

SRCS = scigl-viz.cpp scigl.cpp

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut
endif

#all: $(PROG)

# $(PROG):	$(SRCS)
all:	
	rm -f $(PROG)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
