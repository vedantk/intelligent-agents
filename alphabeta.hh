/*
 * alphabeta.hh
 * Vedant Kumar <vsk@berkeley.edu>
 */

#ifndef __ALPHABETA__HH
#define __ALPHABETA__HH

#include "maxaction.hh"

/*
 * When designing Arenas that make use of Alphabeta, make sure that
 * generateMoves() orders moves from best to worst (to whatever extent
 * possible). The better the ordering, the faster the search.
 */

class AlphabetaAgent : public MaxActionAgent {
private:
	int alphabeta(int depth, int a, int b, bool doMax) {
		if (depth <= 0) {
			return game->eval(playerSign);
		}
		vector<Action*> moves = game->generateMoves();
		if (!moves.size() || game->doEarlyStop()) {
			return game->eval(playerSign);
		}

		game->switchPlayer();
		for (size_t i=0; i < moves.size(); ++i) {
			Action* move = moves[i];
			game->apply(move);
			int score = alphabeta(depth - 1, a, b, !doMax);
			game->revert(move);
			if (doMax) {
				a = max(a, score);
				if (b <= a) {
					break;
				}
			} else {
				b = min(b, score);
				if (b <= a) {
					break;
				}
			}
		}
		game->switchPlayer();
		deleteAllExcept(moves, NULL);
		return doMax ? a : b;
	}

public:
	AlphabetaAgent(string algo, int maxDepth = 12)
		: MaxActionAgent(algo, maxDepth)
	{}

	int initializeSearch() {
		return alphabeta(depth, -INF, INF, false);
	}
};

#endif
