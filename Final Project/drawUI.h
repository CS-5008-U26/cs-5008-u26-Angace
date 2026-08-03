#ifndef DRAWUI_H
#define DRAWUI_H

#include "pqueue.h"

#define ROWS 30         // backgound grid row size
#define COLS 30         // backgound grid column size
#define RUN_SPEED 50   // speed to run the animation
#define TOP_FRONTIER_N 5   // how many frontier entries to show on screen

/* Everything needed to draw one animation frame's HUD (heads-up display).
 * This mirrors the concepts from redblobgames.com/pathfinding/a-star:
 * frontier (priority queue), came_from / reached set (visitedCount),
 * cost_so_far (g), heuristic (h), priority (f).
 * f = g + h. only A* add h */
typedef struct {
    const char *algoName;   // "A*" or "Dijkstra"
    const char *phase;      // "SEARCHING" or "PATH"
    int step;               // count step visited

    int currentRow;     // row
    int currentCol;     // column
    int currentG;       // cost_so_far of current node
    int currentH;       // heuristic value of current node (0 if n/a) 
    int currentPriority; //priority popped from the frontier

    int frontierSize;    //size of the priority queue right now
    int visitedCount;    //* number of nodes removed from the frontier and expanded 

    PQEntry topFrontier[TOP_FRONTIER_N];
    int topCount;
} SearchStats;

/* Enable ANSI color (Windows compatible) */
void enableColors(void);

/* Move cursor home + clear so the animation redraws in place */
void clearScreen(void);

/* Sleep in milliseconds */
void sleepMs(int ms);

/* Draw one complete frame, including the algorithm HUD */
void drawFrame(char map[ROWS][COLS], SearchStats *stats);

#endif
