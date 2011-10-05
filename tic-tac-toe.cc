/*
 * tic-tac-toe.cc
 * Vedant Kumar <vsk@berkeley.edu>
 */

#include "arena.hh"
#include "minimax.hh"

#include <stdio.h>
#include <string.h>

class TTTAction : public Action {
public:
	int posn, owner;

	TTTAction(int loc, int player)
		: posn(loc), owner(player)
	{}

	string toString() {
		char buf[4];
		sprintf(buf, "%d", posn);
		return string(owner > 0 ? "X" : "O") + " to " + string(buf);
	}
};

class TTTArena : public Arena {
public:
	/* Each cell in the game array represents a cell on a tic-tac-toe
	 * board. The cell's sign indicates ownership: -1 (min), 0 (empty),
	 * and 1 (max). This representation makes scoring very simple. */
	int game[9];

	TTTArena(Agent* a, Agent* b)
		: Arena(a, b)
	{
		memset((void*) &game, 0, sizeof(int) * 9);
	}

	void apply(Action* move) {
		TTTAction* act = static_cast<TTTAction*>(move);
		game[act->posn] = act->owner;
	}

	void revert(Action* move) {
		TTTAction* act = static_cast<TTTAction*>(move);
		game[act->posn] = 0;
	}

	int eval() {
		int score = 0;
		for (int i=0; i < 9; ++i) {
			score += game[i];
		}
		return score;
	}

	vector<Action*> generateMoves() {
		vector<Action*> moves;
		int owner = curPlayerSign();
		for (int i=0; i < 9; ++i) {
			if (game[i] == 0) {
				TTTAction* move = new TTTAction(i, owner);
				moves.push_back(move);
			}
		}
		return moves;
	}

	bool doEarlyStop() {
		return false;
	}
};

int main() {
	MinimaxAgent p1("Player A");
	MinimaxAgent p2("Player B");
	TTTArena game(&p1, &p2);
	game.run();
	game.printHistory();
	return 0;
}

