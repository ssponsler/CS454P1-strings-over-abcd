/*
 * Project 1: DFA counting
 * main.cpp
 * Sean Sponsler, Evan Walters
 * Feburary 17th, 2023
 * Description: This program takes the given DFA and counts 
 * the number of strings of length N that are accepted by the DFA.
 * 
 * DFA: Given string w of length N, using the alphabet = {a, b, c, d}, 
 * any substring of length 6 in string w, must have 
 * one of each symbol {a, b, c, d}. Strings less than length 6 are accepted.
 */

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cassert>
using namespace std;

int delta(const int state, const int input);
string decode(const int stateNum);
int encode(const string state);
long long int count(const int N);


int main() {

	int N;

	// get number of strings

	cout << "Input a length N (1-300) to find the amount of possible strings for the DFA: ";

	cin >> N;

	cout << endl << "The number of valid string so of length " << N << " for the DFA is: " << count(N) << endl;

	return 0;
}

//********************************************************************************
// Function: delta
// In: current state index, next input number
// Return: a resulting state number
// DESC: 
// Frist off, 
// the state and symbol numbers are decoded back into a string and a char.
// Later on return they are encoded again.
// 
// The rule of the DFA is that any substring of length 6 in string w, must have 
// have one of each symbol {a, b, c, d}. 
// 
// Given the current state and next input, the function determines which
// state will result; such as {a, aa, ab, ... , ddddc, ddddd, reject}
//********************************************************************************

int delta(const int stateNum, const int symbolNum) {

	// decode given statenum and symbolnum into their string and char counter parts
	const string state = decode(stateNum);
	char input;

	switch (symbolNum) {
		case 0: input = 'a';
			break;
		case 1: input = 'b';
			break;
		case 2: input = 'c';
			break;
		case 3: input = 'd';
			break;
	}


	// cant get states with > 5 symbols, unless it's the rejecting state
	assert(state.length() <= 5 || state == "reject");
	assert(input == 'a' || input == 'b' || input == 'c' || input == 'd');

	// reject if already in rejecting state
		if (state == "reject") {
			return encode("reject");
		}


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
		return encode(newState);   // accept with current newState

	// if all symbols exist in concatenated string
	else if (a && b && c && d)
		return encode(newState.substr(1, 5)); // return string that doesn't include first symbol

	// reject everything else
	else
		return encode("reject");
}

//********************************************************************************
// Function: decode
// In: number corresponding to state
// Return: a state
// DESC: using base 4, with {0, 1, 2, 3} which corresponds to {a, b, c, d} and
// one to one maps a number to a specific state of the DFA. This function 
// converts a base 4 number into a state.
//	Note: Accounts for leading a's by subtracting number of states leading 
//  up to the specific length
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

//********************************************************************************
// Function: encode
// In: string state
// Return: number refering to state
// DESC: Using base 4, with {0, 1, 2, 3} which corresponds to {a, b, c, d} and
// one to one maps a number to a specific state of the DFA. This functions 
// converts the state into a base 4 number.
//	Note: Accounts for leading a's by adding number of states leading 
//  up to the specific length
//********************************************************************************
int encode(string s) {
	int encodedInt = 0;

	// in case string is reject state
	if (s == "reject") return 1365;

	for (int i = 0; i < s.length(); i++) {
		int exp = s.length() - (i + 1);
		switch (s[i]) {
			case 'a':
				//0
				encodedInt += (0 * pow(4, exp));
				break;
			case 'b':
				//1
				encodedInt += (1 * pow(4, exp));
				break;
			case 'c':
				//2
				encodedInt += (2 * pow(4, exp));
				break;
			case 'd':
				//3
				encodedInt += (3 * pow(4, exp));
				break;
		}
		//need to add positional offset
		encodedInt += pow(4, i);
	}
	return encodedInt;
}


//********************************************************************************
// Function: count
// In: Length of arbitrary string 
// Return: number of strings of length N (0-300) that are accepted by the DFA
// DESC: counts number of strings that are accepted by DFA starting from 0 to N
//********************************************************************************
long long int count(const int N) {
	const int SIZE = 1366;
	long long int current[SIZE];
	long long int next [SIZE] = {0};

	// assign 1 to every pos in current except the last pos
	for (int i = 0; i < SIZE; i++) {
		current[i] = 1;
	}

	// for "reject" state
	current[SIZE - 1] = 0;
	

	// loop for given size 
	for (int n = 0; n < N; n++) {

		// double loop to look at every input(j) for each state(i)
		for (int i = 0; i < SIZE; i++) {
			for (int j = 0; j < 4; j++) {
				next[i] += current[delta(i, j)];
			}
		}

		// copy next into current and reset next
		for (int k = 0; k < SIZE; k++) {
			current[k] = next[k];
			next[k] = 0;
		}
		
	}

	return current[0];
}
