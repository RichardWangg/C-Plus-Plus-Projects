#include "geesespotter_lib.h"

char *createBoard(std::size_t xdim, std::size_t ydim) {

    char *return_board{new char[xdim*ydim]};

    for (std::size_t i{0}; i<xdim*ydim; i++) {
        return_board[i] = 0b0;
    }

    return return_board;
}

void cleanBoard(char *board) {
    delete[] board;
    board = nullptr;
}

void printBoard(char *board, std::size_t xdim, std::size_t ydim) {

for (int i{0}; i < xdim*ydim; i++) {
    char bits_check;

    bits_check = board[i];

    if ((bits_check >> 4) & 0b1 == 0b1) {
        std::cout << "M";
    } 
    else if ((bits_check >> 5) & 0b1 == 0b1) {
        std::cout << "*";
    } else {
        int bit_checknum;
        bit_checknum = bits_check << 4;
        bit_checknum = bit_checknum >> 4;
        std::cout << bit_checknum;
    }
    
    if ((i+1) % xdim == 0) {
        std::cout << std::endl;
    }
  
}
}

void computeNeighbors(char *board, std::size_t xdim, std::size_t ydim) {
    std::size_t left_column{0};
    std::size_t right_column{xdim-1};

    for (int i{0}; i < (xdim*ydim); i++) {
        std::size_t up_check = i + xdim;
        std::size_t down_check = i - xdim;
        std::size_t num_of_bombs{0};

        if (board[i] == 0) {
            if (i == left_column) {
                if (board[i+1] == 9) {
                    num_of_bombs++;
                }
                if (board[up_check] == 9) {
                    num_of_bombs++;
                }
                if (board[up_check+1] == 9) {
                    num_of_bombs++;
                }
                if (board[down_check] == 9) {
                    num_of_bombs++;
                }
                if (board[down_check+1] == 9) {
                    num_of_bombs++;
                }
                board[i] = num_of_bombs;
            } else if (i == right_column) {
                if (board[i-1] == 9) {
                    num_of_bombs++;
                }
                if (board[up_check] == 9) {
                    num_of_bombs++;
                }
                if (board[up_check-1] == 9) {
                    num_of_bombs++;
                }
                if (board[down_check] == 9) {
                    num_of_bombs++;
                }
                if (board[down_check-1] == 9) {
                    num_of_bombs++;
                }
                board[i] = num_of_bombs;
            } else {
                if (board[i+1] == 9) {
                    num_of_bombs++;
                }
                if (board[i-1] == 9) {
                    num_of_bombs++;
                }
                if (board[up_check] == 9) {
                    num_of_bombs++;
                }
                if (board[up_check+1] == 9) {
                    num_of_bombs++;
                }
                if (board[up_check-1] == 9) {
                    num_of_bombs++;
                }
                if (board[down_check] == 9) {
                    num_of_bombs++;
                }
                if (board[down_check+1] == 9) {
                    num_of_bombs++;
                }
                if (board[down_check-1] == 9) {
                    num_of_bombs++;
                }
                if ((i + 1) % xdim == 0 ) {
                }
                board[i] = num_of_bombs;
            }
        }

        if ((i + 1) % xdim == 0 ) {
            left_column = left_column + xdim;
            right_column = right_column + xdim;
        }
    }
}

void hideBoard(char *board, std::size_t xdim, std::size_t ydim) {
    for (int i{0}; i < xdim*ydim; i++) {
        board[i] = board[i] ^ 0b00100000;
    }
} 

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {
   
   std::size_t check_index;
   std::size_t up_check;
   std::size_t down_check;
   
   for (int i{0}; i < xdim*ydim; i++) {

        if (xdim*yloc == i) {
            check_index = i + xloc;
            up_check = check_index + xdim;
            down_check = check_index - xdim;
        } 
    }
    
    if ((board[check_index] >> 4) == 0b1) {
        return 1;
    } else if ((board[check_index] >> 5) != 0b1) {
        return 2;
    } else if ((board[check_index] & 0b1001) == 0b1001) {
        board[check_index] ^= 0b00100000;
        return 9;
    } else if ((board[check_index] ^ 0b0) == 0b00100000) {
        board[check_index] ^= 0b00100000;
    
        if ((check_index % xdim) == 0) {
            if (((board[check_index + 1] & 0b00010000) == 0b0) && ((board[check_index +1] & 0b00100000) == 0b00100000)) {
                board[check_index + 1] ^= 0b00100000;
            }
            if (((board[up_check] & 0b00010000) == 0b0) && ((board[up_check] & 0b00100000) == 0b00100000)) {
                board[up_check] ^= 0b00100000;
            }
            if (((board[up_check + 1] & 0b00010000) == 0b0) && ((board[up_check +1] & 0b00100000) == 0b00100000)) {
                board[up_check +1] ^= 0b00100000;
            }
            if (((board[down_check] & 0b00010000) == 0b0) && ((board[down_check] & 0b00100000) == 0b00100000)) {
                board[down_check] ^= 0b00100000;
            }
            if (((board[down_check +1] & 0b00010000) == 0b0) && ((board[down_check +1] & 0b00100000) == 0b00100000)) {
            board[down_check +1] ^= 0b00100000;
            }
        } else if (((check_index + 1) % xdim) == 0) {
            if (((board[check_index -1] & 0b00010000) == 0b0) && ((board[check_index -1] & 0b00100000) == 0b00100000)) {
                board[check_index -1] ^= 0b00100000;
            }
            if (((board[up_check] & 0b00010000) == 0b0) && ((board[up_check] & 0b00100000) == 0b00100000)) {
                board[up_check] ^= 0b00100000;
            }
            if (((board[up_check -1] & 0b00010000) == 0b0) && ((board[up_check -1] & 0b00100000) == 0b00100000)) {
                board[up_check -1] ^= 0b00100000;
            }
            if (((board[down_check] & 0b00010000) == 0b0) && ((board[down_check] & 0b00100000) == 0b00100000)) {
                board[down_check] ^= 0b00100000;
            }
            if (((board[down_check -1] & 0b00010000) == 0b0) && ((board[down_check -1] & 0b00100000) == 0b00100000)) {
                board[down_check -1] ^= 0b00100000;
            }
        } else {
            if (((board[check_index + 1] & 0b00010000) == 0b0) && ((board[check_index +1] & 0b00100000) == 0b00100000)) {
                board[check_index + 1] ^= 0b00100000;
            }
            if (((board[check_index -1] & 0b00010000) == 0b0) && ((board[check_index -1] & 0b00100000) == 0b00100000)) {
                board[check_index -1] ^= 0b00100000;
            }
            if (((board[up_check] & 0b00010000) == 0b0) && ((board[up_check] & 0b00100000) == 0b00100000)) {
                board[up_check] ^= 0b00100000;
            }
            if (((board[up_check + 1] & 0b00010000) == 0b0) && ((board[up_check +1] & 0b00100000) == 0b00100000)) {
                board[up_check +1] ^= 0b00100000;
            }
            if (((board[up_check -1] & 0b00010000) == 0b0) && ((board[up_check -1] & 0b00100000) == 0b00100000)) {
                board[up_check -1] ^= 0b00100000;
            }
            if (((board[down_check] & 0b00010000) == 0b0) && ((board[down_check] & 0b00100000) == 0b00100000)) {
                board[down_check] ^= 0b00100000;
            }
            if (((board[down_check +1] & 0b00010000) == 0b0) && ((board[down_check +1] & 0b00100000) == 0b00100000)) {
                board[down_check +1] ^= 0b00100000;
            }
            if (((board[down_check -1] & 0b00010000) == 0b0) && ((board[down_check -1] & 0b00100000) == 0b00100000)) {
                board[down_check -1] ^= 0b00100000;
            }
        }
        return 0;
    } 
    else {
        board[check_index] ^= 0b00100000;
        return 0;
    }
}     


int mark(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {

    int check_index;

    for (int i{0}; i < xdim*ydim; i++) {

        if (xdim*yloc == i) {
            check_index = i + xloc;
            break;
        }

        }
    
    if ((board[check_index] >> 5) != 0b1) {
            return 2;
    } else {
        board[check_index] ^= 0b00010000;
        return 0;
    }
}


bool isGameWon(char *board, std::size_t xdim, std::size_t ydim) {
    int num_bombs{0};
    int tracker{0};

    for (int i{0}; i < xdim*ydim; i++) { 
        if (((board[i] & 0b1001) == 0b1001)) {
            num_bombs++;
        } else if (((board[i] & 0b1001) != 0b1001) && ((board[i] & 0b00100000) == 0b0)) {
            tracker++;
        }
    }

    if ((tracker + num_bombs) == xdim*ydim) {
        return true;
    } else {
        return false;
    }
}