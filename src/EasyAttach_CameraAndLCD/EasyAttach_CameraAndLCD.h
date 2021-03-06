/* Copyright (c) 2017 dkato
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef EASY_ATTACH_CAMERA_AND_LCD_H
#define EASY_ATTACH_CAMERA_AND_LCD_H

#include "DisplayBase/DisplayBase.h"

// camera
#if MBED_CONF_APP_CAMERA
  // camera-type
  #define CAMERA_CVBS                     0x0001
  #define CAMERA_MT9V111                  0x0002
  #define CAMERA_OV7725                   0x0003
  #define CAMERA_OV5642                   0x0004
  #define CAMERA_WIRELESS_CAMERA          0x0083
  #define CAMERA_RASPBERRY_PI             0x2000
  #define CAMERA_RASPBERRY_PI_WIDE_ANGLE  0x2001

  // shield-type
  #define SHIELD_AUDIO_CAMERA         1
  #define SHIELD_WIRELESS_CAMERA      2

  // camera module
  #define MODULE_VDC                  0
  #define MODULE_CEU                  1
  #define MODULE_MIPI                 2

  #ifndef MBED_CONF_APP_SHIELD_TYPE
    #if defined(TARGET_RZ_A1H)
      #if (MBED_CONF_APP_CAMERA_TYPE == CAMERA_WIRELESS_CAMERA)
        #define MBED_CONF_APP_SHIELD_TYPE  SHIELD_WIRELESS_CAMERA
        #undef  MBED_CONF_APP_CAMERA_TYPE
        #define MBED_CONF_APP_CAMERA_TYPE  CAMERA_OV7725
      #else
        #define MBED_CONF_APP_SHIELD_TYPE  SHIELD_AUDIO_CAMERA
      #endif
    #endif
  #endif

  #ifndef MBED_CONF_APP_CAMERA_TYPE
    #if defined(TARGET_GR_LYCHEE)
      #define MBED_CONF_APP_CAMERA_TYPE    CAMERA_OV7725
    #elif defined(TARGET_GR_MANGO) || defined(TARGET_RZ_A2M_EVB) || defined(TARGET_RZ_A2M_EVB_HF) || defined(TARGET_RZ_A2M_SBEV) || defined(TARGET_SEMB1402)
      #define MBED_CONF_APP_CAMERA_TYPE    CAMERA_RASPBERRY_PI
    #else
      #define MBED_CONF_APP_CAMERA_TYPE    CAMERA_MT9V111
    #endif
  #endif

  #if (MBED_CONF_APP_CAMERA_TYPE == CAMERA_CVBS) && defined(TARGET_GR_LYCHEE)
    #error "MBED_CONF_APP_CAMERA_TYPE is not supported in this target."
  #endif

  #if ((MBED_CONF_APP_CAMERA_TYPE & 0x2000) != 0)
    #define CAMERA_MODULE             MODULE_MIPI
  #elif defined(TARGET_RZ_A2M_EVB) || defined(TARGET_RZ_A2M_EVB_HF) || defined(TARGET_RZ_A2M_SBEV) || defined(TARGET_SEMB1402)
    #define CAMERA_MODULE             MODULE_CEU
  #else
    #define CAMERA_MODULE             MODULE_VDC
  #endif

  #if MBED_CONF_APP_CAMERA_TYPE == CAMERA_MT9V111
    #include "MT9V111_config.h"
  #elif MBED_CONF_APP_CAMERA_TYPE == CAMERA_OV7725
    #include "OV7725_config.h"
  #elif MBED_CONF_APP_CAMERA_TYPE == CAMERA_OV5642
    #include "OV5642_config.h"
  #elif MBED_CONF_APP_CAMERA_TYPE == CAMERA_RASPBERRY_PI
    #include "CAMERA/RaspberryPi_config.h"
  #elif MBED_CONF_APP_CAMERA_TYPE == CAMERA_RASPBERRY_PI_WIDE_ANGLE
    #include "RaspberryPi_wide_angle_config.h"
  #endif
#endif

// lcd
#if MBED_CONF_APP_LCD
  // lcd type
  #define LCD_LVDS                    0x8000

  // lcd-type
  #define GR_PEACH_4_3INCH_SHIELD     (0x0000|LCD_LVDS)
  #define GR_PEACH_7_1INCH_SHIELD     (0x0001|LCD_LVDS)
  #define GR_PEACH_DISPLAY_SHIELD     (0x0002)
  #define RSK_TFT                     (0x0003)
  #define TFP410PAP                   (0x0004) /* HDMI and DVI */
  #define TF043HV001A0                (0x0005)
  #define ATM0430D25                  (0x0006)
  #define FG040346DSSWBG03            (0x0007)

  #define GR_PEACH_RSK_TFT            (RSK_TFT|LCD_LVDS)
  #define LVDS_TO_HDMI                (TFP410PAP|LCD_LVDS)
  #define DVI_STICK                   (TFP410PAP)
  #define RGB_TO_HDMI                 (TFP410PAP)

  #ifndef MBED_CONF_APP_LCD_TYPE
    #if defined(TARGET_RZ_A1H)
      #define MBED_CONF_APP_LCD_TYPE    GR_PEACH_4_3INCH_SHIELD
    #elif defined(TARGET_GR_LYCHEE)
      #define MBED_CONF_APP_LCD_TYPE    TF043HV001A0
    #elif defined(TARGET_GR_MANGO)
      #define MBED_CONF_APP_LCD_TYPE    RGB_TO_HDMI
    #elif defined(TARGET_RZ_A2M_EVB) || defined(TARGET_RZ_A2M_EVB_HF)
      #define MBED_CONF_APP_LCD_TYPE    DVI_STICK
    #elif defined(TARGET_RZ_A2M_SBEV) || defined(TARGET_SEMB1402)
      #define MBED_CONF_APP_LCD_TYPE    LVDS_TO_HDMI
    #endif
  #endif

  #if MBED_CONF_APP_LCD_TYPE == GR_PEACH_4_3INCH_SHIELD
    #include "LCD_shield_config_4_3inch.h"
  #elif MBED_CONF_APP_LCD_TYPE == GR_PEACH_7_1INCH_SHIELD
    #include "LCD_shield_config_7_1inch.h"
  #elif MBED_CONF_APP_LCD_TYPE == GR_PEACH_RSK_TFT
    #include "LCD_shield_config_RSK_TFT.h"
  #elif MBED_CONF_APP_LCD_TYPE == GR_PEACH_DISPLAY_SHIELD
    #include "Display_shield_config.h"
  #elif (MBED_CONF_APP_LCD_TYPE == TF043HV001A0 )
    #include "LCD_config_TF043HV001A0.h"
  #elif MBED_CONF_APP_LCD_TYPE == ATM0430D25
    #include "LCD_config_ATM0430D25.h"
  #elif MBED_CONF_APP_LCD_TYPE == FG040346DSSWBG03
    #include "LCD_config_FG040346DSSWBG03.h"
  #elif MBED_CONF_APP_LCD_TYPE == LVDS_TO_HDMI
    #include "LCD/LCD_config_lvds_to_hdmi.h"
  #elif MBED_CONF_APP_LCD_TYPE == RSK_TFT
    #include "LCD_config_RSK_TFT.h"
  #elif (MBED_CONF_APP_LCD_TYPE == RGB_TO_HDMI) || (MBED_CONF_APP_LCD_TYPE == DVI_STICK)
    #include "LCD/LCD_config_rgb_to_hdmi.h"
  #else
    #error "No lcd chosen. Please add 'config.lcd-type.value' to your mbed_app.json (see README.md for more information)."
  #endif
#endif

extern DisplayBase::graphics_error_t EasyAttach_Init(
    DisplayBase& Display,
    uint16_t cap_width = 0,
    uint16_t cap_height = 0
);

extern DisplayBase::graphics_error_t EasyAttach_CameraStart(
    DisplayBase& Display,
    DisplayBase::video_input_channel_t channel = DisplayBase::VIDEO_INPUT_CHANNEL_0
);

extern void EasyAttach_SetTypicalBacklightVol(float typ_vol);

extern void EasyAttach_LcdBacklight(bool type = true);

extern void EasyAttach_LcdBacklight(float value);

#endif
