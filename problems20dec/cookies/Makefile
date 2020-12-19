# This makefile takes any files matching <thing>.cpp
# and compiles them to <thing>.exe
.PHONY: all clean

src := $(shell echo *.cpp)
exe := $(src:cpp=exe)

all: $(exe)

clean:
	-rm *.exe

%.exe: %.cpp
	g++ $< -o $@
