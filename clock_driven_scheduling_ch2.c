#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

void vTask1(void *pvParameters){
    TickType_t LastWakeTime = xTaskGetTickCount();
    const TickType_t Freqiency = pdMS_TO_TICKS(200);

    for(;;){
        printf("Tick %lu : Task %s is active.\n",xTaskGetTickCount(), (char *)pvParameters);
        fflush(stdout);
        vTaskDelayUntil(&LastWakeTime, Freqiency);
    }
}
void vTask2(void *pvParameters){
    TickType_t LastWakeTime = xTaskGetTickCount();
    const TickType_t Freqiency = pdMS_TO_TICKS(500);

    for(;;){
        printf("Tick %lu : Task %s is active.\n",xTaskGetTickCount(), (char *)pvParameters);
        fflush(stdout);
        vTaskDelayUntil(&LastWakeTime, Freqiency);
    }
}
void vTask3(void *pvParameters){
    TickType_t LastWakeTime = xTaskGetTickCount();
    const TickType_t Freqiency = pdMS_TO_TICKS(1000);
    for(;;){
        printf("Tick %lu : Task %s is active.\n",xTaskGetTickCount(), (char *)pvParameters);
        fflush(stdout);
        vTaskDelayUntil(&LastWakeTime, Freqiency);
    }
}
int main(void){
        
    TaskHandle_t vHandler1 = NULL, vHandler2 = NULL, vHandler3 = NULL;
    xTaskCreate(vTask1, "TaskA", configMINIMAL_STACK_SIZE, "A", 1, &vHandler1);
    xTaskCreate(vTask2, "TaskB", configMINIMAL_STACK_SIZE, "B", 1, &vHandler2);
    xTaskCreate(vTask3, "TaskC", configMINIMAL_STACK_SIZE, "C", 1, &vHandler3);

    vTaskStartScheduler();
    for(;;);
    return 0;
}

