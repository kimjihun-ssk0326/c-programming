//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <conio.h>
//#include <windows.h>
//#include <time.h>
//
//#define MAX_LIFE 3
//
//enum Direction { UP = 0, DOWN, LEFT, RIGHT };
//
//// 방향 문자열
//const char* getDirectionString(int dir) {
//    switch (dir) {
//    case UP: return "↑";
//    case DOWN: return "↓";
//    case LEFT: return "←";
//    case RIGHT: return "→";
//    default: return "?";
//    }
//}
//
//// 방향키 입력
//int getUserDirection() {
//    int key = _getch();
//    if (key == 0 || key == 224) {
//        key = _getch();
//        switch (key) {
//        case 72: return UP;
//        case 80: return DOWN;
//        case 75: return LEFT;
//        case 77: return RIGHT;
//        }
//    }
//    return -1;
//}
//
//// ♥ 하트 출력
//void printHearts(int life) {
//    printf("      ");
//    for (int i = 0; i < life; i++) printf("♥ ");
//    for (int i = 0; i < MAX_LIFE - life; i++) printf("  ");
//    printf("\n");
//}
//
//// 기본 정면 얼굴
//void printFaceDefault(int life) {
//    system("cls");
//    printHearts(life);
//    printf("   _______\n");
//    printf("  /       \\\n");
//    printf(" |  O   O  |\n");
//    printf(" |    ^    |\n");
//    printf(" |  \\___/  |\n");
//    printf("  \\_______/\n");
//}
//
//// 방향에 따른 얼굴
//void printComputerFace(int dir, int life) {
//    system("cls");
//    printHearts(life);
//    switch (dir) {
//    case LEFT:
//        printf("     ______\n");
//        printf("    /      \\\n");
//        printf("   O O      |\n");
//        printf("  ( <       |\n");
//        printf("   \\___/    |\n");
//        printf("    \\______/\n");
//        break;
//    case RIGHT:
//        printf("      ______\n");
//        printf("     /      \\\n");
//        printf("    |      O O\n");
//        printf("    |       > )\n");
//        printf("    |     \\___/\n");
//        printf("     \\______/\n");
//        break;
//    case UP:
//        printf("   _______\n");
//        printf("  /  O O  \\\n");
//        printf(" |    ^    |\n");
//        printf(" |  \\___/  |\n");
//        printf(" |         |\n");
//        printf("  \\_______/\n");
//        break;
//    case DOWN:
//        printf("  _______ \n");
//        printf(" /       \\\n");
//        printf("|         |\n");
//        printf("|         |\n");
//        printf("|    O  O  )\n");
//        printf("|      ^  |\n");
//        printf(" \\____'__/ \n");
//        break;
//    default:
//        printFaceDefault(life);
//        break;
//    }
//}
//
//// Cham 출력
//void printChamChamCham() {
//    printf("\n참...\n");
//    Sleep(1000);
//    printf("참...\n");
//    Sleep(1000);
//    printf("참...!\n");
//    Sleep(1000);
//}
//
//// 랭킹 저장
//void saveRanking(int score) {
//    char name[50];
//    printf("이름을 입력하세요: ");
//    scanf("%s", name);
//
//    FILE* fp = fopen("ranking.txt", "a");
//    if (fp != NULL) {
//        fprintf(fp, "%s %d\n", name, score);
//        fclose(fp);
//        printf("랭킹에 저장되었습니다!\n");
//    }
//    else {
//        printf("랭킹 저장 실패!\n");
//    }
//    printf("계속하려면 아무 키나 누르세요...");
//    _getch();
//}
//
//// 게임 실행
//void playGame() {
//    int score = 0;
//    int life = MAX_LIFE;
//    srand((unsigned int)time(NULL));
//
//    while (life > 0) {
//        printFaceDefault(life);
//        printf("\n점수: %d\n", score);
//        printChamChamCham();
//
//        printf("\n방향키를 눌러 방향 선택하세요...\n");
//        int userDir = -1;
//        while (userDir == -1) {
//            userDir = getUserDirection();
//        }
//
//        int compDir = rand() % 4;
//        printComputerFace(compDir, life);
//        printf("\n플레이어: %s\n", getDirectionString(userDir));
//        printf("컴퓨터 : %s\n", getDirectionString(compDir));
//
//        if (userDir == compDir) {
//            printf("\n정답! 점수 +1!\n");
//            score++;
//        }
//        else {
//            printf("\n실패! 기회 -1\n");
//            life--;
//        }
//
//        printf("\n계속하려면 아무 키나 누르세요...");
//        _getch();  // 플레이어 조작 대기
//    }
//
//    // 게임 오버 화면
//    system("cls");
//    printf("💀 게임 오버! 최종 점수: %d\n", score);
//    printf("\n계속하려면 아무 키나 누르세요...");
//    _getch();
//
//    printf("\n랭킹에 등록하시겠습니까? (y/n): ");
//    char choice;
//    do {
//        choice = _getch();
//    } while (choice != 'y' && choice != 'n');
//
//    if (choice == 'y') {
//        saveRanking(score);
//    }
//
//    // 다시하기 or 종료
//    while (1) {
//        printf("\n다시 하시겠습니까? (1: 다시하기 / 2: 종료): ");
//        char retry = _getch();
//        if (retry == '1') {
//            playGame();
//            return;
//        }
//        else if (retry == '2') {
//            printf("\n게임을 종료합니다.\n");
//            exit(0);
//        }
//    }
//}
//
//// 메인 시작화면
//int main() {
//    while (1) {
//        system("cls");
//        printf("============================\n");
//        printf("    🎮 참참참 게임 🎮\n");
//        printf("============================\n");
//        printf("Enter 키를 눌러 시작하세요...\n");
//
//        if (_getch() == 13) break;
//    }
//
//    playGame();
//    return 0;
//}
