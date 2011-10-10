/*
 * minimax.hh
 * Vedant Kumar <vsk@berkeley.edu>
 */

#ifndef __MINIMAX__HH
#define __MINIMAX__HH

#include "maxaction.hh"

class MinimaxAgent : public MaxActionAgent {
private:
	int minimax(int depth, bool doMax) {
		if (depth <= 0) {
			return game->eval(playerSign);
		}
		vector<Action*> moves = game->generateMoves();
		if (!moves.size() || game->doEarlyStop()) {
			return game->eval(playerSign);
		}

		game->switchPlayer();
		int alpha = doMax ? -INF : INF;
		for (size_t i=0; i < moves.size(); ++i) {
			Action* move = moves[i];
			game->apply(move);
			int score = minimax(depth - 1, !doMax);
			game->revert(move);
			if (doMax) {
				alpha = max(alpha, score);
			} else {
				alpha = min(alpha, score);
			}
		}
		game->switchPlayer();
		deleteAllExcept(moves, NULL);
		return alpha;
	}

public:
	MinimaxAgent(string algo, int maxDepth = 10)
		: MaxActionAgent(algo, maxDepth)
	{}

	int initializeSearch() {
		return minimax(depth, false);
	}
};

#endif
