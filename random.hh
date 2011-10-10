/*
 * random.hh
 * Vedant Kumar <vsk@berkeley.edu>
 */

#ifndef __RANDOM__HH
#define __RANDOM__HH

#include "arena.hh"

#include <stdlib.h>

class RandomAgent : public Agent {
public:
	RandomAgent(string algo)
		: Agent(algo)
	{
		srand(time(NULL));
	}

	Action* getAction(Arena* state, vector<Action*> moves) {
		return moves[(rand() + state->curPlayerSign()) % moves.size()];
	}
};

#endif	
