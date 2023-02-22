# ekologger-doc
Документация для разработчиков
# Список поддерживаемых Rpc команд
## Стандартные 
```
  typedef enum
	{
			RPC_GET_DEVICE_IDS			=	0,
			RPC_GET_DEVICE_ID			=	1,
			RPC_SET_DEVICE_DATE_TIME = 6,
			RPC_GET_DEVICE_DATE_TIME = 7,
			RPC_FACTORY_RESET = 8,
			RPC_POWER_OFF				=	9,
			RPC_GET_POWER_STATUS = 11,
			RPC_FIND_ME = 20,
			RPC_GET_SOFTWARE_INFO		=	21,
			RPC_GET_MODERN_FIRMWARE_ID = 22
	} StandartId_t;
```
## Специфичные для устройства
```

    typedef enum
		{
      RPC_SET_OPERATION_MODE		=	2056,
			RPC_GET_OPERATION_MODE		=	2057,
			RPC_GET_LIVE_DATA			=	2058,
			RPC_SET_ALLOW_CHARGING		=	2067,
			RPC_SET_ACTIVE_PROBE = 2068,
			RPC_GET_ACTIVE_PROBE = 2069,
			RPC_GET_FLAGS				=	3001,
			RPC_GET_CACHED_NON_CALIBRATED_DATA = 3009
		}CustomId_t;
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

| Characteristic name  | UUID      | Type            | Size in bytes | IO specifiers | Authentication needed | Description                       |
| -------------------  | --------- | ----------------| ------------- | ------------- | --------------------- |-----------------------------------|
| Persistent node count| 0x0301    | uint32          |4              |Read/Notify    |No                     |Read node count from all sd files  |
| Current node read    | 0x0303    | uint64/bytearray|8/170          |Write/Notify   |No                     |Sends all data from selected file  |
| Current node delete  | 0x0304    | uint64          |8              |Write          |No                     |Delete selected file               |
| Nodes Date           | 0x0306    | uint8           |1              |Write/Notify   |No                     |Send info               |



#### Current node read
  To read data from sdcard, server should subscribe to char and write needed file timestamp in ms(year, month, day). Then slave will send all data from selected file. 
  Struct will look like this:
  ```
  MeteoLiveData_t sdcard_data[2]; // struct from 2 probes
  ```
  Each sdcard_data will be send in one MTU packet.
#### How to get list of current files on sdcard
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
