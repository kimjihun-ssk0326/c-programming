// main.c
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void printChamAnimation() {
    const char* stages[] = {
        "참", "참.", "참..",
        "참.. 참", "참.. 참.",
        "참.. 참..", "참.. 참.. 참!"
    };
    for (int i = 0; i < 7; i++) {
        gotoxy(WIDTH / 2 - 10, 0);
        printf("                        ");
        gotoxy(WIDTH / 2 - 10, 0);
        printf("%s", stages[i]);
        Sleep(300);
    }
}

char getDirectionKey(int player) {
    while (1) {
        if (_kbhit()) {
            int ch = _getch();
            if (ch == 0 || ch == 224) {
                ch = _getch(); // 방향키 (플레이어 2)
                switch (ch) {
                case 72: return 'U';
                case 80: return 'D';
                case 75: return 'L';
                case 77: return 'R';
                }
            }
            else {
                switch (ch) { // WASD (플레이어 1)
                case 'W': case 'w': return 'U';
                case 'S': case 's': return 'D';
                case 'A': case 'a': return 'L';
                case 'D': case 'd': return 'R';
                }
            }
        }
    }
}

void drawField(int p1Score[], int p2Score[], int round, char defenderDir, int attacker) {
    system("cls");

    gotoxy(0, 1);
    printf("P1: ");
    for (int i = 0; i < 3; i++) printf("%d%s", p1Score[i], i < 2 ? "/" : "");
    gotoxy(0, 2);
    printf(attacker == 0 ? "[공격]" : "[수비]");

    gotoxy(WIDTH - 10, 1);
    printf("P2: ");
    for (int i = 0; i < 3; i++) printf("%d%s", p2Score[i], i < 2 ? "/" : "");
    gotoxy(WIDTH - 10, 2);
    printf(attacker == 1 ? "[공격]" : "[수비]");

    // 수비 위치 표시
    int cx = WIDTH / 2;
    int cy = HEIGHT / 2;

    gotoxy(cx, cy);
    printf(" ");

    switch (defenderDir) {
    case 'U': gotoxy(cx, cy - 1); break;
    case 'D': gotoxy(cx, cy + 1); break;
    case 'L': gotoxy(cx - 2, cy); break;
    case 'R': gotoxy(cx + 2, cy); break;
    default: gotoxy(cx, cy); break;
    }
    printf("●");
}

void showArrow(char dir) {
    gotoxy(WIDTH / 2, HEIGHT / 2 + 3);
    switch (dir) {
    case 'U': printf("↑"); break;
    case 'D': printf("↓"); break;
    case 'L': printf("←"); break;
    case 'R': printf("→"); break;
    }
}

void blinkChangeMessage() {
    for (int i = 0; i < 4; i++) {
        gotoxy(WIDTH / 2 - 6, HEIGHT / 2);
        printf(i % 2 == 0 ? "공수 교대 중..." : "                ");
        Sleep(300);
    }
}

int main() {
    int p1Score[3] = { 0 }, p2Score[3] = { 0 };
    int round = 0;
    int swapCount = 0;
    int attacker = 0; // 0 = P1, 1 = P2
    char defenderDir = 'U'; // 초기 수비 위치

    while (swapCount < 3) {
        drawField(p1Score, p2Score, round, defenderDir, attacker);
        printChamAnimation();

        gotoxy(WIDTH / 2 - 10, HEIGHT - 3);
        printf(attacker == 0 ? "P1 공격 방향 선택 (WASD): " : "P2 공격 방향 선택 (←↑↓→): ");
        char attackDir = getDirectionKey(attacker);

        gotoxy(WIDTH / 2 - 10, HEIGHT - 2);
        printf(attacker == 1 ? "P1 수비 방향 선택 (WASD): " : "P2 수비 방향 선택 (←↑↓→): ");
        defenderDir = getDirectionKey(1 - attacker);

        drawField(p1Score, p2Score, round, defenderDir, attacker); // 수비 위치 갱신
        showArrow(attackDir);
        Sleep(1000);

        int success = attackDir == defenderDir;
        if (success) {
            blinkChangeMessage();
            attacker = 1 - attacker;
            swapCount++;
        }
        else {
            if (attacker == 0) p2Score[round]++;
            else p1Score[round]++;
        }

        if (swapCount % 1 == 0) round = swapCount;
    }

    int p1Total = p1Score[0] + p1Score[1] + p1Score[2];
    int p2Total = p2Score[0] + p2Score[1] + p2Score[2];

    system("cls");
    printf("게임 종료!\n");
    printf("최종 점수: P1 %d : %d P2\n", p1Total, p2Total);
    if (p1Total > p2Total) printf("플레이어 1 승리!\n");
    else if (p1Total < p2Total) printf("플레이어 2 승리!\n");
    else printf("무승부!\n");

    return 0;
}
