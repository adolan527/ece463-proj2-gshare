//
// Created by Aweso on 11/10/2025.
//

#include "BranchPredictor.h"
#include <cstdio>
#include <cstdlib>
void BranchPredictor::ReadTraceFile(char *trace_file) {
    FILE* file = fopen(trace_file,"r");
    if (!file) {
        printf("Failed to open %s\n",trace_file);
        return;
    }
    uint64_t address = 0;
    char status = 0;
    char buffer[32] ={0};
    int x = 0;
    char* endptr;

    while (!feof(file)) {
        endptr = nullptr;
        fgets(buffer,32,file);
        if (feof(file))break;
        address = strtol(buffer,&endptr,16);
        status = endptr[1];
        auto index = GetIndex(address);
        bool actual_taken = status == 't';
        PredictBranch(index,actual_taken);

    }

    fclose(file);
}


bool BranchPredictor::PredictBranch(size_t index, bool actual_taken) {
    m_prediction_counter++;
    bool predict_taken = false;
    auto predictor = m_counters[index];

    if (predictor>=2) {
        predict_taken = true;
        if (actual_taken) m_counters[index] = 3;
        else {
            --m_counters[index];
            m_misprediction_counter++;
        }
    }else {
        predict_taken = false;
        if (!actual_taken) m_counters[index] = 0;
        else {
            ++m_counters[index];
            m_misprediction_counter++;
        }
    }

    if (m_mode == Gshare) { // update global branch history register
        m_gbhr = m_gbhr >> 1;
        uint64_t bit = actual_taken ? 1 : 0;
        bit = bit << m_gbhr_bits;
        m_gbhr |= bit;
        m_gbhr &= ~(0xFFFFFFFFFFFFFFFF << m_gbhr_bits); // safety mask
    }

    return predict_taken;
}

size_t BranchPredictor::GetIndex(uint64_t address) {
    address = address >> 2; // remove 2 LSB (block offset)
    uint64_t mask = ~(0xFFFFFFFFFFFFFFFF << m_pc_bits); // 1's only in lowest m_pc_bits
    address &= mask; // pc index
    if (m_mode == Bimodal) return address;
    uint64_t gbhr_mask = m_gbhr << (m_pc_bits - m_gbhr_bits);
    address ^= gbhr_mask;
    address &= mask; // safety mask
    if (m_mode == Gshare) return address;

    // how did we get here?
    printf("Invalid mode\n");
    return 0;

}

void BranchPredictor::PrintStatistics(FILE *file) {
    printf(" number of predictions:\t%llu\n",m_prediction_counter);
    printf(" number of mispredictions:\t%llu\n",m_misprediction_counter);
    printf(" misprediction rate:\t%.2f%%\n",100.0f * (double)m_misprediction_counter/(double)m_prediction_counter);
    printf("FINAL %s CONTENTS\n",m_mode==Bimodal ? "BIMODAL" : m_mode == Gshare ? "GSHARE" : "INVALID_MODE");
    for (int i = 0; i < m_counters.size(); i++) {
        printf(" %d\t%d\n",i,m_counters[i]);
    }
}

