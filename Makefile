CXX = clang++
OPTS = -O3 -g
CXXFLAGS = -Wall -Wextra $(OPTS)

OBJS = arena.hh.gch minimax.hh.gch alphabeta.hh.gch tic-tac-toe

all: $(OBJS)

%.hh.gch: %.hh
	$(CXX) -c $^ $(CXXFLAGS)

arena.hh.gch: arena.hh
minimax.hh.gch: minimax.hh
alphabeta.hh.gch: alphabeta.hh
tic-tac-toe: tic-tac-toe.cc

clean:
	rm -f $(OBJS)
