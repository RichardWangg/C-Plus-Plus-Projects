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

    for (int i{0}; i < xdim*ydim; i++) {
        int num_of_bombs{0};
        int up_check = i + xdim;
        int down_check = i - xdim;

        if (board[i] == 0) {
                if ((board[i-1] == 9) && ((i-1) >= 0)) {
                    num_of_bombs++;
                } 
                if ((board[i+1] == 9) && ((i+1) <= xdim*ydim)) {
                    num_of_bombs++;
                } 
                if ((board[up_check] == 9) && (up_check <= xdim*ydim)) {
                    num_of_bombs++;
                }
                if ((board[up_check+1] == 9) && ((up_check + 1) <= xdim*ydim)) {
                    num_of_bombs++;
                }
                if ((board[up_check-1] == 9) && ((up_check <= xdim*ydim)) && ((up_check - 1) != (i+(xdim-1)))) {
                    num_of_bombs++;
                }
                if ((board[down_check] == 9) && (down_check >= 0)) {
                    num_of_bombs++;
                }
                if ((board[down_check+1] == 9) && (down_check >= 0) && ((down_check+1) != (i -(xdim-1)))) {
                    num_of_bombs++;
                }
                if ((board[down_check-1] == 9) && ((down_check) >= 0)) {
                    num_of_bombs++;
                }
            board[i] = num_of_bombs;
        } 

    }
}

void hideBoard(char *board, std::size_t xdim, std::size_t ydim) {
    for (int i{0}; i < xdim*ydim; i++) {
        board[i] = board[i] ^ 0b00100000;
    }
} 

int reveal(char *board, std::size_t xdim, std::size_t ydim, std::size_t xloc, std::size_t yloc) {
    int check_index;
    int check_index_2;
    int check_index_3;

    for (int i{0}; i < xdim*ydim; i++) {

        if (xdim*yloc == i) {
            check_index = i + xloc;
            check_index_2 = check_index + xdim;
            check_index_3 = check_index - xdim;
        } 

    }
    
    if ((board[check_index] >> 4) == 0b1) {
        return 1;
    } else if ((board[check_index] >> 5) != 0b1) {
        return 2;
    } else if ((board[check_index] & 0b1001) == 0b1001) {
        board[check_index] ^= 0b00100000;
        return 9;
    } else if ((board[check_index] & 0b0) == 0b0) {
        board[check_index] ^= 0b00100000;

        if (((board[check_index+1] >> 5) == 0b1) && ((board[check_index + 1] >> 4) != 0b1)) {
            board[check_index + 1] ^= 0b00100000;
        }
        if (((board[check_index-1] >> 5) == 0b1) && ((board[check_index - 1] >> 4) != 0b1)) {
            board[check_index - 1] ^= 0b00100000;
        }
        if (((board[check_index_2] >> 5) == 0b1) && ((board[check_index_2] >> 4) != 0b1)) {
            board[check_index_2] ^= 0b00100000;
        }
        if (((board[check_index_2 + 1] >> 5) == 0b1) && ((board[check_index_2 + 1] >> 4) != 0b1) && ((check_index_2 + 1) <= xdim*ydim)) {
            if ((xloc != (xdim-1)) && (yloc != (ydim-1))) {
            board[check_index_2 + 1] ^= 0b00100000;
            }
        }
        if (((board[check_index_2 - 1] >> 5) == 0b1) && ((board[check_index_2 - 1] >> 4) != 0b1)) {
            board[check_index_2 - 1] ^= 0b00100000;
        }
        if (((board[check_index_3] >> 5) == 0b1) && ((board[check_index_3] >> 4) != 0b1)) {
            board[check_index_3] ^= 0b00100000;
        }
        if (((board[check_index_3 + 1] >> 5) == 0b1) && ((board[check_index_3 + 1] >> 4) != 0b1)) {
            board[check_index_3 + 1] ^= 0b00100000;
        }
        if (((board[check_index_3 - 1] >> 5) == 0b1) && ((board[check_index_3] >> 4) != 0b1)) {
            if (((xloc != 0) && (yloc != 0))) { 
            board[check_index_3 - 1] ^= 0b00100000;
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
    return false;
}

