#include <iostream>
#include <cstring>
#include "BranchPredictor.h"

int main(int argc, char **argv) {
    /*
        auto bp0 = BranchPredictor(Bimodal,6,0);
        auto bp1 = BranchPredictor(Bimodal,12,0);
        auto bp2 = BranchPredictor(Gshare,9,3);
        auto bp3 = BranchPredictor(Gshare,14,8);

        bp0.ReadTraceFile("gcc_trace.txt");
        bp0.PrintStatistics(stdout);
        bp1.ReadTraceFile("gcc_trace.txt");
        bp1.PrintStatistics(stdout);
        bp2.ReadTraceFile("gcc_trace.txt");
        bp2.PrintStatistics(stdout);
        bp3.ReadTraceFile("gcc_trace.txt");
        bp3.PrintStatistics(stdout);

        return 0;

        */
    const char bimodal_string[] = "bimodal";
    const char gshare_string[] = "gshare";

    if (argc > 5 || argc < 4) {
        printf("Usage: sim MODE PARAM1 [PARAM2] TRACEFILE");
        printf("Valid modes: \"%s\" or \"%s\"\n",bimodal_string,gshare_string);
        return 0;
    }

    Mode mode = None;
    size_t pc_bits = 0, gbhr_bits = 0;
    char* trace_file = nullptr;

    if (strcmp(argv[1],bimodal_string) == 0) mode = Bimodal;
    else if (strcmp(argv[1],gshare_string) == 0) mode = Gshare;
    else {
        printf("Invalid mode\n");
        return 0;
    }

    pc_bits = strtol(argv[2],nullptr,10);
    if (mode == Gshare) {
        gbhr_bits = strtol(argv[3],nullptr,10);
        trace_file = argv[4];
    } else {
        gbhr_bits = 0;
        trace_file = argv[3];
    }

    auto bp = BranchPredictor(mode,pc_bits,gbhr_bits);
    bp.ReadTraceFile(trace_file);
    printf("COMMAND\n");
    for (int i = 0; i < argc;i++) printf(" %s",argv[i]);
    printf("\nOUTPUT\n");
    bp.PrintStatistics();







    return 0;
}