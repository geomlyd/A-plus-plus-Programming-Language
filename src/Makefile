.PHONY: clean

BUILD_DIR := $(abspath $(CURDIR)/../build)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

EXEC1 := $(BUILD_DIR)/app.out
EXEC2 := $(BUILD_DIR)/appCLIDebug.out
EXEC3 := $(BUILD_DIR)/appGUIDebug.out
CC := g++
CPPFLAGS := -Wall -std=c++11

exclude = app.cpp appCLIDebug.cpp appGUIDebug.cpp alpha_parser.cpp alpha_lexer.cpp GUIDebuggerInputController.cpp GUIDebuggerWindow.cpp
exclude2 = alpha_parser.o alpha_lexer.o
SOURCES := $(wildcard *.cpp)
SOURCES := $(filter-out $(exclude), $(SOURCES))
OBJECTS := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SOURCES))
OBJECTS := $(filter-out $(exclude2), $(OBJECTS))

debug: CPPFLAGS += -g
debug: all

release: CPPFLAGS += -DNDEBUG -Ofast
release: all

all: $(BUILD_DIR)/alpha_parser.o $(BUILD_DIR)/alpha_lexer.o app.cpp appGUIDebug.cpp appCLIDebug.cpp \
	$(BUILD_DIR)/GUIDebuggerInputController.o $(BUILD_DIR)/GUIDebuggerWindow.o $(OBJECTS)

	$(CC) $(OBJECTS) $(BUILD_DIR)/alpha_parser.o $(BUILD_DIR)/alpha_lexer.o app.cpp -o $(EXEC1)
	$(CC) $(OBJECTS) $(BUILD_DIR)/alpha_parser.o $(BUILD_DIR)/alpha_lexer.o appCLIDebug.cpp -o $(EXEC2)
	$(CC) $(OBJECTS) -lpthread $(BUILD_DIR)/GUIDebuggerInputController.o $(BUILD_DIR)/GUIDebuggerWindow.o \
	$(BUILD_DIR)/alpha_parser.o $(BUILD_DIR)/alpha_lexer.o appGUIDebug.cpp -o $(EXEC3) `pkg-config --libs gtkmm-3.0`

$(BUILD_DIR)/alpha_parser.o: alpha_parser.cpp
	$(CC) $(CPPFLAGS) -c alpha_parser.cpp -o $@

alpha_parser.cpp: alpha_parser.y function_actions.h error_handler.h
	bison --yacc -Wconflicts-rr --verbose alpha_parser.y

alpha_lexer.cpp: yyalpha.l alpha_parser.cpp alpha_parser.hpp 
	flex yyalpha.l 

$(BUILD_DIR)/alpha_lexer.o: alpha_lexer.cpp error_handler.h
	$(CC) $(CPPFLAGS) -c alpha_lexer.cpp -o $@

$(BUILD_DIR)/GUIDebuggerInputController.o: GUIDebuggerInputController.cpp GUIDebuggerInputController.h GUIDebuggerWindow.h
	$(CC) $(CPPFLAGS) -c GUIDebuggerInputController.cpp `pkg-config --cflags gtkmm-3.0` -o $@

$(BUILD_DIR)/GUIDebuggerWindow.o: GUIDebuggerWindow.cpp GUIDebuggerWindow.h
	$(CC) $(CPPFLAGS) -c GUIDebuggerWindow.cpp `pkg-config --cflags gtkmm-3.0` -o $@

$(BUILD_DIR)/%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f *.out *.o $(BUILD_DIR)/*.out $(BUILD_DIR)/*.o alpha_lexer.cpp alpha_parser.cpp alpha_parser.hpp
