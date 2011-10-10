CXX = clang++
OPTS = -O3 -g
CXXFLAGS = -Wall -Wextra $(OPTS)

OBJS = arena.hh.gch maxaction.hh.gch random.hh.gch \
       minimax.hh.gch alphabeta.hh.gch human.hh.gch tic-tac-toe

all: $(OBJS)

%.hh.gch: %.hh
	$(CXX) -c $^ $(CXXFLAGS)

arena.hh.gch: arena.hh
maxaction.hh.gch: maxaction.hh
random.hh.gch: random.hh
minimax.hh.gch: minimax.hh
alphabeta.hh.gch: alphabeta.hh
human.hh.gch: human.hh
tic-tac-toe: tic-tac-toe.cc

clean:
	rm -f $(OBJS)

redo: clean all
