CXX = g++
CXXFLAGS = -std=c++17
SRC_DIR = src/sources
INC_DIR = src/headers

SRC = $(SRC_DIR)/Atom.cpp $(SRC_DIR)/fcts.cpp $(SRC_DIR)/groReader.cpp $(SRC_DIR)/garfieldSolver.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
EXE = LipidX

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -o $(EXE) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXE)

.PHONY: all clean
