# Output file name
TARGET = MATHGAME

# Source files
SOURCES = buttons.cpp MATHGAME.cpp Animation.cpp mini_game.cpp \
           pet_stats.cpp AdultAvoWindow.cpp BabyAvoWindow.cpp \
           AdultGhostWindow.cpp BabyGhostWindow.cpp EatingAdultAvo.cpp \
           EatingBabyAvo.cpp EatingAdultGhostWindow.cpp EatingBabyGhost.cpp

# SFML library paths and flags
SFML_INCLUDE = -I/opt/homebrew/Cellar/sfml/2.6.1/include
SFML_LIB = -L/opt/homebrew/Cellar/sfml/2.6.1/lib
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -arch arm64

# Build executable
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SFML_INCLUDE) $(SFML_LIB) $(SOURCES) $(SFML_LIBS) -o $(TARGET)

# Clean workspace
clean:
	rm -f $(TARGET) *.o
