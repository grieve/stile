CC = g++
DEBUG = -g
CFLAGS = -Wall $(DEBUG) -I src/ -lsfml-graphics -lsfml-window -lsfml-system
LFLAGS = -Wall $(DEBUG) 

PROJECT = stile_examples
DEP_LINKS = 	

PROJECT_SRCS  = main.cc
PROJECT_OBJS = main.o


default: $(PROJECT)

include ../stile/Makefile.inc

$(PROJECT) : $(DEPS)
	$(CC) $(CFLAGS) $(PROJECT_SRCS) $(STILE_SRCS) $(DEPS_LINKS) $(LIBS) -o $(PROJECT).bin
ifndef $(RUN)
	xterm -e ./$(PROJECT).bin
endif

include ../Box2D/Makefile.inc
box2d.a :
	$(CC) $(CFLAGS) -c $(BOX2D_SRCS)
	ar rcs box2d.a $(BOX2D_OBJS)

clean :
	\rm -f *.o *.a *~ */*.o */*~ */*.a *.bin
