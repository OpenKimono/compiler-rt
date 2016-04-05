.SUFFIXES:

TARGETS := fib-serial foo memops
TOOLKIT = ../toolkit

default: $(TARGETS)

# Toolkit rules go before including 'common.mk' so that they are
# preferentially matched.
$(TOOLKIT)/%.o: $(TOOLKIT)/%.cpp
	make -C $(TOOLKIT) $*

$(TOOLKIT)/%.o: $(TOOLKIT)/%.c
	make -C $(TOOLKIT) $*

../csirt/csirt.o: ../csirt/csirt.c
	make -C ../csirt $*

include ../common.mk

EXTRA = -emit-llvm -fcsi -g
CFLAGS += $(EXTRA)
CXXFLAGS += $(EXTRA)

# By default link with the null tool.  To use another tool, do
# e.g. 'make foo TOOL=print_tool'
TOOL ?= null_tool
TOOL_OBJ = $(patsubst %,$(TOOLKIT)/%.o,$(TOOL))
CSIRT_OBJ = ../csirt/csirt.o

ifeq ($(TOOL), call-graph)
LDFLAGS += `pkg-config --libs --cflags glib-2.0`
endif

ifeq ($(TOOL), gprof_tool)
CFLAGS += -fno-omit-frame-pointer
CXXFLAGS += -fno-omit-frame-pointer
EXTRA += -fno-omit-frame-pointer
LDFLAGS += -pg
endif

fib-serial: fib-serial.o $(TOOL_OBJ) $(CSIRT_OBJ)
foo: foo.o bar.o $(TOOL_OBJ) $(CSIRT_OBJ)
memops: memops.o $(TOOL_OBJ) $(CSIRT_OBJ)

fib-serial.o: fib-serial.cpp
	$(CXX) -c -emit-llvm $(EXTRA) $^ -o $@

foo.o: foo.cpp
	$(CXX) -c $(EXTRA) $^ -o $@

bar.o: bar.cpp
	$(CXX) -c $(EXTRA) $^ -o $@

memops.o: memops.cpp
	$(CXX) -c $(EXTRA) $^ -o $@

# The right file extention for bitcode is *.ll
%.ll: %.cpp
	$(CXX) -O0 -S $(EXTRA) $^ -o $@

%.bc: %.cpp
	/usr/local/llvm-cilk/bin/clang++ -O0 -S -fsanitize=thread -emit-llvm -c $^ -o $@

%.s: %.cpp
	$(CXX) -S -O3 $^ -o $@

%: %.o
	$(CXX) $^ $(LDFLAGS) -O3 -flto $(LDLIBS) -o $@

clean:
	-rm -f $(TARGETS) *.o *.s *.ll *.bc
	make -C $(TOOLKIT) clean
