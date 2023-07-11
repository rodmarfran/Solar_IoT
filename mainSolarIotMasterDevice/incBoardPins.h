/**
 * @file incBoardPins.h
 * @brief Include com a definição dos pinos do ESP32 para o projeto do Solar IoT Master Device.
 * @details Este arquivo contém a definição dos pinos do ESP32 para o projeto do Solar IoT Master Device.
 * @author Rodrigo França
 * @version 1.0.0
 * @date 2023-07-02
 * @license MIT License
 */

#ifndef INCBOARDPINS_H
#define INCBOARDPINS_H

#include <Arduino.h>

/**
 * @class CBoardPins
 * @brief Classe para definição dos pinos do ESP32 para o projeto do Solar IoT Master Device
 */
class CBoardPins {
public:
  static const uint8_t CU8_TX_RX_CTRL_PIN = 4u; /**< Pino de controle de Tx/Rx para o RS485 */
};

#endif