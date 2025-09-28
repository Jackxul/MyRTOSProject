#include <stdio.h>   
#include "FreeRTOS.h"
#include "task.h"

void vCyclicTask(void* pvParameters){
    const TickType_t cycleTime = pdMS_TO_TICKS(1000); // 1 second cycle time
    TickType_t LastWakeTime = xTaskGetTickCount(); // Initialize the last wake time
    
    for(;;){

        //Slot 1
        printf("[Cycle %lu] Slot 1 : Read sensor\n", xTaskGetTickCount());
        fflush(stdout);
        vTaskDelay(pdMS_TO_TICKS(200));

        //Slot 2
        printf("[Cycle %lu] Slot 2 : Process data\n", xTaskGetTickCount());
        fflush(stdout);
        vTaskDelay(pdMS_TO_TICKS(300));
        
        //Slot 3
        printf("[Cycle %lu] Slot 3 : Send data\n", xTaskGetTickCount());
        fflush(stdout);
        vTaskDelayUntil(&LastWakeTime, cycleTime); // wait until the next cycle
                                                   // Limitation: if the task overruns, it will skip cycles --> So All the sum of all slots execute time must be less than cycle time

    }

}

int main(void){

    xTaskCreate(vCyclicTask, "CyclicTask", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    vTaskStartScheduler();

    for(;;);
    return 0;
}

