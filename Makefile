# source: https://gitlab.fit.cvut.cz/husekrad/pa2-cvika-2022/blob/master/cv10/semestralka/Makefile
LOGIN = eliasma7

CXX = g++
CXXFLAGS = -std=c++17 -Wall -pedantic
FLAGS =

# Find all source files in the src/ directory
SOURCES = $(wildcard src/*.cpp)
# Generate the corresponding object file names
OBJECTS = $(patsubst src/%.cpp, build/%.o, ${SOURCES})
# Generate the corresponding dependency file names
DEPS = $(patsubst src/%.cpp, build/%.dep, ${SOURCES})

.PHONY: all compile run clean doc

all: compile doc

compile: ${LOGIN}
# Link the object files to create an executable
# $^ - all prerequisites, $@ - target
${LOGIN}: ${OBJECTS}
	@mkdir -p build/
	${CXX} ${CXXFLAGS} ${FLAGS} $^ -o $@
# Compile each source file into an object file inside build directory
build/%.o: src/%.cpp
	@mkdir -p build/
	${CXX} ${CXXFLAGS} ${FLAGS} -c $< -o $@
# compiles and runs the file
run: compile
	./${LOGIN}

doc: doc/index.html

doc/index.html: Doxyfile DOCUMENTATION.md $(wildcard src/*)
	doxygen Doxyfile

clean:
	rm -rf doc ${LOGIN} build
# Generate dependency files for each source file. Create in build with the .dep extension. Generate from .cpp files in src/ every time some file in src changes
# $< - first, > - redirect, $@ - target
build/%.dep: src/%.cpp src/*
	@mkdir -p build/
	${CXX} -MM -MT $(patsubst src/%.cpp, build/%.o, $<) $< > $@
# Include the generated dependency files
include ${DEPS}