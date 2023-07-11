#include "incBoardPins.h"
#include "incSystemConstants.h"
#include "libIntDevices.h"
#include "libModbusMaster.h"
#include "libDatalog.h"

/* Instanciação das bibliotecas do projeto */

CIntDevices xIntDevices;
CModbusMaster xModbusMaster(CBoardPins::CU8_TX_RX_CTRL_PIN, CSystemConstants::CU8_KRON_MODBUS_SLAVE_ADDR, &(Serial2), CSystemConstants::CU32_SERIAL_MODBUS_BAUD_RATE);
CDatalog xDatalog(CSystemConstants::CU32_UPDATE_DATALOG_TIME_MS / 1000);

/* Variaveis para leitura dos registradores da Kron */

typedef enum KronModbusRegTypes {
  eKron16bRaw = 0,
  eKron16bUint,
  eKron16bInt,
  eKron32bRaw,
  eKron32bUint,
  eKron32bFp
} TKronModbusRegTypes;

typedef struct KronModbusRegister {
    uint16_t u16RegisterAddr;
    TKronModbusRegTypes eRegisterType;
} TKronModbusRegister;

const TKronModbusRegister CX_KRON_REGISTERS_LIST[752] = {
  {30003, eKron32bFp},   {30009, eKron32bFp},   {30011, eKron32bFp},   {30015, eKron32bFp},  {30017, eKron32bFp},   {30019, eKron32bFp},   {30021, eKron32bFp},   {30025, eKron32bFp},   {30027, eKron32bFp},   {30031, eKron32bFp},   {30033, eKron32bFp},   {30035, eKron32bFp},  {30037, eKron32bFp},   {30041, eKron32bFp},   {30043, eKron32bFp},   {30045, eKron32bFp}, 
  {30049, eKron32bFp},   {30051, eKron32bFp},   {30053, eKron32bFp},   {30057, eKron32bFp},  {30059, eKron32bFp},   {30061, eKron32bFp},   {30065, eKron32bFp},   {30067, eKron32bFp},   {30069, eKron32bFp},   {30073, eKron32bFp},   {30075, eKron32bFp},   {30077, eKron32bFp},  {30081, eKron32bFp},   {30083, eKron32bFp},   {30087, eKron32bFp},   {30089, eKron32bFp}, 
  {30093, eKron32bFp},   {31003, eKron32bFp},   {31009, eKron32bFp},   {31011, eKron32bFp},  {31015, eKron32bFp},   {31017, eKron32bFp},   {31019, eKron32bFp},   {31021, eKron32bFp},   {31025, eKron32bFp},   {31027, eKron32bFp},   {31031, eKron32bFp},   {31033, eKron32bFp},  {31035, eKron32bFp},   {31037, eKron32bFp},   {31041, eKron32bFp},   {31043, eKron32bFp}, 
  {31045, eKron32bFp},   {31049, eKron32bFp},   {31051, eKron32bFp},   {31053, eKron32bFp},  {31057, eKron32bFp},   {31059, eKron32bFp},   {31061, eKron32bFp},   {31065, eKron32bFp},   {31067, eKron32bFp},   {31069, eKron32bFp},   {31073, eKron32bFp},   {31075, eKron32bFp},  {32003, eKron32bFp},   {32009, eKron32bFp},   {32011, eKron32bFp},   {32015, eKron32bFp}, 
  {32017, eKron32bFp},   {32019, eKron32bFp},   {32021, eKron32bFp},   {32025, eKron32bFp},  {32027, eKron32bFp},   {32031, eKron32bFp},   {32033, eKron32bFp},   {32035, eKron32bFp},   {32037, eKron32bFp},   {32041, eKron32bFp},   {32043, eKron32bFp},   {32045, eKron32bFp},  {32049, eKron32bFp},   {32051, eKron32bFp},   {32053, eKron32bFp},   {32057, eKron32bFp}, 
  {32059, eKron32bFp},   {32061, eKron32bFp},   {32065, eKron32bFp},   {32067, eKron32bFp},  {32069, eKron32bFp},   {32073, eKron32bFp},   {32075, eKron32bFp},   {30201, eKron32bFp},   {30203, eKron32bFp},   {30205, eKron32bFp},   {30207, eKron32bFp},   {30209, eKron32bFp},  {30211, eKron32bFp},   {30213, eKron32bFp},   {30215, eKron32bFp},   {30601, eKron16bRaw}, 
  {30602, eKron16bRaw},  {30603, eKron16bRaw},  {30604, eKron16bRaw},  {30605, eKron16bRaw}, {30606, eKron16bRaw},  {30607, eKron16bRaw},  {30608, eKron16bInt},  {30609, eKron16bInt},  {30611, eKron16bInt},  {30612, eKron16bInt},  {30614, eKron16bInt},  {30761, eKron32bFp},  {30765, eKron32bFp},   {30767, eKron32bFp},   {30769, eKron32bFp},   {30773, eKron32bFp}, 
  {30775, eKron32bFp},   {30621, eKron16bRaw},  {30622, eKron16bRaw},  {30623, eKron16bRaw}, {30624, eKron16bRaw},  {30625, eKron16bRaw},  {30626, eKron16bRaw},  {30627, eKron16bRaw},  {30628, eKron16bInt},  {30629, eKron16bInt},  {30631, eKron16bInt},  {30632, eKron16bInt}, {30634, eKron16bInt},  {30781, eKron32bFp},   {30785, eKron32bFp},   {30787, eKron32bFp}, 
  {30789, eKron32bFp},   {30793, eKron32bFp},   {30795, eKron32bFp},   {30641, eKron16bRaw}, {30642, eKron16bRaw},  {30643, eKron16bRaw},  {30644, eKron16bRaw},  {30645, eKron16bRaw},  {30646, eKron16bRaw},  {30647, eKron16bRaw},  {30648, eKron16bInt},  {30649, eKron16bInt}, {30651, eKron16bInt},  {30652, eKron16bInt},  {30654, eKron16bInt},  {30801, eKron32bFp}, 
  {30805, eKron32bFp},   {30807, eKron32bFp},   {30809, eKron32bFp},   {30813, eKron32bFp},  {30815, eKron32bFp},   {30661, eKron16bRaw},  {30662, eKron16bRaw},  {30663, eKron16bRaw},  {30664, eKron16bRaw},  {30665, eKron16bRaw},  {30666, eKron16bRaw},  {30667, eKron16bRaw}, {30668, eKron16bInt},  {30669, eKron16bInt},  {30671, eKron16bInt},  {30672, eKron16bInt}, 
  {30674, eKron16bInt},  {30821, eKron32bFp},   {30825, eKron32bFp},   {30827, eKron32bFp},  {30829, eKron32bFp},   {30833, eKron32bFp},   {30835, eKron32bFp},   {30921, eKron16bRaw},  {30922, eKron16bRaw},  {30923, eKron16bRaw},  {30924, eKron16bRaw},  {30925, eKron16bInt}, {30926, eKron16bInt},  {30928, eKron16bInt},  {30929, eKron16bInt},  {30930, eKron16bInt}, 
  {30931, eKron16bInt},  {30932, eKron16bInt},  {30934, eKron16bInt},  {30935, eKron16bInt}, {30936, eKron16bInt},  {30937, eKron16bInt},  {30938, eKron16bInt},  {30940, eKron16bInt},  {30941, eKron16bInt},  {30942, eKron16bInt},  {33001, eKron16bInt},  {33003, eKron16bInt}, {33004, eKron16bInt},  {33006, eKron16bInt},  {33007, eKron16bInt},  {33009, eKron16bInt}, 
  {33010, eKron16bInt},  {33012, eKron16bInt},  {33013, eKron16bInt},  {33015, eKron16bInt}, {33016, eKron16bInt},  {33018, eKron16bInt},  {33019, eKron16bInt},  {33021, eKron16bInt},  {33022, eKron16bInt},  {33024, eKron16bInt},  {33025, eKron16bInt},  {33027, eKron16bInt}, {33028, eKron16bInt},  {33030, eKron16bInt},  {33201, eKron16bInt},  {33203, eKron16bInt}, 
  {33204, eKron16bInt},  {33206, eKron16bInt},  {33207, eKron16bInt},  {33209, eKron16bInt}, {33210, eKron16bInt},  {33212, eKron16bInt},  {33213, eKron16bInt},  {33215, eKron16bInt},  {33216, eKron16bInt},  {33218, eKron16bInt},  {33219, eKron16bInt},  {33221, eKron16bInt}, {33222, eKron16bInt},  {33224, eKron16bInt},  {33225, eKron16bInt},  {33227, eKron16bInt}, 
  {33228, eKron16bInt},  {33230, eKron16bInt},  {33401, eKron16bInt},  {33403, eKron16bInt}, {33404, eKron16bInt},  {33406, eKron16bInt},  {33407, eKron16bInt},  {33409, eKron16bInt},  {33410, eKron16bInt},  {33412, eKron16bInt},  {33413, eKron16bInt},  {33415, eKron16bInt}, {33416, eKron16bInt},  {33418, eKron16bInt},  {33419, eKron16bInt},  {33421, eKron16bInt}, 
  {33422, eKron16bInt},  {33424, eKron16bInt},  {33425, eKron16bInt},  {33427, eKron16bInt}, {33428, eKron16bInt},  {33430, eKron16bInt},  {33801, eKron32bFp},   {33805, eKron32bFp},   {33807, eKron32bFp},   {33811, eKron32bFp},   {33813, eKron32bFp},   {33817, eKron32bFp},  {33819, eKron32bFp},   {33823, eKron32bFp},   {33829, eKron32bFp},   {33831, eKron32bFp}, 
  {33835, eKron32bFp},   {33837, eKron32bFp},   {33841, eKron32bFp},   {33843, eKron32bFp},  {33847, eKron32bFp},   {33849, eKron32bFp},   {33853, eKron32bFp},   {33901, eKron16bInt},  {33905, eKron16bInt},  {33906, eKron16bInt},  {33907, eKron16bRaw},  {33908, eKron16bRaw}, {33909, eKron16bRaw},  {33910, eKron16bRaw},  {34001, eKron32bFp},   {34003, eKron32bFp}, 
  {34005, eKron32bFp},   {34007, eKron32bFp},   {34009, eKron32bFp},   {34011, eKron32bFp},  {34013, eKron32bFp},   {34015, eKron32bFp},   {34017, eKron32bFp},   {34019, eKron32bFp},   {34021, eKron32bFp},   {34023, eKron32bFp},   {34025, eKron32bFp},   {34027, eKron32bFp},  {34029, eKron32bFp},   {34031, eKron32bFp},   {34033, eKron32bFp},   {34035, eKron32bFp}, 
  {34037, eKron32bFp},   {34039, eKron32bFp},   {34041, eKron32bFp},   {34043, eKron32bFp},  {34045, eKron32bFp},   {34047, eKron32bFp},   {34049, eKron32bFp},   {34051, eKron32bFp},   {34053, eKron32bFp},   {34055, eKron32bFp},   {34057, eKron32bFp},   {34059, eKron32bFp},  {34061, eKron32bFp},   {34063, eKron32bFp},   {34065, eKron32bFp},   {34067, eKron32bFp}, 
  {34069, eKron32bFp},   {34071, eKron32bFp},   {34073, eKron32bFp},   {34075, eKron32bFp},  {34077, eKron32bFp},   {34079, eKron32bFp},   {34161, eKron32bFp},   {34163, eKron32bFp},   {34165, eKron32bFp},   {34167, eKron32bFp},   {34169, eKron32bFp},   {34171, eKron32bFp},  {34173, eKron32bFp},   {34175, eKron32bFp},   {34177, eKron32bFp},   {34179, eKron32bFp}, 
  {34181, eKron32bFp},   {34183, eKron32bFp},   {34185, eKron32bFp},   {34187, eKron32bFp},  {34189, eKron32bFp},   {34191, eKron32bFp},   {34193, eKron32bFp},   {34195, eKron32bFp},   {34197, eKron32bFp},   {34199, eKron32bFp},   {34201, eKron32bFp},   {34203, eKron32bFp},  {34205, eKron32bFp},   {34207, eKron32bFp},   {34209, eKron32bFp},   {34211, eKron32bFp}, 
  {34213, eKron32bFp},   {34215, eKron32bFp},   {34217, eKron32bFp},   {34219, eKron32bFp},  {34221, eKron32bFp},   {34223, eKron32bFp},   {34225, eKron32bFp},   {34227, eKron32bFp},   {34229, eKron32bFp},   {34231, eKron32bFp},   {34233, eKron32bFp},   {34235, eKron32bFp},  {34237, eKron32bFp},   {34239, eKron32bFp},   {34241, eKron32bFp},   {34243, eKron32bFp}, 
  {34245, eKron32bFp},   {34247, eKron32bFp},   {34249, eKron32bFp},   {34251, eKron32bFp},  {34253, eKron32bFp},   {34255, eKron32bFp},   {34257, eKron32bFp},   {34259, eKron32bFp},   {34261, eKron32bFp},   {34263, eKron32bFp},   {34265, eKron32bFp},   {34267, eKron32bFp},  {34269, eKron32bFp},   {34271, eKron32bFp},   {34273, eKron32bFp},   {34275, eKron32bFp}, 
  {34277, eKron32bFp},   {34279, eKron32bFp},   {34281, eKron32bFp},   {34283, eKron32bFp},  {34285, eKron32bFp},   {34287, eKron32bFp},   {34289, eKron32bFp},   {34291, eKron32bFp},   {34293, eKron32bFp},   {34295, eKron32bFp},   {34297, eKron32bFp},   {34299, eKron32bFp},  {34301, eKron32bFp},   {34303, eKron32bFp},   {34305, eKron32bFp},   {34307, eKron32bFp}, 
  {34309, eKron32bFp},   {34311, eKron32bFp},   {34313, eKron32bFp},   {34315, eKron32bFp},  {34317, eKron32bFp},   {34319, eKron32bFp},   {34401, eKron32bFp},   {34403, eKron32bFp},   {34405, eKron32bFp},   {34407, eKron32bFp},   {34409, eKron32bFp},   {34411, eKron32bFp},  {34413, eKron32bFp},   {34415, eKron32bFp},   {34417, eKron32bFp},   {34419, eKron32bFp}, 
  {34421, eKron32bFp},   {34423, eKron32bFp},   {34425, eKron32bFp},   {34427, eKron32bFp},  {34429, eKron32bFp},   {34431, eKron32bFp},   {34433, eKron32bFp},   {34435, eKron32bFp},   {34437, eKron32bFp},   {34439, eKron32bFp},   {34441, eKron32bFp},   {34443, eKron32bFp},  {34445, eKron32bFp},   {34447, eKron32bFp},   {34449, eKron32bFp},   {34451, eKron32bFp}, 
  {34453, eKron32bFp},   {34455, eKron32bFp},   {34457, eKron32bFp},   {34459, eKron32bFp},  {34461, eKron32bFp},   {34463, eKron32bFp},   {34465, eKron32bFp},   {34467, eKron32bFp},   {34469, eKron32bFp},   {34471, eKron32bFp},   {34473, eKron32bFp},   {34475, eKron32bFp},  {34477, eKron32bFp},   {34479, eKron32bFp},   {35003, eKron32bFp},   {35005, eKron32bFp}, 
  {35007, eKron32bFp},   {35009, eKron32bFp},   {35011, eKron32bFp},   {35013, eKron32bFp},  {35163, eKron32bFp},   {35165, eKron32bFp},   {35167, eKron32bFp},   {35169, eKron32bFp},   {35171, eKron32bFp},   {35173, eKron32bFp},   {35243, eKron32bFp},   {35245, eKron32bFp},  {35247, eKron32bFp},   {35249, eKron32bFp},   {35251, eKron32bFp},   {35253, eKron32bFp}, 
  {35403, eKron32bFp},   {35405, eKron32bFp},   {35407, eKron32bFp},   {35409, eKron32bFp},  {35411, eKron32bFp},   {35413, eKron32bFp},   {36003, eKron32bFp},   {36005, eKron32bFp},   {36007, eKron32bFp},   {36009, eKron32bFp},   {36011, eKron32bFp},   {36013, eKron32bFp},  {36163, eKron32bFp},   {36165, eKron32bFp},   {36167, eKron32bFp},   {36169, eKron32bFp}, 
  {36171, eKron32bFp},   {36173, eKron32bFp},   {36243, eKron32bFp},   {36245, eKron32bFp},  {36247, eKron32bFp},   {36249, eKron32bFp},   {36251, eKron32bFp},   {36253, eKron32bFp},   {36403, eKron32bFp},   {36405, eKron32bFp},   {36407, eKron32bFp},   {36409, eKron32bFp},  {36411, eKron32bFp},   {36413, eKron32bFp},   {37001, eKron32bFp},   {37003, eKron32bFp}, 
  {37005, eKron32bFp},   {37007, eKron32bFp},   {37009, eKron32bFp},   {37011, eKron32bFp},  {37013, eKron32bFp},   {37015, eKron32bFp},   {37017, eKron32bFp},   {37019, eKron32bFp},   {37021, eKron32bFp},   {37023, eKron32bFp},   {37025, eKron32bFp},   {37027, eKron32bFp},  {37029, eKron32bFp},   {37031, eKron32bFp},   {37033, eKron32bFp},   {37035, eKron32bFp}, 
  {37037, eKron32bFp},   {37039, eKron32bFp},   {37041, eKron32bFp},   {37043, eKron32bFp},  {37045, eKron32bFp},   {37047, eKron32bFp},   {37049, eKron32bFp},   {37051, eKron32bFp},   {37053, eKron32bFp},   {37055, eKron32bFp},   {37057, eKron32bFp},   {37059, eKron32bFp},  {37061, eKron32bFp},   {37063, eKron32bFp},   {37065, eKron32bFp},   {37067, eKron32bFp}, 
  {37069, eKron32bFp},   {37071, eKron32bFp},   {37073, eKron32bFp},   {37075, eKron32bFp},  {37077, eKron32bFp},   {37079, eKron32bFp},   {37081, eKron32bFp},   {37083, eKron32bFp},   {37085, eKron32bFp},   {37087, eKron32bFp},   {37089, eKron32bFp},   {37091, eKron32bFp},  {37185, eKron32bFp},   {37187, eKron32bFp},   {37189, eKron32bFp},   {37191, eKron32bFp}, 
  {37193, eKron32bFp},   {37195, eKron32bFp},   {37197, eKron32bFp},   {37199, eKron32bFp},  {37201, eKron32bFp},   {37203, eKron32bFp},   {37205, eKron32bFp},   {37207, eKron32bFp},   {37209, eKron32bFp},   {37211, eKron32bFp},   {37213, eKron32bFp},   {37215, eKron32bFp},  {37217, eKron32bFp},   {37219, eKron32bFp},   {37221, eKron32bFp},   {37223, eKron32bFp}, 
  {37225, eKron32bFp},   {37227, eKron32bFp},   {37229, eKron32bFp},   {37231, eKron32bFp},  {37233, eKron32bFp},   {37235, eKron32bFp},   {37237, eKron32bFp},   {37239, eKron32bFp},   {37241, eKron32bFp},   {37243, eKron32bFp},   {37245, eKron32bFp},   {37247, eKron32bFp},  {37249, eKron32bFp},   {37251, eKron32bFp},   {37253, eKron32bFp},   {37255, eKron32bFp}, 
  {37257, eKron32bFp},   {37259, eKron32bFp},   {37261, eKron32bFp},   {37263, eKron32bFp},  {37265, eKron32bFp},   {37267, eKron32bFp},   {37269, eKron32bFp},   {37271, eKron32bFp},   {37273, eKron32bFp},   {37275, eKron32bFp},   {37277, eKron32bFp},   {37301, eKron32bFp},  {37303, eKron32bFp},   {37305, eKron32bFp},   {37307, eKron32bFp},   {37309, eKron32bFp}, 
  {37311, eKron32bFp},   {37313, eKron32bFp},   {37315, eKron32bFp},   {37317, eKron32bFp},  {37319, eKron32bFp},   {37321, eKron32bFp},   {37323, eKron32bFp},   {37325, eKron32bFp},   {37327, eKron32bFp},   {37329, eKron32bFp},   {37331, eKron32bFp},   {37333, eKron32bFp},  {37335, eKron32bFp},   {37337, eKron32bFp},   {37339, eKron32bFp},   {37341, eKron32bFp}, 
  {37343, eKron32bFp},   {37345, eKron32bFp},   {37347, eKron32bFp},   {37349, eKron32bFp},  {37351, eKron32bFp},   {37353, eKron32bFp},   {37355, eKron32bFp},   {37357, eKron32bFp},   {37359, eKron32bFp},   {37361, eKron32bFp},   {37363, eKron32bFp},   {37365, eKron32bFp},  {37367, eKron32bFp},   {37369, eKron32bFp},   {37371, eKron32bFp},   {37373, eKron32bFp}, 
  {37375, eKron32bFp},   {37377, eKron32bFp},   {37379, eKron32bFp},   {37381, eKron32bFp},  {37383, eKron32bFp},   {37385, eKron32bFp},   {37387, eKron32bFp},   {37389, eKron32bFp},   {37391, eKron32bFp},   {37393, eKron32bFp},   {37395, eKron32bFp},   {37493, eKron32bFp},  {37495, eKron32bFp},   {37497, eKron32bFp},   {37499, eKron32bFp},   {37501, eKron32bFp}, 
  {37503, eKron32bFp},   {37505, eKron32bFp},   {37507, eKron32bFp},   {37509, eKron32bFp},  {37511, eKron32bFp},   {37513, eKron32bFp},   {37515, eKron32bFp},   {37517, eKron32bFp},   {37519, eKron32bFp},   {37521, eKron32bFp},   {37523, eKron32bFp},   {37525, eKron32bFp},  {37527, eKron32bFp},   {37529, eKron32bFp},   {37531, eKron32bFp},   {37533, eKron32bFp}, 
  {37535, eKron32bFp},   {37537, eKron32bFp},   {37539, eKron32bFp},   {37541, eKron32bFp},  {37543, eKron32bFp},   {37545, eKron32bFp},   {37547, eKron32bFp},   {37549, eKron32bFp},   {37551, eKron32bFp},   {37553, eKron32bFp},   {37555, eKron32bFp},   {37557, eKron32bFp},  {37559, eKron32bFp},   {37561, eKron32bFp},   {37563, eKron32bFp},   {37565, eKron32bFp}, 
  {37567, eKron32bFp},   {37569, eKron32bFp},   {37571, eKron32bFp},   {37573, eKron32bFp},  {37575, eKron32bFp},   {37577, eKron32bFp},   {37579, eKron32bFp},   {37581, eKron32bFp},   {37583, eKron32bFp},   {37585, eKron32bFp},   {37587, eKron32bFp},   {37589, eKron32bFp},  {37591, eKron32bFp},   {37593, eKron32bFp},   {37595, eKron32bFp},   {37597, eKron32bFp}, 
  {37983, eKron32bRaw},  {37985, eKron32bRaw},  {37989, eKron32bRaw},  {38001, eKron32bFp},  {38005, eKron32bFp},   {32901, eKron16bUint}, {32902, eKron16bUint}, {32903, eKron16bUint}, {32904, eKron16bUint}, {39001, eKron32bFp},   {39007, eKron32bFp},   {39009, eKron32bFp},  {39013, eKron32bFp},   {39015, eKron32bFp},   {39017, eKron32bFp},   {39019, eKron32bFp}, 
  {39023, eKron32bFp},   {39025, eKron32bFp},   {39029, eKron32bFp},   {39031, eKron32bFp},  {39033, eKron32bFp},   {39037, eKron32bFp},   {39039, eKron32bFp},   {39041, eKron32bFp},   {39045, eKron32bFp},   {39047, eKron32bFp},   {39049, eKron32bFp},   {39053, eKron32bFp},  {39055, eKron32bFp},   {39057, eKron32bFp},   {39061, eKron32bFp},   {39063, eKron32bFp}, 
  {39065, eKron32bFp},   {39069, eKron32bFp},   {39101, eKron16bInt},  {39103, eKron16bInt}, {39104, eKron16bInt},  {39106, eKron16bInt},  {39107, eKron16bInt},  {39109, eKron16bInt},  {39110, eKron16bInt},  {39112, eKron16bInt},  {39113, eKron16bInt},  {39115, eKron16bInt}, {39116, eKron16bInt},  {39118, eKron16bInt},  {39119, eKron16bInt},  {39121, eKron16bInt}, 
  {39122, eKron16bInt},  {39124, eKron16bInt},  {39125, eKron16bInt},  {39127, eKron16bInt}, {39128, eKron16bInt},  {39130, eKron16bInt},  {39501, eKron32bFp},   {39503, eKron32bFp},   {39505, eKron32bFp},   {39507, eKron32bFp},   {39509, eKron32bFp},   {39511, eKron32bFp},  {39513, eKron32bFp},   {39515, eKron32bFp},   {39517, eKron32bFp},   {39519, eKron32bFp}, 
  {39521, eKron32bFp},   {39523, eKron32bFp},   {39525, eKron32bFp},   {39701, eKron32bFp},  {39703, eKron32bFp},   {39705, eKron32bFp},   {39707, eKron32bFp},   {39709, eKron32bFp},   {39711, eKron32bFp},   {39713, eKron32bFp},   {39715, eKron32bFp},   {39717, eKron32bFp},  {39719, eKron32bFp},   {39721, eKron32bFp},   {39723, eKron32bFp},   {39725, eKron32bFp}
};

uint16_t u16KronRegsIndex = 0;

void setup() {
  /* Coloque seu código de configuração aqui, para ser executado uma vez: */

  /* Inicia o serial de debug */
  Serial.begin(CSystemConstants::CU32_SERIAL_USBDEBUG_BAUD_RATE);

  /* Inicia os dispositivos internos do sistema */
  if (!xIntDevices.bBegin()) {
    Serial.println("Falha ao iniciar o IntDevices!");
  }

  /* Inicia o log por um arquivo CSV */
  if (!xDatalog.bBegin()) {
    Serial.println("Falha ao iniciar o Datalog!");
  }

  xModbusMaster.begin();

  /* Grava o cabeçalho dos dados */
  if (xDatalog.bDatalogInit) {
    xDatalog.xLogCsv.bAddCsvEntryText("Timestamp");
    if (xIntDevices.bIntDevicesInit) {
      xDatalog.xLogCsv.bAddCsvEntryText("Temperature");
      xDatalog.xLogCsv.bAddCsvEntryText("Humidity");
    }
    for (u16KronRegsIndex = 0; u16KronRegsIndex < (sizeof(CX_KRON_REGISTERS_LIST)/sizeof(CX_KRON_REGISTERS_LIST[0])); u16KronRegsIndex++) {
      char pcStrRegisterNumberBuff[16];
      sprintf(pcStrRegisterNumberBuff, "Kron %04u", CX_KRON_REGISTERS_LIST[u16KronRegsIndex].u16RegisterAddr);
      xDatalog.xLogCsv.bAddCsvEntryText((const char*)pcStrRegisterNumberBuff);
    }
    xDatalog.xLogCsv.bEndCsvLine();
  }

}

void loop() {
  /* Coloque seu código principal aqui, para ser executado repetidamente: */

  if (xDatalog.bDatalogInit) {
    if (xDatalog.bGetWriteLogTimeFlag()) {
      xDatalog.clearWriteLogTimeFlag();

      /* Escreve no arquivo CSV os registradores da Kron */
      xDatalog.xLogCsv.bStartCsvLine();
      xDatalog.bWriteRtcTimestampToLog();
      if (xIntDevices.bIntDevicesInit) {
        xDatalog.xLogCsv.bAddCsvEntryFloat(xIntDevices.fGetAht10Temperature(), 6);
        xDatalog.xLogCsv.bAddCsvEntryFloat(xIntDevices.fGetAht10Humidity()   , 6);
      }
      for (u16KronRegsIndex = 0; u16KronRegsIndex < (sizeof(CX_KRON_REGISTERS_LIST)/sizeof(CX_KRON_REGISTERS_LIST[0])); u16KronRegsIndex++) {
        uint16_t u16RegisterValue = 0;
        uint32_t u32RegisterValue = 0;
        float fRegisterValue = 0.0f;
        switch (CX_KRON_REGISTERS_LIST[u16KronRegsIndex].eRegisterType) {
          case eKron16bRaw:
            u16RegisterValue = xModbusMaster.u16GetKronRegister16bValue(CX_KRON_REGISTERS_LIST[u16KronRegsIndex].u16RegisterAddr);
            xDatalog.xLogCsv.bAddCsvEntryRaw16b(u16RegisterValue);
            break;
          case eKron16bUint:
            u16RegisterValue = xModbusMaster.u16GetKronRegister16bValue(CX_KRON_REGISTERS_LIST[u16KronRegsIndex].u16RegisterAddr);
            xDatalog.xLogCsv.bAddCsvEntryUint16b(u16RegisterValue);
            break;
          case eKron16bInt:
            u16RegisterValue = xModbusMaster.u16GetKronRegister16bValue(CX_KRON_REGISTERS_LIST[u16KronRegsIndex].u16RegisterAddr);
            xDatalog.xLogCsv.bAddCsvEntryInt16b((int16_t)u16RegisterValue);
            break;
          case eKron32bRaw:
            u32RegisterValue = xModbusMaster.u32GetKronRegister32bValue(CX_KRON_REGISTERS_LIST[u16KronRegsIndex].u16RegisterAddr);
            xDatalog.xLogCsv.bAddCsvEntryRaw32b(u32RegisterValue);
            break;
          // case eKron32bUint:
          //   u32RegisterValue = xModbusMaster.u32GetKronRegister32bValue(CX_KRON_REGISTERS_LIST[u16KronRegsIndex].u16RegisterAddr);
          //   xDatalog.xLogCsv.bAddCsvEntryUint32b(u32RegisterValue);
          //   break;
          case eKron32bFp:
            fRegisterValue = xModbusMaster.fGetKronRegisterIeee32bFpValue(CX_KRON_REGISTERS_LIST[u16KronRegsIndex].u16RegisterAddr);
            xDatalog.xLogCsv.bAddCsvEntryFloat(fRegisterValue, 6);
            break;
        }
      }
      xDatalog.xLogCsv.bEndCsvLine();

      /* Envia as variaveis da Kron por Serial para debug */
      // Serial.print("Tensao Trifasica (V): ");                Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(30003), 4);
      // Serial.print("Tensao Linha 1 (V): ");                  Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3011), 4);
      // Serial.print("Tensao Linha 3 (V): ");                  Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3015), 4);
      // Serial.print("Corrente Trifasica (A): ");              Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3017), 4);
      // Serial.print("Corrente de Neutro: ");                  Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3019), 4);
      // Serial.print("Corrente Linha 1 (A): ");                Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3021), 4);
      // Serial.print("Corrente Linha 3 (A): ");                Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3025), 4);
      // Serial.print("Frequencia Linha 1: ");                  Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3027), 4);
      // Serial.print("Frequencia Linha 3: ");                  Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3031), 4);
      // Serial.print("Frequencia Linha 1 (IEC - 10s): ");      Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3033), 4);
      // Serial.print("Potencia Ativa Trifasica (W): ");        Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3035), 4);
      // Serial.print("Potencia Ativa Linha 1 (W): ");          Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3037), 4);
      // Serial.print("Potencia Ativa Linha 3 (W): ");          Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3041), 4);
      // Serial.print("Potencia Reativa Trifasica (VAr): ");    Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3043), 4);
      // Serial.print("Potencia Reativa Linha 1 (VAr): ");      Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3045), 4);
      // Serial.print("Potencia Reativa Linha 3 (VAr): ");      Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3049), 4);
      // Serial.print("Potencia Aparente Trifasica (VA): ");    Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3051), 4);
      // Serial.print("Potencia Aparente Linha 1 (VA): ");      Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3053), 4);
      // Serial.print("Potencia Aparente Linha 3 (VA): ");      Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3057), 4);
      // Serial.print("Fator de Potencia Trifasico: ");         Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3059), 4);
      // Serial.print("Fator de Potencia Linha 1: ");           Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3061), 4);
      // Serial.print("Fator de Potencia Linha 3: ");           Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3065), 4);
      // Serial.print("Fator de Pot. Trifasico - Desloc.: ");   Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3067), 4);
      // Serial.print("Fator de Pot. Linha 1 - Desloc.: ");     Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3069), 4);
      // Serial.print("Fator de Pot. Linha 3 - Desloc.: ");     Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3073), 4);
      // Serial.print("Desequilibrio de Tensao: ");             Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3075), 4);
      // Serial.print("Sensacao inst. de Flicker Linha 1: ");   Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3077), 4);
      // Serial.print("Sensacao inst. de Flicker Linha 3: ");   Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3081), 4);
      // Serial.print("Nivel de Flicker em 10 min. Linha 1: "); Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3083), 4);
      // Serial.print("Nivel de Flicker em 10 min. Linha 3: "); Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3087), 4);
      // Serial.print("Nivel de Flicker em 2 horas Linha 1: "); Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3089), 4);
      // Serial.print("Nivel de Flicker em 2 horas Linha 3: "); Serial.println(xModbusMaster.fGetKronRegisterIeee32bFpValue(3093), 4);
      // Serial.println("-----------------------");
    } /* Fim da exeução temporizada */
  }

}
