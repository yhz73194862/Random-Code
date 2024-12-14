#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
uchar code seg_code[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
uchar data_array[13] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

// 定时器0中断服务程序
void Timer0_ISR() interrupt 1 {
    static uint count = 0;
    TH0 = 0xFC;  // 重装定时器初值，1ms中断一次
    TL0 = 0x18;
    count++;
    if (count >= 1000) {  // 1秒时间到
        count = 0;        // 左移数组
        uchar temp = data_array[0];
        for (uchar i = 0; i < 12; i++) {
            data_array[i] = data_array[(i + 1)%13];
        }
        data_array[12] = temp;
    }
}

void main() {
    TMOD = 0x01;  // 定时器0模式1
    TH0 = 0xFC;   // 定时器初值，1ms中断一次
    TL0 = 0x18;
    ET0 = 1;      // 使能定时器0中断
    EA = 1;       // 使能总中断
    TR0 = 1;      // 启动定时器0
    while (1) {
    uchar i , ji = 500;
    for (i = 0; i < 8; i++) {
        P0 = seg_code[data_array[i]];  // 送段码
        P2 = ~(1 << i);  // 送位选信号，注意是共阳极数码管，所以位选信号要取反
        ji = 500;
        while (ji--);
        P2 = 0xFF;  // 关闭所有数码管
    }
}

 }