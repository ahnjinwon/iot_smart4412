#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>

#define DOT_DEVICE "/dev/dot"
#define TACT_DEVICE "/dev/tactsw"
#define TACTSW_READ 0
#define CLCD_DEVICE "/dev/clcd"  // CLCD 디바이스 파일 경로

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

int dotmatrix_fd;
int tactswitch_fd;
int tact;
int clcd_fd;  // CLCD 디바이스 파일 디스크립터
unsigned char c;
int num=0;
int isStop = 0;

void initDotMatrix() {
    dotmatrix_fd = open(DOT_DEVICE, O_RDWR);
    if (dotmatrix_fd < 0) {
        perror("Failed to open dot matrix device");
        exit(EXIT_FAILURE);
    }
}

void initTactSwitch() {
    tactswitch_fd = open(TACT_DEVICE, O_RDWR);
    if (tactswitch_fd < 0) {
        perror("Failed to open tactile switch device");
        exit(EXIT_FAILURE);
    }
}

void initCLCD() {
    clcd_fd = open(CLCD_DEVICE, O_RDWR);
    if (clcd_fd < 0) {
        perror("Failed to open CLCD device");
        exit(EXIT_FAILURE);
    }
}

void displayMole(int moleIndex) {
    unsigned char dotmatrix_data[8];

    memset(dotmatrix_data, 0, sizeof(dotmatrix_data));
    memcpy(dotmatrix_data, mole[moleIndex], sizeof(dotmatrix_data));

    write(dotmatrix_fd, dotmatrix_data, 8);
}



void updateCLCD(int score) {
    char clcd_message[16];
    int clcd_message_len;

    snprintf(clcd_message, sizeof(clcd_message), "Score: %d", score);
    clcd_message_len = strlen(clcd_message);
    write(clcd_fd, clcd_message, clcd_message_len);
}

int main() {
    int score = 0;
    int moleIndex = 0;
    int switch_status;
    int button;
    int random;
    int state = 0;

    initDotMatrix();
    initTactSwitch();
    initCLCD();

    while (1) {
    // moleIndex에 랜덤한 값 설정
    int moleIndex = rand() % 9;

    displayMole(moleIndex);

    usleep(2000000); // Display mole for 2 seconds

    tact = open(TACT_DEVICE, O_RDWR);
    read(tact, &c, sizeof(c));
    close(tact);
    switch(c)       // 스위치 1~9번
    {
        case 1: num = 1; break;
        case 2: num = 2; break;
        case 3: num = 3; break;
        case 4: num = 4; break;
        case 5: num = 5; break;
        case 6: num = 6; break;
        case 7: num = 7; break;
        case 8: num = 8; break;
        case 9: num = 9; break;
        case 12: isStop = 1; break;
    }
    if(num == (moleIndex+1)) {
        score++;
        printf("get the mole!\n");
        updateCLCD(score);
    }
    else {
            printf("Missed the mole!\n");
            }
        
}

    close(dotmatrix_fd);
    close(tactswitch_fd);

    return 0;
}
