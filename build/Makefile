CXX = g++

CXXFLAGS = -Wall -Werror -std=c++11

SRC = logread.cpp logappend.cpp server.cpp input_validation.cpp ciphering.cpp

OBJ = $(SRC:.cpp=.o)

LOGREAD_EXEC = bin/logread
LOGAPPEND_EXEC = bin/logappend
SERVER_EXEC = bin/server

BIN_DIR = bin

all: $(BIN_DIR) $(LOGREAD_EXEC) $(LOGAPPEND_EXEC) $(SERVER_EXEC)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(LOGREAD_EXEC): logread.o input_validation.o ciphering.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(LOGAPPEND_EXEC): logappend.o input_validation.o ciphering.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SERVER_EXEC): server.o input_validation.o ciphering.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)/*.o $(BIN_DIR)/*


.PHONY: all clean run
