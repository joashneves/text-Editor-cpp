# Makefile for text-Editor-cpp

# Compiler
CXX = g++

# Executable name
EXEC = text_editor

# Source files
SRCS = main.cpp models/EditorWindow/EditorWindow.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -I.
CXXFLAGS += $(shell fltk-config --cxxflags)

# Linker flags
LDFLAGS = $(shell fltk-config --ldflags)

# Default target
all: $(EXEC)

# Link the executable
$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) $(LDFLAGS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean
