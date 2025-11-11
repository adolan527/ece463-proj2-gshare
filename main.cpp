#include <iostream>
#include <cstring>
#include "BranchPredictor.h"

int main(int argc, char **argv) {

/*
    for (int m = 7; m <= 20; m++) {
        printf("%d, ",m);
        for (int n = 0; n <= m; n++) {
            auto bp = BranchPredictor(Gshare,m,n);
            bp.ReadTraceFile("gcc_trace.txt");
            printf("%.2f, ",bp.GetMispredictionRate());
        }
        for (int j = 20; j >= m; j--) printf(",");
        printf("\n");
    }
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