/*
 * arena.hh
 * Vedant Kumar <vsk@berkeley.edu>
 */

#ifndef __ARENA__HH
#define __ARENA__HH

#include <vector>
#include <string>
#include <iostream>
#include <climits>

#define INF (INT_MAX - 1)

using namespace std;

class Arena;
class Agent;
class Action;

class Action {
public:
	virtual ~Action() {};
	virtual void display() = 0;
};

/* Free useless Action objects to reclaim the memory. */
void deleteAllExcept(vector<Action*> moves, Action* keep) {
	for (size_t i=0; i < moves.size(); ++i) {
		if (moves[i] != keep) {
			delete moves[i];
		}
	}
}

class Agent {
public:
	string name;

	Agent(string algo)
		: name(algo)
	{}

	virtual ~Agent() {};

	/* Find the optimal Action. */
	virtual Action* getAction(Arena* state, vector<Action*> moves) = 0;
};

class Arena {
public:
	Agent* amax; /* The MAX player. */
	Agent* amin; /* The MIN player. */
	Agent* curPlayer; /* The current player. */
	vector<Action*> history; /* The move history. */

	Arena(Agent* a, Agent* b)
		: amax(a), amin(b), curPlayer(a)
	{}

	virtual ~Arena() {};

	/* Apply an action to the state. */
	virtual void apply(Action* move) = 0;

	/* Revert the effects of an action. */
	virtual void revert(Action* move) = 0;

	/* Calculate state utility from curPlayer's point of view. */
	virtual int eval(int playerSign) = 0;

	/* Generate all possible moves for the current player. */
	virtual vector<Action*> generateMoves() = 0;

	/* Sometimes it's useful to end a simulation early. */
	virtual bool doEarlyStop() = 0;

	/* Display the current state. */
	virtual void show() = 0;

	/* Update the game state so that the next player can move. */
	void switchPlayer() {
		curPlayer = (curPlayer == amax) ? amin : amax;
	}

	/* Carry out a complete simulation, return true if amax wins. */
	bool run() {
		while (!doEarlyStop()) {
			vector<Action*> moves = generateMoves();
			Agent* other = (curPlayer == amax) ? amin : amax;
			if (!moves.size()) {
				cout << other->name << " wins (opponent has no moves).\n";
				return other == amax;
			}
			Action* move = curPlayer->getAction(this, moves);
			apply(move);
			history.push_back(move);
			switchPlayer();
			deleteAllExcept(moves, move);
		}
		/* The player who forces an early stop wins. */
		cout << curPlayer->name << " loses.\n";
		return -curPlayerSign() > 0;
	}

	/* Print out the history of accepted moves. Call once per run. */
	void printHistory() {
		cout << "--- Playing back game history. ---\n";
		Agent* cur = amax;
		for (size_t i=0; i < history.size(); ++i) {
			Action* move = history[i];
			cout << "[" << cur->name << ": " << i << "] ";
			move->display();
			cur = (cur == amax) ? amin : amax;
			delete move;
		}
		cout << endl;
	}

	/* Determine the numeric sign of the current player. */
	int curPlayerSign() {
		return (curPlayer == amax) ? 1 : -1;
	}
};

#endif
