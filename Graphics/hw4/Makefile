##########################################################
#  CMPSC 457                                             #
#  Simple Makefile for HW 4                              #
#  March 22, 2017                                        #
#  Sukmoon Chang                                         #
#  sukmoon@psu.edu                                       #
#                                                        #
#  Your source codes should be named as                  #
#                                                        #
#            template.cxx                                #
#                                                        #
#                                                        #
#  To compile your program, type                         #
#                                                        #
#            make template                               #
#                                                        #
#  or, simply type                                       #
#                                                        #
#            make                                        #
#                                                        #
#  on your shell.                                        #
#                                                        #
#                                                        #
#  To run your program, type                             #
#                                                        #
#            make run MODEL=n                            #
#                                                        #
#  or, type                                              #
#                                                        #
#            ./template n                                #
#                                                        #
#  where n is one of 1, 2, 3, 4, 5, 6                    # 
#                                                        #
#                                                        #
#  To remove the executable 'template' and other backup  #
#  files (e.g., template.cxx~, etc), type                #
#                                                        #
#            make clean                                  #
#                                                        #
##########################################################


# compiler to be used
CC = g++

# flags to the compiler
#CXX_FLAGS = -Wall -ansi -pedantic
CXX_FLAGS = -Wall -std=c++0x -pedantic -O2





# path to directories containing header files
INC_DIR = -I. -I/home/cmpsc457/s17/glm-master


# GL related libraries
GL_LIBS = -lglut -lGLU -lGL

# X related libraries
X_LIBS = -lXext -lm

# Dependent files
DEP_H = model.h
DEP_CXX = model.cxx


# Default model
MODEL = 1


#### TARGETS ####

template: template.cxx $(DEP_H) $(DEP_CXX)
	$(CC) -o template template.cxx $(DEP_CXX) $(CXX_FLAGS) $(INC_DIR) $(GL_LIBS) $(X_LIBS)

run: template
	./template $(MODEL)

clean:
	rm -f template  *.o *~


test_model: test_model.cxx $(DEP_H) $(DEP_CXX)
	$(CC) -o test_model test_model.cxx $(DEP_CXX) $(CXX_FLAGS) $(INC_DIR) $(GL_LIBS) $(X_LIBS)

run_test_model: test_model
	./test_model

