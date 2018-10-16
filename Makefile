SRC_DIR:= ./src/
INC:= -I ./include/
SRCS:=$(wildcard ./src/*.cc)
DEPS:=$(shell ls ./include/*h)
OBJS:=$(SRCS:%.cc=%.o)
LIBS:= -lpthread
CXX:= g++
CXXFLAGS:= -fPIC -Wall -g -std=c++11 $(INC) $(LIBS) -Wno-unused-function

EXE:=./bin/main

$(EXE):$(OBJS)
	$(CXX) -o $@ $(OBJS) $(CXXFLAGS)
%.o:%.cc $(DEPS)
	$(CXX)  -c $< -o $@ $(INC) $(CXXFLAGS)
clean:
	rm -rf $(EXE) $(OBJS)
