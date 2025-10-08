/**
 * File: binary_semaphore.c
 * Author: Jack Liao
 * Description: 
 * Created on: 2025-10-08 23:09:37
 */
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

SemaphoreHandle_t xBinarySemaphore;  // 宣告 Binary Semaphore

// 模擬中斷服務常式 (ISR)
void vButtonISR(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    // 給予 semaphore，喚醒等待的任務
    xSemaphoreGiveFromISR(xBinarySemaphore, &xHigherPriorityTaskWoken);

    // 若需要，進行 context switch
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

// 任務：等待中斷信號量
void vTaskButtonHandler(void *pvParameters)
{
    for (;;)
    {
        if (xSemaphoreTake(xBinarySemaphore, portMAX_DELAY) == pdTRUE)
        {
            printf("Button Press Detected! Task running...\n");
        }
    }
}

void main(void)
{
    // 建立 Binary Semaphore
    xBinarySemaphore = xSemaphoreCreateBinary();

    if (xBinarySemaphore != NULL)
    {
        xTaskCreate(vTaskButtonHandler, "ButtonHandler", 2048, NULL, 2, NULL);
        vTaskStartScheduler();
    }

    for (;;); // 不應到這裡
}
