/*
 * Project 1: DFA counting
 * main.cpp
 * Sean Sponsler, Evan Walters
 * Feburary 17th, 2023
 * Description:
 */

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

string delta(const string state, const char input);


int main() {

	cout << "Testing state: \"abacb\"  with in: 'c': " << delta("abacb", 'c') << endl;		// valid state with rejecting input
	cout << "Testing state: \"abacb\"  with in: 'd': " << delta("abacb", 'd') << endl;		// valid state with accepting input
	cout << "Testing state: \"reject\" with in: 'a': " << delta("reject", 'c') << endl;		// already in reject state
	cout << "Testing state: \"aba\"    with in: 'c': " << delta("aba", 'c') << endl;		// state with < 5 symbols
	cout << "Testing state: \"\"       with in: 'a': " << delta("", 'a') << endl;			// empty state
	return 0;
}

string delta(const string state, const char input) {

	// cant get states with > 5 symbols, unless it's the rejecting state
	assert(state.length() <= 5 || state == "reject");
	assert(input == 'a' || input == 'b' || input == 'c' || input == 'd');

	// reject if already in rejecting state
	if (state == "reject") return "reject";


	string newState = state + input;	// concatenate input symbol to current state
	bool a = 0, b = 0, c = 0, d = 0;	// initialize a bool for each letter


	// check 6 length string and get bool for each letter
	for (int i = 0; i < newState.length(); i++) {
		if (newState[i] == 'a') a = 1;
		else if (newState[i] == 'b') b = 1;
		else if (newState[i] == 'c') c = 1;
		else if (newState[i] == 'd') d = 1;
		else {
			cerr << "\nERROR: State houses incorrent symbol. Terminating...\n";
			exit(1);
		}
	}


	// if all symbols exist in concatenated string
	if (a && b && c && d)
		return newState.substr(1, 5); // return string that doesn't include first symbol

	// if state is small 
	else if (newState.length() < 6)
		return newState;   // accept with current newState

	// reject everything else
	else
		return "reject";
}
