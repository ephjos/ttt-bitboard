/*
 * Implementation of CLI tic-tac-toe using bitboards. Refer to
 * "Bitboard Methods for Games" by Cameron Browne for more details.
 *
 * The board is mapped to the keypad structure:
 *
 * 7 8 9
 * 4 5 6
 * 1 2 3
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Game state
typedef struct state_t {
	short bits_x;
	short bits_o;
	bool turn;
} state_t;

// We use the least significant 9 bits, maps to layout like: 0b987654321
static const short mask = 0b111111111;

// Masks to match win conditions
static const short row_0 = 0b111000000;
static const short row_1 = 0b000111000;
static const short row_2 = 0b000000111;
static const short col_0 = 0b001001001;
static const short col_1 = 0b010010010;
static const short col_2 = 0b100100100;
static const short dia_0 = 0b001010100;
static const short dia_1 = 0b100010001;

void print_state(state_t s)
{
	printf("\n");
	for (int i = 2; i >= 0; i--) {
		for (int j = 0; j < 3; j++) {
			short mask = 1 << ((i*3) + j);
			char c = (s.bits_x & mask) ? 'X' : (s.bits_o & mask) ? 'O' : '-';
			printf("|%c", c);
		}
		printf("|\n");
	}
}

int main(int argc, char** argv)
{
	state_t state = {0};

	// Loop while there are still open spaces on the board
	while (~(state.bits_x | state.bits_o) & mask) {
		print_state(state);

		// Get turn specific information
		char turn_c = state.turn ? 'O' : 'X';
		short *turn_bits = state.turn ? &state.bits_o : &state.bits_x;

		// Prompt user for move
		printf("%c turn > ", turn_c);
		short move = getchar();

		// Verify input is 1-9
		if (move < 49 || move > 57) {
				printf("Unknown move, please try again\n");
				// Clear buffer
				if (move != '\n') {
					while((getchar()) != '\n');
				}
				continue;
		}

		// Map from input to mask for move
		short move_mask = 1 << (move-49);

		// Check if cell is already taken
		if ((state.bits_x | state.bits_o) & move_mask) {
				printf("Cell already taken, please try again\n");
				// Clear buffer
				if (move != '\n') {
					while((getchar()) != '\n');
				}
				continue;
		}

		// Apply the move
		*turn_bits = *turn_bits | move_mask;

		// Check if current player won
		if (
				((row_0 & *turn_bits) == row_0) |
				((row_1 & *turn_bits) == row_1) |
				((row_2 & *turn_bits) == row_2) |
				((col_0 & *turn_bits) == col_0) |
				((col_1 & *turn_bits) == col_1) |
				((col_2 & *turn_bits) == col_2) |
				((dia_0 & *turn_bits) == dia_0) |
				((dia_1 & *turn_bits) == dia_1)
			 ) {
			print_state(state);
			printf("%c wins!\n", turn_c);
			return 0;
		}

		// Give turn to next player
		state.turn = !state.turn;

		// Clear buffer
		while((getchar()) != '\n');
	}

	// There are no empty spaces on the board and nobody won
	print_state(state);
	printf("Tie!\n");

	return 0;
}
