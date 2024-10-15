# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic
DEBUG_FLAGS = -g
RELEASE_FLAGS = -O2

# Source files and target executable
SRC = main.cpp AdultAvoWindow.cpp AdultGhostWindow.cpp Animation.cpp \
      BabyAvoWindow.cpp BabyGhostWindow.cpp EatingAdultGhostWindow.cpp \
      EatingBabyAvo.cpp EatingBabyGhost.cpp Item.cpp MATHGAME.cpp \
      adult_avo.cpp adult_ghost.cpp avo.cpp baby_avo.cpp baby_ghost.cpp \
      ghost.cpp mini_game.cpp pet_stats.cpp quotesFile.cpp sprite_loader.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = my_virtual_pet

# Build types
ifeq ($(BUILD_TYPE), debug)
    CXXFLAGS += $(DEBUG_FLAGS)
else ifeq ($(BUILD_TYPE), release)
    CXXFLAGS += $(RELEASE_FLAGS)
else
    $(error BUILD_TYPE must be set to 'debug' or 'release')
endif

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Compiling
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJ) $(TARGET)

# Dependency tracking
%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@ \
	&& echo "$< : $@" >> $@

# .PHONY targets
.PHONY: all clean

