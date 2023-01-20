# ekologger-doc
Документация для разработчиков
# Список поддерживаемых Rpc команд
## Стандартные 
```
enum EsRpcStdId
{
  CAPS_GET           = 0,   "esBA_Call|Return all procedure ids, supported by the hardware";
  FWID_GET           = 1,   "esBA_Call|Query firmware identification block";
  DATETIME_SET       = 6,   "esBL_Call_esDT|Set device date and time";
  DATETIME_GET       = 7,   "esDT_Call|Get device date and time";
  SHUTDOWN           = 9,   "VOID_Call|Schedule device power down";
  POWER_STATUS_GET   = 11,  "esBA_Call|Return device power status";
  SW_INFO_GET        = 21,  "esBA_Call|Query software identification block";
  FWID_MODERN_GET    = 22,  "esBA_Call|Query firmware identification block of modern devices which support dual ID feature";
}
```
```
## Специфичные для устройства


enum EsOperationMode
{
  MeteoIdle = 1, 
  MeteoLimited = 2,
  MeteoLiveUnlimited = 3
}

enum EsRpcEkologgerId
{
  SET_OPERATION_MODE = 2056 "VOID_UINT8|Set device operation mode see EsRpcDeviceOperationMode"
  GET_OPERATION_MODE = 2057 "UINT8_VOID|Get device operation mode see EsRpcDeviceOperationMode"
}
```
## Особенности работы по EKONNECT, USB(UART) интерфейсу
Перед первым подключением рекомендуется пинговать устройство минимум 2 раза, так как первый первый пакет может быть потерян

