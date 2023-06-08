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
void stage_clcd_print(); //스테이지
void game_start();  //택트스위치 누르면 게임 시작
void timer();    //타이머
void initDotMatrix();
void initTactSwitch();
void displayMole();



unsigned char mole[9][8] = {
    // 도트 매트릭스 화면
    {0, 96, 96, 0, 0, 0, 0, 0}, //1번두더지
    {0, 24, 24, 0, 0, 0, 0, 0}, //2번두더지
    {0, 6, 6, 0, 0, 0, 0, 0},   //3번두더지
    {0, 0, 0, 96, 96, 0, 0, 0}, //4번두더지
    {0, 0, 0, 24, 24, 0, 0, 0}, //5번두더지
    {0, 0, 0, 6, 6, 0, 0, 0},   //6번두더지
    {0, 0, 0, 0, 0, 96, 96, 0}, //7번두더지
    {0, 0, 0, 0, 0, 24, 24, 0}, //8번두더지
    {0, 0, 0, 0, 0, 6, 6, 0}    //9번두더지
};

const unsigned char fnd_data[16] = {    //fnd
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0xA0, 0x88, 0x83, 0xC6, 0xA1, 0x8E
};


int dotmatrix_fd;
int tactswitch_fd;
int tact;

int main() {

    FILE* file;
    int clcd_d;     //clcd
    long best_score;    //최고점수
    long current_score = 0;//현재점수
    long current_score2 = 0;
    int run = 0;    //게임 진행을 위한 무한루프
    int state = 0;  //게임 시작 전 무한루프를 위한 정수
    int count = 60; //남은시간
    int life = 5;   //목숨
    int stage = 1;  //스테이지
    int timed = 0;
    unsigned char c;
    int num = 100;
    int isStop = 0;
    int life2 = 5;


    file = fopen("best_score.txt", "r");    //텍스트 파일에서 최고 점수 받기
    fscanf(file, "%ld", &best_score);
    fclose(file);
    
    game_start(best_score, current_score, state);   //게임시작 전 함수

    int end_time = (unsigned)time(NULL);//끝나는 시간
    end_time += 90; //60초 카운트
    stage_clcd_print(stage, best_score, current_score, life);

    while (run == 0) {  //무한루프 돌면서 게임 시작
        int started_time = (unsigned)time(NULL);
        if (stage == 1) {   //1스테이지
            initDotMatrix();
            initTactSwitch();

            int moleIndex = rand() % 9;

            displayMole(moleIndex);

            usleep(1300000); // Display mole for 2 seconds

            tact = open(tact_d, O_RDWR);
            read(tact, &c, sizeof(c));
            close(tact);
            switch (c)       // 스위치 1~9번
            {
            case 4: num = 1; break;
            case 5: num = 2; break;
            case 6: num = 3; break;
            case 7: num = 4; break;
            case 8: num = 5; break;
            case 9: num = 6; break;
            case 10: num = 7; break;
            case 11: num = 8; break;
            case 12: num = 9; break;
            }
            if (num == (moleIndex + 1)) {
                current_score += 10;
                printf("get the mole!\n");
                num = 100;
            }
            else {
                printf("Missed the mole!\n");
                life--;
                num = 100;
            }


            close(dotmatrix_fd);
            close(tactswitch_fd);
            if (current_score > current_score2) {
                stage_clcd_print(stage, best_score, current_score, life);
                current_score2 = current_score;
            }
            if (life != life2) {
                stage_clcd_print(stage, best_score, current_score, life);
                life2 = life;
            }
            timer(end_time, started_time);
            if (current_score >= 100) { //100점을 넘기면 2스테이지 진입
                stage = 2;
            }

        }

        if (stage == 2) {   //2스테이지
            initDotMatrix();
            initTactSwitch();

            int moleIndex = rand() % 9;

            displayMole(moleIndex);

            usleep(700000); // Display mole for 2 seconds

            tact = open(tact_d, O_RDWR);
            read(tact, &c, sizeof(c));
            close(tact);
            switch (c)       // 스위치 1~9번
            {
            case 4: num = 1; break;
            case 5: num = 2; break;
            case 6: num = 3; break;
            case 7: num = 4; break;
            case 8: num = 5; break;
            case 9: num = 6; break;
            case 10: num = 7; break;
            case 11: num = 8; break;
            case 12: num = 9; break;
            }
            if (num == (moleIndex + 1)) {
                current_score+=15;
                printf("get the mole!\n");
                num = 100;
            }
            else {
                printf("Missed the mole!\n");
                life--;
                num = 100;
            }
            close(dotmatrix_fd);
            close(tactswitch_fd);
            if (current_score != current_score2) {
                stage_clcd_print(stage, best_score, current_score, life);
                current_score2 = current_score;
            }

            if (life != life2) {
                stage_clcd_print(stage, best_score, current_score, life);
                life2 = life;
            }
            timer(end_time, started_time);
            if (current_score >= 250) { //250점을 넘기면 3스테이지 진입
                stage = 3;
            }
        }

        if (stage == 3) {   //3스테이지
            initDotMatrix();
            initTactSwitch();

            int moleIndex = rand() % 9;

            displayMole(moleIndex);

            usleep(400000); // Display mole for 2 seconds

            tact = open(tact_d, O_RDWR);
            read(tact, &c, sizeof(c));
            close(tact);
            switch (c)       // 스위치 1~9번
            {
            case 4: num = 1; break;
            case 5: num = 2; break;
            case 6: num = 3; break;
            case 7: num = 4; break;
            case 8: num = 5; break;
            case 9: num = 6; break;
            case 10: num = 7; break;
            case 11: num = 8; break;
            case 12: num = 9; break;
            }
            if (num == (moleIndex + 1)) {
                current_score+=20;
                printf("get the mole!\n");
                num = 100;

            }
            else {
                printf("Missed the mole!\n");
                life--;
                num = 100;
            }
            close(dotmatrix_fd);
            close(tactswitch_fd);
            if (current_score != current_score2) {
                stage_clcd_print(stage, best_score, current_score, life);
                current_score2 = current_score;
            }
            if (life != life2) {
                stage_clcd_print(stage, best_score, current_score, life);
                life2 = life;
            }
            timer(end_time, started_time);
        }

        int start_time = (unsigned)time(NULL);  //시간 체크
        if (end_time - start_time <= 0) {
            int clcd_d;
            char str[30] = "CLEAR!";
            if ((clcd_d = open(clcd, O_RDWR)) < 0)
            {
                perror("open");
                exit(1);
            }
            write(clcd_d, str, strlen(str));
            close(clcd_d);
            sleep(1);
            run = 1;
        }

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
        FILE* file;
        file = fopen("best_score.txt", "w");
        fprintf(file, "%ld", current_score);
        fclose(file);

        int clcd_d;
        char new_bestscore[5];
        char clcd_score[30] = "best_score: ";
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
}

void stage_clcd_print(int stage, long best_score ,long current_score, int life) {  //1스테이지 clcd출력문

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
    sprintf(stage_clcd, "%d ", stage);
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
        state = 1;
        break;
    }
    close(clcd_d);
    close(tact);
}


void timer(int end_time, int started_time) {
    int fnd_d;
    unsigned char fnd_value[4];

    if ((fnd_d = open(FND_DEVICE, O_RDWR)) < 0)
    {
        perror("open");
        exit(1);
    }

    int seconds=end_time-started_time;
    // 60초 타이머
    fnd_value[0] = fnd_data[0];
    fnd_value[1] = fnd_data[0];
    fnd_value[2] = fnd_data[seconds / 10]; // 십의 자리
    fnd_value[3] = fnd_data[seconds % 10]; // 일의 자리

    write(fnd_d, fnd_value, sizeof(fnd_value));
    sleep(1);
    close(fnd_d);
}
int count = 0;


void initDotMatrix() {
    dotmatrix_fd = open(dot, O_RDWR);
    if (dotmatrix_fd < 0) {
        perror("Failed to open dot matrix device");
        exit(EXIT_FAILURE);
    }
}

void initTactSwitch() {
    tactswitch_fd = open(dot, O_RDWR);
    if (tactswitch_fd < 0) {
        perror("Failed to open tactile switch device");
        exit(EXIT_FAILURE);
    }
}

void displayMole(int moleIndex) {
    unsigned char dotmatrix_data[8];

    memset(dotmatrix_data, 0, sizeof(dotmatrix_data));
    memcpy(dotmatrix_data, mole[moleIndex], sizeof(dotmatrix_data));

    write(dotmatrix_fd, dotmatrix_data, 8);
}