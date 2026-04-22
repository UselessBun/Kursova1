#include <iostream>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;
struct domino{
    int a,b;
    int x1,y1,x2,y2;
};
const int ROWS = 6;
const int COLS = 10;
const int MAX_SKIPPED = 4;

bool visited[ROWS][COLS];
bool domino_used[7][7];
domino answer[28];
int found_count = 0;
int skipped_count = 0;

int riddle[ROWS][COLS] = {
    {0,0,1,1,2,3,3,5,4,0},
    {3,3,2,5,6,6,3,4,2,0},
    {6,3,0,6,1,1,6,4,2,0},
    {2,2,4,3,6,6,1,3,2,2},
    {2,4,4,0,0,5,4,5,5,5},
    {1,1,4,6,0,5,1,3,5,3}
};
bool solve(int r, int c) {
    // Якщо всі 28 доміно знайдено, повертаємо успіх
    if (found_count == 28) return true;
    if (r == ROWS) return false;

    // Перехід до наступної клітинки
    int next_r = r, next_c = c + 1;
    if (next_c == COLS) {
        next_r = r + 1;
        next_c = 0;
    }

    if (visited[r][c]) return solve(next_r, next_c);

    // ВАРІАНТ 1: ГОРИЗОНТАЛЬНО
    if (c + 1 < COLS && !visited[r][c + 1]) {
        int v1 = riddle[r][c], v2 = riddle[r][c + 1];
        int low = min(v1, v2), high = max(v1, v2);

        if (!domino_used[low][high]) {
            domino_used[low][high] = true;
            visited[r][c] = visited[r][c + 1] = true;
            answer[found_count++] = {low, high, r, c, r, c + 1};

            if (solve(next_r, next_c)) return true;

            found_count--;
            domino_used[low][high] = false;
            visited[r][c] = visited[r][c + 1] = false;
        }
    }

    // ВАРІАНТ 2: ВЕРТИКАЛЬНО
    if (r + 1 < ROWS && !visited[r + 1][c]) {
        int v1 = riddle[r][c], v2 = riddle[r + 1][c];
        int low = min(v1, v2), high = max(v1, v2);

        if (!domino_used[low][high]) {
            domino_used[low][high] = true;
            visited[r][c] = visited[r + 1][c] = true;
            answer[found_count++] = {low, high, r, c, r + 1, c};

            if (solve(next_r, next_c)) return true;

            found_count--;
            domino_used[low][high] = false;
            visited[r][c] = visited[r + 1][c] = false;
        }
    }

    // ВАРІАНТ 3: ПРОПУСК (якщо ліміт дозволяє)
    if (skipped_count < MAX_SKIPPED) {
        skipped_count++;
        visited[r][c] = true; // Тимчасово позначаємо як зайняту (пропущену)
        if (solve(next_r, next_c)) return true;
        visited[r][c] = false;
        skipped_count--;
    }

    return false;
}
bool compareDominoes(const domino& d1, const domino& d2) {
    if (d1.a != d2.a) {
        return d1.a < d2.a;
    }
    return d1.b < d2.b;
}

int main() {
    auto start = high_resolution_clock::now();
    cout<<"Original Grid:\n";
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << riddle[i][j] << " ";
        }
        cout << endl;
    }
    if (solve(0, 0)) {
        sort(answer, answer + 28, compareDominoes);
        cout << "Solution found!" << endl;
        for (int i = 0; i < 28; i++) {
            if (i > 0 && answer[i].a != answer[i-1].a) cout << endl;
            cout << "Domino " << answer[i].a << "-" << answer[i].b 
                 << " at (" << answer[i].x1 << "," << answer[i].y1 << ") & (" 
                 << answer[i].x2 << "," << answer[i].y2 << ")" << endl;
        }
        cout << "\nVisual Grid (Red background = unused cells):\n";
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                bool cell_is_used = false;
                for (int k = 0; k < 28; k++) {
                    if ((answer[k].x1 == i && answer[k].y1 == j) || 
                        (answer[k].x2 == i && answer[k].y2 == j)) {
                        cell_is_used = true;
                        break;
                    }
                }
                if (!cell_is_used) {
                    // Якщо клітинка не належить жодному доміно з відповіді — вона зайва
                    cout << "\033[101m " << riddle[i][j] << " \033[0m ";
                } else {
                    cout << " " << riddle[i][j] << "  ";
                }
            }
            cout << endl;
        }
    } else {
        cout << "No solution exists." << endl;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout <<"Program took: "<< duration.count() << " milliseconds" << endl;
    return 0;
}