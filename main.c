//���ĺ� ������� ����
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
#define fnd "/dev/fnd"

void Set_score();   //���� ����� �ְ����� ����
void stage_1_clcd_print();  //1�������� clcd ���
void stage_2_clcd_print();  //2�������� clcd ���
void stage_3_clcd_print();  //3�������� clcd ���
void game_start();  //��Ʈ����ġ ������ ���� ����

unsigned char mole[9][8] = {
    // ��Ʈ ��Ʈ���� ȭ��
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x00}, //1���δ���
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00}, //2���δ���
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00}, //3���δ���
    {0x00, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00}, //4���δ���
    {0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00}, //5���δ���
    {0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00}, //6���δ���
    {0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00}, //7���δ���
    {0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00}, //8���δ���
    {0x00, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00}  //9���δ���
};

int main() {

    FILE* file;
    int clcd_d;     //clcd
    long best_score;    //�ְ�����
    long current_score = 0;//��������
    int run = 0;    //���� ������ ���� ���ѷ���
    int state = 0;
    int count = 60; //�����ð�
    int life = 5;   //���
    int stage = 1;  //��������
    int end_time = (unsigned)time(NULL);//������ �ð�
    end_time += 10; //60�� ī��Ʈ

    file = fopen("best_score.txt", "r");    //�ؽ�Ʈ ���Ͽ��� �ְ� ���� �ޱ�
    fscanf(file, "%ld", &best_score);
    fclose(file);
    
    game_start(best_score, current_score, state);
    while (state = 0) { //�ð�üũ�� ���� ���ѷ���
        if (state == 1)
            break;
    }
    while (run == 0) {  //���ѷ��� ���鼭 ���� ����
        if (stage == 1) {   //1��������
            stage_1_clcd_print(best_score, current_score, life);

        }
        int start_time = (unsigned)time(NULL);  //�ð� üũ
        if (end_time - start_time == 0) {   //60�ʰ� ������
            if ((clcd_d = open(clcd, O_RDWR)) < 0)
            {
                perror("open");
                exit(1);
            }
            write(clcd_d, "Clear!", strlen("Clear!"));
            close(clcd_d);
            sleep(1);
            run = 1;
        }
        
        if (life == 0) {    //����� 0�� �Ǹ�
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
    best_score = 50000;
    Set_score(best_score,current_score);    //���� ������ �ְ����� ��
    return 0;
}

void Set_score(long best_score, long current_score) {   //���������� ���� �ְ������� ���Ͽ� �ؽ�Ʈ ���Ͽ� �ְ����� ���� clcd�� ����
    if (current_score > best_score) {
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
    else {
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

void stage_1_clcd_print(long best_score ,long current_score, int life) {  //1�������� clcd��¹�

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
    sprintf(stage_clcd, "1");
    sprintf(score_current, "%d  ", current_score);
    sprintf(score_best, "%d  ", best_score);
    sprintf(life_clcd, "%d ", life);
    strcat(clcd_stage, stage_clcd);
    strcat(clcd_stage, clcd_life);
    strcat(clcd_stage, life_clcd);
    strcat(clcd_stage, clcd_text1);
    strcat(clcd_stage, score_current);

    write(clcd_d, clcd_stage, strlen(clcd_stage));
    close(clcd_d);
}

void stage_2_clcd_print(long best_score, long current_score) {  //2�������� clcd��¹�

    int clcd_d;
    char stage_clcd[5];
    char score_current[5];
    char score_best[5];

    char clcd_stage[30] = "stage : ";
    char clcd_text1[30] = "score: ";
    char clcd_text2[30] = "best_score: ";

    if ((clcd_d = open(clcd, O_RDWR)) < 0)
    {
        perror("open");
        exit(1);
    }
    sprintf(stage_clcd, "2\n");
    sprintf(score_current, "%d  ", current_score);
    sprintf(score_best, "%d  ", best_score);
    strcat(clcd_stage, stage_clcd);
    strcat(clcd_stage, clcd_text1);
    strcat(clcd_stage, score_current);
    strcat(clcd_stage, clcd_text2);
    strcat(clcd_stage, score_best);

    write(clcd_d, clcd_stage, strlen(clcd_stage));
    close(clcd_d);
}

void stage_3_clcd_print(long best_score, long current_score) {  //3�������� clcd��¹�

    int clcd_d;
    char stage_clcd[5];
    char score_current[5];
    char score_best[5];

    char clcd_stage[30] = "stage : ";
    char clcd_text1[30] = "score: ";
    char clcd_text2[30] = "best_score: ";

    if ((clcd_d = open(clcd, O_RDWR)) < 0)
    {
        perror("open");
        exit(1);
    }
    sprintf(stage_clcd, "3\n");
    sprintf(score_current, "%d  ", current_score);
    sprintf(score_best, "%d  ", best_score);
    strcat(clcd_stage, stage_clcd);
    strcat(clcd_stage, clcd_text1);
    strcat(clcd_stage, score_current);
    strcat(clcd_stage, clcd_text2);
    strcat(clcd_stage, score_best);

    write(clcd_d, clcd_stage, strlen(clcd_stage));
    close(clcd_d);
}


void game_start(long best_score, long current_score, int state) { //��Ʈ����ġ ������ ���ӽ���
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
    write(clcd_d, str, strlen(str));
    
    while (1)
    {
        read(tact, &c, sizeof(c));
        if (c)
            break;
    }
    switch (c)  //�ƹ� ��ư�̳� ������ ���� ����
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