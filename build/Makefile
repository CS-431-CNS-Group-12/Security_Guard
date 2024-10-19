CXX = g++

CXXFLAGS = -std=c++20

SRC = logread.cpp logappend.cpp server.cpp input_validation.cpp ciphering.cpp sha256.cpp

OBJ = $(SRC:.cpp=.o)

LOGREAD_EXEC = logread
LOGAPPEND_EXEC = logappend
SERVER_EXEC = server

INSTALL_DIR = /usr/local/bin

all: $(LOGREAD_EXEC) $(LOGAPPEND_EXEC) $(SERVER_EXEC)

$(LOGREAD_EXEC): logread.o input_validation.o ciphering.o sha256.o server.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(LOGAPPEND_EXEC): logappend.o input_validation.o ciphering.o sha256.o server.o
	$(CXX) $(CXXFLAGS) -o $@ $^
 
$(SERVER_EXEC): server.o input_validation.o ciphering.o sha256.o 
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(LOGREAD_EXEC) $(LOGAPPEND_EXEC) $(SERVER_EXEC)

install: $(LOGREAD_EXEC) $(LOGAPPEND_EXEC) $(SERVER_EXEC)
	@if [ ! -d "$(INSTALL_DIR)" ]; then \
		echo "Creating $(INSTALL_DIR)"; \
		sudo mkdir -p $(INSTALL_DIR); \
	fi
	sudo install $(LOGREAD_EXEC) $(INSTALL_DIR)/logread
	sudo install $(LOGAPPEND_EXEC) $(INSTALL_DIR)/logappend
	sudo install $(SERVER_EXEC) $(INSTALL_DIR)/server

uninstall:
	rm -f $(INSTALL_DIR)/logread $(INSTALL_DIR)/logappend $(INSTALL_DIR)/server

.PHONY: all clean install uninstall
