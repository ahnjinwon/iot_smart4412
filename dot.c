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
void stage_1_clcd_print();  //1�������� clcd ���
void stage_2_clcd_print();  //2�������� clcd ���
void stage_3_clcd_print();  //3�������� clcd ���
void game_start();  //��Ʈ����ġ ������ ���� ����
void timer();

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

const unsigned char fnd_data[16] = {    //fnd
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0xA0, 0x88, 0x83, 0xC6, 0xA1, 0x8E
};

int main() {

    FILE* file;
    int clcd_d;     //clcd
    long best_score;    //�ְ�����
    long current_score = 0;//��������
    int run = 0;    //���� ������ ���� ���ѷ���
    int state = 0;  //���� ���� �� ���ѷ����� ���� ����
    int count = 60; //�����ð�
    int life = 5;   //���
    int stage = 1;  //��������
    int end_time = (unsigned)time(NULL);//������ �ð�
    end_time += 10; //60�� ī��Ʈ
    int tact;
    int dot_d, i, random;
    unsigned char c;
    int button = 0;


    
    while (1) {
        random = rand() % 9;
        dot_d = open(dot, O_RDWR);
        if (dot_d < 0 | tact < 0)
        {
            printf("���� �߻�");
            exit(0);
        }
        write(dot_d, &mole[random], sizeof(mole[random]));
        usleep(10000);
        close(dot_d);

        tact = open(tact_d, O_RDWR);
        read(tact, &c, sizeof(c));
        close(tact);

        switch (c)  // �δ����� tackswitch ����
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
                write(clcd_d, "����", strlen("����"));
            }
            write(clcd_d, "����", strlen("����"));
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
                write(clcd_d, "����", strlen("����"));
            }
            write(clcd_d, "����", strlen("����"));
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
                write(clcd_d, "����", strlen("����"));
            }
            write(clcd_d, "����", strlen("����"));
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
                write(clcd_d, "����", strlen("����"));
            }
            write(clcd_d, "����", strlen("����"));
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
                write(clcd_d, "����", strlen("����"));
            }
            write(clcd_d, "����", strlen("����"));
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
                write(clcd_d, "����", strlen("����"));
            }
            write(clcd_d, "����", strlen("����"));
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
                write(clcd_d, "����", strlen("����"));
            }
            write(clcd_d, "����", strlen("����"));
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
                write(clcd_d, "����", strlen("����"));
            }
            write(clcd_d, "����", strlen("����"));
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
                write(clcd_d, "����", strlen("����"));
            }
            write(clcd_d, "����", strlen("����"));
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
                write(clcd_d, "����", strlen("����"));
            }
            write(clcd_d, "����", strlen("����"));
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
                write(clcd_d, "����", strlen("����"));
            }
            write(clcd_d, "����", strlen("����"));
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
                write(clcd_d, "����", strlen("����"));
            }
            write(clcd_d, "����", strlen("����"));
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
    file = fopen("best_score.txt", "r");    //�ؽ�Ʈ ���Ͽ��� �ְ� ���� �ޱ�
    fscanf(file, "%ld", &best_score);
    fclose(file);
    
    game_start(best_score, current_score, state);
    while (state = 0) { //��Ȯ�� �ð�üũ�� ���� ���� ���� ������ ���ѷ��� ��������
        if (state == 1)
            break;
    }
    while (run == 0) {  //���ѷ��� ���鼭 ���� ����

        timer();

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

        if (stage == 1) {   //1��������
            stage_1_clcd_print(best_score, current_score, life);
            if (current_score >= 100) { //100���� �ѱ�� 2�������� ����
                stage = 2;
            }
        }

        if (stage == 2) {   //2��������
            stage_2_clcd_print(best_score, current_score, life);
            if (current_score >= 250) { //250���� �ѱ�� 3�������� ����
                stage = 3;
            }
        }

        if (stage == 3) {   //3��������
            stage_3_clcd_print(best_score, current_score, life);
        }

    }
    Set_score(best_score,current_score);    //���� ������ �ְ����� ��
    return 0;
}

void Set_score(long best_score, long current_score) {   //���������� ���� �ְ������� ��
    if (current_score > best_score) {   //��� ���� �� New Best Score�� ���� ǥ��, txt���Ͽ� �ְ���� ����
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

void stage_2_clcd_print(long best_score, long current_score, int life) {  //2�������� clcd��¹�

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

void stage_3_clcd_print(long best_score, long current_score, int life) {  //3�������� clcd��¹�

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
    // 60�� Ÿ�̸�
    for (seconds = 60; seconds >= 0; seconds--)
    {
        fnd_value[0] = fnd_data[0];
        fnd_value[1] = fnd_data[0];
        fnd_value[2] = fnd_data[seconds / 10]; // ���� �ڸ�
        fnd_value[3] = fnd_data[seconds % 10]; // ���� �ڸ�

        write(fnd_d, fnd_value, sizeof(fnd_value));

        sleep(1);
    }

    close(fnd_d);
*/