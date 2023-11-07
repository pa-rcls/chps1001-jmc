CXX = g++
CXXFLAGS = -std=c++17
SRC_DIR = src/sources
INC_DIR = src/headers

SRC = $(SRC_DIR)/fcts.cpp main.cpp
OBJ = $(SRC:.cpp=.o)
EXE = myprogram

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -o $(EXE) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXE)

.PHONY: all clean
