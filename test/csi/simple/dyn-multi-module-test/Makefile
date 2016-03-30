TOOLKIT = ../../toolkit

# Toolkit rules go before including 'common.mk' so that they are
# preferentially matched.
$(TOOLKIT)/%.o: $(TOOLKIT)/%.cpp
	make -C $(TOOLKIT) $*

# By default link with the null tool.  To use another tool, do
# e.g. 'make foo TOOL=print_tool'
TOOL ?= null_tool
TOOL_OBJ = $(patsubst %,$(TOOLKIT)/%.o,$(TOOL))
CSIRT_OBJ = ../../csirt/csirt.o

#COV_FLAGS = -fprofile-instr-generate -fcoverage-mapping
COV_FLAGS=

include ../../common.mk
CXX=clang++

OBJECTS=a.o libb.so

default: main

main: main.o $(CSIRT_OBJ) $(OBJECTS) $(TOOL_OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -fcsi -flto $(COV_FLAGS) $^ -o $@ -L. -lb

%.o: %.cpp
	$(CXX) -c $(EXTRA) $(COV_FLAGS) -fcsi -emit-llvm $^ -o $@

b.o: b.cpp
	$(CXX) -c $(EXTRA) -fPIC $(COV_FLAGS) -fcsi -emit-llvm $^ -o $@

libb.so: b.o $(TOOL_OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(EXTRA) -fcsi -flto -shared -o $@ $^

main.o: main.cpp
	$(CXX) -c $(EXTRA) -fcsi -emit-llvm $(COV_FLAGS) $^ -o $@

clean:
	rm -f main *.o
