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
### Device data access and control characteristics (UUID 0x0200)

| Characteristic name          | UUID      | Type            | Size in bytes | IO specifiers | Authentication needed | Description                       |
| -----------------------------| --------- | ----------------| ------------- | ------------- | --------------------- |-----------------------------------|
| Live Data                    | 0x0202    | MeteoLiveData_t |170            |Read           |No                     |Read live data struct from 2 probes|
| Live Data save               | 0x0203    | uint8           | 1             |Write          |No                     |On write saves live data to sd card|

### Device persistent data access and control (UUID 0x0300)

| Characteristic name| UUID      | Type            | Size in bytes | IO specifiers | Authentication needed | Description                       |
| -------------------| --------- | ----------------| ------------- | ------------- | --------------------- |-----------------------------------|
| Live Data          | 0x0301    | MeteoLiveData_t |170            |Read           |No                     |Read live data struct from 2 probes|
| Current node read  | 0x0303    | uint64/bytearray|8/170          |Write/Notify   |No                     |Sends all data from selected file  |
| Current node delete| 0x0303    | uint64          |8              |Write          |No                     |Deletes selected file              |

# Current node read
  To read data from sdcard, server should subscribe to char and write needed file timestamp in ms(year, month, day). Then slave will send all data from selected file. 
  Struct will look like this:
  ```
  MeteoLiveData[2]; // struct from 2 probes
  ```
  This struct will be send in one MTU packet.
# How to get list of current files on sdcard
 ```
 typedef struct
 {
  uint64_t ms;
  uint32_t node_count;
 }node_date_t;
 ```
  Subscribe to Nodes date char, and then write 1 to it. Slave will send nodes_date_t struct for each file, which should be interpreted as "first 8 bytes - timestamp of file in ms, 4 bytes - node_count in file", at the end slave sends empty struct (all 12 bytes are zero), to indicate that there are no more files on sdcard;
  
### Ready-to-use live data characteristics (UUID 0x0500)

On char notification, sends data immediately, then updates it in 1 second interval
| Characteristic name          | UUID        | Type    | Size in bytes | IO specifiers | Authentication needed | Description                        |
| -----------------------------| --------- | --------| ------------- | ------------- | --------------------- |--------------------------------------|
| Temperature C, probe 1       | 0x0504    | float32 | 4             |Read/Notify    |No                     |Read measured temperature from probe 1|
| Relative humidity %, probe 1 | 0x0505    | float32 | 4             |Read/Notify    |No                     |Read measured humidity from probe 1   |
| Pressure GPa, probe 1        | 0x0506    | float32 | 4             |Read/Notify    |No                     |Read measured pressure from probe 1   |
| Temperature C, probe 2       | 0x0507    | float32 | 4             |Read/Notify    |No                     |Read measured temperature from probe 2|
| Relative humidity %, probe 2 | 0x0508    | float32 | 4             |Read/Notify    |No                     |Read measured humidity from probe 2   |
| Pressure GPa, probe 2        | 0x0509    | float32 | 4             |Read/Notify    |No                     |Read measured pressure from probe 2   |
| Velocity m/s, probe 1        | 0x0510    | float32 | 4             |Read/Notify    |No                     |Read measured pressure from probe 2   |
| Velocity m/s, probe 2        | 0x0511    | float32 | 4             |Read/Notify    |No                     |Read measured pressure from probe 2   |
| Wbgt index C                 | 0x0512    | float32 | 4             |Read/Notify    |No                     |Read measured wbgt index              |
