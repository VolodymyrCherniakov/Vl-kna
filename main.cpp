#include "mbed.h"
#include "stm32746g_discovery_lcd.h"

DigitalOut led1(LED1);
DigitalIn button(USER_BUTTON);
Thread thread;
Thread thread2;
Thread thread3;


void init(){
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);


}

void button_thread(){
    while(true){
        if(button.read()){
            BSP_LCD_Clear(LCD_COLOR_RED);
            BSP_LCD_DisplayStringAt(0, 120, (uint8_t *)"BUTTON THREAD", CENTER_MODE);
        }
        ThisThread::sleep_for(200);
    }
}

void led1_thread(){
    while (true) {
        led1 = !led1;
        ThisThread::sleep_for(1000);
    }
}

void display_thread(){
    BSP_LCD_Clear(LCD_COLOR_BLACK);
    BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
    BSP_LCD_SetBackColor(LCD_COLOR_YELLOW);
    BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    while(true ){
        //if(!button.read()){
            BSP_LCD_Clear(LCD_COLOR_BLACK);
            BSP_LCD_DisplayStringAt(0, 1, (uint8_t *)"DISPLAY THREAD", RIGHT_MODE);
            ThisThread::sleep_for(2000);
            BSP_LCD_Clear(LCD_COLOR_YELLOW) ;
            BSP_LCD_DisplayStringAt(0, 240, (uint8_t *)"DISPLAY THREAD", LEFT_MODE) ;
            ThisThread::sleep_for(2000);
       // }
    }
}


int main(){
    init();
    thread.start(led1_thread);
    thread2.start(display_thread);
    thread3.start(button_thread);
    while(true){

        wait_ms(1000);
    }

}
