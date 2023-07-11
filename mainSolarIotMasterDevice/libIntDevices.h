/**
 * @file libIntDevices.h
 * @brief Biblioteca para uso dos dispositivos internos do Solar IoT Master Device.
 * @details Esta biblioteca simplifica dos dispositivos internos do Solar IoT Master Device.
 * @author Rodrigo França
 * @version 1.0.0
 * @date 2023-07-02
 * @license MIT License
 */

#ifndef LIBINTDEVICES_H
#define LIBINTDEVICES_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>

/**
 * @class CIntDevices
 * @brief Classe para utilização dos dispositivos internos do Solar IoT Master Device
 */
class CIntDevices {
public:
  /**
   * @brief Construtor para a classe CIntDevices
   */
  explicit CIntDevices(void);

  /**
   * @brief Construtor de cópia para a classe CIntDevices
   * @param CX_OTHER Outro objeto da classe CIntDevices
   */
  CIntDevices(const CIntDevices& CX_OTHER);

  /**
   * @brief Destrutor para a classe CIntDevices
   */
  ~CIntDevices(void);

  /**
   * @brief Inicializa os dispositivos internos do Solar IoT Master Device
   * @returns True se a inicialização for bem-sucedida, false caso contrário.
   */
  bool bBegin(void);
  
  /**
   * @brief Realiza a leitura da temperatura do sensor AHT10
   * @returns O valor da temperatura em Graus Celsius. Se o sensor não estiver inicializado, o valor de retorno é indefinido
   */
  float fGetAht10Temperature(void);
  
  /**
   * @brief Realiza a leitura da umidade do sensor AHT10
   * @returns O valor da umidade como uma porcentagem (%). Se o sensor não estiver inicializado, o valor de retorno é indefinido
   */
  float fGetAht10Humidity(void);

  bool bIntDevicesInit;                      /**< Flag para indicar que o IntDevices foi devidamente inicilizado */

private:
  Adafruit_AHTX0 _xAht10Dev;                 /**< Instância da classe Adafruit_AHTX0 para controlar o sensor AHT10 */
  Adafruit_Sensor *_xAht10TemperatureSensor; /**< Instância da classe Adafruit_Sensor para a temperatura do sensor AHT10 */
  Adafruit_Sensor *_xAht10HumiditySensor;    /**< Instância da classe Adafruit_Sensor para a umidade do sensor AHT10 */
};

#endif
