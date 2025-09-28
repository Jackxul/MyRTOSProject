#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"


volatile int shared_counter = 0;

TaskHandle_t vHandler1 = NULL, vHandler2 = NULL, vHandler3 = NULL;

void vTask1(void *pvParameters){
    TickType_t LastWakeTime = xTaskGetTickCount();
    const TickType_t Freqiency = pdMS_TO_TICKS(300);
    int* counter = (int*)pvParameters;

    for(;;){
        printf("Tick %lu : Task %s executed, shared_count = %d\n",xTaskGetTickCount(), "A", (*counter) += 1);
        fflush(stdout);
        vTaskDelayUntil(&LastWakeTime, Freqiency);
        if(uxTaskGetNumberOfTasks() == 2){
            printf("Task B is freed, so Task A deleted itself.\n");
            vTaskDelete(NULL); // Delete itself when only 2 tasks remain (Means the adrress of Task B is freed)
                                    //
        }
    }
    
}
void vTask2(void *pvParameters){
    TickType_t LastWakeTime = xTaskGetTickCount();
    const TickType_t Freqiency = pdMS_TO_TICKS(500);
    int taskBcounter = 0;
    int* counter = (int*)pvParameters;
    
    for(;;){
        printf("Tick %lu : Task %s executed, shared_count = %d\n",xTaskGetTickCount(), "B", (*counter) += 2);
        fflush(stdout);
        taskBcounter++;
        vTaskDelayUntil(&LastWakeTime, Freqiency);
        if(taskBcounter == 3){
            printf("Task B deleted itself.\n");
            vTaskDelete(NULL); // Delete itself after executing 3 times
                                    //
        }
    }
}
void vTask3(void *pvParameters){
    TickType_t LastWakeTime = xTaskGetTickCount();
    const TickType_t Freqiency = pdMS_TO_TICKS(1000);
    int* counter = (int*)pvParameters;

    for(;;){
        if(vHandler1 != NULL && eTaskGetState(vHandler1) == eDeleted){
            printf("TaskC stops updating because TaskA is deleted.\n");
        }else{
            printf("Tick %lu : Task %s executed, shared_count = %d\n",xTaskGetTickCount(), "C", (*counter) += 3);
            fflush(stdout);
            vTaskDelayUntil(&LastWakeTime, Freqiency);
        }
    }
}
int main(void){
        


    xTaskCreate(vTask1, "TaskA", configMINIMAL_STACK_SIZE, (void *)&shared_counter, 3, &vHandler1);
    xTaskCreate(vTask2, "TaskB", configMINIMAL_STACK_SIZE, (void *)&shared_counter, 2, &vHandler2);
    xTaskCreate(vTask3, "TaskC", configMINIMAL_STACK_SIZE, (void *)&shared_counter, 1, &vHandler3);
    vTaskStartScheduler();
    for(;;);
    return 0;
}

