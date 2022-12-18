#include "mbed.h"
#include <cstdint>
#include <cstdio>
#include <string>
#include <iostream>
#include <stdio.h>
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"
Mutex stdio_mutex;
//#include <thread>

// main() runs in its own thread in the OS

Thread thread1s;
Thread thread2s;
Thread thread3s;

struct threading {
    int offset;
    uint8_t* text;
    int druhy;
    int sleep;

};

void text_thread(threading* nazev)
{
    while (true) {
        stdio_mutex.lock();
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(nazev->druhy, nazev->offset, nazev->text, CENTER_MODE);
        ThisThread::sleep_for(nazev->sleep);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(nazev->druhy, nazev->offset, nazev->text, CENTER_MODE);
        ThisThread::sleep_for(nazev->sleep);
        stdio_mutex.unlock();

    }
}

/*void text2_thread()
{
    while (true) {
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(0, 80, (uint8_t *)"hodne random text", CENTER_MODE);
        ThisThread::sleep_for(8s);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(0, 80, (uint8_t *)"hodne random text", CENTER_MODE);
        ThisThread::sleep_for(8s);
    }
}

void text3_thread()
{
    while (true) {
        BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
        BSP_LCD_DisplayStringAt(0, 160, (uint8_t *)"poslednicek", CENTER_MODE);
        ThisThread::sleep_for(5s);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(0, 160, (uint8_t *)"poslednicek", CENTER_MODE);
        ThisThread::sleep_for(5s);
    }
}*/

int main()
{

    BSP_LCD_Init();

    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
    BSP_LCD_Clear(LCD_COLOR_WHITE);
    int a = 256;
    int b = 456;
    int c = 850;
    threading thread1;
    thread1.offset = 1;
    thread1.text = (uint8_t*)"ahoj af";
    thread1.druhy = 0;
    thread1.sleep = 400;
    threading thread2;
    thread2.offset = 80;
    thread2.text = (uint8_t*)"ahoj addd";
    thread2.druhy = 0;
    thread2.sleep = 500;
    threading thread3;
    thread3.offset = 160;
    thread3.text = (uint8_t*)"ahoj aggggg";
    thread3.druhy = 0;
    thread3.sleep = 700;

    thread1s.start(callback(text_thread, &thread1));
    thread2s.start(callback(text_thread, &thread2));
    thread3s.start(callback(text_thread, &thread3));
    /*thread1.start(text_thread);
    thread2.start(text2_thread);
    thread3.start(text3_thread);*/
    while (true) {

    }
}

