/**********************************************************************************************
 * Filename:       color_service.h
 *
 * Description:    This file contains the color_service service definitions and
 *                 prototypes.
 *
 * Copyright (c) 2015-2018, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *************************************************************************************************/


#ifndef _COLOR_SERVICE_H_
#define _COLOR_SERVICE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*********************************************************************
 * INCLUDES
 */

/*********************************************************************
* CONSTANTS
*/
// Service UUID
#define COLOR_SERVICE_SERV_UUID 0xBABE

//  Characteristic defines
#define COLOR_SERVICE_COLOR_N_1_ID   0
#define COLOR_SERVICE_COLOR_N_1_UUID 0xBAE1
#define COLOR_SERVICE_COLOR_N_1_LEN  6

//  Characteristic defines
#define COLOR_SERVICE_COLOR_N_2_ID   1
#define COLOR_SERVICE_COLOR_N_2_UUID 0xBAE2
#define COLOR_SERVICE_COLOR_N_2_LEN  6

//  Characteristic defines
#define COLOR_SERVICE_COLOR_N_3_ID   2
#define COLOR_SERVICE_COLOR_N_3_UUID 0xBAE3
#define COLOR_SERVICE_COLOR_N_3_LEN  6

//  Characteristic defines
#define COLOR_SERVICE_COLOR_N_4_ID   3
#define COLOR_SERVICE_COLOR_N_4_UUID 0xBAE4
#define COLOR_SERVICE_COLOR_N_4_LEN  6

//  Characteristic defines
#define COLOR_SERVICE_COLOR_N_5_ID   4
#define COLOR_SERVICE_COLOR_N_5_UUID 0xBAE5
#define COLOR_SERVICE_COLOR_N_5_LEN  6

//  Characteristic defines
#define COLOR_SERVICE_COLOR_N_6_ID   5
#define COLOR_SERVICE_COLOR_N_6_UUID 0xBAE6
#define COLOR_SERVICE_COLOR_N_6_LEN  6

//  Characteristic defines
#define COLOR_SERVICE_COLOR_N_7_ID   6
#define COLOR_SERVICE_COLOR_N_7_UUID 0xBAE7
#define COLOR_SERVICE_COLOR_N_7_LEN  6

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * Profile Callbacks
 */

// Callback when a characteristic value has changed
typedef void (*color_serviceChange_t)(uint16_t connHandle, uint8_t paramID, uint16_t len, uint8_t *pValue);

typedef struct
{
  color_serviceChange_t        pfnChangeCb;  // Called when characteristic value changes
  color_serviceChange_t        pfnCfgChangeCb;
} color_serviceCBs_t;



/*********************************************************************
 * API FUNCTIONS
 */


/*
 * Color_service_AddService- Initializes the Color_service service by registering
 *          GATT attributes with the GATT server.
 *
 */
extern bStatus_t Color_service_AddService( uint8_t rspTaskId);

/*
 * Color_service_RegisterAppCBs - Registers the application callback function.
 *                    Only call this function once.
 *
 *    appCallbacks - pointer to application callbacks.
 */
extern bStatus_t Color_service_RegisterAppCBs( color_serviceCBs_t *appCallbacks );

/*
 * Color_service_SetParameter - Set a Color_service parameter.
 *
 *    param - Profile parameter ID
 *    len - length of data to right
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
extern bStatus_t Color_service_SetParameter(uint8_t param, uint16_t len, void *value);

/*
 * Color_service_GetParameter - Get a Color_service parameter.
 *
 *    param - Profile parameter ID
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
extern bStatus_t Color_service_GetParameter(uint8_t param, uint16_t *len, void *value);

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* _COLOR_SERVICE_H_ */
