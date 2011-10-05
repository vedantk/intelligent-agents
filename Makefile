CXX = clang++
OPTS = -O3 -g
CXXFLAGS = -Wall -Wextra $(OPTS)

OBJS = arena.hh.gch minimax.hh.gch tic-tac-toe

all: $(OBJS)

%.hh.gch: %.hh
	$(CXX) -c $^ $(CXXFLAGS)

arena.hh.gch: arena.hh
minimax.hh.gch: minimax.hh
tic-tac-toe: tic-tac-toe.cc

clean:
	rm -f $(OBJS)
