/*
 * tic-tac-toe.cc
 * Vedant Kumar <vsk@berkeley.edu>
 */

#include "arena.hh"
#include "minimax.hh"
#include "alphabeta.hh"

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
		/* Any decent compiler will unroll and combine these loops. */
		for (int row=0; row < 3; ++row) {
			int off = row * 3;
			if (game[off] != 0 && (game[off] == game[off+1] == game[off+2])) {
				return INF * game[off];
			}
		}

		for (int col=0; col < 3; ++col) {
			if (game[col] != 0 && (game[col] == game[col+3] == game[col+6])) {
				return INF * game[col];
			}
		}

		if (game[0] != 0 && (game[0] == game[4] == game[8])) {
			return INF * game[0];
		}

		if (game[2] != 0 && (game[2] == game[4] == game[6])) {
			return INF * game[2];
		}

		int score = 0;
		for (int i=0; i < 9; ++i) {
			score += game[i];
		}
		return score;
	}

	vector<Action*> generateMoves() {
		vector<Action*> moves;
		int owner = curPlayerSign();
		if (eval() == -INF * owner) {
			/* If the other player has already won... */
			return moves;
		}

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

	AlphabetaAgent p3("Player C");
	TTTArena game2(&p1, &p3);
	game2.run();
	game2.printHistory();

	AlphabetaAgent p4("Player D");
	TTTArena game3(&p3, &p4);
	game3.run();
	game3.printHistory();

	return 0;
}
