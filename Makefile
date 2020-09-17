.PHONY: clean

EXEC1 := app.out
EXEC2 := appCLIDebug.out
EXEC3 := appGUIDebug.out
CC := g++
CPPFLAGS := -Wall -std=c++11

exclude = app.cpp appCLIDebug.cpp appGUIDebug.cpp alpha_parser.cpp alpha_lexer.cpp GUIDebuggerInputController.cpp GUIDebuggerWindow.cpp
exclude2 = alpha_parser.o alpha_lexer.o
SOURCES := $(wildcard *.cpp)
SOURCES := $(filter-out $(exclude), $(SOURCES))
OBJECTS := $(patsubst %.cpp, %.o, $(SOURCES))
OBJECTS := $(filter-out $(exclude2), $(OBJECTS))

debug: CPPFLAGS += -g
debug: all

release: CPPFLAGS += -DNDEBUG -Ofast
release: all

all: alpha_parser.o alpha_lexer.o app.cpp appGUIDebug.cpp appCLIDebug.cpp GUIDebuggerInputController.o GUIDebuggerWindow.o $(OBJECTS)
	$(CC) $(OBJECTS) alpha_parser.o alpha_lexer.o app.cpp -o $(EXEC1)
	#$(CC) $(OBJECTS) alpha_parser.o alpha_lexer.o appCLIDebug.cpp -o $(EXEC2)
	$(CC) $(OBJECTS) -lpthread GUIDebuggerInputController.o GUIDebuggerWindow.o alpha_parser.o alpha_lexer.o appGUIDebug.cpp -o $(EXEC3) `pkg-config --libs gtkmm-3.0`

alpha_parser.o: alpha_parser.cpp
	$(CC) $(CPPFLAGS) -c alpha_parser.cpp

alpha_parser.cpp: alpha_parser.y function_actions.h error_handler.h
	bison --yacc -Wconflicts-rr --verbose alpha_parser.y

alpha_lexer.cpp: yyalpha.l alpha_parser.cpp alpha_parser.hpp 
	flex yyalpha.l 

alpha_lexer.o: alpha_lexer.cpp error_handler.h
	g++ $(CPPFLAGS) -c alpha_lexer.cpp

GUIDebuggerInputController.o: GUIDebuggerInputController.cpp GUIDebuggerInputController.h GUIDebuggerWindow.h
	g++ $(CPPFLAGS) -c GUIDebuggerInputController.cpp `pkg-config --cflags gtkmm-3.0`

GUIDebuggerWindow.o: GUIDebuggerWindow.cpp GUIDebuggerWindow.h
	g++ $(CPPFLAGS) -c GUIDebuggerWindow.cpp `pkg-config --cflags gtkmm-3.0`

clean:
	rm -f *.out *.o alpha_lexer.cpp alpha_parser.cpp alpha_parser.hpp
