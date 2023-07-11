/**
 * @file libIntDevices.ino
 * @brief Implementação da biblioteca para uso dos dispositivos internos do Solar IoT Master Device.
 * @details Esta implementação inclui as funções necessárias para uso dos dispositivos internos do Solar IoT Master Device.
 * @author Rodrigo França
 * @version 1.0.0
 * @date 2023-07-02
 * @license MIT License
 */

#include "libIntDevices.h"

/**
 * @brief Construtor para a classe CIntDevices
 */
CIntDevices::CIntDevices(void) {}

/**
 * @brief Construtor de cópia para a classe CIntDevices
 * @param CX_OTHER Outro objeto da classe CIntDevices
 */
CIntDevices::CIntDevices(const CIntDevices& CX_OTHER){}

/**
 * @brief Destrutor para a classe CIntDevices
 */
CIntDevices::~CIntDevices(void) {}

/**
 * @brief Inicializa os dispositivos internos do Solar IoT Master Device
 * @returns True se a inicialização for bem-sucedida, false caso contrário
 */
bool CIntDevices::bBegin(void) {
  bool bStatus = false;

  Wire.begin();
  if (_xAht10Dev.begin()) {
    _xAht10TemperatureSensor = _xAht10Dev.getTemperatureSensor();
    _xAht10HumiditySensor    = _xAht10Dev.getHumiditySensor();
	bStatus = true;
  } else {
    _xAht10TemperatureSensor = NULL;
    _xAht10HumiditySensor    = NULL;
  }

  bIntDevicesInit = bStatus;
  
  return (bStatus);
}

/**
 * @brief Realiza a leitura da temperatura do sensor AHT10
 * @returns O valor da temperatura em graus Celsius. Se o sensor não estiver inicializado, o valor de retorno é indefinido
 */
float CIntDevices::fGetAht10Temperature(void) {
	
  if (!_xAht10TemperatureSensor) {
    return NAN;  // retorna NaN se o sensor não estiver disponível
  }
  sensors_event_t xTemperature;
  _xAht10TemperatureSensor->getEvent(&xTemperature);
  return (xTemperature.temperature);
  
}

/**
 * @brief Realiza a leitura da umidade do sensor AHT10
 * @returns O valor da umidade como uma porcentagem (%). Se o sensor não estiver inicializado, o valor de retorno é indefinido
 */
float CIntDevices::fGetAht10Humidity(void) {
	
  if (!_xAht10HumiditySensor) {
    return NAN;  // retorna NaN se o sensor não estiver disponível
  }
  sensors_event_t xHumidity;
  _xAht10HumiditySensor->getEvent(&xHumidity);
  return (xHumidity.relative_humidity);
  
}
