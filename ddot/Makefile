#/**
# \file 
# 
# @brief Makefile for dot: sample program for cblas_ddot function 
# 
# @version 21.03.01
# 
# @author Julio Jos&eacute; &Aacute;guila Guerrero
# 
# @date March 20th, 2021
#    
# @note Last change was in March 20th, 2021.
# */

CC = mpicc
FLAGS = -O3 -s -pipe -Wall -fomit-frame-pointer -march=native \
       -I../array -w
LIBRARY= array.a
EXEC= ddot
 
all: ${EXEC}

${EXEC}: ${EXEC}.c
	${CC} ${FLAGS} -c ${EXEC}.c
	${CC} ${FLAGS} -o ${EXEC} ${EXEC}.o ${LIBRARY} -lblas -fopenmp

clean:
	(rm -f core) 
	(rm -f *.o)
	(rm -f *~)
	(rm ${EXEC})
