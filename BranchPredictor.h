//
// Created by Aweso on 11/10/2025.
//

#ifndef ECE463_PROJ2_BRANCHPREDICTOR_H
#define ECE463_PROJ2_BRANCHPREDICTOR_H
#include <cstdint>
#include <vector>
#include <cstdio>
/*
n= 0
When you get a branch from the trace file, there are three steps:
(1) Determine the branch’s index into the prediction table.
(2) Make a prediction. Use index to get the branch’s counter from the prediction table. If the
counter value is greater than or equal to 2, then the branch is predicted taken, else it is predicted
not-taken.
(3) Update the branch predictor based on the branch’s actual outcome. The branch’s counter in
the prediction table is incremented if the branch was taken, decremented if the branch was nottaken. The counter saturates at the extremes (0 and 3), however.

When n > 0, there is an n-bit global branch history register. In this case, the index is based on
both the branch’s PC and the global branch history register, as shown in Fig. 2 below. The global
branch history register is initialized to all zeroes (00...0) at the beginning of the simulation.
Steps:
When you get a branch from the trace file, there are four steps:
(1) Determine the branch’s index into the prediction table. Fig. 2 shows how to generate the
index: the current n-bit global branch history register is XORed with the uppermost n bits of the
m PC bits.
(2) Make a prediction. Use index to get the branch’s counter from the prediction table. If the
counter value is greater than or equal to 2, then the branch is predicted taken, else it is predicted
not-taken.
(3) Update the branch predictor based on the branch’s actual outcome. The branch’s counter in
the prediction table is incremented if the branch was taken, decremented if the branch was nottaken. The counter saturates at the extremes (0 and 3), however.
(4) Update the global branch history register. Shift the register right by 1 bit position, and place
the branch’s actual outcome into the most-significant bit position of the register.
*/

enum Mode {
    Bimodal,
    Gshare,
    None
};


class BranchPredictor {
private:
    Mode m_mode;
    size_t m_pc_bits, m_gbhr_bits;
    uint64_t m_gbhr;
    uint64_t m_prediction_counter, m_misprediction_counter;
    std::vector<unsigned char> m_counters;

    size_t GetIndex(uint64_t address);
    bool PredictBranch(size_t index, bool actual_taken);


public:
    BranchPredictor (Mode mode, size_t m, size_t n)
    : m_mode(mode), m_pc_bits(m), m_gbhr_bits(n), m_gbhr(0), m_prediction_counter(0), m_misprediction_counter(0){
        m_counters.resize(1 << m_pc_bits,2);
    }

    void ReadTraceFile(char *trace_file);

    void PrintStatistics(FILE *file = stdout);

    void PrintMispredictionRate(FILE *file = stdout);

    double GetMispredictionRate();
};


#endif //ECE463_PROJ2_BRANCHPREDICTOR_H