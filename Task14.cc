/* ----------------------------------------------------------------<Header>-
    Name: task14.cc
    Title: Domino riddle solver
    Group: TV-52
    Student: Ploskonos S.D.
    Written: 2026-05-10
    Revised: 2026-05-10
    Description: Write a program that solves the domino riddle. On a 6x10 grid, 
    there are 28 dominoes (each with two numbers from 0 to 6) that must be 
    placed without overlap. Each cell in the grid contains a number from 0 to 6,
    and each domino must cover two adjacent cells (horizontally or vertically)
    that match the numbers on the domino. The program should find a valid 
    arrangement of all dominoes on the grid, allowing for up to 4 cells to
    be left unused if necessary. The output should display the positions of
    each domino and a visual representation of the grid, highlighting any 
    unused cells. Additionally, the program should measure and display
    the time taken to find the solution.
 ------------------------------------------------------------------</Header>-*/
#include <iostream>
#include <chrono>
#include <algorithm>

/* ---------------------------------------------------------------------[<]-
    Structure: Domino
    Synopsis: Represents a domino piece with its values and positions on the grid.
 ---------------------------------------------------------------------[>]-*/
struct Domino{
    int a,b;
    int x1,y1,x2,y2;
};

/* ---------------------------------------------------------------------[<]-
    Structure: SolverContext
    Synopsis: Represents the context for solving the domino riddle.
 ---------------------------------------------------------------------[>]-*/
struct SolverContext {
    static const int ROWS = 6;
    static const int COLS = 10;
    static const int MAX_SKIPPED = 4;
    static const int TOTAL_DOMINOES = 28;
    int riddle[ROWS][COLS];
    bool visited[ROWS][COLS];
    bool domino_used[7][7];
    Domino answer[TOTAL_DOMINOES];
    int found_count;
    int skipped_count;
    SolverContext(int input_riddle[ROWS][COLS]) {
        found_count = 0;
        skipped_count = 0;
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                riddle[i][j] = input_riddle[i][j];
                visited[i][j] = false;
            }
        }
        for (int i = 0; i < 7; ++i) {
            for (int j = 0; j < 7; ++j) {
                domino_used[i][j] = false;
            }
        }
    }
};
bool compareDominoes(const Domino& d1, const Domino& d2);
bool solve(int r, int c, SolverContext& ctx);

int main() {
    int initial_grid[6][10] = {
        {0,0,1,1,2,3,3,5,4,0},
        {3,3,2,5,6,6,3,4,2,0},
        {6,3,0,6,1,1,6,4,2,0},
        {2,2,4,3,6,6,1,3,2,2},
        {2,4,4,0,0,5,4,5,5,5},
        {1,1,4,6,0,5,1,3,5,3}
    };
    SolverContext ctx(initial_grid);
    auto start = std::chrono::high_resolution_clock::now();
    std::cout<<"Original Grid:\n";
    for (int i = 0; i < SolverContext::ROWS; i++) {
        for (int j = 0; j < SolverContext::COLS; j++) {
            std::cout << ctx.riddle[i][j] << " ";
        }
        std::cout << std::endl;
    }
    if (solve(0, 0, ctx)) {
        std::sort(ctx.answer, ctx.answer + 28, compareDominoes);
        std::cout << "Solution found!" << std::endl;
        for (int i = 0; i < 28; i++) {
            if (i > 0 && ctx.answer[i].a != ctx.answer[i-1].a) std::cout << std::endl;
            std::cout << "Domino " << ctx.answer[i].a << "-" << ctx.answer[i].b 
                      << " at (" << ctx.answer[i].x1 << "," << ctx.answer[i].y1 << ") & ("
                      << ctx.answer[i].x2 << "," << ctx.answer[i].y2 << ")" << std::endl;
        }
        std::cout << "\nVisual Grid (Red background = unused cells):\n";
        for (int i = 0; i < SolverContext::ROWS; i++) {
            for (int j = 0; j < SolverContext::COLS; j++) {
                bool cell_is_used = false;
                for (int k = 0; k < 28; k++) {
                    if ((ctx.answer[k].x1 == i && ctx.answer[k].y1 == j) || 
                        (ctx.answer[k].x2 == i && ctx.answer[k].y2 == j)) {
                        cell_is_used = true;
                        break;
                    }
                }
                if (!cell_is_used) {
                    std::cout << "\033[101m " << ctx.riddle[i][j] << " \033[0m ";
                } else {
                    std::cout << " " << ctx.riddle[i][j] << "  ";
                }
            }
            std::cout << std::endl;
        }
    } else {
        std::cout << "No solution exists." << std::endl;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout <<"Program took: "<< duration.count() << " milliseconds" << std::endl;
    return 0;
}

/* ---------------------------------------------------------------------[<]-
    Function: compareDominoes
    Synopsis: Compares two dominoes based on their values.
 ---------------------------------------------------------------------[>]-*/
bool compareDominoes(const Domino& d1, const Domino& d2) {
    if (d1.a != d2.a) return d1.a < d2.a;
    return d1.b < d2.b;
}

/** ---------------------------------------------------------------------[<]-
    Function: solve
    Synopsis: Recursively solves the domino riddle.
 ---------------------------------------------------------------------[>]-*/
bool solve(int r, int c, SolverContext& ctx) {
    if (ctx.found_count == SolverContext::TOTAL_DOMINOES) return true;
    if (r == SolverContext::ROWS) return false;
    int next_r = r, next_c = c + 1;
    if (next_c == SolverContext::COLS) {
        next_r = r + 1;
        next_c = 0;
    }
    if (ctx.visited[r][c]) return solve(next_r, next_c, ctx);
    if (c + 1 < SolverContext::COLS && !ctx.visited[r][c + 1]) {
        int v1 = ctx.riddle[r][c], v2 = ctx.riddle[r][c + 1];
        int low = std::min(v1, v2), high = std::max(v1, v2);

        if (!ctx.domino_used[low][high]) {
            ctx.domino_used[low][high] = true;
            ctx.visited[r][c] = ctx.visited[r][c + 1] = true;
            ctx.answer[ctx.found_count++] = {low, high, r, c, r, c + 1};

            if (solve(next_r, next_c, ctx)) return true;

            ctx.found_count--;
            ctx.domino_used[low][high] = false;
            ctx.visited[r][c] = ctx.visited[r][c + 1] = false;
        }
    }
    if (r + 1 < SolverContext::ROWS && !ctx.visited[r + 1][c]) {
        int v1 = ctx.riddle[r][c], v2 = ctx.riddle[r + 1][c];
        int low = std::min(v1, v2), high = std::max(v1, v2);

        if (!ctx.domino_used[low][high]) {
            ctx.domino_used[low][high] = true;
            ctx.visited[r][c] = ctx.visited[r + 1][c] = true;
            ctx.answer[ctx.found_count++] = {low, high, r, c, r + 1, c};

            if (solve(next_r, next_c, ctx)) return true;

            ctx.found_count--;
            ctx.domino_used[low][high] = false;
            ctx.visited[r][c] = ctx.visited[r + 1][c] = false;
        }
    }
    if (ctx.skipped_count < SolverContext::MAX_SKIPPED) {
        ctx.skipped_count++;
        ctx.visited[r][c] = true;
        if (solve(next_r, next_c, ctx)) return true;
        ctx.visited[r][c] = false;
        ctx.skipped_count--;
    }
    return false;
}