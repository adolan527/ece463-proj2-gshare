//
// Created by Aweso on 11/10/2025.
//

#ifndef ECE463_PROJ2_BRANCHPREDICTOR_H
#define ECE463_PROJ2_BRANCHPREDICTOR_H
#include <cstdint>

class BranchPredictor {
    size_t pc_bit_count, gbhr_bit_count;


    BranchPredictor (size_t m, size_t n)
    : pc_bit_count(m), gbhr_bit_count(n){

    }
};


#endif //ECE463_PROJ2_BRANCHPREDICTOR_H