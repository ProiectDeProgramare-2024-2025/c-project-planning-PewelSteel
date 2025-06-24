# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# Source and object files
SRC = src/Question.cpp src/Player.cpp src/GameSession.cpp
OBJS = $(SRC:.cpp=.o)

# Targets
all: game_engine.exe game_ui.exe

game_engine.exe: game_engine.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ game_engine.cpp $(OBJS)

game_ui.exe: game_ui.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ game_ui.cpp $(OBJS)

# Rule for building .o files from .cpp
src/%.o: src/%.cpp include/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f *.exe src/*.o
