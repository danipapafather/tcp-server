.PHONY: all

CXXCOMPILER := g++
CXXFLAGS := -Wall -Wextra -Werror -std=c++20
SOURCE_FILES := main.cpp include/server.cpp
EXECUTABLE := main

all: $(SOURCE_FILES)
	$(CXXCOMPILER) $(SOURCE_FILES) -o $(EXECUTABLE) $(CXXFLAGS)