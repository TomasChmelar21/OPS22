#include "mbed.h"
#include "stm32746g_discovery_lcd.h"
#include <Callback.h>
//#include "functions.h"

Mutex stdio_mutex;
Mutex freePlaces;
Semaphore Semaphor(4);

Thread cars1;
Thread cars2;
Thread cars3;
Thread cars4;
Thread cars5;


struct placeForCar {
    int x = 0;
    int y = 100;
    struct placeForCar* last = NULL;
};
struct park {
    uint32_t BG_Colour = LCD_COLOR_BLACK;
    struct placeForCar* volno;
};
struct car {
    char* txt = "                                                ";
    uint32_t BG_Colour;
    uint32_t period;
};
struct PC {
    struct park* P;
    struct car* C;
};


struct placeForCar* getFreeParkPlace(struct park* parkPlace) {
    struct placeForCar* tmp = parkPlace->volno;
    parkPlace->volno = (parkPlace->volno)->last;
    return tmp;
}
void setFreeParkPlace(struct park* parkPlace, struct placeForCar* m) {
    m->last = parkPlace->volno;
    parkPlace->volno = m;
}


void threading(struct PC* PCx) {
    while (true) {
        struct park* p = PCx->P;
        struct car* c = PCx->C;

        Semaphor.acquire();

        freePlaces.lock();
        struct placeForCar* m = getFreeParkPlace(p);
        freePlaces.unlock();

        stdio_mutex.lock();
        BSP_LCD_SetBackColor(c->BG_Colour);
        BSP_LCD_SetFont(&Font24);
        BSP_LCD_DisplayStringAt(m->x, m->y, (uint8_t*)(c->txt), CENTER_MODE);
        stdio_mutex.unlock();


        ThisThread::sleep_for(c->period);


        stdio_mutex.lock();
        BSP_LCD_SetBackColor(p->BG_Colour);
        BSP_LCD_SetFont(&Font24);
        BSP_LCD_DisplayStringAt(m->x, m->y, (uint8_t*)(c->txt), CENTER_MODE);
        stdio_mutex.unlock();

        freePlaces.lock();
        setFreeParkPlace(p, m);
        freePlaces.unlock();


        Semaphor.release();
    }
}

int main()
{
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
    BSP_LCD_Clear(LCD_COLOR_BLACK);



    struct placeForCar placeForCar0;
    placeForCar0.y = 272 - 34;

    struct placeForCar placeForCar1;
    placeForCar1.y = 272 - 68 - 34;
    placeForCar1.last = &placeForCar0;

    struct placeForCar placeForCar2;
    placeForCar2.y = 272 - 136 - 34;
    placeForCar2.last = &placeForCar1;

    struct placeForCar placeForCar3;
    placeForCar3.y = 272 - 204 - 34;
    placeForCar3.last = &placeForCar2;

    struct park parkPlace;
    parkPlace.volno = &placeForCar3;



    struct car auto0;
    auto0.BG_Colour = LCD_COLOR_ORANGE;
    auto0.period = 3000;

    struct car auto1;
    auto1.BG_Colour = LCD_COLOR_BLUE;
    auto1.period = 1000;

    struct car auto2;
    auto2.BG_Colour = LCD_COLOR_GREEN;
    auto2.period = 5000;

    struct car auto3;
    auto3.BG_Colour = LCD_COLOR_RED;
    auto3.period = 2500;

    struct car auto4;
    auto4.BG_Colour = LCD_COLOR_YELLOW;
    auto4.period = 1000;



    struct PC PC0;
    PC0.P = &parkPlace;
    PC0.C = &auto0;

    struct PC PC1;
    PC1.P = &parkPlace;
    PC1.C = &auto1;

    struct PC PC2;
    PC2.P = &parkPlace;
    PC2.C = &auto2;

    struct PC PC3;
    PC3.P = &parkPlace;
    PC3.C = &auto3;

    struct PC PC4;
    PC4.P = &parkPlace;
    PC4.C = &auto4;


    cars1.start(callback(threading, &PC0));
    cars2.start(callback(threading, &PC1));
    cars3.start(callback(threading, &PC2));
    cars4.start(callback(threading, &PC3));
    cars5.start(callback(threading, &PC4));
    while (true) {


    }
}