#ifndef __shm__
#define __shm__

#include <stdint.h>
#include "FreeRTOS.h"
#include "semphr.h"

#define PACKET_SOF 0xAA

/* ======================================================================== */
/* 1. 시스템 상태 및 제어 열거형(Enum) 정의                                    */
/* ======================================================================== */
typedef enum
{
    SYS_IDLE = 0,
    SYS_IDENTIFY,
    SYS_AUTHENTICATE,
    SYS_NEGOTIATE,
    SYS_ACTIVE,
    SYS_FAULT,
    SYS_QUARANTINE
} SystemState_t;

typedef enum
{
    MODULE_NONE = 0,
    MODULE_GENERAL,      // Module A: 일반 배송 모듈
    MODULE_COLD_CHAIN,   // Module B: 냉장 배송 모듈
    MODULE_UNKNOWN       // 등록되지 않았거나 알 수 없는 모듈
} ModuleType_t;

typedef enum
{
    FAULT_NONE = 0,
    FAULT_IDENTIFY_TIMEOUT,
    FAULT_AUTH_FAIL,
    FAULT_AUTH_TIMEOUT,
    FAULT_POWER_REJECT,
    FAULT_NEGOTIATE_TIMEOUT,
    FAULT_POWER_VIOLATION_MAX
} FaultCode_t;

/* ======================================================================== */
/* 2. STM32 커널 내부 관리용 전체 공유 메모리 구조체                            */
/* ======================================================================== */
typedef struct
{
    /* System State */
    SystemState_t system_state;
    ModuleType_t module_type;
    FaultCode_t latest_fault;

    uint32_t module_id;

    uint8_t dock_detected;
    uint8_t auth_result;
    uint8_t power_granted;
    uint8_t module_function_enabled;

    /* Driving */
    uint32_t target_speed_rpm;
    uint32_t current_speed_rpm;
    uint16_t motor_pwm_duty;

    /* Power Policy */
    uint32_t requested_power_w;
    uint32_t granted_power_w;
    uint32_t reported_power_w;
    uint8_t power_violation_count;

    /* Module A */
    uint32_t pressure_value;

    /* Module B */
    uint32_t target_temp_c;
    uint32_t current_temp_c;
    uint8_t peltier_pwm;
    uint8_t fan_pwm;

    /* Warning */
    uint32_t warning_flag;
    uint8_t sleep_flag;
} SystemSharedData_t;


/* ======================================================================== */
/* 4. 외부 참조 함수 선언                                                    */
/* ======================================================================== */
void Send_System_Packet(SystemSharedData_t* shared_data);

#endif
