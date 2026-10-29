CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2

T1 := Task1_AlphaCipher
T2 := Task2_BetaCipher

BIN := bin
OBJ := obj

T1_SRC := $(T1)/main.cpp $(T1)/modeAlphaCipher.cpp
T2_SRC := $(T2)/main.cpp $(T2)/modeBetaCipher.cpp
T1_OBJ := $(T1_SRC:%.cpp=$(OBJ)/%.o)
T2_OBJ := $(T2_SRC:%.cpp=$(OBJ)/%.o)

.PHONY: all task1 task2 run1 run2 clean

all: task1 task2

task1: $(BIN)/$(T1)
task2: $(BIN)/$(T2)

$(BIN)/$(T1): $(T1_OBJ)
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BIN)/$(T2): $(T2_OBJ)
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) $^ -o $@

# компиляция .cpp -> .o (с автоматическим учётом заголовков)
$(OBJ)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

run1: task1
	./$(BIN)/$(T1)

run2: task2
	./$(BIN)/$(T2)

clean:
	rm -rf $(BIN) $(OBJ)

-include $(T1_OBJ:.o=.d) $(T2_OBJ:.o=.d)
