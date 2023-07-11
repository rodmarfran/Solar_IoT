/**
 * @file libLogCsv.h
 * @brief Biblioteca para gerenciar o log de dados em um cartão SD no formato CSV.
 * @details Esta biblioteca simplifica a gestão do log de dados em um cartão SD no formato CSV.
 * @author Rodrigo França
 * @version 1.0.0
 * @date 2023-07-02
 * @license MIT License
 */

#ifndef LIBLOGCSV_H
#define LIBLOGCSV_H

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

/**
 * @class CLogCsv
 * @brief Classe para gerenciar o log de dados em um cartão SD no formato CSV
 */
class CLogCsv {
public:
  /**
   * @brief Construtor
   * @param PCC_CSV_FILENAME Nome do arquivo de log CSV
   */
  explicit CLogCsv(const char* PCC_CSV_FILENAME);

  /**
   * @brief Construtor de cópia
   * @param CX_OTHER Outro objeto da classe CLogCsv
   */
  CLogCsv(const CLogCsv& CX_OTHER);

  /**
   * @brief Destrutor
   */
  ~CLogCsv();

  /**
   * @brief Cria um novo arquivo .csv no Módulo SD Card e escreve "Index" nele
   * @returns Verdadeiro se o arquivo foi criado e "Index" foi escrito com sucesso, falso se houve um problema na inicialização do cartão SD, na abertura do arquivo ou na escrita nele
   */
  bool bCreateCsvFile(void);
  
  /**
   * @brief Adiciona uma entrada de texto ao arquivo .csv. Esta função é usada para popular o .csv com dados
   * @param text O texto a ser escrito no arquivo .csv
   * @returns Verdadeiro se o texto foi escrito com sucesso no arquivo, falso se houve um problema na abertura do arquivo ou na escrita nele
   */
  bool bAddCsvEntryText(const char* CPC_TEXT_ENTRY);
  
  /**
   * @brief Adiciona uma entrada de valor hexadecimal 16-bit ao arquivo .csv. Esta função é usada para popular o .csv com dados
   * @param u16RawValue O valor hexadecimal de 16-bit a ser escrito no arquivo .csv
   * @returns Verdadeiro se o valor hexadecimal de 16-bit foi escrito com sucesso no arquivo, falso se houve um problema na abertura do arquivo ou na escrita nele
   */
  bool bAddCsvEntryRaw16b(uint16_t u16RawValue);
  
  /**
   * @brief Adiciona uma entrada de número unsigned int de 16-bit ao arquivo .csv. Esta função é usada para popular o .csv com dados
   * @param u16UintEntry O número unsigned int de 16-bit a ser escrito no arquivo .csv
   * @returns Verdadeiro se o número unsigned int de 16-bit foi escrito com sucesso no arquivo, falso se houve um problema na abertura do arquivo ou na escrita nele
   */
  bool bAddCsvEntryUint16b(uint16_t u16UintEntry);
  
  /**
   * @brief Adiciona uma entrada de número signed int de 16-bit ao arquivo .csv. Esta função é usada para popular o .csv com dados
   * @param u16IntEntry O número signed int de 16-bit a ser escrito no arquivo .csv
   * @returns Verdadeiro se o número signed int de 16-bit foi escrito com sucesso no arquivo, falso se houve um problema na abertura do arquivo ou na escrita nele
   */
  bool bAddCsvEntryInt16b(int16_t u16IntEntry);
  
  /**
   * @brief Adiciona uma entrada de valor hexadecimal 32-bit ao arquivo .csv. Esta função é usada para popular o .csv com dados
   * @param u32RawValue O valor hexadecimal de 32-bit a ser escrito no arquivo .csv
   * @returns Verdadeiro se o valor hexadecimal de 32-bit foi escrito com sucesso no arquivo, falso se houve um problema na abertura do arquivo ou na escrita nele
   */
  bool bAddCsvEntryRaw32b(uint32_t u32RawValue);

  /**
   * @brief Adiciona uma entrada de número flutuante ao arquivo .csv. Esta função é usada para popular o .csv com dados
   * @param fFloatEntry O número flutuante a ser escrito no arquivo .csv
   * @param u8DecimalPlaces O número de casas decimais para o número flutuante
   * @returns Verdadeiro se o número flutuante foi escrito com sucesso no arquivo, falso se houve um problema na abertura do arquivo ou na escrita nele
   */
  bool bAddCsvEntryFloat(float fFloatEntry, uint8_t u8DecimalPlaces);
  
  /**
   * @brief Inicia uma nova linha de dados no arquivo .csv e escreve um índice incrementado nele, usado quando uma nova linha de dados precisa ser gravada no arquivo .csv
   * @returns Verdadeiro se a nova linha foi iniciada com sucesso e o índice foi escrito, falso se houve um problema na abertura do arquivo ou na escrita nele
   */
  bool bStartCsvLine(void);
  
  /**
   * @brief Termina uma linha no arquivo .csv. Esta função é usada quando a linha atual de dados no arquivo .csv está concluída
   * @returns Verdadeiro se a nova linha foi escrita com sucesso no arquivo, falso se houve um problema na abertura do arquivo ou na escrita nele
   */
  bool bEndCsvLine(void);

private:
  const char *_PCC_CSV_FILENAME; /**< Constante para o nome do arquivo CSV */
  File _xCsvFile;                /**< Instância do arquivo CSV */
  uint32_t _u32CsvIndex = 0;     /**< Indice dos dados do arquivo CSV */
};

#endif
