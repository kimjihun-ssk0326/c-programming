#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define MAX_LIFE 3
#define CENTER_X 40  // 중앙 기준 x 좌표

enum Direction { UP = 0, DOWN, LEFT, RIGHT };

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

const char* getDirectionString(int dir) {
    switch (dir) {
    case UP: return "↑";
    case DOWN: return "↓";
    case LEFT: return "←";
    case RIGHT: return "→";
    default: return "?";
    }
}

int getUserDirection() {
    int key = _getch();
    if (key == 0 || key == 224) {
        key = _getch();
        switch (key) {
        case 72: return UP;
        case 80: return DOWN;
        case 75: return LEFT;
        case 77: return RIGHT;
        }
    }
    return -1;
}

void printHearts(int life) {
    gotoxy(CENTER_X, 2);
    for (int i = 0; i < life; i++) printf("♥ ");
    for (int i = 0; i < MAX_LIFE - life; i++) printf("  ");
}

void printFaceDefault(int life) {
    system("cls");
    printHearts(life);
    gotoxy(CENTER_X, 4); printf("   _______");
    gotoxy(CENTER_X, 5); printf("  /       \\");
    gotoxy(CENTER_X, 6); printf(" |  O   O  |");
    gotoxy(CENTER_X, 7); printf(" |    ^    |");
    gotoxy(CENTER_X, 8); printf(" |  \\\___/  |");
    gotoxy(CENTER_X, 9); printf("  \\\_______/");
}

void printComputerFace(int dir, int life) {
    system("cls");
    printHearts(life);
    switch (dir) {
    case LEFT:
        gotoxy(CENTER_X, 4); printf("     ______");
        gotoxy(CENTER_X, 5); printf("    /      \\");
        gotoxy(CENTER_X, 6); printf("   O O      |");
        gotoxy(CENTER_X, 7); printf("  ( <       |");
        gotoxy(CENTER_X, 8); printf("   \\\___/    |");
        gotoxy(CENTER_X, 9); printf("    \\\______/");
        break;
    case RIGHT:
        gotoxy(CENTER_X, 4); printf("      ______");
        gotoxy(CENTER_X, 5); printf("     /      \\");
        gotoxy(CENTER_X, 6); printf("    |      O O");
        gotoxy(CENTER_X, 7); printf("    |       > )");
        gotoxy(CENTER_X, 8); printf("    |     \\\___/");
        gotoxy(CENTER_X, 9); printf("     \\\______/");
        break;
    case UP:
        gotoxy(CENTER_X, 4); printf("   _______");
        gotoxy(CENTER_X, 5); printf("  /  O O  \\");
        gotoxy(CENTER_X, 6); printf(" |    ^    |");
        gotoxy(CENTER_X, 7); printf(" |  \\\___/  |");
        gotoxy(CENTER_X, 8); printf(" |         |");
        gotoxy(CENTER_X, 9); printf("  \\\_______/");
        break;
    case DOWN:
        gotoxy(CENTER_X, 4); printf("  _______ ");
        gotoxy(CENTER_X, 5); printf(" /       \\");
        gotoxy(CENTER_X, 6); printf("|         |");
        gotoxy(CENTER_X, 7); printf("|         |");
        gotoxy(CENTER_X, 8); printf("|    O  O  )");
        gotoxy(CENTER_X, 9); printf("|      ^  |");
        gotoxy(CENTER_X, 10); printf(" \\\____'__/ ");
        break;
    default:
        printFaceDefault(life);
        break;
    }
}

void printChamChamCham() {
    gotoxy(CENTER_X, 15); printf("참...");
    Sleep(1000);
    gotoxy(CENTER_X, 16); printf("참...");
    Sleep(1000);
    gotoxy(CENTER_X, 17); printf("참...!");
    Sleep(1000);
}

void saveRanking(int score) {
    char name[50];
    printf("이름을 입력하세요: ");
    scanf("%s", name);

    FILE* fp = fopen("ranking.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "%s %d\n", name, score);
        fclose(fp);
        printf("랭킹에 저장되었습니다!\n");
    }
    else {
        printf("랭킹 저장 실패!\n");
    }
    printf("계속하려면 아무 키나 누르세요...");
    _getch();
}

void playGame() {
    int score = 0;
    int life = MAX_LIFE;
    srand((unsigned int)time(NULL));

    while (life > 0) {
        printFaceDefault(life);
        gotoxy(CENTER_X, 11); printf("점수: %d", score);

        gotoxy(CENTER_X, 13); printf("방향키를 눌러 방향을 선택하세요...");
        int userDir = -1;
        while (userDir == -1) {
            userDir = getUserDirection();
        }

        printChamChamCham();

        int compDir = rand() % 4;
        printComputerFace(compDir, life);

        gotoxy(CENTER_X, 11); printf("플레이어: %s", getDirectionString(userDir));
        gotoxy(CENTER_X, 12); printf("컴퓨터 : %s", getDirectionString(compDir));

        if (userDir == compDir) {
            gotoxy(CENTER_X, 14); printf("정답! 점수 +1!");
            score++;
        }
        else {
            gotoxy(CENTER_X, 14); printf("실패! 기회 -1");
            life--;
        }

        gotoxy(CENTER_X, 18); printf("계속하려면 아무 키나 누르세요...");
        _getch();
    }

    system("cls");
    gotoxy(CENTER_X, 5); printf("\U0001F480 게임 오버! 최종 점수: %d\n", score);
    gotoxy(CENTER_X, 7); printf("계속하려면 아무 키나 누르세요...");
    _getch();

    gotoxy(CENTER_X, 9); printf("랭킹에 등록하시겠습니까? (y/n): ");
    char choice;
    do {
        choice = _getch();
    } while (choice != 'y' && choice != 'n');

    if (choice == 'y') {
        saveRanking(score);
    }

    while (1) {
        gotoxy(CENTER_X, 11); printf("다시 하시겠습니까? (1: 다시하기 / 2: 종료): ");
        char retry = _getch();
        if (retry == '1') {
            playGame();
            return;
        }
        else if (retry == '2') {
            gotoxy(CENTER_X, 13); printf("게임을 종료합니다.\n");
            exit(0);
        }
    }
}

int main() {
    while (1) {
        system("cls");
        gotoxy(CENTER_X, 5); printf("============================");
        gotoxy(CENTER_X, 6); printf("    \U0001F3AE 참참참 게임 \U0001F3AE");
        gotoxy(CENTER_X, 7); printf("============================");
        gotoxy(CENTER_X, 9); printf("Enter 키를 눌러 시작하세요...");

        if (_getch() == 13) break;
    }

    playGame();
    return 0;
}