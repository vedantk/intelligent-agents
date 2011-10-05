/*
 * minimax.hh
 * Vedant Kumar <vsk@berkeley.edu>
 */

#ifndef __MINIMAX__HH
#define __MINIMAX__HH

#include "arena.hh"

#include <map>
#include <algorithm>

const int minimax_depth = 10;

int minimax(Arena* state, int depth, int playerSign) {
	if (depth <= 0) {
		return state->eval();
	}

	int alpha = -playerSign * INF;
	vector<Action*> moves = state->generateMoves();
	if (!moves.size()) {
		return state->eval();
	}
	for (size_t i=0; i < moves.size(); ++i) {
		Action* move = moves[i];
		state->apply(move);
		int score = minimax(state, depth - 1, -playerSign);
		state->revert(move);
		if (playerSign > 0) {
			alpha = max(alpha, score);
		} else {
			alpha = min(alpha, score);
		}
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
		vector<int> scores;
		map<int, Action*> scoreMoveMap;
		int sign = state->curPlayerSign();
		for (size_t i=0; i < moves.size(); ++i) {
			Action* move = moves[i];
			state->apply(move);
			int score = minimax(state, minimax_depth, -sign);
			state->revert(move);
			scores.push_back(score);
			scoreMoveMap[score] = move;
		}
		int target;
		if (sign > 0) {
			target = *max_element(scores.begin(), scores.end());
		} else {
			target = *min_element(scores.begin(), scores.end());
		}
		return scoreMoveMap[target];
	}
};

#endif
