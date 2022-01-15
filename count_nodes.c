#include <stdio.h>
#include <stdlib.h>
#include "ttt.h"

int main(int argc, char ** argv) {
	/* Uses init_board, init_board(START_BOARD), and join_graph(START_BOARD) and count the # of entries in the htable that have
	init == 1*/

	int count = 0;
	init_boards();
	init_board(START_BOARD);
	join_graph(START_BOARD);

	for (int i = 0; i < HSIZE; i++) {
		if (htable[i].init == 1) {
			count++;
		}
	}
	printf("The count = %d\n", count);
}
