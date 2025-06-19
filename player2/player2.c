#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

#define WIDTH 60
#define HEIGHT 20

void gotoxy(int x, int y) {
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setColor(int fg, int bg) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bg << 4) | fg);
}

void drawFace(int x, int y, char dir) {
    switch (dir) {
    case 'U':
        gotoxy(x, y);     printf("   _______");
        gotoxy(x, y + 1); printf("  /  O O  \\");
        gotoxy(x, y + 2); printf(" |    ^    |");
        gotoxy(x, y + 3); printf(" |  \\___/  |");
        gotoxy(x, y + 4); printf(" |         |");
        gotoxy(x, y + 5); printf("  \\_______/");
        break;
    case 'D':
        gotoxy(x, y);     printf("  _______ ");
        gotoxy(x, y + 1); printf(" /       \\");
        gotoxy(x, y + 2); printf("|         |");
        gotoxy(x, y + 3); printf("|         |");
        gotoxy(x, y + 4); printf("|    O  O  )");
        gotoxy(x, y + 5); printf("|      ^  |");
        gotoxy(x, y + 6); printf(" \\____'__/ ");
        break;
    case 'L':
        gotoxy(x, y);     printf("     ______");
        gotoxy(x, y + 1); printf("    /      \\");
        gotoxy(x, y + 2); printf("   O O      |");
        gotoxy(x, y + 3); printf("  ( <       |");
        gotoxy(x, y + 4); printf("   \\___/    |");
        gotoxy(x, y + 5); printf("    \\______/");
        break;
    case 'R':
        gotoxy(x, y);     printf("      ______");
        gotoxy(x, y + 1); printf("     /      \\");
        gotoxy(x, y + 2); printf("    |      O O");
        gotoxy(x, y + 3); printf("    |       > )");
        gotoxy(x, y + 4); printf("    |     \\___/");
        gotoxy(x, y + 5); printf("     \\______/");
        break;
    }
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
                ch = _getch();
                switch (ch) {
                case 72: return 'U'; // Up
                case 80: return 'D'; // Down
                case 75: return 'L'; // Left
                case 77: return 'R'; // Right
                }
            }
            else {
                switch (ch) {
                case 'W': case 'w': return 'U';
                case 'S': case 's': return 'D';
                case 'A': case 'a': return 'L';
                case 'D': case 'd': return 'R';
                }
            }
        }
    }
}

const char* getArrow(char dir) {
    switch (dir) {
    case 'U': return "↑";
    case 'D': return "↓";
    case 'L': return "←";
    case 'R': return "→";
    default: return "?";
    }
}

void drawScores(int p1Score[], int p2Score[]) {
    int centerX = WIDTH / 2;
    gotoxy(centerX - 15, 1);
    printf("P1: ");
    for (int i = 0; i < 3; i++) {
        printf("%d%s", p1Score[i], i < 2 ? "/" : "");
    }
    gotoxy(centerX + 10, 1);
    printf("P2: ");
    for (int i = 0; i < 3; i++) {
        printf("%d%s", p2Score[i], i < 2 ? "/" : "");
    }
}

void drawField(int p1Score[], int p2Score[], int round, char defenderDir, int attacker) {
    system("cls");

    int centerX = WIDTH / 2;
    int faceX = centerX - 5;
    int faceY = HEIGHT / 2 - 6;

    drawScores(p1Score, p2Score);

    gotoxy(centerX - 15, 2);
    printf(attacker == 0 ? "[공격]" : "[수비]");
    gotoxy(centerX + 10, 2);
    printf(attacker == 1 ? "[공격]" : "[수비]");

    drawFace(faceX, faceY, defenderDir);
}

void blinkChangeMessage() {
    for (int i = 0; i < 4; i++) {
        gotoxy(WIDTH / 2 - 6, HEIGHT / 2 + 4);
        printf(i % 2 == 0 ? "공수 교대 중..." : "                ");
        Sleep(300);
    }
}

void highlightScore(int p1Score[], int p2Score[], int round, int attacker) {
    int centerX = WIDTH / 2;

    int x, y = 1;
    if (attacker == 0) {
        x = centerX + 10;
    }
    else {
        x = centerX - 15;
    }

    int posX = x + 4 + round * 2;

    gotoxy(posX, y);
    setColor(4, 0);

    int val = (attacker == 0) ? p2Score[round] : p1Score[round];
    printf("%d", val);

    Sleep(300);

    setColor(7, 0);

    drawScores(p1Score, p2Score);
}

void showResultAndSelect(int p1Total, int p2Total);

void playGame() {
    int p1Score[3] = { 0 }, p2Score[3] = { 0 };
    int swapCount = 0;
    int attacker = 0;
    char defenderDir = 'U';

    while (swapCount < 6) {
        int round = swapCount / 2;

        drawField(p1Score, p2Score, round, defenderDir, attacker);
        printChamAnimation();

        int inputY = HEIGHT - 3;

        // 항상 공격, 수비 텍스트 같이 출력
        gotoxy(2, inputY);
        printf("P1 방향 선택 (WASD): ");

        gotoxy(35, inputY);
        printf("P2 방향 선택 (←↑↓→): ");

        char attackDir = 0, defenderInputDir = 0;

        // 공격 방향 입력
        if (attacker == 0) {
            gotoxy(2 + 22, inputY);
            attackDir = getDirectionKey(attacker);
        }
        else {
            gotoxy(35 + 22, inputY);
            attackDir = getDirectionKey(attacker);
        }

        // 수비 방향 입력
        if (attacker == 1) {
            gotoxy(2 + 22, inputY);
            defenderInputDir = getDirectionKey(1 - attacker);
        }
        else {
            gotoxy(35 + 22, inputY);
            defenderInputDir = getDirectionKey(1 - attacker);
        }
        defenderDir = defenderInputDir;

        drawField(p1Score, p2Score, round, defenderDir, attacker);

        // 공격 방향 표시 - 좌우 나누기
        if (attacker == 0) {
            gotoxy(2, HEIGHT / 2 + 3);
            printf("공격 방향: %s  ", getArrow(attackDir));
        }
        else {
            gotoxy(35, HEIGHT / 2 + 3);
            printf("공격 방향: %s  ", getArrow(attackDir));
        }

        Sleep(1000);

        if (attackDir == defenderDir) {
            if (swapCount < 5) {
                blinkChangeMessage();
            }
            attacker = 1 - attacker;
            swapCount++;
        }
        else {
            if (attacker == 0) {
                p2Score[round]++;
            }
            else {
                p1Score[round]++;
            }
            highlightScore(p1Score, p2Score, round, attacker);
        }

        defenderDir = 'U';
        drawField(p1Score, p2Score, round, defenderDir, attacker);
    }

    int p1Total = p1Score[0] + p1Score[1] + p1Score[2];
    int p2Total = p2Score[0] + p2Score[1] + p2Score[2];

    showResultAndSelect(p1Total, p2Total);
}

void showResultAndSelect(int p1Total, int p2Total) {
    system("cls");
    int centerX = WIDTH / 2 - 7;
    int centerY = HEIGHT / 2 - 2;

    gotoxy(centerX, centerY);
    if (p1Total > p2Total) printf("플레이어 1 승리!");
    else if (p1Total < p2Total) printf("플레이어 2 승리!");
    else printf("무승부!");

    gotoxy(centerX, centerY + 2);
    printf("다시하기");
    gotoxy(centerX, centerY + 3);
    printf("나가기");

    int selection = 0;
    while (1) {
        gotoxy(centerX - 2, centerY + 2 + selection);
        printf(">");
        gotoxy(centerX - 2, centerY + 2 + (1 - selection));
        printf(" ");

        int ch = _getch();
        if (ch == 0 || ch == 224) {
            ch = _getch();
            if (ch == 72 || ch == 80) {
                selection = 1 - selection;
            }
        }
        else if (ch == 13) {
            if (selection == 0) {
                playGame();
                return;
            }
            else if (selection == 1) {
                gotoxy(centerX, centerY + 5);
                printf("게임을 종료합니다.\n");
                exit(0);
            }
        }
    }
}

int main() {
    playGame();
    return 0;
}
