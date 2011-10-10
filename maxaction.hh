/*
 * maxaction.hh
 * Vedant Kumar <vsk@berkeley.edu>
 */

#ifndef __MAXACTION__HH
#define __MAXACTION__HH

#include "arena.hh"

#include <algorithm>

class MaxActionAgent : public Agent {
protected:
	Arena* game;
	int playerSign;
	int depth;

public:
	MaxActionAgent(string algo, int maxDepth = 12)
		: Agent(algo), depth(maxDepth)
	{}

	virtual int initializeSearch() = 0;

	Action* getAction(Arena* state, vector<Action*> moves) {
		game = state;
		Action* best = NULL;
		int best_score = -INF;
		playerSign = state->curPlayerSign();
		game->switchPlayer();
		for (size_t i=0; i < moves.size(); ++i) {
			Action* move = moves[i];
			state->apply(move);
			int score = initializeSearch();
			state->revert(move);
			if (score > best_score) {
				best = move;
				best_score = score;
			}
		}
		game->switchPlayer();
		return best;
	}
};

#endif
