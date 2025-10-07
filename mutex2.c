/**
 * File: mutex2.c
 * Author: Jack Liao
 * Description: 
 * Created on: 2025-10-07 22:41:48
 */

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

volatile int sum = 0;
SemaphoreHandle_t xMutex;

void vTask1(void *pvParameters){
    for(;;){
        if(xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE){
            sum++;
            printf("Task1 incremented counter to %d\n", sum);
            fflush(stdout);
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}
void vTask2(void *pvParameters){
    for(;;){
        if(xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE){
            sum += 2;
            printf("Task2 incremented counter to %d\n", sum);
            fflush(stdout);
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}



int main(void){
    xMutex = xSemaphoreCreateMutex();
    if(xMutex == NULL){
        printf("Mutex creation fail");
        for(;;);
    }
    xTaskCreate(vTask1, "Task1", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(vTask2, "Task2", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();
    for(;;);

    return 0;
}




