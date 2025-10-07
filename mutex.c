/**
 * File: mutex.c
 * Author: Jack Liao
 * Description: 
 * Created on: 2025-10-07 18:21:37
 */

#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

volatile int shared_counter = 0;
SemaphoreHandle_t xMutex;

void TaskA(void *pvParameters){
    for(;;){
        if(xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE){
            printf("TaskA incremented counter to %d\n", shared_counter);
            shared_counter++;
            xSemaphoreGive(xMutex);//拿到鎖才能丟鎖
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    } 
}
void TaskB (void *pvParameters){
    for(;;){
        if(xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE){
            printf("TaskB decremented counter to %d\n", shared_counter);
            shared_counter += 2;
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(150));
    }
}
void TaskD (void *pvParameters){
    for(;;){
        if(xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE){
            printf("TaskD decremented counter to %d\n", shared_counter);
            shared_counter += 7;
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(300));
    
    }
}
void TaskE (void *pvParameters){
    for(;;){
        if(xSemaphoreTake(xMutex, portMAX_DELAY) == pdTRUE){
            printf("TaskE decremented counter to %d\n", shared_counter);
            shared_counter += 10;
            xSemaphoreGive(xMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(200));
    
    }
}
void TaskC (void *pvParameters){
    for(;;){
        static int x = 0;
        printf("TaskC counter as %d\n", x);
        x += 58;
        vTaskDelay(pdMS_TO_TICKS(600));
    
    }
}
int main(void){
    xMutex = xSemaphoreCreateMutex();

    if(xMutex == NULL){
        
        printf("Mutex create failed!\n");
        for(;;);
    }

    xTaskCreate(TaskA, "TaskA", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(TaskB, "TaskB", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(TaskC, "TaskC", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
    xTaskCreate(TaskD, "TaskD", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(TaskE, "TaskE", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    vTaskStartScheduler();
    for(;;);
    return 0;
}

