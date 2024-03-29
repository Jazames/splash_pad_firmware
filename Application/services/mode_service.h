/**********************************************************************************************
 * Filename:       mode_service.h
 *
 * Description:    This file contains the mode_service service definitions and
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


#ifndef _MODE_SERVICE_H_
#define _MODE_SERVICE_H_

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
#define MODE_SERVICE_SERV_UUID 0xCAFE
#define MODE_SERVICE_SERV_UUID_BASE128(uuid) 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0xB0, 0x00, 0x40, 0x51, 0x04, LO_UINT16(uuid), HI_UINT16(uuid), 0x00, \
    0xF0
//  Characteristic defines
#define MODE_SERVICE_MODE_N_1_ID   0
#define MODE_SERVICE_MODE_N_1_UUID 0xF001
#define MODE_SERVICE_MODE_N_1_LEN  8

//  Characteristic defines
#define MODE_SERVICE_MODE_N_2_ID   1
#define MODE_SERVICE_MODE_N_2_UUID 0xF002
#define MODE_SERVICE_MODE_N_2_LEN  8

//  Characteristic defines
#define MODE_SERVICE_MODE_N_3_ID   2
#define MODE_SERVICE_MODE_N_3_UUID 0xF003
#define MODE_SERVICE_MODE_N_3_LEN  8

//  Characteristic defines
#define MODE_SERVICE_MODE_N_4_ID   3
#define MODE_SERVICE_MODE_N_4_UUID 0xF004
#define MODE_SERVICE_MODE_N_4_LEN  8

//  Characteristic defines
#define MODE_SERVICE_MODE_N_5_ID   4
#define MODE_SERVICE_MODE_N_5_UUID 0xF005
#define MODE_SERVICE_MODE_N_5_LEN  8

//  Characteristic defines
#define MODE_SERVICE_MODE_N_6_ID   5
#define MODE_SERVICE_MODE_N_6_UUID 0xF006
#define MODE_SERVICE_MODE_N_6_LEN  8

//  Characteristic defines
#define MODE_SERVICE_MODE_N_7_ID   6
#define MODE_SERVICE_MODE_N_7_UUID 0xF007
#define MODE_SERVICE_MODE_N_7_LEN  8

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
typedef void (*mode_serviceChange_t)(uint16_t connHandle, uint8_t paramID, uint16_t len, uint8_t *pValue);

typedef struct
{
  mode_serviceChange_t        pfnChangeCb;  // Called when characteristic value changes
  mode_serviceChange_t        pfnCfgChangeCb;
} mode_serviceCBs_t;



/*********************************************************************
 * API FUNCTIONS
 */


/*
 * Mode_service_AddService- Initializes the Mode_service service by registering
 *          GATT attributes with the GATT server.
 *
 */
extern bStatus_t Mode_service_AddService( uint8_t rspTaskId);

/*
 * Mode_service_RegisterAppCBs - Registers the application callback function.
 *                    Only call this function once.
 *
 *    appCallbacks - pointer to application callbacks.
 */
extern bStatus_t Mode_service_RegisterAppCBs( mode_serviceCBs_t *appCallbacks );

/*
 * Mode_service_SetParameter - Set a Mode_service parameter.
 *
 *    param - Profile parameter ID
 *    len - length of data to right
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
extern bStatus_t Mode_service_SetParameter(uint8_t param, uint16_t len, void *value);

/*
 * Mode_service_GetParameter - Get a Mode_service parameter.
 *
 *    param - Profile parameter ID
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
extern bStatus_t Mode_service_GetParameter(uint8_t param, uint16_t *len, void *value);

/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* _MODE_SERVICE_H_ */
