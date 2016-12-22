
INC_DIR:= ./include/
SRC_DIR:= ./src/
SRCS:=$(wildcard ./src/*.cc)
LIBS:= -lpthread
CXX:= /opt/rh/devtoolset-2/root/usr/bin/c++
CXXFLAGS:=-Wall -g -std=c++11 $(addprefix -I, $(INC_DIR)) $(LIBS)

EXE:=./bin/main

$(EXE):$(SRCS)
	$(CXX) -o $@ $(SRCS) $(CXXFLAGS)
clean:
	rm -rf $(EXE)
