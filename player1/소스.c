#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define MAX_LIFE 3

// 방향 정의
enum Direction { UP = 0, DOWN, LEFT, RIGHT };

// 방향 숫자를 문자열로 변환
const char* getDirectionString(int dir) {
    switch (dir) {
    case UP: return "↑";
    case DOWN: return "↓";
    case LEFT: return "←";
    case RIGHT: return "→";
    default: return "?";
    }
}

// 방향키 입력 받기
int getUserDirection() {
    int key = _getch();
    if (key == 0 || key == 224) {
        key = _getch(); // 방향키 코드
        switch (key) {
        case 72: return UP;
        case 80: return DOWN;
        case 75: return LEFT;
        case 77: return RIGHT;
        }
    }
    return -1; // 방향키 아님
}

// Cham Cham Cham! 출력
void printChamChamCham() {
    printf("참...\n");
    Sleep(1000);
    printf("참...\n");
    Sleep(1000);
    printf("참...!\n");
    Sleep(1000);
}

// 랭킹 저장 함수
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
    Sleep(1000);
}

// 게임 실행 함수
void playGame() {
    int score = 0;
    int life = MAX_LIFE;
    srand((unsigned int)time(NULL));

    while (life > 0) {
        system("cls");
        printf("점수: %d / 남은 기회: %d\n", score, life);
        printChamChamCham();

        printf("방향키를 눌러 방향 선택하세요...\n");
        int userDir = -1;
        while (userDir == -1) {
            userDir = getUserDirection();
        }

        int compDir = rand() % 4;

        printf("플레이어: %s\n", getDirectionString(userDir));
        printf("컴퓨터:  %s\n", getDirectionString(compDir));

        if (userDir == compDir) {
            printf("정답! 점수 +1!\n");
            score++;
        }
        else {
            printf("실패! 기회 -1\n");
            life--;
        }

        Sleep(1500);
    }

    // 게임 종료
    system("cls");
    printf("게임 오버! 최종 점수: %d\n", score);

    printf("랭킹에 등록하시겠습니까? (y/n): ");
    char choice;
    do {
        choice = _getch();
    } while (choice != 'y' && choice != 'n');

    if (choice == 'y') {
        saveRanking(score);
    }

    // 다시하기 or 종료 선택
    while (1) {
        printf("\n다시 하시겠습니까? (1: 다시하기 / 2: 종료): ");
        char retry = _getch();
        if (retry == '1') {
            playGame();  // 재귀 호출로 다시 시작
            return;
        }
        else if (retry == '2') {
            printf("\n게임을 종료합니다.\n");
            exit(0);
        }
    }
}

// 메인 함수 (게임 시작 화면)
int main() {
    while (1) {
        system("cls");
        printf("============================\n");
        printf("    🎮 참참참 게임 🎮\n");
        printf("============================\n");
        printf("Enter 키를 눌러 시작하세요...\n");

        if (_getch() == 13) break; // Enter 입력 시 시작
    }

    playGame();
    return 0;
}
