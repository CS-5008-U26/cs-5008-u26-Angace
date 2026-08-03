#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "drawUI.h"

#ifdef _WIN32
#include <windows.h>
#endif

#ifndef _WIN32
#include <unistd.h>
#endif

/* ANSI colors */
#define RESET   "\033[0m"
#define RED     "\x1B[41m"
#define GREEN   "\x1B[42m"
#define YELLOW  "\x1b[104m"
#define GREY    "\x1B[100m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"

void enableColors(void)
{
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;

    GetConsoleMode(hOut, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, mode);
#endif
}

/* Move the cursor back to the top-left and clear the screen using ANSI
 * escape codes instead of system("cls")/system("clear"). This is much
 * faster (no extra process spawned every frame) and lets the animation
 * redraw in place instead of scrolling. */
void clearScreen(void)
{
    printf("\033[H");
    printf("\033[2J");
    fflush(stdout);
}

void sleepMs(int ms)
{
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

static void drawCell(char c)
{
    switch (c) {
        case 'S':
            printf(GREEN "S " RESET);
            break;

        case 'G':
            printf(RED "G " RESET);
            break;

        case '#':
            printf(GREY "# " RESET);
            break;

        case '*':
            printf(YELLOW "* " RESET);
            break;

        case '@':
            printf(GREEN "@ " RESET);
            break;

        case 'o':
            printf(CYAN "o " RESET);
            break;

        default:
            printf(". ");
    }
}

static void drawGrid(char map[ROWS][COLS])
{
    printf("    ");
    for (int c = 0; c < COLS; c++) {
        printf("%2d", c);
    }
    printf("\n");

    for (int r = 0; r < ROWS; r++) {
        printf("%2d", r);

        for (int c = 0; c < COLS; c++) {
            drawCell(map[r][c]);
        }
        printf("\n");
    }
}

static void drawFrontierList(SearchStats *stats)
{
    printf(MAGENTA "Frontier (priority queue), lowest priority first:\n" RESET);

    if (stats->topCount == 0) {
        printf("  (empty)\n");
        return;
    }

    for (int i = 0; i < stats->topCount; i++) {
        printf("  #%d  (%2d,%2d)  priority=%d\n",
               i + 1,
               stats->topFrontier[i].row,
               stats->topFrontier[i].col,
               stats->topFrontier[i].priority);
    }

    if (stats->frontierSize > stats->topCount) {
        printf("  ... and %d more waiting in the queue\n",
               stats->frontierSize - stats->topCount);
    }
}

void drawFrame(char map[ROWS][COLS], SearchStats *stats)
{
    clearScreen();

    printf("\n================= %s : %s =================\n\n",
           stats->algoName, stats->phase);

    drawGrid(map);

    printf("\n--------------------------------------------------------------\n");
    printf("Step : %d\n", stats->step);

    if ((stats->currentRow >= 0) && (stats->currentCol >= 0)) {
        printf("Current Node : (%d, %d)\n", stats->currentRow, stats->currentCol);

        if (strcmp(stats->phase, "SEARCHING") == 0) {
            if (stats->currentH > 0 || strcmp(stats->algoName, "A*") == 0) {
                /* A* : show the g + h = f breakdown from the article */
                printf("  cost_so_far (g) = %d\n", stats->currentG);
                printf("  heuristic    (h) = %d\n", stats->currentH);
                printf("  priority     (f = g + h) = %d\n", stats->currentPriority);
            } else {
                /* Dijkstra : priority is just cost_so_far */
                printf("  cost_so_far (g) = priority = %d\n", stats->currentG);
            }
        }
    } else {
        printf("Current Node : Finished\n");
    }

    printf("Explored Nodes : %d\n", stats->visitedCount);

    if (strcmp(stats->phase, "SEARCHING") == 0) {
        printf("Frontier size : %d\n\n", stats->frontierSize);
        drawFrontierList(stats);
    }

    printf("\nLegend\n");
    printf(GREEN  "S " RESET " Start     ");
    printf(RED    "G " RESET " Goal     ");
    printf(GREY   "# " RESET " Wall\n");

    printf(YELLOW "* " RESET " Path      ");
    printf(GREEN   "@ " RESET " Current   ");
    printf(CYAN   "o " RESET " Explored\n");

    fflush(stdout);
}
