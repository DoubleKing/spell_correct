SRC_DIR:= ./src/
SRCS:=$(wildcard ./src/*.cc)
OBJS:=$(SRCS:%.cc=%.o)
LIBS:= -lpthread -L ./tools/inifile/ -linifile -L ./tools/cJSON/ -lcJSON
CXX:= g++
CXXFLAGS:=  -g -std=c++11 $(LIBS) -Wno-unused-function

EXE:=./src/spell_correct

$(EXE):$(OBJS)
	$(CXX) -o $@ $(OBJS) $(CXXFLAGS)
%.o:%.cc
	$(CXX)  -c $< -o $@  $(CXXFLAGS)
clean:
	rm -rf $(EXE) $(OBJS)
install:
	cp $(EXE) ./bin/
