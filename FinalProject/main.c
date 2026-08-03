/* CS5008 Final Project - Finding the Best Route
 * Team: JSD squad (Zhuo Wang, Jenney) (Yang Huang, Sandra) (Lei Tuo)
 *
 * Implements A* and Dijkstra's Algorithm on a 30x30 grid, following the
 * model described in:
 * Patel, Amit J., "Introduction to the A* Algorithm", Red Blob Games,
 * https://www.redblobgames.com/pathfinding/a-star/introduction.html
 *
 * The user enters start/goal, watches A* solve it, presses ENTER, then
 * watches Dijkstra solve the same problem so the two can be compared.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "drawUI.h"
#include "pqueue.h"

/* ===== Symbol data ===== */
#define EMPTY   '.'     // cell has not been touched by the search yet
#define WALL    '#'     // wall / obstacle, never enters the frontier
#define START   'S'     // the fixed starting cell chosen by the user
#define GOAL    'G'     // the fixed goal cell chosen by the user
#define VISITED 'o'     // cell has been popped from the frontier and fully
#define CURRENT '@'     // cell that searched. only for the animation frame where it's active, 
                        // then immediately change to VISITED symbol
#define PATH    '*'     // cell belongs to the final reconstructed shortest path

/* ===== Create struct ====== */
typedef struct nodePathfinder{
    int g;         //cost_so_far: distance from start along the found path 
    int visited;   //determin whether current node is popped from the frontier and expanded
    int parentRow; //came_from: used to rebuild the path of row
    int parentCol; //came_from: used to rebuild the path of column
} Node;

/* Store the final results so the two algorithms can be compared */
typedef struct PathSearch {
    int pathFound;     // store found path
    int pathLength;    // store path length
    int exploredNodes; // store expored nodes
} SearchResult;

/* ===== Global state ====== */
char map[ROWS][COLS];   //map
Node nodes[ROWS][COLS]; //node that saved cordination
int startRow; // integer to hold row number of start node
int startCol; // integer to hold column number of start node
int goalRow;  // integer to hold row number of goal node
int goalCol;  // integer to store column number of goal node

/* ====== Grid Setup ======= */
void initializeGrid(void)
{
    for (int r = 0; r < ROWS; r++) { // visit the row
        for (int c = 0; c < COLS; c++) { //visit the column
            map[r][c] = EMPTY;  // fill cowith EMPTY symbol
        }
    }

    /* Creating walls or obstacles */
    for (int r = 5; r <= 20; r++) {  // left vertical wall
        map[r][10] = WALL;
    }
    for (int c = 12; c <= 25; c++) {  // horizontal wall
        map[18][c] = WALL;
    }
    for (int r = 8; r <= 22; r++) {   // right vertical wall
        map[r][18] = WALL;
    }

    /* Create a closed area around (27, 27) for testing "No path found." */
    for (int c = 26; c <= 28; c++) {
        map[26][c] = WALL;
        map[28][c] = WALL;
    }
    for (int r = 26; r <= 28; r++) {
        map[r][26] = WALL;
        map[r][28] = WALL;
    }
}

/* ====== Reset the search bookkeeping ==== */
// call before each algorithm run, and clear any leftover path/visited
//  marks on the map while keeping the walls, start, and goal.
void resetSearchData(void)
{
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            //reset algorithmic state: "not reached yet, no parent".
            nodes[r][c].g = INT_MAX;
            nodes[r][c].visited = 0;
            nodes[r][c].parentRow = -1;
            nodes[r][c].parentCol = -1;

            // reset path nodes, visted nodes, and current nodes to empty symbol
            if ((map[r][c] == PATH) || (map[r][c] == VISITED) || (map[r][c] == CURRENT)) {
                map[r][c] = EMPTY;
            }
        }
    }
    // keep start and goal in case override by visited
    map[startRow][startCol] = START;
    map[goalRow][goalCol] = GOAL;
}

/***********  USER INPUT VALIDATION ************/

/* for validating input cant exist the grid size*/
int isValidLocation(int row, int col)
{
    if ((row < 0) || (row >= ROWS)) { //row cant small than 0 and exceed 30
        return 0;
    }
    if ((col < 0) || (col >= COLS)) { //row cant small than 0 and exceed 30
        return 0;
    }
    return 1;
}

/* for validating input conflict with walls or cross walls */
int isWall(int row, int col)
{
    return map[row][col] == WALL;
}

/* ======= Get start and goal inputs */
void getUserInput()
{
    while (1) {
        // get start node
        printf("Enter start row (0 - 29): ");
        scanf("%d", &startRow);

        printf("Enter start column (0 - 29): ");
        scanf("%d", &startCol);

        // validate input
        if (!isValidLocation(startRow, startCol)) {
            printf("\nInvalid start location.\n\n");
            continue;
        }
        if (isWall(startRow, startCol)) {
            printf("\nStart location conflicts with wall.\n\n");
            continue;
        }

        // get goal node
        printf("Enter goal row (0 - 29): ");
        scanf("%d", &goalRow);

        printf("Enter goal column (0 - 29): ");
        scanf("%d", &goalCol);

        // validate input
        if (!isValidLocation(goalRow, goalCol)) {
            printf("\nInvalid goal location.\n\n");
            continue;
        }
        if (isWall(goalRow, goalCol)) {
            printf("\nGoal location conflicts with wall.\n\n");
            continue;
        }

        // validate start and goal conflict
        if ((startRow == goalRow) && (startCol == goalCol)) {
            printf("\nStart and Goal cannot be the same location.\n\n");
            continue;
        }
        break;
    }
    // set start and goal on the grid
    map[startRow][startCol] = START;
    map[goalRow][goalCol] = GOAL;
}

/* ========  Manhattan distance heuristic ========
 * formula:  h = |dx| + |dy|
 * Admissible (never overestimates) for 4-directional grid movement with
 * cost 1 per step, which is what guarantees A* still finds the shortest
 * path, just like Dijkstra does. */
int heuristic(int row, int col)
{
    return abs(row - goalRow) + abs(col - goalCol);
}

/**********  C O R E   S E A R C H  ***********/

/* Implements the pseudocode from the "Movement costs" / "The A* algorithm"
 * sections of the article. useHeuristic = 0 gives plain Dijkstra
 * (priority = cost_so_far); useHeuristic = 1 gives A* (priority = g + h). */
SearchResult runSearch(const char *algoName, int useHeuristic)
{
    resetSearchData();

    //Frontier: use minimum priority queue of (row, column) cells waiting to be expanded, 
    // ordered by "priority" (g for Dijkstra, g+h for A*). 
    // Units can be pushed into this queue multiple times if a cheaper path is found later
    PriorityQueue frontier;  // set frontier
    pqInit(&frontier, 256);

    // 4 directional movement offsets: up, down, left, right
    int rowMove[4] = {-1, 1, 0, 0};  // move row to up and down to check
    int colMove[4] = {0, 0, -1, 1};  // move col to left and right to check

    nodes[startRow][startCol].g = 0; //the start cell costs 0 to reach
    int startPriority = useHeuristic ? heuristic(startRow, startCol) : 0;
    pqPush(&frontier, startRow, startCol, startPriority);

    int step = 0;  // initiate cells have been expanded so far
    int visitedCount = 0;  // initiate node of visited finially

    while (!pqEmpty(&frontier)) {
        PQEntry currentEntry = pqPop(&frontier);
        int r = currentEntry.row;
        int c = currentEntry.col;

        /* this location may be sitting in the queue more
         * than once with different priorities (the article calls this out
         * explicitly). Once it's been expanded, later copies are stale. */
        if (nodes[r][c].visited) {
            continue;
        }
        /* this cell is now officially "expanded" for good, g is final and won't be visited */
        step++;
        nodes[r][c].visited = 1;
        visitedCount++;

        /* mark as the "currently being processed" cell*/
        if (map[r][c] == EMPTY) {
            map[r][c] = CURRENT;
        }

        /* build for frame to show realtime algorithom process*/
        SearchStats stats = {0};
        stats.algoName = algoName;
        stats.phase = "SEARCHING";
        stats.step = step;
        stats.currentRow = r;
        stats.currentCol = c;
        stats.currentG = nodes[r][c].g;
        stats.currentH = useHeuristic ? heuristic(r, c) : 0;
        stats.currentPriority = currentEntry.priority;
        stats.frontierSize = pqSize(&frontier);
        stats.visitedCount = visitedCount;
        pqTopN(&frontier, stats.topFrontier, TOP_FRONTIER_N, &stats.topCount);

        drawFrame(map, &stats);
        sleepMs(RUN_SPEED);

        // in case current won't override visted
        if (map[r][c] == CURRENT) {
            map[r][c] = VISITED;
        }

        /* Early exit, exactly as described in the article: stop as soon as
         * the goal is popped off the frontier rather than when it's first
         * discovered. */
        if ((r == goalRow) && (c == goalCol)) {
            break;
        }

        /* look at all 4 orthogonal neighbors of the cell we just expanded, 
        and see if going through THIS cell gives them a cheaper */
        for (int i = 0; i < 4; i++) {
            int nr = r + rowMove[i];
            int nc = c + colMove[i];

            if (!isValidLocation(nr, nc)) { // skip neighbors that are outside the grid
                continue;
            } 
            if (isWall(nr, nc)) { // skip blocked by wall
                continue;
            }
            if (nodes[nr][nc].visited) { // skip already visited
                continue;
            }

            int newCost = nodes[r][c].g + 1;   // graph.cost(current, next) = 1

            /* "add it if the new path to the location is better than the
             * best previous path" */
            // 2 cases trigger an update, either case just override the cost
            // 1. neighbor has never been reached before (g == INT_MAX), or
            // 2. just found a strictly cheaper way to reach it.
            if ((nodes[nr][nc].g == INT_MAX) || (newCost < nodes[nr][nc].g)) {
                nodes[nr][nc].g = newCost;
                nodes[nr][nc].parentRow = r;
                nodes[nr][nc].parentCol = c;

                int priority = newCost;  // newCost is g "cost_so_far"
                if (useHeuristic) {
                    priority += heuristic(nr, nc);  //  A* add h
                }
                pqPush(&frontier, nr, nc, priority);
            }
        }
    }

    pqFree(&frontier);

    /* ---- Reconstruct and animate the path ----
     * The article reconstructs paths by walking came_from backwards from
     * goal to start. We collect it into an array first so we can animate
     * it forward, start -> goal, which reads more naturally. */
    int pathRowArr[ROWS * COLS]; // set parent row array
    int pathColArr[ROWS * COLS]; // set parent col array
    int pathCount = 0; // initiate count of path of parent nodes
    int pr = goalRow; // parent row
    int pc = goalCol; // parent column
    int pathExists = nodes[goalRow][goalCol].visited;  // indicate goal is not reachable

    /* walk backwards from goal to start via parent pointers, and count each node*/
    while (pathExists && !((pr == startRow) && (pc == startCol))) {
        int parentRow = nodes[pr][pc].parentRow;
        int parentCol = nodes[pr][pc].parentCol;

        // palse if pathExists is true, to in case the loop keeps going
        if ((parentRow == -1) || (parentCol == -1)) {
            break;
        }

        if (!((pr == goalRow) && (pc == goalCol))) {
            pathRowArr[pathCount] = pr;
            pathColArr[pathCount] = pc;
            pathCount++;
        }

        pr = parentRow;
        pc = parentCol;
    }

    // using for statistic current visiting cells from start to goal
    for (int i = pathCount - 1; i >= 0; i--) {
        map[pathRowArr[i]][pathColArr[i]] = PATH;

        SearchStats stats = {0};
        stats.algoName = algoName;
        stats.phase = "PATH";
        stats.step = pathCount - i;
        stats.currentRow = pathRowArr[i];
        stats.currentCol = pathColArr[i];
        stats.currentG = nodes[pathRowArr[i]][pathColArr[i]].g;
        stats.visitedCount = visitedCount;

        drawFrame(map, &stats);
        sleepMs(RUN_SPEED);
    }
    // keep start and goal on the screen after animation and clean screen
    map[startRow][startCol] = START;
    map[goalRow][goalCol] = GOAL;

    /* final frame with no active cell highlighted,
    so the completed path stays visible on screen after the animation ends.*/
    SearchStats finalStats = {0};
    finalStats.algoName = algoName;
    finalStats.phase = "PATH";
    finalStats.step = pathCount;
    finalStats.currentRow = -1;
    finalStats.currentCol = -1;
    finalStats.visitedCount = visitedCount;
    drawFrame(map, &finalStats);

    /* Print result and summary on the screen */
    printf("\n ========== %s Result ==========\n", algoName);
    if (!pathExists) {
        printf("No path found.\n");
    } else {
        printf("Path Length    : %d\n", nodes[goalRow][goalCol].g);
    }
    printf("Explored Nodes : %d\n", visitedCount);
    printf("Search Steps   : %d\n", step);
    printf("\n\n\n");

    /* Return the final values for the comparison table in main. */
    SearchResult result;
    result.pathFound = pathExists;
    result.pathLength = pathExists ? nodes[goalRow][goalCol].g : -1;
    result.exploredNodes = visitedCount;

    return result;
}

/* run the shared search core in "A*" mode */
SearchResult runAStar()
{
    return runSearch("A*", 1);  // useHeuristic = 1
}

/* run the shared search core in Dijkstra mode */
SearchResult runDijkstra()
{
    return runSearch("Dijkstra", 0); // useHeuristic = 0
}

/********** M A I N ***********/
int main()
{
    char s[100];
    enableColors();
    initializeGrid();

    /* Get user input of start and goal coordinate*/
    printf("\n ======= Input Start and Goal position =======\n");
    getUserInput();

    /* Remove the newline left by scanf */
    getchar();

    printf("\nPress ENTER to start A*.");
    getchar();

    /* Show A* Algorithm and Animation*/
    printf("\n================= A* Algorithm Visualization ==============\n\n");
    SearchResult aStarResult = runAStar();

    printf("\nPress ENTER to continue to Dijkstra.");
    getchar();
    
    /* Show Dijkstra Algorithm and Animation*/
    printf("\n================= Dijkstra Algorithm Visualization ==============\n\n");
    SearchResult dijkstraResult = runDijkstra();

    /* Print both results together for a direct comparison. */
    printf("\nPress ENTER to view the final comparison.");
    getchar();
    printf("\n========== Final Comparison ==========\n");
    printf("%-12s %-14s %-15s\n",
           "Algorithm",
           "Path Length",
           "Explored Nodes");

    if (aStarResult.pathFound) {
        printf("%-12s %-14d %-15d\n",
               "A*",
               aStarResult.pathLength,
               aStarResult.exploredNodes);
    } else {
        printf("%-12s %-14s %-15d\n",
               "A*",
               "No path",
               aStarResult.exploredNodes);
    }

    if (dijkstraResult.pathFound) {
        printf("%-12s %-14d %-15d\n",
               "Dijkstra",
               dijkstraResult.pathLength,
               dijkstraResult.exploredNodes);
    } else {
        printf("%-12s %-14s %-15d\n",
               "Dijkstra",
               "No path",
               dijkstraResult.exploredNodes);
    }

    /* Exit the program */
    printf("\nPress ENTER to exit the program.");
    fgets(s,100,stdin);
    return 0;
}