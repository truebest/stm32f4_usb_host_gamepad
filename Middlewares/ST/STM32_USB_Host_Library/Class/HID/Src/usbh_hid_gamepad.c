//
// Created by trueb on 13.09.2021.
//

#include "usbh_hid_gamepad.h"
#include "usbh_hid_parser.h"




#define                  NUM_BYTES      8

HID_GAMEPAD_Info_TypeDef  gamepad_info;
uint8_t                  gamepad_report_data[NUM_BYTES];
uint8_t                  gamepad_rx_report_buf[NUM_BYTES];

static USBH_StatusTypeDef USBH_HID_GamepadDecode(USBH_HandleTypeDef *phost);

USBH_StatusTypeDef USBH_HID_GamepadInit(USBH_HandleTypeDef *phost)
{
    uint32_t i;
    HID_HandleTypeDef *HID_Handle = (HID_HandleTypeDef *) phost->pActiveClass->pData;

    for (int i = 0; i < NUM_BYTES; ++i) {
        gamepad_info.raw[i] = 0;
    }


    for (i = 0U; i < (sizeof(gamepad_report_data) / sizeof(uint8_t)); i++)
    {
        gamepad_report_data[i] = 0U;
        gamepad_rx_report_buf[i] = 0U;
    }

    if (HID_Handle->length > sizeof(gamepad_report_data))
    {
        HID_Handle->length = sizeof(gamepad_report_data);
    }
    HID_Handle->pData = (uint8_t *)(void *)gamepad_rx_report_buf;
    USBH_HID_FifoInit(&HID_Handle->fifo, phost->device.Data, HID_QUEUE_SIZE * sizeof(gamepad_report_data));

    return USBH_OK;
}

HID_GAMEPAD_Info_TypeDef *USBH_HID_GetGamepadInfo(USBH_HandleTypeDef *phost)
{
    if (USBH_HID_GamepadDecode(phost) == USBH_OK)
    {
        return &gamepad_info;
    }
    else
    {
        return NULL;
    }
}

static USBH_StatusTypeDef USBH_HID_GamepadDecode(USBH_HandleTypeDef *phost)
{
    HID_HandleTypeDef *HID_Handle = (HID_HandleTypeDef *) phost->pActiveClass->pData;

    if (HID_Handle->length == 0U)
    {
        return USBH_FAIL;
    }
    /*Fill report */
    if (USBH_HID_FifoRead(&HID_Handle->fifo, gamepad_report_data, HID_Handle->length) ==  HID_Handle->length)
    {
        /*Decode report */
        for (int i = 0; i < NUM_BYTES; ++i) {
            gamepad_info.raw[i] = gamepad_report_data[i];
        }


        return USBH_OK;
    }
    return   USBH_FAIL;
}