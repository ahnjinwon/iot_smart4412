//���ĺ� ������� ����
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

void Set_score();   //���� ����� �ְ����� ����
void clcd_print();  //clcd ���
void game_start();  //��Ʈ����ġ ������ ���� ����

unsigned char mole[9][8] = {
    // ��Ʈ ��Ʈ���� ȭ��
    {0x00, 0x60, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00}, //7���δ���
    {0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00}, //8���δ���
    {0x00, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00}, //9���δ���
    {0x00, 0x00, 0x00, 0x60, 0x60, 0x00, 0x00, 0x00}, //4���δ���
    {0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00}, //5���δ���
    {0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00}, //6���δ���
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x00}, //1���δ���
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00}, //2���δ���
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00}  //3���δ���
};

int main() {
    /*
    int dot_d, i, random;
    dot_d = open(dot, O_RDWR);
    if (dot_d < 0)
    {
        printf("���� �߻�");
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

    file = fopen("best_score.txt", "r");    //�ؽ�Ʈ ���Ͽ��� �ְ� ���� �ޱ�
    fscanf(file, "%ld", &best_score);
    fclose(file);
    
    game_start(best_score, current_score);
    
    Set_score(best_score,current_score);    //���� ������ �ְ����� ��
    return 0;
}

void Set_score(long best_score, long current_score) {   //���������� ���� �ְ������� ���Ͽ� �ؽ�Ʈ ���Ͽ� �ְ����� �����Լ�
    if (current_score > best_score) {
        FILE* file;
        file = fopen("best_score.txt", "w");
        fprintf(file, "%ld", current_score);
        fclose(file);
    }
}

void clcd_print(long best_score ,long current_score) {  //clcd��¹�

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

void game_start(long best_score, long current_score) { //��Ʈ����ġ ������ ���ӽ���
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
    switch (c)  //�ƹ� ��ư�̳� ������ ���� ����
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