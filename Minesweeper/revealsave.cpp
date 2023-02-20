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

    std::cout << "check_index = " << check_index << std::endl;
    std::cout << "upcheck = " << up_check <<std::endl;
    std::cout << "downchock =" << down_check <<std::endl;
    
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
            if (((board[check_index + 1] >> 4) != 0b1) && ((board[check_index +1] >> 5) == 0b1)) {
                board[check_index + 1] ^= 0b00100000;
            }
            if (((board[up_check] >> 4) != 0b1) && ((board[up_check] >> 5) == 0b1)) {
                board[up_check] ^= 0b00100000;
            }
            if (((board[up_check + 1] >> 4) != 0b1) && ((board[up_check +1] >> 5) == 0b1)) {
                board[up_check +1] ^= 0b00100000;
            }
            if (((board[down_check] >> 4) != 0b1) && ((board[down_check] >> 5) == 0b1)) {
                board[down_check] ^= 0b00100000;
            }
            if (((board[down_check +1] >> 4) != 0b1) && ((board[down_check +1] >> 5) == 0b1)) {
            board[down_check +1] ^= 0b00100000;
            }
        } else if (((check_index + 1) % xdim) == 0) {
            if (((board[check_index -1] >> 4) != 0b1) && ((board[check_index -1] >> 5) == 0b1)) {
                board[check_index -1] ^= 0b00100000;
            }
            if (((board[up_check] >> 4) != 0b1) && ((board[up_check] >> 5) == 0b1)) {
                board[up_check] ^= 0b00100000;
            }
            if (((board[up_check -1] >> 4) != 0b1) && ((board[up_check -1] >> 5) == 0b1)) {
                board[up_check -1] ^= 0b00100000;
            }
            if (((board[down_check] >> 4) != 0b1) && ((board[down_check] >> 5) == 0b1)) {
                board[down_check] ^= 0b00100000;
            }
            if (((board[down_check -1] >> 4) != 0b1) && ((board[down_check -1] >> 5) == 0b1)) {
                board[down_check -1] ^= 0b00100000;
            }
        } else {
            if (((board[check_index + 1] >> 4) != 0b1) && ((board[check_index +1] >> 5) == 0b1)) {
                board[check_index + 1] ^= 0b00100000;
            }
            if (((board[check_index -1] >> 4) != 0b1) && ((board[check_index -1] >> 5) == 0b1)) {
                board[check_index -1] ^= 0b00100000;
            }
            if (((board[up_check] >> 4) != 0b1) && ((board[up_check] >> 5) == 0b1)) {
                board[up_check] ^= 0b00100000;
            }
            if (((board[up_check + 1] >> 4) != 0b1) && ((board[up_check +1] >> 5) == 0b1)) {
                board[up_check +1] ^= 0b00100000;
            }
            if (((board[up_check -1] >> 4) != 0b1) && ((board[up_check -1] >> 5) == 0b1)) {
                board[up_check -1] ^= 0b00100000;
            }
            if (((board[down_check] >> 4) != 0b1) && ((board[down_check] >> 5) == 0b1)) {
                board[down_check] ^= 0b00100000;
            }
            if (((board[down_check +1] >> 4) != 0b1) && ((board[down_check +1] >> 5) == 0b1)) {
                board[down_check +1] ^= 0b00100000;
            }
            if (((board[down_check -1] >> 4) != 0b1) && ((board[down_check -1] >> 5) == 0b1)) {
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