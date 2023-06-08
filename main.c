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

void Set_score();   //���� ����� �ְ����� ����
void stage_clcd_print(); //��������
void game_start();  //��Ʈ����ġ ������ ���� ����
void timer();    //Ÿ�̸�
void initDotMatrix();
void initTactSwitch();
void displayMole();



unsigned char mole[9][8] = {
    // ��Ʈ ��Ʈ���� ȭ��
    {0, 96, 96, 0, 0, 0, 0, 0}, //1���δ���
    {0, 24, 24, 0, 0, 0, 0, 0}, //2���δ���
    {0, 6, 6, 0, 0, 0, 0, 0},   //3���δ���
    {0, 0, 0, 96, 96, 0, 0, 0}, //4���δ���
    {0, 0, 0, 24, 24, 0, 0, 0}, //5���δ���
    {0, 0, 0, 6, 6, 0, 0, 0},   //6���δ���
    {0, 0, 0, 0, 0, 96, 96, 0}, //7���δ���
    {0, 0, 0, 0, 0, 24, 24, 0}, //8���δ���
    {0, 0, 0, 0, 0, 6, 6, 0}    //9���δ���
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
    long best_score;    //�ְ�����
    long current_score = 0;//��������
    long current_score2 = 0;
    int run = 0;    //���� ������ ���� ���ѷ���
    int state = 0;  //���� ���� �� ���ѷ����� ���� ����
    int count = 60; //�����ð�
    int life = 5;   //���
    int stage = 1;  //��������
    int timed = 0;
    unsigned char c;
    int num = 100;
    int isStop = 0;
    int life2 = 5;


    file = fopen("best_score.txt", "r");    //�ؽ�Ʈ ���Ͽ��� �ְ� ���� �ޱ�
    fscanf(file, "%ld", &best_score);
    fclose(file);
    
    game_start(best_score, current_score, state);   //���ӽ��� �� �Լ�

    int end_time = (unsigned)time(NULL);//������ �ð�
    end_time += 90; //60�� ī��Ʈ
    stage_clcd_print(stage, best_score, current_score, life);

    while (run == 0) {  //���ѷ��� ���鼭 ���� ����
        int started_time = (unsigned)time(NULL);
        if (stage == 1) {   //1��������
            initDotMatrix();
            initTactSwitch();

            int moleIndex = rand() % 9;

            displayMole(moleIndex);

            usleep(1300000); // Display mole for 2 seconds

            tact = open(tact_d, O_RDWR);
            read(tact, &c, sizeof(c));
            close(tact);
            switch (c)       // ����ġ 1~9��
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
            if (current_score >= 100) { //100���� �ѱ�� 2�������� ����
                stage = 2;
            }

        }

        if (stage == 2) {   //2��������
            initDotMatrix();
            initTactSwitch();

            int moleIndex = rand() % 9;

            displayMole(moleIndex);

            usleep(700000); // Display mole for 2 seconds

            tact = open(tact_d, O_RDWR);
            read(tact, &c, sizeof(c));
            close(tact);
            switch (c)       // ����ġ 1~9��
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
            if (current_score >= 250) { //250���� �ѱ�� 3�������� ����
                stage = 3;
            }
        }

        if (stage == 3) {   //3��������
            initDotMatrix();
            initTactSwitch();

            int moleIndex = rand() % 9;

            displayMole(moleIndex);

            usleep(400000); // Display mole for 2 seconds

            tact = open(tact_d, O_RDWR);
            read(tact, &c, sizeof(c));
            close(tact);
            switch (c)       // ����ġ 1~9��
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

        int start_time = (unsigned)time(NULL);  //�ð� üũ
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

        if (life <= 0) {    //����� 0�� �Ǹ� Game Over
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

    Set_score(best_score,current_score);    //���� ������ �ְ����� ��
    return 0;

}

void Set_score(long best_score, long current_score) {   //���������� ���� �ְ������� ��
    if (current_score > best_score) {   //��� ���� �� New Best Score�� ���� ǥ��, txt���Ͽ� �ְ��� ����
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
    else {                              //��� ���� ���� �� ���� �ְ������� ǥ��
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

void stage_clcd_print(int stage, long best_score ,long current_score, int life) {  //1�������� clcd��¹�

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

void game_start(long best_score, long current_score, int state) { //���� ���� �κ�
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
    write(clcd_d, str, strlen(str));    //���α׷� ���� �� clcd�� press any button ǥ��
    
    while (1)
    {
        read(tact, &c, sizeof(c));
        if (c)
            break;
    }
    switch (c)  //�ƹ� ��ư�̳� ������ �ְ����� ǥ�� �� ���� ����
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
    // 60�� Ÿ�̸�
    fnd_value[0] = fnd_data[0];
    fnd_value[1] = fnd_data[0];
    fnd_value[2] = fnd_data[seconds / 10]; // ���� �ڸ�
    fnd_value[3] = fnd_data[seconds % 10]; // ���� �ڸ�

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