#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FND_DEVICE "/dev/fnd"

const unsigned char fnd_data[16] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8,
    0x80, 0x90, 0xA0, 0x88, 0x83, 0xC6, 0xA1, 0x8E
};

int main()
{
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

    return 0;
}
