CFLAGS = -Wall -std=c++17 -O3
LDFLAGS = -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2 -D_THREAD_SAFE 
BIN_NAME = farsoft_renderer


all: *.cpp 
	g++ $(CFLAGS) -o $(BIN_NAME) *.cpp $(LDFLAGS)

debug: main.cpp
	g++ -O0 -g -o $(BIN_NAME) *.cpp $(LDFLAGS)

clean:
	rm -f $(BIN_NAME)
