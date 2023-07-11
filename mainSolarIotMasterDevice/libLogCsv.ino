/**
 * @file libLogCsv.ino
 * @brief Implementação da biblioteca para gerenciar o log de dados em um cartão SD no formato CSV.
 * @details Esta implementação inclui as funções necessárias para gerenciar o log de dados em um cartão SD no formato CSV com a biblioteca libLogCsv.
 * @author Rodrigo França
 * @version 1.0.0
 * @date 2023-07-02
 * @license MIT License
 */

#include "libLogCsv.h"

/**
 * @brief Construtor
 * @param PCC_CSV_FILENAME Nome do arquivo de log CSV
 */
CLogCsv::CLogCsv(const char* PCC_CSV_FILENAME)
  : _PCC_CSV_FILENAME(PCC_CSV_FILENAME) {}

/**
 * @brief Construtor de cópia para a classe CLogCsv
 * @param CX_OTHER Outro objeto da classe CLogCsv
 */
CLogCsv::CLogCsv(const CLogCsv& CX_OTHER)
  : _PCC_CSV_FILENAME(CX_OTHER._PCC_CSV_FILENAME) {}

/**
 * @brief Destrutor para a classe CLogCsv
 */
CLogCsv::~CLogCsv() {}

/**
 * @brief Cria um novo arquivo .csv no Módulo SD Card e escreve "Index" nele
 * @returns True se o arquivo foi criado e "Index" foi escrito com sucesso, false se houve um problema na inicialização do cartão SD, na abertura do arquivo ou na escrita nele
 */
bool CLogCsv::bCreateCsvFile(void) {
  bool bStatus = false;

  /* Inicializa o cartão SD */
  if (SD.begin(5)) {

    /* Abre o arquivo para escrita */
    _xCsvFile = SD.open(_PCC_CSV_FILENAME, FILE_WRITE);

    /* Se o arquivo foi aberto com sucesso */
    if (_xCsvFile) {
      /* Escreve "Index" no arquivo */
      _xCsvFile.print("Index");
      /* Fecha o arquivo */
      _xCsvFile.close();
      /* Retorna true para indicar sucesso */
      bStatus = true;
    }
  }
  /* Se o cartão SD não pôde ser inicializado ou o arquivo não pôde ser aberto, retorna false */
  return (bStatus);
}

/**
 * @brief Adiciona uma entrada de texto ao arquivo .csv. Esta função é usada para popular o .csv com dados
 * @param text O texto a ser escrito no arquivo .csv
 * @returns True se o texto foi escrito com sucesso no arquivo, false se houve um problema na abertura do arquivo ou na escrita nele
 */
bool CLogCsv::bAddCsvEntryText(const char* CPC_TEXT_ENTRY) {
  bool bStatus = false;
	
  /* Abre o arquivo no modo anexar */
  _xCsvFile = SD.open(_PCC_CSV_FILENAME, FILE_APPEND);

  /* Se o arquivo foi aberto com sucesso */
  if (_xCsvFile) {
    /* Escreve uma vírgula no arquivo */
    _xCsvFile.print(",");
    /* Escreve o texto no arquivo */
    _xCsvFile.print(CPC_TEXT_ENTRY);
    /* Fecha o arquivo */
    _xCsvFile.close();
    /* Retorna true para indicar sucesso */
    bStatus = true;
  }
  /* Se o arquivo não pôde ser aberto, retorna false */
  return (bStatus);
}

/**
 * @brief Adiciona uma entrada de valor hexadecimal 16-bit ao arquivo .csv. Esta função é usada para popular o .csv com dados
 * @param u16RawValue O valor hexadecimal de 16-bit a ser escrito no arquivo .csv
 * @returns Verdadeiro se o valor hexadecimal de 16-bit foi escrito com sucesso no arquivo, falso se houve um problema na abertura do arquivo ou na escrita nele
 */
bool CLogCsv::bAddCsvEntryRaw16b(uint16_t u16RawValue) {
  bool bStatus = false;
	
  /* Abre o arquivo no modo anexar */
  _xCsvFile = SD.open(_PCC_CSV_FILENAME, FILE_APPEND);

  /* Se o arquivo foi aberto com sucesso */
  if (_xCsvFile) {
    /* Escreve uma vírgula no arquivo */
    _xCsvFile.print(",");
    /* Escreve o valor hexadecimal no arquivo */
    _xCsvFile.printf("0x%04X", u16RawValue);
    /* Fecha o arquivo */
    _xCsvFile.close();
    /* Retorna true para indicar sucesso */
    bStatus = true;
  }
  /* Se o arquivo não pôde ser aberto, retorna false */
  return (bStatus);
}

/**
 * @brief Adiciona uma entrada de número unsigned int de 16-bit ao arquivo .csv. Esta função é usada para popular o .csv com dados
 * @param u16UintEntry O número unsigned int de 16-bit a ser escrito no arquivo .csv
 * @returns Verdadeiro se o número unsigned int de 16-bit foi escrito com sucesso no arquivo, falso se houve um problema na abertura do arquivo ou na escrita nele
 */
bool CLogCsv::bAddCsvEntryUint16b(uint16_t u16UintEntry) {
  bool bStatus = false;
	
  /* Abre o arquivo no modo anexar */
  _xCsvFile = SD.open(_PCC_CSV_FILENAME, FILE_APPEND);

  /* Se o arquivo foi aberto com sucesso */
  if (_xCsvFile) {
    /* Escreve uma vírgula no arquivo */
    _xCsvFile.print(",");
    /* Escreve o número no arquivo */
    _xCsvFile.print(u16UintEntry);
    /* Fecha o arquivo */
    _xCsvFile.close();
    /* Retorna true para indicar sucesso */
    bStatus = true;
  }
  /* Se o arquivo não pôde ser aberto, retorna false */
  return (bStatus);
}

/**
 * @brief Adiciona uma entrada de número signed int de 16-bit ao arquivo .csv. Esta função é usada para popular o .csv com dados
 * @param u16IntEntry O número signed int de 16-bit a ser escrito no arquivo .csv
 * @returns Verdadeiro se o número signed int de 16-bit foi escrito com sucesso no arquivo, falso se houve um problema na abertura do arquivo ou na escrita nele
 */
bool CLogCsv::bAddCsvEntryInt16b(int16_t u16IntEntry) {
  bool bStatus = false;
	
  /* Abre o arquivo no modo anexar */
  _xCsvFile = SD.open(_PCC_CSV_FILENAME, FILE_APPEND);

  /* Se o arquivo foi aberto com sucesso */
  if (_xCsvFile) {
    /* Escreve uma vírgula no arquivo */
    _xCsvFile.print(",");
    /* Escreve o número no arquivo */
    _xCsvFile.print(u16IntEntry);
    /* Fecha o arquivo */
    _xCsvFile.close();
    /* Retorna true para indicar sucesso */
    bStatus = true;
  }
  /* Se o arquivo não pôde ser aberto, retorna false */
  return (bStatus);
}

/**
 * @brief Adiciona uma entrada de valor hexadecimal 32-bit ao arquivo .csv. Esta função é usada para popular o .csv com dados
 * @param u32RawValue O valor hexadecimal de 32-bit a ser escrito no arquivo .csv
 * @returns Verdadeiro se o valor hexadecimal de 32-bit foi escrito com sucesso no arquivo, falso se houve um problema na abertura do arquivo ou na escrita nele
 */
bool CLogCsv::bAddCsvEntryRaw32b(uint32_t u32RawValue) {
  bool bStatus = false;
	
  /* Abre o arquivo no modo anexar */
  _xCsvFile = SD.open(_PCC_CSV_FILENAME, FILE_APPEND);

  /* Se o arquivo foi aberto com sucesso */
  if (_xCsvFile) {
    /* Escreve uma vírgula no arquivo */
    _xCsvFile.print(",");
    /* Escreve o valor hexadecimal no arquivo */
    _xCsvFile.printf("0x%08X", u32RawValue);
    /* Fecha o arquivo */
    _xCsvFile.close();
    /* Retorna true para indicar sucesso */
    bStatus = true;
  }
  /* Se o arquivo não pôde ser aberto, retorna false */
  return (bStatus);
}

/**
 * @brief Adiciona uma entrada de número flutuante ao arquivo .csv. Esta função é usada para popular o .csv com dados
 * @param fFloatEntry O número flutuante a ser escrito no arquivo .csv
 * @param u8DecimalPlaces O número de casas decimais para o número flutuante
 * @returns True se o número flutuante foi escrito com sucesso no arquivo, false se houve um problema na abertura do arquivo ou na escrita nele
 */
bool CLogCsv::bAddCsvEntryFloat(float fFloatEntry, uint8_t u8DecimalPlaces) {
  bool bStatus = false;
	
  /* Abre o arquivo no modo anexar */
  _xCsvFile = SD.open(_PCC_CSV_FILENAME, FILE_APPEND);

  /* Se o arquivo foi aberto com sucesso */
  if (_xCsvFile) {
    /* Escreve uma vírgula no arquivo */
    _xCsvFile.print(",");
    /* Escreve o número float no arquivo com o número especificado de casas decimais */
    _xCsvFile.print(fFloatEntry, u8DecimalPlaces);
    /* Fecha o arquivo */
    _xCsvFile.close();
    /* Retorna true para indicar sucesso */
    bStatus = true;
  }
  /* Se o arquivo não pôde ser aberto, retorna false */
  return (bStatus);
}

/**
 * @brief Inicia uma nova linha de dados no arquivo .csv e escreve um índice incrementado nele, usado quando uma nova linha de dados precisa ser gravada no arquivo .csv
 * @returns True se a nova linha foi iniciada com sucesso e o índice foi escrito, false se houve um problema na abertura do arquivo ou na escrita nele
 */
bool CLogCsv::bStartCsvLine(void) {
  bool bStatus = false;
	
  /* Abre o arquivo no modo anexar */
  _xCsvFile = SD.open(_PCC_CSV_FILENAME, FILE_APPEND);

  /* Se o arquivo foi aberto com sucesso */
  if (_xCsvFile) {
    /* Escreve o índice atual no arquivo */
    _xCsvFile.print(_u32CsvIndex++);
    /* Fecha o arquivo */
    _xCsvFile.close();
    /* Retorna true para indicar sucesso */
    bStatus = true;
  }
  /* Se o arquivo não pôde ser aberto, retorna false */
  return (bStatus);
}

/**
 * @brief Termina uma linha no arquivo .csv. Esta função é usada quando a linha atual de dados no arquivo .csv está concluída
 * @returns True se a nova linha foi escrita com sucesso no arquivo, false se houve um problema na abertura do arquivo ou na escrita nele
 */
bool CLogCsv::bEndCsvLine(void) {
  bool bStatus = false;
	
  /* Abre o arquivo no modo de anexação */
  _xCsvFile = SD.open(_PCC_CSV_FILENAME, FILE_APPEND);

  /* Se o arquivo foi aberto com sucesso */
  if (_xCsvFile) {
    /* Termina a linha atual no arquivo, escrevendo um caractere de nova linha */
    _xCsvFile.println();
    /* Fecha o arquivo */
    _xCsvFile.close();
    /* Retorna true para indicar sucesso */
    bStatus = true;
  }
  /* Se o arquivo não pôde ser aberto, retorna false */
  return (bStatus);
}
