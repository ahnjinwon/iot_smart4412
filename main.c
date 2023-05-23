//알파벳 순서대로 띄우기
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <asm/ioctls.h>


#define dot "/dev/dot"
#define clcd "/dev/clcd"
#define tact_d "/dev/tactsw"

void Set_score();   //게임 종료시 최고점수 수정
void clcd_print();  //clcd 출력
void game_start();  //택트스위치 누르면 게임 시작

unsigned char mole[9][8] = {
    // 도트 매트릭스 화면
    {0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00}, //7번두더지
    {0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00}, //8번두더지
    {0x00, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00}, //9번두더지
    {0x00, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00}, //4번두더지
    {0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00}, //5번두더지
    {0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00}, //6번두더지
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x00}, //1번두더지
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00}, //2번두더지
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00}  //3번두더지
};

int main() {
    /*
    int dot_d, i, random;
    dot_d = open(dot, O_RDWR);
    if (dot_d < 0)
    {
        printf("오류 발생");
        exit(0);
    }

    for (i = 0; i < 9; i++)
    {
        write(dot_d, &mole[i], sizeof(mole[i]));
        sleep(1);
    }
    close(dot_d);
    */

    FILE* file;
    long best_score;
    long current_score = 0;

    file = fopen("best_score.txt", "r");    //텍스트 파일에서 최고 점수 받기
    fscanf(file, "%ld", &best_score);
    fclose(file);
    
    game_start(best_score, current_score);
    
    Set_score(best_score,current_score);    //게임 종료후 최고점수 비교
    return 0;
}

void Set_score(long best_score, long current_score) {   //현재점수와 기존 최고점수를 비교하여 텍스트 파일에 최고점수 쓰기함수
    if (current_score > best_score) {
        FILE* file;
        file = fopen("best_score.txt", "w");
        fprintf(file, "%ld", current_score);
        fclose(file);
    }
}

void clcd_print(long best_score ,long current_score) {  //clcd출력문

    int clcd_d;
    char score_current[5];
    char score_best[5];
    char clcd_text1[30] = "player_score: ";
    char clcd_text2[30] = "best_score: ";

    if ((clcd_d = open(clcd, O_RDWR)) < 0)
    {
        perror("open");
        exit(1);
    }
    sprintf(score_current, "%d  ", current_score);
    sprintf(score_best, "%d  ", best_score);
    strcat(clcd_text1, score_current);
    strcat(clcd_text1, clcd_text2);
    strcat(clcd_text1, score_best);

    write(clcd_d, clcd_text1, strlen(clcd_text1));
    close(clcd_d);
}

void game_start(long best_score, long current_score) { //택트스위치 누르면 게임시작
    int clcd_d;
    char str[] = "Press Any Button to Start!";
    int tact;
    unsigned char c;
    current_score = 0;

    if ((tact = open(tact_d, O_RDWR)) < 0)
    {
        perror("open");
        exit(1);
    }
    while (1)
    {
        read(tact, &c, sizeof(c));
        if (c)
            break;
    }
    switch (c)  //아무 버튼이나 누르면 게임 시작
    {
    case 1: clcd_print(best_score, current_score);
        break;
    case 2: clcd_print(best_score, current_score);
        break;
    case 3: clcd_print(best_score, current_score);
        break;
    case 4: clcd_print(best_score, current_score);
        break;
    case 5: clcd_print(best_score, current_score);
        break;
    case 6: clcd_print(best_score, current_score);
        break;
    case 7: clcd_print(best_score, current_score);
        break;
    case 8: clcd_print(best_score, current_score);
        break;
    case 9: clcd_print(best_score, current_score);
        break;
    case 10: clcd_print(best_score, current_score);
        break;
    case 11: clcd_print(best_score, current_score);
        break;
    case 12: clcd_print(best_score, current_score);
        break;
    }
    close(tact);
}