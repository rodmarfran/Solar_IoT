/**
 * @file libDatalog.h
 * @brief Biblioteca para realizar log de dados.
 * @details Esta biblioteca simplifica o realizar log de dados.
 * @author Rodrigo França
 * @version 1.0.0
 * @date 2023-07-02
 * @license MIT License
 */

#ifndef LIBDATALOG_H
#define LIBDATALOG_H

#include <Arduino.h>
#include <Wire.h>
#include <RTClib.h>
#include "libLogCsv.h"

/**
 * @class CDatalog
 * @brief Classe para realizar log de dados
 */
class CDatalog {
public:
  /**
   * @brief Construtor
   * @param CU32_LOGTIME_INTERVAL_S Intervalo de tempo para atualizar o arquivo de log
   */
  explicit CDatalog(const uint32_t CU32_LOGTIME_INTERVAL_S);

  /**
   * @brief Construtor de cópia
   * @param CX_OTHER Outro objeto da classe CDatalog
   */
  CDatalog(const CDatalog& CX_OTHER);

  /**
   * @brief Destrutor
   */
  ~CDatalog();

  /**
   * @brief Inicializa o log de dados
   * @returns True se a inicialização for bem-sucedida, false caso contrário
   */
  bool bBegin(void);
  
  /**
   * @brief Realiza a leitura da temperatura do RTC DS3231
   * @returns Temperatura medida pelo RTC, em graus Celsius
   */
  inline float fGetRtcTemperature(void);
  
  /**
   * @brief Escreve o timestamp atual no log
   * @param pcStrTimestampBuff Buffer aonde o timestamp atual deve ser escrito
   */
  void getRtcTimestamp(char *pcStrTimestampBuff);
  
  /**
   * @brief Escreve o timestamp atual no log
   * @returns True se a escrita for bem-sucedida, false caso contrário
   */
  bool bWriteRtcTimestampToLog(void);

  /**
   * @brief Le o flag de escrita no log
   * @returns True se o tempo atual é o intervalo certo para escrever no log, False se não
   */
  bool bGetWriteLogTimeFlag(void);

  /**
   * @brief Limpa o flag de escrita no log e calcula o tempo de atualização do log
   */
  void clearWriteLogTimeFlag(void);
  
  CLogCsv xLogCsv;              /**< Instância da classe CLogCsv para gravar dados no formato CSV */
  bool bDatalogInit;            /**< Flag para indicar que o Datalog foi devidamente inicilizado */

private:
  /**
   * @brief Calcula o tempo para realizar a atulização do arquivo de log
   * @param u32CurrentLogTimeS Tempo atual (em segundos)
   * @returns Tempo para realizar a atulização do arquivo de log (em segundos)
   */
  uint32_t _CalculateWriteLogTimeS(uint32_t u32CurrentLogTimeS);

  const uint32_t _CU32_LOGTIME_INTERVAL_S; /**< Intervalo de tempo para atualizar o arquivo de log (em segundos) */
  uint32_t _u32WriteLogTimeS;              /**< Tempo para realizar a atulização do arquivo de log (em segundos) */
  bool _bWriteLogTimeFlag;                 /**< Flag que indica que passou de tempo de atualizar o log */
  char _pcStrTimestampBuff[32];            /**< Buffer para o timestamp atual */
  char _pcStrFilenameBuff[32];             /**< Buffer para o nome do arquivo de log */
  RTC_DS3231 _xDs3231Rtc;                  /**< Instância da classe RTC_DS3231 para controlar o RTC DS3231 */
};

#endif
