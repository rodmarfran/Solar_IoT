/**
 * @file libModbusMaster.ino
 * @brief Implementação da biblioteca para o um mestre Modbus simplificado.
 * @details Esta implementação inclui as funções necessárias para um mestre Modbus simplificado.
 * @author Rodrigo França
 * @version 1.0.0
 * @date 2023-07-02
 * @license MIT License
 */

#include "libModbusMaster.h"

/**
 * @brief Construtor
 * @param CU8_TX_RX_CTRL_PIN Pino de controle de Tx/Rx para o RS485
 * @param CU8_KRON_MODBUS_SLAVE_ADDR Endereço Modbus do dispositivo Kron
 * @param CX_SERIAL_MODBUS Serial para ser usado pelo Modbus
 * @param CU32_SERIAL_BAUD_RATE Baud Rate do Serial para ser usado pelo Modbus
 */
CModbusMaster::CModbusMaster(const uint8_t CU8_TX_RX_CTRL_PIN, const uint8_t CU8_KRON_MODBUS_SLAVE_ADDR, HardwareSerial* const CPX_SERIAL_MODBUS, const uint32_t CU32_SERIAL_BAUD_RATE)
  : _CU8_TX_RX_CTRL_PIN(CU8_TX_RX_CTRL_PIN), _CU8_KRON_MODBUS_SLAVE_ADDR(CU8_KRON_MODBUS_SLAVE_ADDR), _CPX_SERIAL_MODBUS(CPX_SERIAL_MODBUS), _CU32_SERIAL_BAUD_RATE(CU32_SERIAL_BAUD_RATE) {}

/**
 * @brief Construtor de cópia para a classe CModbusMaster
 * @param CX_OTHER Outro objeto da classe CModbusMaster
 */
CModbusMaster::CModbusMaster(const CModbusMaster& CX_OTHER)
  : _CU8_TX_RX_CTRL_PIN(CX_OTHER._CU8_TX_RX_CTRL_PIN), _CU8_KRON_MODBUS_SLAVE_ADDR(CX_OTHER._CU8_KRON_MODBUS_SLAVE_ADDR), _CPX_SERIAL_MODBUS(CX_OTHER._CPX_SERIAL_MODBUS), _CU32_SERIAL_BAUD_RATE(CX_OTHER._CU32_SERIAL_BAUD_RATE) {}

/**
 * @brief Destrutor para a classe CModbusMaster
 */
CModbusMaster::~CModbusMaster() {}

/**
 * @brief Inicializa o mestre Modbus simplificado
 */
void CModbusMaster::begin(void) {
  _CPX_SERIAL_MODBUS->begin(9600);
  pinMode(_CU8_TX_RX_CTRL_PIN, OUTPUT);
  digitalWrite (_CU8_TX_RX_CTRL_PIN, _CU8_RS485_RECEIVE) ;
}

/**
 * @brief Realiza a leitura de registradores de 16-bit do dispositivo da Kron por Modbus
 * @param u16FirstRegAddr O endereço do registrador de 16-bit a ser lido
 * @return Retorna o valor do registrador como um valor raw de 16-bit
 */
uint16_t CModbusMaster::u16GetKronRegister16bValue(uint16_t u16FirstRegAddr) {
  uint16_t u16AmountOfReg = 1;
  
  _createDataFrame(_CU8_KRON_MODBUS_SLAVE_ADDR, 0x04, (u16FirstRegAddr - 30001), u16AmountOfReg);

  _exchangeKronModbusData(_u8DataFrameBuffer, 8, _u8RawDataBuffer, 7);

  TBytesTo16bValue xBytesTo16bValue;
  xBytesTo16bValue.u8Bytes[1] = _u8RawDataBuffer[3];
  xBytesTo16bValue.u8Bytes[0] = _u8RawDataBuffer[4];
  
  return (xBytesTo16bValue.u16RawValue);
}

/**
 * @brief Realiza a leitura de registradores de 32-bit do dispositivo da Kron por Modbus
 * @param u16FirstRegAddr O endereço do registrador de 32-bit a ser lido
 * @return Retorna o valor do registrador como um valor raw de 32-bit
 */
uint32_t CModbusMaster::u32GetKronRegister32bValue(uint16_t u16FirstRegAddr) {
  uint16_t u16AmountOfReg = 2;
  
  _createDataFrame(_CU8_KRON_MODBUS_SLAVE_ADDR, 0x04, (u16FirstRegAddr - 30001), u16AmountOfReg);

  _exchangeKronModbusData(_u8DataFrameBuffer, 8, _u8RawDataBuffer, 9);

  TBytesTo32bValue xBytesTo32bValue;
  xBytesTo32bValue.u8Bytes[3] = _u8RawDataBuffer[3];
  xBytesTo32bValue.u8Bytes[2] = _u8RawDataBuffer[4];
  xBytesTo32bValue.u8Bytes[1] = _u8RawDataBuffer[5];
  xBytesTo32bValue.u8Bytes[0] = _u8RawDataBuffer[6];
  
  return (xBytesTo32bValue.u32RawValue);
}

/**
 * @brief Realiza a leitura de registradores de IEEE 32-bit float do dispositivo da Kron por Modbus
 * @param u16FirstRegAddr O endereço do registrador de IEEE 32-bit float a ser lido
 * @return Retorna o valor do registrador como um valor raw de IEEE 32-bit float
 */
float CModbusMaster::fGetKronRegisterIeee32bFpValue(uint16_t u16FirstRegAddr) {
  uint16_t u16AmountOfReg = 2;
  
  _createDataFrame(_CU8_KRON_MODBUS_SLAVE_ADDR, 0x04, (u16FirstRegAddr - 30001), u16AmountOfReg);

  _exchangeKronModbusData(_u8DataFrameBuffer, 8, _u8RawDataBuffer, 9);

  TBytesTo32bValue xBytesTo32bValue;
  xBytesTo32bValue.u8Bytes[3] = _u8RawDataBuffer[6];
  xBytesTo32bValue.u8Bytes[2] = _u8RawDataBuffer[5];
  xBytesTo32bValue.u8Bytes[1] = _u8RawDataBuffer[4];
  xBytesTo32bValue.u8Bytes[0] = _u8RawDataBuffer[3];
  
  return (xBytesTo32bValue.fIeee32Float);
}

/**
 * @brief Calcula o CRC16 para o Modbus
 * @param pu8Message Ponteiro para a mensagem da qual o CRC16 será calculado
 * @param u16DataLen Comprimento dos dados na mensagem
 * @return Retorna o valor calculado do CRC16
 */
uint16_t CModbusMaster::_u16CalculateModbusCrc16(uint8_t *pu8Message, uint16_t u16DataLen) {
  uint8_t u8CrcHi = 0xFF; 
  uint8_t u8CrcLo = 0xFF;
  uint8_t u8Index;
  while (u16DataLen--) {
      u8Index = u8CrcHi ^ *pu8Message++; 
      u8CrcHi = u8CrcLo ^ _CU8_MODBUS_CRC_HI[u8Index];
      u8CrcLo = _CU8_MODBUS_CRC_LO[u8Index];
  }
  return ((uint16_t)u8CrcHi << 8 | u8CrcLo);
}

/**
 * @brief Cria um data frame para o Modbus
 * @param u8SlaveAddr Endereço do escravo Modbus
 * @param u8FunctionCode Código de função Modbus
 * @param u16FirstRegAddr Endereço do primeiro registro
 * @param u16AmountOfReg Quantidade de registros
 */
void CModbusMaster::_createDataFrame(uint8_t u8SlaveAddr, uint8_t u8FunctionCode, uint16_t u16FirstRegAddr, uint16_t u16AmountOfReg) {
  _u8DataFrameBuffer[0] = u8SlaveAddr;
  _u8DataFrameBuffer[1] = u8FunctionCode;
  _u8DataFrameBuffer[2] = (u16FirstRegAddr >> 8) & 0xFF;
  _u8DataFrameBuffer[3] = u16FirstRegAddr & 0xFF;
  _u8DataFrameBuffer[4] = (u16AmountOfReg >> 8) & 0xFF;
  _u8DataFrameBuffer[5] = u16AmountOfReg & 0xFF;
  
  uint16_t u16DataFrameCrc = _u16CalculateModbusCrc16(_u8DataFrameBuffer, 6); 
  _u8DataFrameBuffer[6] = (u16DataFrameCrc >> 8) & 0xFF;
  _u8DataFrameBuffer[7] = u16DataFrameCrc & 0xFF;
}

/**
 * @brief Realiza o envio de um dataframe e a recepção de raw data do dispositivo da Kron por Modbus
 * @param pu8DataFrameBuffer Ponteiro para o buffer do Data Frame a ser transmitido para dispositivo da Kron por Modbus
 * @param u8DataFrameSize Tamanho do Data Frame a ser transmitido para dispositivo da Kron por Modbus
 * @param pu8RawDataBuffer Ponteiro para o buffer de Raw Data a ser recebido pelo dispositivo da Kron por Modbus
 * @param u8RawDataSize  Tamanho do Raw Data a ser recebido pelo dispositivo da Kron por Modbus
 */
void CModbusMaster::_exchangeKronModbusData(uint8_t *pu8DataFrameBuffer, uint8_t u8DataFrameSize, uint8_t *pu8RawDataBuffer, uint8_t u8RawDataSize) {

  digitalWrite(_CU8_TX_RX_CTRL_PIN, _CU8_RS485_TRANSMIT);
  _CPX_SERIAL_MODBUS->write(pu8DataFrameBuffer, u8DataFrameSize);
  _CPX_SERIAL_MODBUS->flush();

  digitalWrite(_CU8_TX_RX_CTRL_PIN, _CU8_RS485_RECEIVE);
  
  while(!_CPX_SERIAL_MODBUS->available()){}
  _CPX_SERIAL_MODBUS->readBytes(pu8RawDataBuffer, u8RawDataSize);

  // Serial.println(_u8RawDataBuffer[0], HEX);
  // Serial.println(_u8RawDataBuffer[1], HEX);
  // Serial.println(_u8RawDataBuffer[2], HEX);
  // Serial.println(_u8RawDataBuffer[3], HEX);
  // Serial.println(_u8RawDataBuffer[4], HEX);
  // Serial.println(_u8RawDataBuffer[5], HEX);
  // Serial.println(_u8RawDataBuffer[6], HEX);
  // Serial.println(_u8RawDataBuffer[7], HEX);
  // Serial.println(_u8RawDataBuffer[8], HEX);
  // Serial.println(_u8RawDataBuffer[9], HEX);

  delay(10);

}