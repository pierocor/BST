#Dirs
EXEDIR=bin
SRCDIR=src
HEADDIR=include
OUTDIR=out
#Executable
EXE=bst_bin.x
MAIN=bst
HEAD= mod
#Compiler
LFLAGS=
CC=g++
CFLAGS=-g -std=c++11 -Wall -Wextra -I include 

default: $(EXE)

$(EXE): ${MAIN}.o ${SRCDIR}/${HEAD}.o
	$(CC) $^ -o ${EXEDIR}/$(EXE) $(LFLAGS)

${SRCDIR}/${HEAD}.o: ${HEADDIR}/${HEAD}.h

%.o: %.cc
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf ${SRCDIR}/*.o  *.o *~

.PHONY: clean

clean-outputs: 
	rm -rf ${OUT}/*.dat

.PHONY: clean-outputs

clean-all:
	rm -rf ${SRCDIR}/*.o ${EXEDIR}/${EXE} ${OUTDIR}/*.dat *~ *.o ${SRCDIR}/*~ ${HEADDIR}/*~
