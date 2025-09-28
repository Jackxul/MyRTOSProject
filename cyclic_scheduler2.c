#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

volatile int shared_counter = 0;

void vCyclicTask(void * pvParameters){
    const TickType_t cycleTime = pdMS_TO_TICKS(1000); // 1 second cycle time
    TickType_t LastWakeTime = xTaskGetTickCount(); // Initialize the last wake time

    for(;;){
        //slot 1
        printf("Task A running\n");
        shared_counter += 1;
        vTaskDelayUntil(&LastWakeTime, pdMS_TO_TICKS(200));
        //slot 2
        if(shared_counter <= 150){
            printf("Task B running\n");
            shared_counter += 2;
        }else{
            printf("Task B stopped updating\n");
        }
        vTaskDelayUntil(&LastWakeTime, pdMS_TO_TICKS(500)); // !!!! 200 + 300 = 500 週期絕對時間(非等待時間)
        //slot 3
        if(xTaskGetTickCount() <=  20000){
            printf("Task C running\n");
            shared_counter += 3;
        }else{
            printf("Task C stopped updating\n");
        }
        vTaskDelayUntil(&LastWakeTime, cycleTime); // wait until the next cycle
        printf("Shared_counter : %d \nNext cycle\n", shared_counter);
                                                           // Limitation: if the task overruns, it will skip cycles --> So All the sum of all slots execute time must be less than cycle time
    }
}

int main(void){

    xTaskCreate(vCyclicTask, "CyclicTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    vTaskStartScheduler();

    for(;;);
    return 0;
}
