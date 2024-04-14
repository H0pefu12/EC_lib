/**
 * @Author: H0pefu12 147677733+H0pefu12@users.noreply.github.com
 * @Date: 2024-04-01 00:59:52
 * @LastEditTime: 2024-04-01 15:32:11
 * @LastEditors: H0pefu12 147677733+H0pefu12@users.noreply.github.com
 * @Description: 
 * @FilePath: /MDK-ARMd:/0_Important/RM_iRobot/02_Engineer/Engineer_Chassis/EC_lib/device/Motor/RMDMotor/RMDMotor.h
 */
//=====================================================================================================
// djiMotor.h
//=====================================================================================================
//
//       IRobot  EC_lib
//
// author: @ dji
// modify: @ Specific_Cola
//
//
//
//=====================================================================================================
#ifndef RMDMOTOR_H__
#define RMDMOTOR_H__

#include "bsp_can.h"
#include "bsp_dwt.h"
#include "controller.h"
#include "main.h"
#include "struct_typedef.h"

#define MAX_RMD_MOTOR_NUM 3   // 姑且算一个can7个电机
#define OFFLINE_TIME_MAX 0.1  // 单位s
typedef enum {
    RMD_MOTOR_MASK = 0x80,
    RMD_MOTOR_4015 = 0x81,

} RMD_Motor_type_t;

typedef struct {
    uint8_t cmd_id;
    int8_t temperature;
    int16_t iq;
    int16_t speed;
    uint16_t encoder;
} RMD_Motor_Info_t;

typedef struct {
    int16_t iqControl;
} RMD_Command_t;

typedef struct RMD_Motor_ {
    uint8_t statu;  // online 0  / offline 1
    RMD_Motor_type_t
        motor_type;  // 6020   3508   2006   need add pls contact lwt
    RMD_Motor_Info_t state_interfaces;
    Can_Device_t* can_info;
    RMD_Command_t command_interfaces;

    void (*motorCallback)(struct RMD_Motor_*);
} RMD_Motor_t;

typedef struct {
    RMD_Motor_type_t motor_type;

#ifdef CAN_DEVICE
    CAN_HandleTypeDef* can_handle;
#elif defined(FDCAN_DEVICE)
    FDCAN_HandleTypeDef* can_handle;
#endif

    uint8_t id;
} RMD_Motor_Register_t;

RMD_Motor_t* rmdMotorAdd(RMD_Motor_Register_t* reg);
void rmdMotorDelete(RMD_Motor_t* motor);
void rmdMotorInfoUpdate(RMD_Motor_t* motor, uint8_t* data);
Return_t rmdMotorSendMessage(RMD_Motor_t* motor);

#endif  // !DJIMOTOR_H__