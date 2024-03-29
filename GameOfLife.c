#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __unix__
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <ctype.h>

#define DEAD '.'
#define ALIVE 'o'

#define BLINKER 0
#define TOAD 1
#define BEACON 2
#define PULSAR 3
#define PENTADECATHLON 4
#define GLIDER 5
#define GOSPER_GLIDER_GUN 6
#define LWSS 7
#define RANDOM 8

#define NITERS 250

unsigned int GLOBAL_nlines;
unsigned int GLOBAL_ncolumns;

char* GLOBAL_grid_A = NULL;
char* GLOBAL_grid_B = NULL;

void gridInit(char* grid, int pattern){
	for(int i = 0; i < GLOBAL_ncolumns * GLOBAL_nlines; i++){
		grid[i] = DEAD;
    }
	switch(pattern){
		case BLINKER:
			grid[11] = grid[12] = grid[13] = ALIVE;
		break;
		case TOAD:
			grid[14] = grid[15] = grid[16] = grid[19] = grid[20] = grid[21] = ALIVE;
		break;
		case BEACON:
			grid[7] = grid[8] = grid[13] = grid[22] = grid[27] = grid[28] = ALIVE;
		break;
		case PULSAR:
			grid[22] = grid[28] = grid[39] = grid[45] = grid[56] = grid[57] = grid[61] = grid[62] = grid[86] = grid[87] = grid[88] = grid[91] = grid[92] = grid[94] = grid[95] = grid[98] = grid[99] = grid[100] = grid[105] = grid[107] = grid[109] = grid[111] = grid[113] = grid[115] = grid[124] = grid[125] = grid[129] = grid[130] = grid[158] = grid[159] = grid[163] = grid[164] = grid[173] = grid[175] = grid[177] = grid[179] = grid[181] = grid[183] = grid[188] = grid[189] = grid[190] = grid[193] = grid[194] = grid[196] = grid[197] = grid[200] = grid[201] = grid[202] = grid[226] = grid[227] = grid[231] = grid[232] = grid[243] = grid[249] = grid[260] = grid[266] = ALIVE;
		break;
		case PENTADECATHLON:
			grid[37] = grid[38] = grid[39] = grid[49] = grid[60] = grid[70] = grid[71] = grid[72] = grid[92] = grid[93] = grid[94] = grid[103] = grid[104] = grid[105] = grid[125] = grid[126] = grid[127] = grid[137] = grid[148] = grid[158] = grid[159] = grid[160] = ALIVE;
		break;
        case GLIDER:
			grid[1] = grid[17] = grid[30] = grid[31] = grid[32] = ALIVE;
		break;
        case GOSPER_GLIDER_GUN:
			grid[63] = grid[99] = grid[101] = grid[127] = grid[128] = grid[135] = grid[136] = grid[149] = grid[150] = grid[164] = grid[168] = grid[173] = grid[174] = grid[187] = grid[188] = grid[191] = grid[192] = grid[201] = grid[207] = grid[211] = grid[212] = grid[229] = grid[230] = grid[239] = grid[243] = grid[245] = grid[246] = grid[251] = grid[253] = grid[277] = grid[283] = grid[291] = grid[316] = grid[320] = grid[355] = grid[356] = ALIVE;
		break;
        case LWSS:
			grid[31] = grid[34] = grid[65] = grid[91] = grid[95] = grid[122] = grid[123] = grid[124] = grid[125] = ALIVE;
		break;
		case RANDOM:
			srand((unsigned int)time(NULL));
			for(int i = 0; i < GLOBAL_ncolumns * GLOBAL_nlines; i++){
				if(rand() % 10 <= 1){
                    grid[i] = ALIVE;
                }
            }
        break;
	}
}

int gridCompare(char* gridA, char* gridB){
	for(int i = 0; i < GLOBAL_ncolumns * GLOBAL_nlines; i++){
		if(gridA[i] != gridB[i]){
            return(1);
        }
    }
	return(0);
}

void gridEvolve(char* current, char* next){
	int row, col;
	for(int i = 0; i < GLOBAL_ncolumns * GLOBAL_nlines; i++){
		row = i / GLOBAL_ncolumns, col = i % GLOBAL_ncolumns;
        int count = 0;
		for(int j = col - 1; j <= col + 1 && count <= 4; j++){
			for(int k = row - 1; k <= row + 1; k++){
				if((j == col && k == row) || (j < 0 || j >= GLOBAL_ncolumns) || (k < 0 || k >= GLOBAL_nlines)){
                    continue;
                }
				if(current[k * GLOBAL_ncolumns + j] == ALIVE) {
                    count++;
                }
			}
		}
		next[i] = count == 3 || (count == 2 && current[i] == ALIVE) ? ALIVE : DEAD;
	}
}

void defineDimensions(int pattern){
	switch(pattern){
		case BLINKER:
			GLOBAL_nlines = GLOBAL_ncolumns = 5;
		break;
		case TOAD:
		case BEACON:
			GLOBAL_nlines = GLOBAL_ncolumns = 6;
		break;
		case PULSAR:
			GLOBAL_nlines = GLOBAL_ncolumns = 17;
		break;
		case PENTADECATHLON:
			GLOBAL_nlines = 18;
			GLOBAL_ncolumns = 11;
		break;
        case GLIDER:
			GLOBAL_nlines = GLOBAL_ncolumns = 15;
		break;
        case GOSPER_GLIDER_GUN:
			GLOBAL_nlines = 20;
            GLOBAL_ncolumns = 38;
		break;
        case LWSS:
			GLOBAL_nlines = 7;
            GLOBAL_ncolumns = 30;
		break;
		case RANDOM:
            srand((unsigned int)time(NULL));
			GLOBAL_nlines = rand() % 16 + 5;
			GLOBAL_ncolumns = rand() % 31 + 10;
        break;
	}
}

void gridShow(char* grid){
	for(int i = 0; i < GLOBAL_nlines; i++){
		printf("%.*s\n", GLOBAL_ncolumns, grid + i * GLOBAL_ncolumns);
	}
}

int main(int argc, char** argv){
	unsigned int pattern, niters = 0, sleepTime = 0;
	if(argc != 2 && argc != 3){
        printf("\nUsage:\t%s <pattern> <sleepTime>\n\n\tpattern:\t0 - BLINKER\n\t\t\t1 - TOAD\n\t\t\t2 - BEACON\n\t\t\t3 - PULSAR\n\t\t\t4 - PENTADECATHLON\n\t\t\t5 - GLIDER\n\t\t\t6 - GOSPER GLIDER GUN\n\t\t\t7 - LWSS\n\t\t\t8 - RANDOM\n\n\tsleepTime (optional):\tvalue in ms between 0 and 10000\n", argv[0]);
        return(-1);
    }
	if(!isdigit(*argv[1])) return(-1);
    sleepTime = atoi(argv[2]);
    if(sleepTime < 0 || sleepTime > 10000) return(-1);
    #ifdef __unix__
    sleepTime *= 1000;
    #endif
	pattern = atoi(argv[1]);
	if(pattern > 8 || pattern < 0) return(-1);

	defineDimensions(pattern);
	GLOBAL_grid_A = (char*)malloc(GLOBAL_ncolumns * GLOBAL_nlines * sizeof(char));
	GLOBAL_grid_B = (char*)malloc(GLOBAL_ncolumns * GLOBAL_nlines * sizeof(char));
	gridInit(GLOBAL_grid_A, pattern);

	while(niters++ < NITERS){
        #ifdef _WIN32
        Sleep(sleepTime);
		system("cls");
        #endif
        #ifdef __unix__
        usleep(sleepTime);
        system("clear");
        #endif
		gridShow(GLOBAL_grid_A);
		gridEvolve(GLOBAL_grid_A, GLOBAL_grid_B);
		if(gridCompare(GLOBAL_grid_A, GLOBAL_grid_B)){
			char* temp = GLOBAL_grid_A;
			GLOBAL_grid_A = GLOBAL_grid_B;
			GLOBAL_grid_B = temp;
		}else break;
	}

	if(niters - 1 == NITERS){
        printf("\nFINISHED all iterations\n");
    }

	free(GLOBAL_grid_A);
	free(GLOBAL_grid_B);
	return(0);
}