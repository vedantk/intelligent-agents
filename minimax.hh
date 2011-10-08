/*
 * minimax.hh
 * Vedant Kumar <vsk@berkeley.edu>
 */

#ifndef __MINIMAX__HH
#define __MINIMAX__HH

#include "arena.hh"

#include <algorithm>

const int minimax_depth = 7;

int minimax(Arena* state, int depth, int playerSign, bool doMax) {
	if (depth <= 0) {
		return state->eval(playerSign);
	}

	int alpha = doMax ? -INF : INF;
	vector<Action*> moves = state->generateMoves();
	if (!moves.size()) {
		return state->eval(playerSign);
	}
	for (size_t i=0; i < moves.size(); ++i) {
		Action* move = moves[i];
		state->apply(move);
		int score = minimax(state, depth - 1, -playerSign, !doMax);
		if (doMax) {
			alpha = max(alpha, score);
		} else {
			alpha = min(alpha, score);
		}
		state->revert(move);
	}
	deleteAllExcept(moves, NULL);
	return alpha;
}

class MinimaxAgent : public Agent {
public:
	MinimaxAgent(string algo)
		: Agent(algo)
	{}

	Action* getAction(Arena* state, vector<Action*> moves) {
		Action* best = NULL;
		int best_score = -INF;
		int sign = state->curPlayerSign();
		for (size_t i=0; i < moves.size(); ++i) {
			Action* move = moves[i];
			state->apply(move);
			int score = minimax(state, minimax_depth, -sign, false);
			state->revert(move);
			if (score > best_score) {
				best = move;
				best_score = score;
			}
		}
		return best;
	}
};

#endif
