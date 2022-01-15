#include <stdio.h>
#include <stdlib.h>
#include "ttt.h"

int main(int argc, char ** argv) {

	//Initialize boards and the first board
	init_boards();
	init_board(START_BOARD);
	join_graph(START_BOARD);
	compute_score();

	for (int i = 1; i < argc; i++) {
		int index = atoi(argv[i]);
		print_node(htable[index]);
	}
}
