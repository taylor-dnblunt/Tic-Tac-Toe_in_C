#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ttt.h"

void init_boards() {
	//Go through entire htable and set init to 0
	for (int i = 0; i < HSIZE; i++) {
		htable[i].init = 0;
	}
}

int depth(Board board) { //refers to the depth of the graph/how many turns have been played/a depth of 0 is no turns played
	//Returns number of X's and O's on board
	char c = board[0];
	int count = 0;
	int depthCount = 0;
	while (c != '\0') {
		if ((c == 'X') || (c == 'O')) {
			depthCount++;
		}
		count++;
		c = board[count];
	}
	return depthCount;
}

char winner(Board board) {
	//Go through wins array
	for (int i = 0; i < 8; i++) {
		if ((board[pos2idx[WINS[i][0]]] == 'X')  && (board[pos2idx[WINS[i][1]]] == 'X') && (board[pos2idx[WINS[i][2]]] == 'X')) {
			return 'X';
		}
		if ((board[pos2idx[WINS[i][0]]] == 'O')  && (board[pos2idx[WINS[i][1]]] == 'O') && (board[pos2idx[WINS[i][2]]] == 'O')) {
			return 'O';
		}
	}
	//if its neither of the above if statements the game is either over and a draw '-' or the game is incomplete '?'
	if (depth(board) == 9) {
		return '-';
	}
	return '?';
}

char turn(Board board) {
	//X if x's turn, O if o's turn, - if the game is over
	if (depth(board) == 9 || winner(board) == 'X' || winner(board) == 'O') {
		return '-';
	}
	if (depth(board) % 2 == 0) {
		return 'X';
	}
	//if neither of the above if statements trigger then it is O's turn
	return 'O';
}

void init_board(Board board) {
	/*Compute hash index using board_hash in ttt1.c then use the structure in that index to initialize all the values
	using previous functions*/
	int bHash = board_hash(board);
	htable[bHash].init = 1;
	htable[bHash].turn = turn(board);
	htable[bHash].depth = depth(board);
	strcpy(htable[bHash].board, board);
	htable[bHash].winner = winner(htable[bHash].board);
}

void join_graph(Board board) {

	Board tempBoard;

	for (int i = 0; i < 9; i++) {
		int bHash = board_hash(board);
		if (board[pos2idx[i]] == 'X' || board[pos2idx[i]] == 'O' || turn(board) == '-') {
			htable[bHash].move[i] = -1;
		} else { //The board position is not an X or O and must be a number
			strcpy(tempBoard, board);

			//Place who's turn it is into the after board
			tempBoard[pos2idx[i]] = turn(board);

			//Set the current indices move to be the after board
			int tempHash = board_hash(tempBoard);
			htable[bHash].move[i] = tempHash;

			//Begin recursion if its a new board
			if (htable[tempHash].init == 0) {
				init_board(tempBoard);
				join_graph(tempBoard);
			}
		}
	}
}

void compute_score() {
	for (int i = 9; i > 0; i--) {
		//Go through entire hash table 9 times
		//Each time you go through the hash table ignore nodes not at that specific depth
		for (int j = 0; j < HSIZE; j++) {
			//Go through all nodes at the depth i and init 1
			if(htable[j].depth == i && htable[j].init == 1) {
				if (htable[j].winner == 'X') {
					htable[j].score = 1;
				} else if (htable[j].winner == 'O') {
					htable[j].score = -1;
				} else if (htable[j].winner == '-') {
					htable[j].score = 0;
				}
				if (htable[j].winner == '?') {//Else winner = '?' and winner is determined from move array

					int max = -100;
					int min = 100;
					for (int k = 0; k < 9; k++) { //Go through move array and check for min and max
						if (htable[j].move[k] != -1) {
							if (htable[htable[j].move[k]].score > max) {
								max = htable[htable[j].move[k]].score;
							}
							if (htable[htable[j].move[k]].score < min) {
								min = htable[htable[j].move[k]].score;
							}
						}
					}
					if (htable[j].turn == 'X') {
						//Take max score
						htable[j].score = max;
					}
					if (htable[j].turn == 'O') {
						//Take min score
						htable[j].score = min;
					}
				}
			}
		}
	}
}

int best_move(int board) {
	//Returns the best possible move position based on scores
	int maxMove = -100;
	int minMove = 100;
	int move = 0;

	//Go through move array
	for (int i = 0; i < 9; i++) {
		//Only go through moves that are not taken
		if (htable[board].move[i] != -1) {
			//Use minimum score for O's
			if (htable[board].turn == 'O') {
				if (htable[htable[board].move[i]].score < minMove) {
					minMove = htable[htable[board].move[i]].score;
					move = i;
				}
			}
			//Use maximum score for X's
			if (htable[board].turn == 'X') {
				if (htable[htable[board].move[i]].score > maxMove) {
					maxMove = htable[htable[board].move[i]].score;
					move = i;
				}
			}
		}
	}
	return move;
}


