/*
 * human.hh
 * Vedant Kumar <vsk@berkeley.edu>
 */

#ifndef __HUMAN__HH
#define __HUMAN__HH

#include "arena.hh"

#include <stdio.h>

class HumanAgent : public Agent {
public:
	HumanAgent(string name)
		: Agent(name)
	{}

	Action* getAction(Arena* state, vector<Action*> moves) {
		cout << "Current game state:\n";
		state->show();
		cout << "Pick one of the following options (enter a number):\n";
		for (size_t i=0; i < moves.size(); ++i) {
			cout << i << ") ";
			moves[i]->display();
		}
		cout << "Choice: ";
		size_t idx = 0;
		scanf("%zu", &idx);
		cout << "Processing choice #" << idx << endl;
		return moves[(idx < moves.size()) ? idx : 0];
	}
};

#endif
