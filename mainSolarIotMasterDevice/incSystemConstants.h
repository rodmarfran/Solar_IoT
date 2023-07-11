/**
 * @file incSystemConstants.h
 * @brief Include com a definição das constantes de sistema para o projeto do Solar IoT Master Device.
 * @details Este arquivo contém a definição constantes de sistema para serem usados em no projeto do Solar IoT Master Device.
 * @author Rodrigo França
 * @version 1.0.0
 * @date 2023-07-02
 * @license MIT License
 */

#ifndef INCSYSTEMCONSTANTS_H
#define INCSYSTEMCONSTANTS_H

#include <Arduino.h>

/**
 * @class CSystemConstants
 * @brief Classe para definição das constantes de sistema para o projeto do Solar IoT Master Device
 */
class CSystemConstants {
public:
  static const uint32_t CU32_SERIAL_USBDEBUG_BAUD_RATE = 115200lu;             /**< Baud rate para o Serial de debug USB */
  static const uint32_t CU32_SERIAL_MODBUS_BAUD_RATE   = 9600lu;               /**< Baud rate para o Serial do Modbus */
  static const uint8_t CU8_KRON_MODBUS_SLAVE_ADDR      = 254u;                 /**< Endereço Modbus do dispositivo Kron */
  static const uint32_t CU32_UPDATE_DATALOG_TIME_MS    = 15ul * 60ul * 1000ul; /**< Intervalo de tempo para iteração - atualizar o arquivo CSV - 15 minutos */
};

#endif