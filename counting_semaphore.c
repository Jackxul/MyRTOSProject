/**
 * File: counting_semaphore.c
 * Author: Jack Liao
 * Description: 
 * Created on: 2025-10-08 23:11:17
 */
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

SemaphoreHandle_t xCountingSemaphore;

// 模擬使用資源的任務
void vTaskResourceUser(void *pvParameters)
{
    const char *pcTaskName = (const char *)pvParameters;

    for (;;)
    {
        if (xSemaphoreTake(xCountingSemaphore, portMAX_DELAY) == pdTRUE)
        {
            printf("%s: Got resource, using it...\n", pcTaskName);
            vTaskDelay(pdMS_TO_TICKS(1000));  // 模擬工作
            printf("%s: Done, releasing resource.\n", pcTaskName);
            xSemaphoreGive(xCountingSemaphore);  // 釋放資源
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }
}

void main(void)
{
    // 建立 Counting Semaphore，最大值=2，初始值=2 (代表兩個可用資源)
    xCountingSemaphore = xSemaphoreCreateCounting(2, 2);

    if (xCountingSemaphore != NULL)
    {
        xTaskCreate(vTaskResourceUser, "TaskA", 2048, "Task A", 2, NULL);
        xTaskCreate(vTaskResourceUser, "TaskB", 2048, "Task B", 2, NULL);
        xTaskCreate(vTaskResourceUser, "TaskC", 2048, "Task C", 2, NULL);
        vTaskStartScheduler();
    }

    for (;;);
}
