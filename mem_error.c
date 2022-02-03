//
// Created by Sahircan Sürmeli on 23.1.2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "mem_error.h"

void print_mem_error() {
    fprintf(stderr, "Memory allocation error!\n");
    exit(EXIT_FAILURE);
}
