/**********************************************************************************************
 * Filename:       mode_service.c
 *
 * Description:    This file contains the implementation of the service.
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


/*********************************************************************
 * INCLUDES
 */
#include <string.h>

#include <icall.h>

/* This Header file contains all BLE API and icall structure definition */
#include "icall_ble_api.h"

#include "mode_service.h"

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
* GLOBAL VARIABLES
*/

// mode_service Service UUID
CONST uint8_t mode_serviceUUID[ATT_BT_UUID_SIZE] =
{
  LO_UINT16(MODE_SERVICE_SERV_UUID), HI_UINT16(MODE_SERVICE_SERV_UUID)
};

// mode_n_1 UUID
CONST uint8_t mode_service_Mode_n_1UUID[ATT_UUID_SIZE] =
{
  TI_BASE_UUID_128(MODE_SERVICE_MODE_N_1_UUID)
};
// mode_n_2 UUID
CONST uint8_t mode_service_Mode_n_2UUID[ATT_UUID_SIZE] =
{
  TI_BASE_UUID_128(MODE_SERVICE_MODE_N_2_UUID)
};
// mode_n_3 UUID
CONST uint8_t mode_service_Mode_n_3UUID[ATT_UUID_SIZE] =
{
  TI_BASE_UUID_128(MODE_SERVICE_MODE_N_3_UUID)
};
// mode_n_4 UUID
CONST uint8_t mode_service_Mode_n_4UUID[ATT_UUID_SIZE] =
{
  TI_BASE_UUID_128(MODE_SERVICE_MODE_N_4_UUID)
};
// mode_n_5 UUID
CONST uint8_t mode_service_Mode_n_5UUID[ATT_UUID_SIZE] =
{
  TI_BASE_UUID_128(MODE_SERVICE_MODE_N_5_UUID)
};
// mode_n_6 UUID
CONST uint8_t mode_service_Mode_n_6UUID[ATT_UUID_SIZE] =
{
  TI_BASE_UUID_128(MODE_SERVICE_MODE_N_6_UUID)
};
// mode_n_7 UUID
CONST uint8_t mode_service_Mode_n_7UUID[ATT_UUID_SIZE] =
{
  TI_BASE_UUID_128(MODE_SERVICE_MODE_N_7_UUID)
};

/*********************************************************************
 * LOCAL VARIABLES
 */

static mode_serviceCBs_t *pAppCBs = NULL;

/*********************************************************************
* Profile Attributes - variables
*/

// Service declaration
static CONST gattAttrType_t mode_serviceDecl = { ATT_BT_UUID_SIZE, mode_serviceUUID };

// Characteristic "Mode_n_1" Properties (for declaration)
static uint8_t mode_service_Mode_n_1Props = GATT_PROP_READ | GATT_PROP_WRITE | GATT_PROP_WRITE_NO_RSP | GATT_PROP_NOTIFY;

// Characteristic "Mode_n_1" Value variable
static uint8_t mode_service_Mode_n_1Val[MODE_SERVICE_MODE_N_1_LEN] = {0};

// Characteristic "Mode_n_1" CCCD
static gattCharCfg_t *mode_service_Mode_n_1Config;
// Characteristic "Mode_n_2" Properties (for declaration)
static uint8_t mode_service_Mode_n_2Props = GATT_PROP_READ | GATT_PROP_WRITE | GATT_PROP_WRITE_NO_RSP | GATT_PROP_NOTIFY;

// Characteristic "Mode_n_2" Value variable
static uint8_t mode_service_Mode_n_2Val[MODE_SERVICE_MODE_N_2_LEN] = {0};

// Characteristic "Mode_n_2" CCCD
static gattCharCfg_t *mode_service_Mode_n_2Config;
// Characteristic "Mode_n_3" Properties (for declaration)
static uint8_t mode_service_Mode_n_3Props = GATT_PROP_READ | GATT_PROP_WRITE | GATT_PROP_WRITE_NO_RSP | GATT_PROP_NOTIFY;

// Characteristic "Mode_n_3" Value variable
static uint8_t mode_service_Mode_n_3Val[MODE_SERVICE_MODE_N_3_LEN] = {0};

// Characteristic "Mode_n_3" CCCD
static gattCharCfg_t *mode_service_Mode_n_3Config;
// Characteristic "Mode_n_4" Properties (for declaration)
static uint8_t mode_service_Mode_n_4Props = GATT_PROP_READ | GATT_PROP_WRITE | GATT_PROP_WRITE_NO_RSP | GATT_PROP_NOTIFY;

// Characteristic "Mode_n_4" Value variable
static uint8_t mode_service_Mode_n_4Val[MODE_SERVICE_MODE_N_4_LEN] = {0};

// Characteristic "Mode_n_4" CCCD
static gattCharCfg_t *mode_service_Mode_n_4Config;
// Characteristic "Mode_n_5" Properties (for declaration)
static uint8_t mode_service_Mode_n_5Props = GATT_PROP_READ | GATT_PROP_WRITE | GATT_PROP_WRITE_NO_RSP | GATT_PROP_NOTIFY;

// Characteristic "Mode_n_5" Value variable
static uint8_t mode_service_Mode_n_5Val[MODE_SERVICE_MODE_N_5_LEN] = {0};

// Characteristic "Mode_n_5" CCCD
static gattCharCfg_t *mode_service_Mode_n_5Config;
// Characteristic "Mode_n_6" Properties (for declaration)
static uint8_t mode_service_Mode_n_6Props = GATT_PROP_READ | GATT_PROP_WRITE | GATT_PROP_WRITE_NO_RSP | GATT_PROP_NOTIFY;

// Characteristic "Mode_n_6" Value variable
static uint8_t mode_service_Mode_n_6Val[MODE_SERVICE_MODE_N_6_LEN] = {0};

// Characteristic "Mode_n_6" CCCD
static gattCharCfg_t *mode_service_Mode_n_6Config;
// Characteristic "Mode_n_7" Properties (for declaration)
static uint8_t mode_service_Mode_n_7Props = GATT_PROP_READ | GATT_PROP_WRITE | GATT_PROP_WRITE_NO_RSP | GATT_PROP_NOTIFY;

// Characteristic "Mode_n_7" Value variable
static uint8_t mode_service_Mode_n_7Val[MODE_SERVICE_MODE_N_7_LEN] = {0};

// Characteristic "Mode_n_7" CCCD
static gattCharCfg_t *mode_service_Mode_n_7Config;

/*********************************************************************
* Profile Attributes - Table
*/

static gattAttribute_t mode_serviceAttrTbl[] =
{
  // mode_service Service Declaration
  {
    { ATT_BT_UUID_SIZE, primaryServiceUUID },
    GATT_PERMIT_READ,
    0,
    (uint8_t *)&mode_serviceDecl
  },
    // Mode_n_1 Characteristic Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &mode_service_Mode_n_1Props
    },
      // Mode_n_1 Characteristic Value
      {
        { ATT_UUID_SIZE, mode_service_Mode_n_1UUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        mode_service_Mode_n_1Val
      },
      // Mode_n_1 CCCD
      {
        { ATT_BT_UUID_SIZE, clientCharCfgUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        (uint8 *)&mode_service_Mode_n_1Config
      },
    // Mode_n_2 Characteristic Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &mode_service_Mode_n_2Props
    },
      // Mode_n_2 Characteristic Value
      {
        { ATT_UUID_SIZE, mode_service_Mode_n_2UUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        mode_service_Mode_n_2Val
      },
      // Mode_n_2 CCCD
      {
        { ATT_BT_UUID_SIZE, clientCharCfgUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        (uint8 *)&mode_service_Mode_n_2Config
      },
    // Mode_n_3 Characteristic Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &mode_service_Mode_n_3Props
    },
      // Mode_n_3 Characteristic Value
      {
        { ATT_UUID_SIZE, mode_service_Mode_n_3UUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        mode_service_Mode_n_3Val
      },
      // Mode_n_3 CCCD
      {
        { ATT_BT_UUID_SIZE, clientCharCfgUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        (uint8 *)&mode_service_Mode_n_3Config
      },
    // Mode_n_4 Characteristic Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &mode_service_Mode_n_4Props
    },
      // Mode_n_4 Characteristic Value
      {
        { ATT_UUID_SIZE, mode_service_Mode_n_4UUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        mode_service_Mode_n_4Val
      },
      // Mode_n_4 CCCD
      {
        { ATT_BT_UUID_SIZE, clientCharCfgUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        (uint8 *)&mode_service_Mode_n_4Config
      },
    // Mode_n_5 Characteristic Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &mode_service_Mode_n_5Props
    },
      // Mode_n_5 Characteristic Value
      {
        { ATT_UUID_SIZE, mode_service_Mode_n_5UUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        mode_service_Mode_n_5Val
      },
      // Mode_n_5 CCCD
      {
        { ATT_BT_UUID_SIZE, clientCharCfgUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        (uint8 *)&mode_service_Mode_n_5Config
      },
    // Mode_n_6 Characteristic Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &mode_service_Mode_n_6Props
    },
      // Mode_n_6 Characteristic Value
      {
        { ATT_UUID_SIZE, mode_service_Mode_n_6UUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        mode_service_Mode_n_6Val
      },
      // Mode_n_6 CCCD
      {
        { ATT_BT_UUID_SIZE, clientCharCfgUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        (uint8 *)&mode_service_Mode_n_6Config
      },
    // Mode_n_7 Characteristic Declaration
    {
      { ATT_BT_UUID_SIZE, characterUUID },
      GATT_PERMIT_READ,
      0,
      &mode_service_Mode_n_7Props
    },
      // Mode_n_7 Characteristic Value
      {
        { ATT_UUID_SIZE, mode_service_Mode_n_7UUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        mode_service_Mode_n_7Val
      },
      // Mode_n_7 CCCD
      {
        { ATT_BT_UUID_SIZE, clientCharCfgUUID },
        GATT_PERMIT_READ | GATT_PERMIT_WRITE,
        0,
        (uint8 *)&mode_service_Mode_n_7Config
      },
};

/*********************************************************************
 * LOCAL FUNCTIONS
 */
static bStatus_t mode_service_ReadAttrCB( uint16_t connHandle, gattAttribute_t *pAttr,
                                           uint8_t *pValue, uint16_t *pLen, uint16_t offset,
                                           uint16_t maxLen, uint8_t method );
static bStatus_t mode_service_WriteAttrCB( uint16_t connHandle, gattAttribute_t *pAttr,
                                            uint8_t *pValue, uint16_t len, uint16_t offset,
                                            uint8_t method );

/*********************************************************************
 * PROFILE CALLBACKS
 */
// Simple Profile Service Callbacks
CONST gattServiceCBs_t mode_serviceCBs =
{
  mode_service_ReadAttrCB,  // Read callback function pointer
  mode_service_WriteAttrCB, // Write callback function pointer
  NULL                       // Authorization callback function pointer
};

/*********************************************************************
* PUBLIC FUNCTIONS
*/

/*
 * Mode_service_AddService- Initializes the Mode_service service by registering
 *          GATT attributes with the GATT server.
 *
 */
extern bStatus_t Mode_service_AddService( uint8_t rspTaskId )
{
  uint8_t status;

  // Allocate Client Characteristic Configuration table
  mode_service_Mode_n_1Config = (gattCharCfg_t *)ICall_malloc( sizeof(gattCharCfg_t) * linkDBNumConns );
  if ( mode_service_Mode_n_1Config == NULL )
  {
    return ( bleMemAllocError );
  }

  // Initialize Client Characteristic Configuration attributes
  GATTServApp_InitCharCfg( CONNHANDLE_INVALID, mode_service_Mode_n_1Config );
  // Allocate Client Characteristic Configuration table
  mode_service_Mode_n_2Config = (gattCharCfg_t *)ICall_malloc( sizeof(gattCharCfg_t) * linkDBNumConns );
  if ( mode_service_Mode_n_2Config == NULL )
  {
    return ( bleMemAllocError );
  }

  // Initialize Client Characteristic Configuration attributes
  GATTServApp_InitCharCfg( CONNHANDLE_INVALID, mode_service_Mode_n_2Config );
  // Allocate Client Characteristic Configuration table
  mode_service_Mode_n_3Config = (gattCharCfg_t *)ICall_malloc( sizeof(gattCharCfg_t) * linkDBNumConns );
  if ( mode_service_Mode_n_3Config == NULL )
  {
    return ( bleMemAllocError );
  }

  // Initialize Client Characteristic Configuration attributes
  GATTServApp_InitCharCfg( CONNHANDLE_INVALID, mode_service_Mode_n_3Config );
  // Allocate Client Characteristic Configuration table
  mode_service_Mode_n_4Config = (gattCharCfg_t *)ICall_malloc( sizeof(gattCharCfg_t) * linkDBNumConns );
  if ( mode_service_Mode_n_4Config == NULL )
  {
    return ( bleMemAllocError );
  }

  // Initialize Client Characteristic Configuration attributes
  GATTServApp_InitCharCfg( CONNHANDLE_INVALID, mode_service_Mode_n_4Config );
  // Allocate Client Characteristic Configuration table
  mode_service_Mode_n_5Config = (gattCharCfg_t *)ICall_malloc( sizeof(gattCharCfg_t) * linkDBNumConns );
  if ( mode_service_Mode_n_5Config == NULL )
  {
    return ( bleMemAllocError );
  }

  // Initialize Client Characteristic Configuration attributes
  GATTServApp_InitCharCfg( CONNHANDLE_INVALID, mode_service_Mode_n_5Config );
  // Allocate Client Characteristic Configuration table
  mode_service_Mode_n_6Config = (gattCharCfg_t *)ICall_malloc( sizeof(gattCharCfg_t) * linkDBNumConns );
  if ( mode_service_Mode_n_6Config == NULL )
  {
    return ( bleMemAllocError );
  }

  // Initialize Client Characteristic Configuration attributes
  GATTServApp_InitCharCfg( CONNHANDLE_INVALID, mode_service_Mode_n_6Config );
  // Allocate Client Characteristic Configuration table
  mode_service_Mode_n_7Config = (gattCharCfg_t *)ICall_malloc( sizeof(gattCharCfg_t) * linkDBNumConns );
  if ( mode_service_Mode_n_7Config == NULL )
  {
    return ( bleMemAllocError );
  }

  // Initialize Client Characteristic Configuration attributes
  GATTServApp_InitCharCfg( CONNHANDLE_INVALID, mode_service_Mode_n_7Config );
  // Register GATT attribute list and CBs with GATT Server App
  status = GATTServApp_RegisterService( mode_serviceAttrTbl,
                                        GATT_NUM_ATTRS( mode_serviceAttrTbl ),
                                        GATT_MAX_ENCRYPT_KEY_SIZE,
                                        &mode_serviceCBs );

  return ( status );
}

/*
 * Mode_service_RegisterAppCBs - Registers the application callback function.
 *                    Only call this function once.
 *
 *    appCallbacks - pointer to application callbacks.
 */
bStatus_t Mode_service_RegisterAppCBs( mode_serviceCBs_t *appCallbacks )
{
  if ( appCallbacks )
  {
    pAppCBs = appCallbacks;

    return ( SUCCESS );
  }
  else
  {
    return ( bleAlreadyInRequestedMode );
  }
}

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
bStatus_t Mode_service_SetParameter( uint8_t param, uint16_t len, void *value )
{
  bStatus_t ret = SUCCESS;
  switch ( param )
  {
    case MODE_SERVICE_MODE_N_1_ID:
      if ( len == MODE_SERVICE_MODE_N_1_LEN )
      {
        memcpy(mode_service_Mode_n_1Val, value, len);

        // Try to send notification.
        GATTServApp_ProcessCharCfg( mode_service_Mode_n_1Config, (uint8_t *)&mode_service_Mode_n_1Val, FALSE,
                                    mode_serviceAttrTbl, GATT_NUM_ATTRS( mode_serviceAttrTbl ),
                                    INVALID_TASK_ID,  mode_service_ReadAttrCB);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case MODE_SERVICE_MODE_N_2_ID:
      if ( len == MODE_SERVICE_MODE_N_2_LEN )
      {
        memcpy(mode_service_Mode_n_2Val, value, len);

        // Try to send notification.
        GATTServApp_ProcessCharCfg( mode_service_Mode_n_2Config, (uint8_t *)&mode_service_Mode_n_2Val, FALSE,
                                    mode_serviceAttrTbl, GATT_NUM_ATTRS( mode_serviceAttrTbl ),
                                    INVALID_TASK_ID,  mode_service_ReadAttrCB);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case MODE_SERVICE_MODE_N_3_ID:
      if ( len == MODE_SERVICE_MODE_N_3_LEN )
      {
        memcpy(mode_service_Mode_n_3Val, value, len);

        // Try to send notification.
        GATTServApp_ProcessCharCfg( mode_service_Mode_n_3Config, (uint8_t *)&mode_service_Mode_n_3Val, FALSE,
                                    mode_serviceAttrTbl, GATT_NUM_ATTRS( mode_serviceAttrTbl ),
                                    INVALID_TASK_ID,  mode_service_ReadAttrCB);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case MODE_SERVICE_MODE_N_4_ID:
      if ( len == MODE_SERVICE_MODE_N_4_LEN )
      {
        memcpy(mode_service_Mode_n_4Val, value, len);

        // Try to send notification.
        GATTServApp_ProcessCharCfg( mode_service_Mode_n_4Config, (uint8_t *)&mode_service_Mode_n_4Val, FALSE,
                                    mode_serviceAttrTbl, GATT_NUM_ATTRS( mode_serviceAttrTbl ),
                                    INVALID_TASK_ID,  mode_service_ReadAttrCB);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case MODE_SERVICE_MODE_N_5_ID:
      if ( len == MODE_SERVICE_MODE_N_5_LEN )
      {
        memcpy(mode_service_Mode_n_5Val, value, len);

        // Try to send notification.
        GATTServApp_ProcessCharCfg( mode_service_Mode_n_5Config, (uint8_t *)&mode_service_Mode_n_5Val, FALSE,
                                    mode_serviceAttrTbl, GATT_NUM_ATTRS( mode_serviceAttrTbl ),
                                    INVALID_TASK_ID,  mode_service_ReadAttrCB);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case MODE_SERVICE_MODE_N_6_ID:
      if ( len == MODE_SERVICE_MODE_N_6_LEN )
      {
        memcpy(mode_service_Mode_n_6Val, value, len);

        // Try to send notification.
        GATTServApp_ProcessCharCfg( mode_service_Mode_n_6Config, (uint8_t *)&mode_service_Mode_n_6Val, FALSE,
                                    mode_serviceAttrTbl, GATT_NUM_ATTRS( mode_serviceAttrTbl ),
                                    INVALID_TASK_ID,  mode_service_ReadAttrCB);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    case MODE_SERVICE_MODE_N_7_ID:
      if ( len == MODE_SERVICE_MODE_N_7_LEN )
      {
        memcpy(mode_service_Mode_n_7Val, value, len);

        // Try to send notification.
        GATTServApp_ProcessCharCfg( mode_service_Mode_n_7Config, (uint8_t *)&mode_service_Mode_n_7Val, FALSE,
                                    mode_serviceAttrTbl, GATT_NUM_ATTRS( mode_serviceAttrTbl ),
                                    INVALID_TASK_ID,  mode_service_ReadAttrCB);
      }
      else
      {
        ret = bleInvalidRange;
      }
      break;

    default:
      ret = INVALIDPARAMETER;
      break;
  }
  return ret;
}


/*
 * Mode_service_GetParameter - Get a Mode_service parameter.
 *
 *    param - Profile parameter ID
 *    value - pointer to data to write.  This is dependent on
 *          the parameter ID and WILL be cast to the appropriate
 *          data type (example: data type of uint16 will be cast to
 *          uint16 pointer).
 */
bStatus_t Mode_service_GetParameter( uint8_t param, uint16_t *len, void *value )
{
  bStatus_t ret = SUCCESS;
  switch ( param )
  {
    case MODE_SERVICE_MODE_N_1_ID:
      memcpy(value, mode_service_Mode_n_1Val, MODE_SERVICE_MODE_N_1_LEN);
      break;

    case MODE_SERVICE_MODE_N_2_ID:
      memcpy(value, mode_service_Mode_n_2Val, MODE_SERVICE_MODE_N_2_LEN);
      break;

    case MODE_SERVICE_MODE_N_3_ID:
      memcpy(value, mode_service_Mode_n_3Val, MODE_SERVICE_MODE_N_3_LEN);
      break;

    case MODE_SERVICE_MODE_N_4_ID:
      memcpy(value, mode_service_Mode_n_4Val, MODE_SERVICE_MODE_N_4_LEN);
      break;

    case MODE_SERVICE_MODE_N_5_ID:
      memcpy(value, mode_service_Mode_n_5Val, MODE_SERVICE_MODE_N_5_LEN);
      break;

    case MODE_SERVICE_MODE_N_6_ID:
      memcpy(value, mode_service_Mode_n_6Val, MODE_SERVICE_MODE_N_6_LEN);
      break;

    case MODE_SERVICE_MODE_N_7_ID:
      memcpy(value, mode_service_Mode_n_7Val, MODE_SERVICE_MODE_N_7_LEN);
      break;

    default:
      ret = INVALIDPARAMETER;
      break;
  }
  return ret;
}


/*********************************************************************
 * @fn          mode_service_ReadAttrCB
 *
 * @brief       Read an attribute.
 *
 * @param       connHandle - connection message was received on
 * @param       pAttr - pointer to attribute
 * @param       pValue - pointer to data to be read
 * @param       pLen - length of data to be read
 * @param       offset - offset of the first octet to be read
 * @param       maxLen - maximum length of data to be read
 * @param       method - type of read message
 *
 * @return      SUCCESS, blePending or Failure
 */
static bStatus_t mode_service_ReadAttrCB( uint16_t connHandle, gattAttribute_t *pAttr,
                                       uint8_t *pValue, uint16_t *pLen, uint16_t offset,
                                       uint16_t maxLen, uint8_t method )
{
  bStatus_t status = SUCCESS;

  // See if request is regarding the Mode_n_1 Characteristic Value
if ( ! memcmp(pAttr->type.uuid, mode_service_Mode_n_1UUID, pAttr->type.len) )
  {
    if ( offset > MODE_SERVICE_MODE_N_1_LEN )  // Prevent malicious ATT ReadBlob offsets.
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      *pLen = MIN(maxLen, MODE_SERVICE_MODE_N_1_LEN - offset);  // Transmit as much as possible
      memcpy(pValue, pAttr->pValue + offset, *pLen);
    }
  }
  // See if request is regarding the Mode_n_2 Characteristic Value
else if ( ! memcmp(pAttr->type.uuid, mode_service_Mode_n_2UUID, pAttr->type.len) )
  {
    if ( offset > MODE_SERVICE_MODE_N_2_LEN )  // Prevent malicious ATT ReadBlob offsets.
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      *pLen = MIN(maxLen, MODE_SERVICE_MODE_N_2_LEN - offset);  // Transmit as much as possible
      memcpy(pValue, pAttr->pValue + offset, *pLen);
    }
  }
  // See if request is regarding the Mode_n_3 Characteristic Value
else if ( ! memcmp(pAttr->type.uuid, mode_service_Mode_n_3UUID, pAttr->type.len) )
  {
    if ( offset > MODE_SERVICE_MODE_N_3_LEN )  // Prevent malicious ATT ReadBlob offsets.
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      *pLen = MIN(maxLen, MODE_SERVICE_MODE_N_3_LEN - offset);  // Transmit as much as possible
      memcpy(pValue, pAttr->pValue + offset, *pLen);
    }
  }
  // See if request is regarding the Mode_n_4 Characteristic Value
else if ( ! memcmp(pAttr->type.uuid, mode_service_Mode_n_4UUID, pAttr->type.len) )
  {
    if ( offset > MODE_SERVICE_MODE_N_4_LEN )  // Prevent malicious ATT ReadBlob offsets.
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      *pLen = MIN(maxLen, MODE_SERVICE_MODE_N_4_LEN - offset);  // Transmit as much as possible
      memcpy(pValue, pAttr->pValue + offset, *pLen);
    }
  }
  // See if request is regarding the Mode_n_5 Characteristic Value
else if ( ! memcmp(pAttr->type.uuid, mode_service_Mode_n_5UUID, pAttr->type.len) )
  {
    if ( offset > MODE_SERVICE_MODE_N_5_LEN )  // Prevent malicious ATT ReadBlob offsets.
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      *pLen = MIN(maxLen, MODE_SERVICE_MODE_N_5_LEN - offset);  // Transmit as much as possible
      memcpy(pValue, pAttr->pValue + offset, *pLen);
    }
  }
  // See if request is regarding the Mode_n_6 Characteristic Value
else if ( ! memcmp(pAttr->type.uuid, mode_service_Mode_n_6UUID, pAttr->type.len) )
  {
    if ( offset > MODE_SERVICE_MODE_N_6_LEN )  // Prevent malicious ATT ReadBlob offsets.
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      *pLen = MIN(maxLen, MODE_SERVICE_MODE_N_6_LEN - offset);  // Transmit as much as possible
      memcpy(pValue, pAttr->pValue + offset, *pLen);
    }
  }
  // See if request is regarding the Mode_n_7 Characteristic Value
else if ( ! memcmp(pAttr->type.uuid, mode_service_Mode_n_7UUID, pAttr->type.len) )
  {
    if ( offset > MODE_SERVICE_MODE_N_7_LEN )  // Prevent malicious ATT ReadBlob offsets.
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      *pLen = MIN(maxLen, MODE_SERVICE_MODE_N_7_LEN - offset);  // Transmit as much as possible
      memcpy(pValue, pAttr->pValue + offset, *pLen);
    }
  }
  else
  {
    // If we get here, that means you've forgotten to add an if clause for a
    // characteristic value attribute in the attribute table that has READ permissions.
    *pLen = 0;
    status = ATT_ERR_ATTR_NOT_FOUND;
  }

  return status;
}


/*********************************************************************
 * @fn      mode_service_WriteAttrCB
 *
 * @brief   Validate attribute data prior to a write operation
 *
 * @param   connHandle - connection message was received on
 * @param   pAttr - pointer to attribute
 * @param   pValue - pointer to data to be written
 * @param   len - length of data
 * @param   offset - offset of the first octet to be written
 * @param   method - type of write message
 *
 * @return  SUCCESS, blePending or Failure
 */
static bStatus_t mode_service_WriteAttrCB( uint16_t connHandle, gattAttribute_t *pAttr,
                                        uint8_t *pValue, uint16_t len, uint16_t offset,
                                        uint8_t method )
{
  bStatus_t status  = SUCCESS;
  uint8_t   paramID = 0xFF;

  // See if request is regarding a Client Characterisic Configuration
  if ( ! memcmp(pAttr->type.uuid, clientCharCfgUUID, pAttr->type.len) )
  {
    // Allow only notifications.
    status = GATTServApp_ProcessCCCWriteReq( connHandle, pAttr, pValue, len,
                                             offset, GATT_CLIENT_CFG_NOTIFY);
  }
  // See if request is regarding the Mode_n_1 Characteristic Value
  else if ( ! memcmp(pAttr->type.uuid, mode_service_Mode_n_1UUID, pAttr->type.len) )
  {
    if ( offset + len > MODE_SERVICE_MODE_N_1_LEN )
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      // Copy pValue into the variable we point to from the attribute table.
      memcpy(pAttr->pValue + offset, pValue, len);

      // Only notify application if entire expected value is written
      if ( offset + len == MODE_SERVICE_MODE_N_1_LEN)
        paramID = MODE_SERVICE_MODE_N_1_ID;
    }
  }
  // See if request is regarding the Mode_n_2 Characteristic Value
  else if ( ! memcmp(pAttr->type.uuid, mode_service_Mode_n_2UUID, pAttr->type.len) )
  {
    if ( offset + len > MODE_SERVICE_MODE_N_2_LEN )
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      // Copy pValue into the variable we point to from the attribute table.
      memcpy(pAttr->pValue + offset, pValue, len);

      // Only notify application if entire expected value is written
      if ( offset + len == MODE_SERVICE_MODE_N_2_LEN)
        paramID = MODE_SERVICE_MODE_N_2_ID;
    }
  }
  // See if request is regarding the Mode_n_3 Characteristic Value
  else if ( ! memcmp(pAttr->type.uuid, mode_service_Mode_n_3UUID, pAttr->type.len) )
  {
    if ( offset + len > MODE_SERVICE_MODE_N_3_LEN )
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      // Copy pValue into the variable we point to from the attribute table.
      memcpy(pAttr->pValue + offset, pValue, len);

      // Only notify application if entire expected value is written
      if ( offset + len == MODE_SERVICE_MODE_N_3_LEN)
        paramID = MODE_SERVICE_MODE_N_3_ID;
    }
  }
  // See if request is regarding the Mode_n_4 Characteristic Value
  else if ( ! memcmp(pAttr->type.uuid, mode_service_Mode_n_4UUID, pAttr->type.len) )
  {
    if ( offset + len > MODE_SERVICE_MODE_N_4_LEN )
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      // Copy pValue into the variable we point to from the attribute table.
      memcpy(pAttr->pValue + offset, pValue, len);

      // Only notify application if entire expected value is written
      if ( offset + len == MODE_SERVICE_MODE_N_4_LEN)
        paramID = MODE_SERVICE_MODE_N_4_ID;
    }
  }
  // See if request is regarding the Mode_n_5 Characteristic Value
  else if ( ! memcmp(pAttr->type.uuid, mode_service_Mode_n_5UUID, pAttr->type.len) )
  {
    if ( offset + len > MODE_SERVICE_MODE_N_5_LEN )
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      // Copy pValue into the variable we point to from the attribute table.
      memcpy(pAttr->pValue + offset, pValue, len);

      // Only notify application if entire expected value is written
      if ( offset + len == MODE_SERVICE_MODE_N_5_LEN)
        paramID = MODE_SERVICE_MODE_N_5_ID;
    }
  }
  // See if request is regarding the Mode_n_6 Characteristic Value
  else if ( ! memcmp(pAttr->type.uuid, mode_service_Mode_n_6UUID, pAttr->type.len) )
  {
    if ( offset + len > MODE_SERVICE_MODE_N_6_LEN )
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      // Copy pValue into the variable we point to from the attribute table.
      memcpy(pAttr->pValue + offset, pValue, len);

      // Only notify application if entire expected value is written
      if ( offset + len == MODE_SERVICE_MODE_N_6_LEN)
        paramID = MODE_SERVICE_MODE_N_6_ID;
    }
  }
  // See if request is regarding the Mode_n_7 Characteristic Value
  else if ( ! memcmp(pAttr->type.uuid, mode_service_Mode_n_7UUID, pAttr->type.len) )
  {
    if ( offset + len > MODE_SERVICE_MODE_N_7_LEN )
    {
      status = ATT_ERR_INVALID_OFFSET;
    }
    else
    {
      // Copy pValue into the variable we point to from the attribute table.
      memcpy(pAttr->pValue + offset, pValue, len);

      // Only notify application if entire expected value is written
      if ( offset + len == MODE_SERVICE_MODE_N_7_LEN)
        paramID = MODE_SERVICE_MODE_N_7_ID;
    }
  }
  else
  {
    // If we get here, that means you've forgotten to add an if clause for a
    // characteristic value attribute in the attribute table that has WRITE permissions.
    status = ATT_ERR_ATTR_NOT_FOUND;
  }

  // Let the application know something changed (if it did) by using the
  // callback it registered earlier (if it did).
  if (paramID != 0xFF)
    if ( pAppCBs && pAppCBs->pfnChangeCb )
      pAppCBs->pfnChangeCb(connHandle, paramID, len, pValue); // Call app function from stack task context.

  return status;
}
