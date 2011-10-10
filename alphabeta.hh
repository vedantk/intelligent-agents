/*
 * alphabeta.hh
 * Vedant Kumar <vsk@berkeley.edu>
 */

#ifndef __ALPHABETA__HH
#define __ALPHABETA__HH

#include "arena.hh"

#include <algorithm>

/*
 * When designing Arenas that make use of Alphabeta, make sure that
 * generateMoves() orders moves from best to worst (to whatever extent
 * possible). The better the ordering, the faster the search.
 */

/*
 * Alphabeta currently seems to be picking the rightmost branch of the
 * possible move-set every single time. Why?
 */

const int alphabeta_depth = 12;

int alphabeta(Arena* state, int depth, int a, int b, int playerSign) {
	if (depth <= 0) {
		return state->eval(playerSign);
	}

	vector<Action*> moves = state->generateMoves();
	if (!moves.size()) {
		return state->eval(playerSign);
	}
	for (size_t i=0; i < moves.size(); ++i) {
		Action* move = moves[i];
		state->apply(move);
		int score = alphabeta(state, depth - 1, a, b, -playerSign);
		state->revert(move);
		if (playerSign > 0) {
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
	deleteAllExcept(moves, NULL);
	return (playerSign > 0) ? a : b;
}

class AlphabetaAgent : public Agent {
public:
	AlphabetaAgent(string algo)
		: Agent(algo)
	{}

	Action* getAction(Arena* state, vector<Action*> moves) {
		Action* best = NULL;
		int alpha = -INF, beta = INF;
		int sign = state->curPlayerSign();
		for (size_t i=0; i < moves.size(); ++i) {
			Action* move = moves[i];
			state->apply(move);
			int score = alphabeta(state, alphabeta_depth, alpha, beta, -sign);
			state->revert(move);
			if (sign > 0) {
				alpha = max(alpha, score);
				best = (score == alpha) ? move : best;
			} else {
				beta = min(beta, score);
				best = (score == beta) ? move : best;
			}
		}
		return best;
	}
};

#endif
