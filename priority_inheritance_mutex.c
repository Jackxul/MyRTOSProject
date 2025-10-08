/**
 * File: priority_inheritance_mutex.c
 * Author: Jack Liao
 * Description: 
 * Created on: 2025-10-08 23:06:21
 */
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

SemaphoreHandle_t xMutex;
volatile int shared_resource = 0;

void vLowTask(void *pvParameters){
    for(;;){
        if(xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE){
            printf("[Low] Got the mutex, working...\n");
            fflush(stdout);
            // 模擬低優先權任務需要長時間佔用資源
            for(int i=0; i<5; i++){
                shared_resource++;
                printf("[Low] Working... (%d)\n", shared_resource);
                fflush(stdout);
                vTaskDelay(pdMS_TO_TICKS(200));
            }
            printf("[Low] Released the mutex.\n");
            fflush(stdout);
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vMediumTask(void *pvParameters){
    for(;;){
        printf("[Medium] Running background work.\n");
        fflush(stdout);
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}

void vHighTask(void *pvParameters){
    for(;;){
        vTaskDelay(pdMS_TO_TICKS(500)); // 延遲一下，讓 Low 先取得 Mutex
        printf("[High] Trying to get the mutex...\n");
        fflush(stdout);
        if(xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE){
            printf("[High] Got the mutex! Updating resource.\n");
            shared_resource += 10;
            fflush(stdout);
            vTaskDelay(pdMS_TO_TICKS(100));
            xSemaphoreGive(xMutex);
            printf("[High] Released the mutex.\n");
            fflush(stdout);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void){
    xMutex = xSemaphoreCreateMutex();
    if(xMutex == NULL){
        printf("Mutex creation failed!\n");
        for(;;);
    }

    // 建立三個不同優先權的 Task
    xTaskCreate(vLowTask, "Low", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(vMediumTask, "Medium", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(vHighTask, "High", configMINIMAL_STACK_SIZE, NULL, 3, NULL);

    vTaskStartScheduler();
    for(;;);
    return 0;
}

