//
// Created by trueb on 13.09.2021.
//

#include "usbh_hid.h"

#ifndef __USBH_HID_GAMEPAD_H
#define __USBH_HID_GAMEPAD_H

typedef struct _HID_GAMEPAD_Info
{
    uint8_t              raw[8];
}HID_GAMEPAD_Info_TypeDef;

USBH_StatusTypeDef USBH_HID_GamepadInit(USBH_HandleTypeDef *phost);
HID_GAMEPAD_Info_TypeDef *USBH_HID_GetGamepadInfo(USBH_HandleTypeDef *phost);

#endif //STM32_USB_GAMEPAD_USBH_HID_GAMEPAD_H
