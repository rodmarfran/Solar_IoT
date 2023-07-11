/**
 * @file libDatalog.ino
 * @brief Implementação da biblioteca para realizar log de dados.
 * @details Esta implementação inclui as funções necessárias para realizar log de dados com a biblioteca libDatalog.
 * @author Rodrigo França
 * @version 1.0.0
 * @date 2023-07-02
 * @license MIT License
 */

#include "libDatalog.h"

/**
 * @brief Construtor para a classe CDatalog
 * @param CU32_LOGTIME_INTERVAL_S Intervalo de tempo para atualizar o arquivo de log
 */
CDatalog::CDatalog(const uint32_t CU32_LOGTIME_INTERVAL_S)
  : _CU32_LOGTIME_INTERVAL_S(CU32_LOGTIME_INTERVAL_S), xLogCsv((const char*)_pcStrFilenameBuff) {}

/**
 * @brief Construtor de cópia para a classe CDatalog
 * @param CX_OTHER Outro objeto da classe CDatalog
 */
CDatalog::CDatalog(const CDatalog& CX_OTHER)
  : _CU32_LOGTIME_INTERVAL_S(CX_OTHER._CU32_LOGTIME_INTERVAL_S), xLogCsv(CX_OTHER.xLogCsv) {}

/**
 * @brief Destrutor para a classe CDatalog
 */
CDatalog::~CDatalog() {}

/**
 * @brief Inicializa o log de dados
 * @returns True se a inicialização for bem-sucedida, false caso contrário
 */
bool CDatalog::bBegin(void){
  bool bStatus = false;
  uint32_t u32CurrentLogTimeS = 0;
  
  Wire.begin();
  if (_xDs3231Rtc.begin()) {
	
    if (_xDs3231Rtc.lostPower()) {
      /* Quando o tempo precisa ser definido em um novo dispositivo, ou após uma perda de energia, 
	   * a seguinte linha ajusta o RTC para a data e hora que este esboço foi compilado */
      _xDs3231Rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    DateTime xCurrentRtcTime = _xDs3231Rtc.now();
    sprintf(_pcStrFilenameBuff, "/log%04u%02u%02u%02u%02u%02u.csv", xCurrentRtcTime.year(), xCurrentRtcTime.month(), xCurrentRtcTime.day(), xCurrentRtcTime.hour(), xCurrentRtcTime.minute(), xCurrentRtcTime.second());

    u32CurrentLogTimeS = xCurrentRtcTime.hour() * 3600 + xCurrentRtcTime.minute() * 60 + xCurrentRtcTime.second();
    _u32WriteLogTimeS = _CalculateWriteLogTimeS(u32CurrentLogTimeS);
    _bWriteLogTimeFlag = false;

    if (xLogCsv.bCreateCsvFile()) {
	    bStatus = true;
    }
  }

  bDatalogInit = bStatus;
  
  return (bStatus);
}

/**
 * @brief Realiza a leitura da temperatura do RTC DS3231
 * @returns Temperatura medida pelo RTC, em graus Celsius
 */
float CDatalog::fGetRtcTemperature(void){
	return (_xDs3231Rtc.getTemperature());
}

/**
 * @brief Escreve o timestamp atual no log
 * @param pcStrTimestampBuff Buffer aonde o timestamp atual deve ser escrito
 */
void CDatalog::getRtcTimestamp(char *pcStrTimestampBuff){

  DateTime xCurrentRtcTime = _xDs3231Rtc.now();
	sprintf(pcStrTimestampBuff, "%04u/%02u/%02u %02u:%02u:%02u", xCurrentRtcTime.year(), xCurrentRtcTime.month(), xCurrentRtcTime.day(), xCurrentRtcTime.hour(), xCurrentRtcTime.minute(), xCurrentRtcTime.second());

}

/**
 * @brief Escreve o timestamp atual no log
 * @returns True se a escrita for bem-sucedida, false caso contrário
 */
bool CDatalog::bWriteRtcTimestampToLog(void){
	bool bStatus = false;
	
	getRtcTimestamp(_pcStrTimestampBuff);
	bStatus = xLogCsv.bAddCsvEntryText((const char*)_pcStrTimestampBuff);
	
	return (bStatus);
}

/**
 * @brief Le o flag de escrita no log
 * @returns True se o tempo atual é o intervalo certo para escrever no log, False se não
 */
bool CDatalog::bGetWriteLogTimeFlag(void){
  uint32_t u32CurrentLogTimeS = 0;

  DateTime xCurrentRtcTime = _xDs3231Rtc.now();
  u32CurrentLogTimeS = xCurrentRtcTime.hour() * 3600 + xCurrentRtcTime.minute() * 60 + xCurrentRtcTime.second();

  if (u32CurrentLogTimeS >= _u32WriteLogTimeS) {
    _bWriteLogTimeFlag = true;
  }
  
  return (_bWriteLogTimeFlag);
}

/**
 * @brief Limpa o flag de escrita no log e calcula o tempo de atualização do log
 */
void CDatalog::clearWriteLogTimeFlag(void){

  _u32WriteLogTimeS += _CU32_LOGTIME_INTERVAL_S;
  if (_u32WriteLogTimeS >= 86400) {
    _u32WriteLogTimeS = _u32WriteLogTimeS - 86400;
  }

  _bWriteLogTimeFlag = false;

}

/**
  * @brief Calcula o tempo para realizar a atulização do arquivo de log
  * @param u32CurrentLogTimeS Tempo atual (em segundos)
  * @returns Tempo para realizar a atulização do arquivo de log (em segundos)
  */
uint32_t CDatalog::_CalculateWriteLogTimeS(uint32_t u32CurrentLogTimeS){
  uint32_t u32WriteLogTimeS = 0;

  u32WriteLogTimeS = u32CurrentLogTimeS / _CU32_LOGTIME_INTERVAL_S;
  u32WriteLogTimeS = (u32WriteLogTimeS + 1) * _CU32_LOGTIME_INTERVAL_S;

  if (u32WriteLogTimeS >= 86400) {
    u32WriteLogTimeS = u32WriteLogTimeS - 86400;
  }

  return (u32WriteLogTimeS);
}