#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

/* 簡單的 Task */
void vHelloTask(void *pvParameters)
{
    for (;;)
    {
        printf("Hello from FreeRTOS Task!\n");
        fflush(stdout);
        vTaskDelay(pdMS_TO_TICKS(1000)); // 延遲 1000ms
    }
}
void vTask1(void *pvParameters){

    char * output = (char *)pvParameters;
    for(;;){
        printf("This is Task %s\n", output);
        fflush(stdout);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
void vTask2(void *pvParameters){

    for(;;){
        printf("This is Task %d\n", (int)(intptr_t)pvParameters);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

int main(void)
{
    printf("=== FreeRTOS Hello World Demo ===\n");
    
    //create handler variable
    TaskHandle_t xHandle1 = NULL;
    TaskHandle_t xHandle2 = NULL;
    /* 建立一個 Task */
    xTaskCreate(vHelloTask,           // 任務函數
                "HelloTask",          // 任務名稱
                configMINIMAL_STACK_SIZE, // 堆疊大小
                NULL,                 // 傳入參數
                1,                    // 優先權
                NULL);                // 任務 Handle
    xTaskCreate(vTask1, "Task1", 250, "1", 3, &xHandle1);
    xTaskCreate(vTask2, "Task2", 25, (void *)2, 1, &xHandle2); 
    /* 啟動 Scheduler */
    vTaskStartScheduler();

    /* 如果進到這裡代表 scheduler 沒啟動成功 */
    for (;;)
        ;
    return 0;
}

