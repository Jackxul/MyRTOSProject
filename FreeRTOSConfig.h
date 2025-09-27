#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* 基本設定 */
#define configUSE_PREEMPTION            1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0
#define configUSE_IDLE_HOOK             0
#define configUSE_TICK_HOOK             0
#define configUSE_DAEMON_TASK_STARTUP_HOOK 0

#define configTICK_RATE_HZ              ( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES            ( 5 )
#define configMINIMAL_STACK_SIZE        ( ( unsigned short ) 128 )
#define configTOTAL_HEAP_SIZE           ( ( size_t ) ( 32 * 1024 ) )
#define configMAX_TASK_NAME_LEN         ( 16 )
#define configUSE_16_BIT_TICKS          0
#define configIDLE_SHOULD_YIELD         1

/* 記憶體配置 */
#define configSUPPORT_STATIC_ALLOCATION 0
#define configSUPPORT_DYNAMIC_ALLOCATION 1

/* 除錯 & 鉤子函數 */
#define configUSE_MALLOC_FAILED_HOOK    0
#define configCHECK_FOR_STACK_OVERFLOW  0
#define configUSE_TRACE_FACILITY        0

/* 系統功能 */
#define INCLUDE_vTaskPrioritySet        1
#define INCLUDE_uxTaskPriorityGet       1
#define INCLUDE_vTaskDelete             1
#define INCLUDE_vTaskSuspend            1
#define INCLUDE_vTaskDelayUntil         1
#define INCLUDE_vTaskDelay              1

#endif /* FREERTOS_CONFIG_H */

