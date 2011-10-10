/*
 * minimax.hh
 * Vedant Kumar <vsk@berkeley.edu>
 */

#ifndef __MINIMAX__HH
#define __MINIMAX__HH

#include "arena.hh"

#include <algorithm>

const int minimax_depth = 10;

class MinimaxAgent : public Agent {
private:
	Arena* game;
	int playerSign;

	int minimax(int depth, bool doMax) {
		if (depth <= 0) {
			return game->eval(playerSign);
		}

		int alpha = doMax ? -INF : INF;
		vector<Action*> moves = game->generateMoves();
		if (!moves.size()) {
			return game->eval(playerSign);
		}
		for (size_t i=0; i < moves.size(); ++i) {
			Action* move = moves[i];
			game->apply(move);
			int score = minimax(depth - 1, !doMax);
			if (doMax) {
				alpha = max(alpha, score);
			} else {
				alpha = min(alpha, score);
			}
			game->revert(move);
		}
		deleteAllExcept(moves, NULL);
		return alpha;
	}

public:
	MinimaxAgent(string algo)
		: Agent(algo)
	{}

	Action* getAction(Arena* state, vector<Action*> moves) {
		game = state;
		Action* best = NULL;
		int best_score = -INF;
		playerSign = state->curPlayerSign();
		for (size_t i=0; i < moves.size(); ++i) {
			Action* move = moves[i];
			state->apply(move);
			int score = minimax(minimax_depth, false);
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
