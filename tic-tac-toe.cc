/*
 * tic-tac-toe.cc
 * Vedant Kumar <vsk@berkeley.edu>
 */

#include "random.hh"
#include "minimax.hh"
#include "alphabeta.hh"
#include "human.hh"

#include <string.h>

class TTTAction : public Action {
public:
	int posn, owner;

	TTTAction(int loc, int player)
		: posn(loc), owner(player)
	{}

	void display() {
		cout << (owner > 0 ? "X" : "O") << " to " << posn << "\n";
	}
};

class TTTArena : public Arena {
private:
	/* Each cell in the game array represents a cell on a tic-tac-toe
	 * board. The cell's sign indicates ownership: -1 (min), 0 (empty),
	 * and 1 (max). This representation makes scoring very simple. */
	int game[9];

public:
	TTTArena(Agent* a, Agent* b)
		: Arena(a, b)
	{
		memset(&game, 0, sizeof(int) * 9);
	}

	void apply(Action* move) {
		TTTAction* act = static_cast<TTTAction*>(move);
		game[act->posn] = act->owner;
	}

	void revert(Action* move) {
		TTTAction* act = static_cast<TTTAction*>(move);
		game[act->posn] = 0;
	}

	int eval(int playerSign) {
		/* If a win exists, return its utility for curPlayer. */
		#define CELL(row, col) game[rows[row][col]]
		static int rows[][3] = {
			{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, /* rows */
			{0, 3, 6}, {1, 4, 7}, {2, 5, 8}, /* cols */
			{0, 4, 8}, {2, 4, 6}, /* diagonals */
		};

		#define ALL_EQUAL(a, b, c) ((a == b) && (b == c))
		for (size_t i=0; i < sizeof(rows)/sizeof(rows[0]); ++i) {
			if (CELL(i, 0) != 0
                            && ALL_EQUAL(CELL(i, 0), CELL(i, 1), CELL(i, 2)))
			{
				return (CELL(i, 0) == playerSign) ? 1 : -1;
			}
		}

		return 0;
		#undef CELL
		#undef ALL_EQUAL
	}

	vector<Action*> generateMoves() {
		vector<Action*> moves;
		int owner = curPlayerSign();
		if (eval(owner) != 0) {
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

	void show() {
		for (int i=0; i < 9; ++i) {
			switch (game[i]) {
				case 0: cout << " "; break;
				case 1: cout << "X"; break;
				case -1: cout << "O"; break;
			}
			cout << "|";
			if ((i+1) % 3 == 0) {
				cout << endl;
			}
		}
		cout << endl;
	}
};

int main() {
	MinimaxAgent p1("Minimax-1");
	MinimaxAgent p2("Minimax-2");
	TTTArena game(&p1, &p2);
	game.run();
	game.printHistory();

	AlphabetaAgent p3("Alphabeta-1");
	TTTArena game2(&p1, &p3);
	game2.run();
	game2.printHistory();

	AlphabetaAgent p4("Alphabeta-2");
	TTTArena game3(&p3, &p4);
	game3.run();
	game3.printHistory();

	RandomAgent p5("RandomPlayer-1");
	TTTArena game4(&p1, &p5);
	game4.run();
	game4.printHistory();

	TTTArena game5(&p3, &p1);
	game5.run();
	game5.printHistory();

	HumanAgent p6("Human Challenger");
	TTTArena game6(&p5, &p6);
	game6.run();
	game6.printHistory();

	TTTArena game7(&p6, &p4);
	game7.run();
	game7.printHistory();

	return 0;
}
