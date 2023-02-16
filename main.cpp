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
#include <cmath>
#include <cassert>
using namespace std;

string delta(const string state, const char input);
string decode(const int stateNum);


int main() {
	cout << "-------------TESTING DELTA FUNCTION-------------" << endl;
	cout << "Testing state: \"abacb\"  with in: 'c': " << delta("abacb", 'c') << endl;			// valid state with rejecting input
	cout << "Testing state: \"abacb\"  with in: 'd': " << delta("abacb", 'd') << endl;			// valid state with accepting input
	cout << "Testing state: \"reject\" with in: 'a': " << delta("reject", 'c') << endl;			// already in reject state
	cout << "Testing state: \"aba\"    with in: 'c': " << delta("aba", 'c') << endl;			// state with < 5 symbols
	cout << "Testing state: \"\"       with in: 'a': " << delta("", 'a') << endl;				// empty state
	cout << "Testing state: \"abc\"    with in: 'd': " << delta("abc", 'd') << endl;			// small string with every symbol
	
	cout << "-------------TESTING DECODE FUNCTION-------------" << endl;
	cout << "Testing state num: 641,    should result in: \"bacda\" : " << decode(641) << endl;		// normal test
	cout << "Testing state num: 341,    should result in: \"aaaaa\" : " << decode(341) << endl;		// all a's
	cout << "Testing state num: 6,      should result in: \"ab\"    : " << decode(6) << endl;		// small leading a's
	cout << "Testing state num: 89,     should result in: \"aaba\"  : " << decode(89) << endl;		// medium leading a's
	cout << "Testing state num: 0,      should result in: \"\"      : " << decode(0) << endl;		// empty state
	cout << "Testing state num: 1365,   should result in: \"reject\": " << decode(1365) << endl;		// reject state
	cout << "Testing state num: 1364,   should result in: \"ddddd\" : " << decode(1364) << endl;		// last state
	return 0;
}

//********************************************************************************
// Function: delta
// In: current state, next input
// Return: a resulting state
// DESC: 
// 
// The rule of the DFA is that any substring of length 6 in string w, must have 
// have one of each symbol {a, b, c, d}. 
// 
// Given the current state and next input, the function determines which
// state will result; such as {a, aa, ab, ... , ddddc, ddddd, reject}
//********************************************************************************

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

	// if state is small 
	if (newState.length() < 6)
		return newState;   // accept with current newState
	
	// if all symbols exist in concatenated string
	else if (a && b && c && d)
		return newState.substr(1, 5); // return string that doesn't include first symbol

	// reject everything else
	else
		return "reject";
}

//********************************************************************************
// Function: decode
// In: number corresponding to state
// Return: a state
// DESC: using base 4, with {0, 1, 2, 3} which corresponds to {a, b, c, d}
// one to one maps a number to a specific state of the DFA
//	Note: Accounts for leading a's by subtracting number of states leading 
//  	up to the specific length
//********************************************************************************
string decode(const int stateNum) {
	int temp = stateNum;		
	int L;						// length
	vector <int> remainders;	// store numerical remainders
	string resState = "";		// store string corresponding to remainders

	// find length
	if (stateNum == 1365)	// reject state
		return "reject";
	else if (stateNum == 0)	// empty state
		return "";
	else if (stateNum >= 1 && stateNum <= 4)
		L = 1;
	else if (stateNum >= 5 && stateNum <= 20)
		L = 2;
	else if (stateNum >= 21 && stateNum <= 84)
		L = 3;
	else if (stateNum >= 85 && stateNum <= 340)
		L = 4;
	else if (stateNum >= 341 && stateNum <= 1364)
		L = 5;
	else {
		cerr << "\nERROR: stateNum is too large. Terminating...\n";
		exit(1);
	}


	// subtract to account for leading a's
	for (int i = 0; i < L; i++) {
		temp -= pow(4, i);
	}

	// push remainders onto vector
	for (int i = 0; i < L; i++) {
		remainders.push_back(temp % 4);
		temp /= 4;
	}

	// convert vecotr of remainders to symbols but in reverse order
	for (int i = remainders.size() - 1; i >= 0; i--) {
		if (remainders[i] == 0)
			resState += 'a';
		else if (remainders[i] == 1)
			resState += 'b';
		else if (remainders[i] == 2)
			resState += 'c';
		else
			resState += 'd';
	}

	return resState;

}
