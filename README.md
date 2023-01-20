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
## Специфичные для устройства
```

enum EsOperationMode
{
  MeteoIdle = 1, 
  MeteoLimited = 2,
  MeteoLiveUnlimited = 3
}


enum DataFlag
{
  
}


enum DataTrends
{
  
}

struct LiveData
{
  esDT  m_ts;              //< Timestamp, reserved in ET1
  esU32 m_flags;          //< Data state flags, @see #DataFlag
  esU8  m_heaterTimer;    //< Air U heater timer. 255 - not used, 0..N - seconds until completion
  esU32 m_taAvgTimer;      //< Air Temperature averageing time, s (reserved)
  esU32 m_uAvgTimer;      //< Air U averageing timer, s (reserved)
  esF   m_ta;              //< Air T
  esF    m_rh;              //< Humidity
  esF    m_td;              //< Dew point
  esF   m_tw;              //< Wetbulb T
  esF   m_u;              //< Air U
  esF    m_tg;              //< Black Globe T
  esF    m_wbgt;            //< Wetbulb Globe Temperature w/o Solar index
  esF   m_wbgts;          //< Wetbulb Globe Temperature with Solar radiation index
  esF    m_tr;              //< Radiation  T for U < 1m/s
  esF    m_w;              //< Heat radiation density
  esF    m_p;              //< Pressure
  esF    m_tO;              //< Resulting temperature
  esF    m_reserved1;
  esF    m_reserved2;
  DataTrends m_trends;
};


enum EsRpcEkologgerId
{
  SET_OPERATION_MODE = 2056, "VOID_UINT8_Call|Set device operation mode see EsRpcDeviceOperationMode"
  GET_OPERATION_MODE = 2057, "UINT8_VOID_Call|Get device operation mode see EsRpcDeviceOperationMode"
  GET_LIVE_DATA = 2058, "esBa_VOID_Call|Return LiveData struct for current active probe"
  SET_ALLOW_CHARGING = 2067,
  SET_ACTIVE_PROBE = 2068, "VOID_UINT8|Sets active probe for communication"
  GET_ACTIVE_PROBE = 2069 "UINT8_VOID|Return current active probe"
  
}
```
## Особенности работы по EKONNECT, USB(UART) интерфейсу
Перед первым подключением рекомендуется пинговать устройство минимум 2 раза, так как первый первый пакет может быть потерян
# Bluetooth Low Energy (BLE)
## Сервисы
### Device ID and state characteristics
### Device data access and control characteristics
### Ready-to-use live data
| Characteristic name          | ID        | Type    | Size in bytes | IO specifiers | Authentication needed | Is optional | Description |
| -----------------------------| --------- | --------| ------------- | ------------- | --------------------- |-------------|-------------| 
| Temperature C, probe 1       | 05000400  | float32 |
| Relative humidity %, probe 1 | 05000500  | float32 |
| Pressure GPa, probe 1        | 05000600  | float32 |
| Temperature C, probe 2       | 05000700  | float32 |
