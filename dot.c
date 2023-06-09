#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <asm/ioctls.h>
#include <time.h>


#define dot "/dev/dot"
#define clcd "/dev/clcd"
#define tact_d "/dev/tactsw"
#define FND_DEVICE "/dev/fnd"

void Set_score();   //게임 종료시 최고점수 수정
void stage_1_clcd_print();  //1스테이지 clcd 출력
void stage_2_clcd_print();  //2스테이지 clcd 출력
void stage_3_clcd_print();  //3스테이지 clcd 출력
void game_start();  //택트스위치 누르면 게임 시작
void timer();

unsigned char mole[9][8] = {
    // 도트 매트릭스 화면
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x00}, //1번두더지
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00}, //2번두더지
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00}, //3번두더지
    {0x00, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00}, //4번두더지
    {0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00}, //5번두더지
    {0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00}, //6번두더지
    {0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00}, //7번두더지
    {0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00}, //8번두더지
    {0x00, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00}  //9번두더지
};

const unsigned char fnd_data[16] = {    //fnd
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0xA0, 0x88, 0x83, 0xC6, 0xA1, 0x8E
};

int main() {

    FILE* file;
    int clcd_d;     //clcd
    long best_score;    //최고점수
    long current_score = 0;//현재점수
    int run = 0;    //게임 진행을 위한 무한루프
    int state = 0;  //게임 시작 전 무한루프를 위한 정수
    int count = 60; //남은시간
    int life = 5;   //목숨
    int stage = 1;  //스테이지
    int end_time = (unsigned)time(NULL);//끝나는 시간
    end_time += 10; //60초 카운트
    int tact;
    int dot_d, i, random;
    unsigned char c;
    int button = 0;


    
    while (1) {
        random = rand() % 9;
        dot_d = open(dot, O_RDWR);
        if (dot_d < 0 | tact < 0)
        {
            printf("오류 발생");
            exit(0);
        }
        write(dot_d, &mole[random], sizeof(mole[random]));
        usleep(10000);
        close(dot_d);

        tact = open(tact_d, O_RDWR);
        read(tact, &c, sizeof(c));
        close(tact);

        switch (c)  // 두더지와 tackswitch 연결
        {
        case 1:
            button = 1;

            if ((clcd_d = open(clcd, O_RDWR)) < 0)
            {
                perror("open");
                exit(1);
            }

            if (random == button)
            {
                write(clcd_d, "성공", strlen("성공"));
            }
            write(clcd_d, "성공", strlen("성공"));
            close(clcd_d);
            sleep(2);
            state = 1;
            break;
        case 2:
            button = 2;
            if ((clcd_d = open(clcd, O_RDWR)) < 0)
            {
                perror("open");
                exit(1);
            }

            if (random == button)
            {
                write(clcd_d, "성공", strlen("성공"));
            }
            write(clcd_d, "성공", strlen("성공"));
            close(clcd_d);
            sleep(2);
            state = 1;
            break;

        case 3:
            button = 3;
            if ((clcd_d = open(clcd, O_RDWR)) < 0)
            {
                perror("open");
                exit(1);
            }

            if (random == button)
            {
                write(clcd_d, "성공", strlen("성공"));
            }
            write(clcd_d, "성공", strlen("성공"));
            close(clcd_d);
            sleep(2);
            state = 1;
            break;

        case 4:
            button = 4;
            if ((clcd_d = open(clcd, O_RDWR)) < 0)
            {
                perror("open");
                exit(1);
            }

            if (random == button)
            {
                write(clcd_d, "성공", strlen("성공"));
            }
            write(clcd_d, "성공", strlen("성공"));
            close(clcd_d);
            sleep(2);
            state = 1;
            break;
        case 5:
            button = 5;
            if ((clcd_d = open(clcd, O_RDWR)) < 0)
            {
                perror("open");
                exit(1);
            }

            if (random == button)
            {
                write(clcd_d, "성공", strlen("성공"));
            }
            write(clcd_d, "성공", strlen("성공"));
            close(clcd_d);
            sleep(2);
            state = 1;
            break;
        case 6:
            button = 6;
            if ((clcd_d = open(clcd, O_RDWR)) < 0)
            {
                perror("open");
                exit(1);
            }

            if (random == button)
            {
                write(clcd_d, "성공", strlen("성공"));
            }
            write(clcd_d, "성공", strlen("성공"));
            close(clcd_d);
            sleep(2);
            state = 1;
            break;
        case 7:
            button = 7;
            if ((clcd_d = open(clcd, O_RDWR)) < 0)
            {
                perror("open");
                exit(1);
            }

            if (random == button)
            {
                write(clcd_d, "성공", strlen("성공"));
            }
            write(clcd_d, "성공", strlen("성공"));
            close(clcd_d);
            sleep(2);
            state = 1;
            break;

        case 8:
            button = 8;
            if ((clcd_d = open(clcd, O_RDWR)) < 0)
            {
                perror("open");
                exit(1);
            }

            if (random == button)
            {
                write(clcd_d, "성공", strlen("성공"));
            }
            write(clcd_d, "성공", strlen("성공"));
            close(clcd_d);
            sleep(2);
            state = 1;
            break;

        case 9:
            button = 9;
            if ((clcd_d = open(clcd, O_RDWR)) < 0)
            {
                perror("open");
                exit(1);
            }

            if (random == button)
            {
                write(clcd_d, "성공", strlen("성공"));
            }
            write(clcd_d, "성공", strlen("성공"));
            close(clcd_d);
            sleep(2);
            state = 1;
            break;

        case 10:
            button = 10;
            if ((clcd_d = open(clcd, O_RDWR)) < 0)
            {
                perror("open");
                exit(1);
            }

            if (random == button)
            {
                write(clcd_d, "성공", strlen("성공"));
            }
            write(clcd_d, "성공", strlen("성공"));
            close(clcd_d);
            sleep(2);
            state = 1;
            break;

        case 11:
            button = 11;
            if ((clcd_d = open(clcd, O_RDWR)) < 0)
            {
                perror("open");
                exit(1);
            }

            if (random == button)
            {
                write(clcd_d, "성공", strlen("성공"));
            }
            write(clcd_d, "성공", strlen("성공"));
            close(clcd_d);
            sleep(2);
            state = 1;
            break;
        case 12:
            button = 12;
            if ((clcd_d = open(clcd, O_RDWR)) < 0)
            {
                perror("open");
                exit(1);
            }

            if (random == button)
            {
                write(clcd_d, "성공", strlen("성공"));
            }
            write(clcd_d, "성공", strlen("성공"));
            close(clcd_d);
            sleep(2);
            state = 1;
            break;
        }
        close(clcd_d);
        close(tact);
        close(dot_d);
    }
}


/*
    file = fopen("best_score.txt", "r");    //텍스트 파일에서 최고 점수 받기
    fscanf(file, "%ld", &best_score);
    fclose(file);
    
    game_start(best_score, current_score, state);
    while (state = 0) { //정확한 시간체크를 위해 게임 시작 전까지 무한루프 돌려놓기
        if (state == 1)
            break;
    }
    while (run == 0) {  //무한루프 돌면서 게임 시작

        timer();

        if (life <= 0) {    //목숨이 0이 되면 Game Over
            if ((clcd_d = open(clcd, O_RDWR)) < 0)
            {
                perror("open");
                exit(1);
            }
            write(clcd_d, "Game Over", strlen("Game Over"));
            close(clcd_d);
            sleep(1);
            run = 1;
        }

        if (stage == 1) {   //1스테이지
            stage_1_clcd_print(best_score, current_score, life);
            if (current_score >= 100) { //100점을 넘기면 2스테이지 진입
                stage = 2;
            }
        }

        if (stage == 2) {   //2스테이지
            stage_2_clcd_print(best_score, current_score, life);
            if (current_score >= 250) { //250점을 넘기면 3스테이지 진입
                stage = 3;
            }
        }

        if (stage == 3) {   //3스테이지
            stage_3_clcd_print(best_score, current_score, life);
        }

    }
    Set_score(best_score,current_score);    //게임 종료후 최고점수 비교
    return 0;
}

void Set_score(long best_score, long current_score) {   //현재점수와 기존 최고점수를 비교
    if (current_score > best_score) {   //기록 갱신 시 New Best Score로 점수 표기, txt파일에 최고기록 갱신
        FILE* file;
        file = fopen("best_score.txt", "w");
        fprintf(file, "%ld", current_score);
        fclose(file);

        int clcd_d;
        char new_bestscore[5];
        char clcd_score[30] = "New Best Score! : ";
        sprintf(new_bestscore, "%d ", current_score);
        strcat(clcd_score, new_bestscore);
        if ((clcd_d = open(clcd, O_RDWR)) < 0)
        {
            perror("open");
            exit(1);
        }
        write(clcd_d, clcd_score, strlen(clcd_score));
        close(clcd_d);
    }
    else {                              //기록 갱신 실패 시 기존 최고점수를 표기
        int clcd_d;
        char new_bestscore[5];
        char clcd_score[30] = "best_score: ";
        if ((clcd_d = open(clcd, O_RDWR)) < 0)
        {
            perror("open");
            exit(1);
        }
        write(clcd_d, clcd_score, strlen(clcd_score));
        close(clcd_d);
    }
}

void stage_1_clcd_print(long best_score ,long current_score, int life) {  //1스테이지 clcd출력문

    int clcd_d;
    char stage_clcd[5];
    char life_clcd[5];
    char score_current[5];
    char score_best[5];
    
    char clcd_stage[30] = "stage: ";
    char clcd_life[30] = "life: ";
    char clcd_text1[30] = "score: ";

    if ((clcd_d = open(clcd, O_RDWR)) < 0)
    {
        perror("open");
        exit(1);
    }
    sprintf(stage_clcd, "1 ");
    sprintf(score_current, "%d  ", current_score);
    sprintf(life_clcd, "%d", life);
    strcat(clcd_stage, stage_clcd);
    strcat(clcd_stage, clcd_life);
    strcat(clcd_stage, life_clcd);
    strcat(clcd_stage, clcd_text1);
    strcat(clcd_stage, score_current);

    write(clcd_d, clcd_stage, strlen(clcd_stage));
    close(clcd_d);
}

void stage_2_clcd_print(long best_score, long current_score, int life) {  //2스테이지 clcd출력문

    int clcd_d;
    char stage_clcd[5];
    char life_clcd[5];
    char score_current[5];
    char score_best[5];

    char clcd_stage[30] = "stage: ";
    char clcd_life[30] = "life: ";
    char clcd_text1[30] = "score: ";

    if ((clcd_d = open(clcd, O_RDWR)) < 0)
    {
        perror("open");
        exit(1);
    }
    sprintf(stage_clcd, "2 ");
    sprintf(score_current, "%d  ", current_score);
    sprintf(life_clcd, "%d", life);
    strcat(clcd_stage, stage_clcd);
    strcat(clcd_stage, clcd_life);
    strcat(clcd_stage, life_clcd);
    strcat(clcd_stage, clcd_text1);
    strcat(clcd_stage, score_current);

    write(clcd_d, clcd_stage, strlen(clcd_stage));
    close(clcd_d);
}

void stage_3_clcd_print(long best_score, long current_score, int life) {  //3스테이지 clcd출력문

    int clcd_d;
    char stage_clcd[5];
    char life_clcd[5];
    char score_current[5];
    char score_best[5];

    char clcd_stage[30] = "stage: ";
    char clcd_life[30] = "life: ";
    char clcd_text1[30] = "score: ";

    if ((clcd_d = open(clcd, O_RDWR)) < 0)
    {
        perror("open");
        exit(1);
    }
    sprintf(stage_clcd, "3 ");
    sprintf(score_current, "%d  ", current_score);
    sprintf(life_clcd, "%d", life);
    strcat(clcd_stage, stage_clcd);
    strcat(clcd_stage, clcd_life);
    strcat(clcd_stage, life_clcd);
    strcat(clcd_stage, clcd_text1);
    strcat(clcd_stage, score_current);

    write(clcd_d, clcd_stage, strlen(clcd_stage));
    close(clcd_d);
}


void game_start(long best_score, long current_score, int state) { //게임 시작 부분
    int clcd_d;
    char str[] = "Press Any Button";
    char Best_Score[] = "best_score:";
    char score_best[5];
    int tact;
    unsigned char c;
    sprintf(score_best, "%d  ",best_score);

    if ((tact = open(tact_d, O_RDWR)) < 0)
    {
        perror("open");
        exit(1);
    }
    if ((clcd_d = open(clcd, O_RDWR)) < 0)
    {
        perror("open");
        exit(1);
    }
    write(clcd_d, str, strlen(str));    //프로그램 시작 시 clcd에 press any button 표기
    
    while (1)
    {
        read(tact, &c, sizeof(c));
        if (c)
            break;
    }
    switch (c)  //아무 버튼이나 누르면 최고점수 표시 후 게임 시작
    {
    case 1: 
        if ((clcd_d = open(clcd, O_RDWR)) < 0)
        {
            perror("open");
            exit(1);
        }
        strcat(Best_Score, score_best);
        write(clcd_d, Best_Score, strlen(Best_Score));
        sleep(2);
        stage_1_clcd_print(best_score, current_score, 5);
        state = 1;
        break;
    case 2: 
        if ((clcd_d = open(clcd, O_RDWR)) < 0)
        {
            perror("open");
            exit(1);
        }
        strcat(Best_Score, score_best);
        write(clcd_d, Best_Score, strlen(Best_Score));
        sleep(2); 
        stage_1_clcd_print(best_score, current_score, 5);
        state = 1;
        break;
    case 3: 
        if ((clcd_d = open(clcd, O_RDWR)) < 0)
        {
            perror("open");
            exit(1);
        }
        strcat(Best_Score, score_best);
        write(clcd_d, Best_Score, strlen(Best_Score));
        sleep(2); 
        stage_1_clcd_print(best_score, current_score, 5);
        state = 1;
        break;
    case 4: 
        if ((clcd_d = open(clcd, O_RDWR)) < 0)
        {
            perror("open");
            exit(1);
        }
        strcat(Best_Score, score_best);
        write(clcd_d, Best_Score, strlen(Best_Score));
        sleep(2); 
        stage_1_clcd_print(best_score, current_score, 5);
        state = 1;
        break;
    case 5: 
        if ((clcd_d = open(clcd, O_RDWR)) < 0)
        {
            perror("open");
            exit(1);
        }
        strcat(Best_Score, score_best);
        write(clcd_d, Best_Score, strlen(Best_Score));
        sleep(2); 
        stage_1_clcd_print(best_score, current_score, 5);
        state = 1;
        break;
    case 6: 
        if ((clcd_d = open(clcd, O_RDWR)) < 0)
        {
            perror("open");
            exit(1);
        }
        strcat(Best_Score, score_best);
        write(clcd_d, Best_Score, strlen(Best_Score));
        sleep(2); 
        stage_1_clcd_print(best_score, current_score, 5);
        state = 1;
        break;
    case 7: 
        if ((clcd_d = open(clcd, O_RDWR)) < 0)
        {
            perror("open");
            exit(1);
        }
        strcat(Best_Score, score_best);
        write(clcd_d, Best_Score, strlen(Best_Score));
        sleep(2); 
        stage_1_clcd_print(best_score, current_score, 5);
        state = 1;
        break;
    case 8: 
        if ((clcd_d = open(clcd, O_RDWR)) < 0)
        {
            perror("open");
            exit(1);
        }
        strcat(Best_Score, score_best);
        write(clcd_d, Best_Score, strlen(Best_Score));
        sleep(2); 
        stage_1_clcd_print(best_score, current_score, 5);
        state = 1;
        break;
    case 9: 
        if ((clcd_d = open(clcd, O_RDWR)) < 0)
        {
            perror("open");
            exit(1);
        }
        strcat(Best_Score, score_best);
        write(clcd_d, Best_Score, strlen(Best_Score));
        sleep(2); 
        stage_1_clcd_print(best_score, current_score, 5);
        state = 1;
        break;
    case 10: 
        if ((clcd_d = open(clcd, O_RDWR)) < 0)
        {
            perror("open");
            exit(1);
        }
        strcat(Best_Score, score_best);
        write(clcd_d, Best_Score, strlen(Best_Score));
        sleep(2); 
        stage_1_clcd_print(best_score, current_score, 5);
        state = 1;
        break;
    case 11: 
        if ((clcd_d = open(clcd, O_RDWR)) < 0)
        {
            perror("open");
            exit(1);
        }
        strcat(Best_Score, score_best);
        write(clcd_d, Best_Score, strlen(Best_Score));
        sleep(2); 
        stage_1_clcd_print(best_score, current_score, 5);
        state = 1;
        break;
    case 12: 
        if ((clcd_d = open(clcd, O_RDWR)) < 0)
        {
            perror("open");
            exit(1);
        }
        strcat(Best_Score, score_best);
        write(clcd_d, Best_Score, strlen(Best_Score));
        sleep(2); 
        stage_1_clcd_print(best_score, current_score, 5);
        state = 1;
        break;
    }
    close(clcd_d);
    close(tact);
}

void timer() {
    int fnd_d;
    unsigned char fnd_value[4];

    if ((fnd_d = open(FND_DEVICE, O_RDWR)) < 0)
    {
        perror("open");
        exit(1);
    }

    int seconds;
    // 60초 타이머
    for (seconds = 60; seconds >= 0; seconds--)
    {
        fnd_value[0] = fnd_data[0];
        fnd_value[1] = fnd_data[0];
        fnd_value[2] = fnd_data[seconds / 10]; // 십의 자리
        fnd_value[3] = fnd_data[seconds % 10]; // 일의 자리

        write(fnd_d, fnd_value, sizeof(fnd_value));

        sleep(1);
    }

    close(fnd_d);
*/