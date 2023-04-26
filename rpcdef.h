#ifndef __RPCDEF_H__
#define __RPCDEF_H__

#include <stdint.h>

#define RPC_LONGLEN 35
#define RPC_SHORTLEN 5

typedef uint8_t UINT8;
typedef uint16_t UINT16;
typedef uint64_t UINT64;
typedef int8_t INT8;
typedef int16_t INT16;
typedef int64_t INT64;
typedef int64_t DATETIME;
typedef uint8_t RPCBOOL;

typedef int32_t INT32;
typedef uint32_t UINT32;

#define PACKETLEN_VARS 3

//////////////////////////////////////// Rpc Definitions ///////////////////////////////////
typedef enum
{
    void_void = 1,
    UINT8_void = 2,
    UINT16_void = 3,
    UINT32_void = 4,
    UINT64_void = 5,
    INT8_void = 6,
    INT16_void = 7,
    INT32_void = 8,
    INT64_void = 9,
    BOOL_void = 10,
    DATETIME_void = 11,
    BYTEARRAY_void = 12,
    FLOAT_void = 13,
    void_BYTEARRAY = 14,
    void_UINT16 = 15,
    void_FLOAT = 16,
    BOOL_DATETIME = 17,
    BYTEARRAY_UINT16 = 18,
    void_UINT8 = 19,
    void_UINT32 = 20,
    void_BOOL = 21,
    void_UINT8_FLOAT = 22,
    FLOAT_UINT8 = 23,
    UINT16_BYTEARRAY = 24,
    UINT16_BYTEARRAY_BOOL = 25,
    BYTEARRAY_BYTEARRAY = 26,
    void_UINT8_BYTEARRAY = 27,
    BYTEARRAY_UINT32 = 28,
    BYTEARRAY_UINT32_UINT32 = 29,
    void_UINT32_BYTEARRAY = 30,
    BYTEARRAY_UINT8 = 31
} Signature_t;
typedef enum
{
    RPC_GET_DEVICE_IDS = 0,
    RPC_GET_DEVICE_ID = 1,
    RPC_SET_DEVICE_DATE_TIME = 6,
    RPC_GET_DEVICE_DATE_TIME = 7,
    RPC_FACTORY_RESET = 8,
    RPC_POWER_OFF = 9,
    RPC_GET_POWER_STATUS = 11,
    RPC_DIR_LIST_START = 12,
    RPC_DIR_LIST_NEXT_GET = 13,
    RPC_DIR_DELETE = 14,
    RPC_FILE_DELETE = 15,
    RPC_FS_FREE_SPACE_GET = 16,
    RPC_FILE_READ_START = 17,
    RPC_FILE_READ_NEXT = 18,
    RPC_FIND_ME = 20,
    RPC_GET_SOFTWARE_INFO = 21,
    RPC_GET_MODERN_FIRMWARE_ID = 22
} StandartId_t;

typedef enum
{
    RPC_GET_FLAGS = 3001,
    RPC_SET_RH_HEATER_STATE = 3011,

} MeteoId;
typedef enum
{
    RPC_SET_OPERATION_MODE = 2056,
    RPC_GET_OPERATION_MODE = 2057,
    RPC_GET_LIVE_DATA = 2058,
    RPC_GET_SENSORS_PRESENCE = 2060,
    RPC_SET_ALLOW_CHARGING = 2067,
    RPC_SET_ACTIVE_PROBE = 2068,
    RPC_GET_ACTIVE_PROBE = 2069,
    RPC_GET_PROBE_SERIAL = 2088,
    RPC_SET_DEVICE_SETTINGS = 2090,
    RPC_GET_DEVICE_SETTINGS = 2091,
    RPC_SAVE_LIVEDATA = 2092
} eId;
typedef enum
{
    RPC_SUCCESS = 0,
    RPC_UNKNOWN_ID = 1,
    RPC_BAD_STACK = 2,
    RPC_TIMEOUT = 3,
    RPC_STACK_OVERFLOW = 4,
    RPC_UNKNOWN_SIGNATURE = 5,
    RPC_BAD_SIGNATURE = 6,
    RPC_ID_MISSMATCH = 7,
    RPC_COMM_ERROR = 8,
    RPC_BUSY_NO_DATA = 9,
    RPC_PARAM_ERROR_0 = 10,
    RPC_PARAM_ERROR_1 = 11,
    RPC_PARAM_ERROR_2 = 12,
    RPC_PARAM_ERROR_3 = 13,
    RPC_PARAM_ERROR_4 = 14,
    RPC_PARAM_ERROR_5 = 15
} RpcStatus_t;
#pragma pack(push, 1)
typedef struct
{
    uint8_t ver_major;
    uint8_t ver_minor;
} FirmwareId_t;

typedef struct s_OldDeviceId
{
    uint16_t type;
    uint16_t year;
    uint16_t number;
    FirmwareId_t FirmwareId;
} OldDeviceId_t;

typedef struct s_ModernDeviceId
{
    uint16_t type;
    uint16_t year;
    uint16_t number;
    FirmwareId_t FirmwareId;

} ModernDeviceId_t;

#pragma pack(pop)

// ANY ODRED, IN ALL ANOTHER CASES ORDER DOES MATTER
typedef enum e_DeviceType
{
    DEVICE_ECO_BOIL = 0x0000,
    DEVICE_PHOTO_HEAD = 0x0001,
    DEVICE_ECO_BOI2_LUX = 0x0002,
    DEVICE_ECO_BOI_ANE = 0x0003,
    DEVICE_METEO_HEAD = 0x0004,
    DEVICE_EMI_HEAD = 0x0005,
    DEVICE_EKOLOGGER = 11,
    DEVICE_TENZOR_PHOTOHEAD = 40001,
    DEVICE_TENZOR_BOI2_LUX = 40002
} DeviceType_t;

typedef enum
{
    RPC_METEO_IDLE = 1,
    RPC_METEO_LIVE_LIMITED = 2,
    RPC_METEO_LIVE_UNLIMITED = 3
} MeteoMode_t;

typedef union u_SensorPresence
{
    uint8_t byte;
    struct
    {
        uint8_t block_this_probe : 1; // 1 - probe was blocked

        // 1 - present, 0 - not present
        uint8_t probe : 1; //  probe / temperature sensor
        uint8_t rh : 1;    // humidity sensor
        uint8_t p : 1;     // pressure sensor
        uint8_t v : 1;     // Adc / wind velocity sensor
    } bits;
} SensorPresence_t; // each probe has its own SensorPresence

typedef union
{
#pragma pack(push, 1)
    struct
    {
        uint32_t ta_rh : 1;        // bit 0 - no Temperature sensor or Humidity sensor
        uint32_t v : 1;            // bit 1 - no wind velocity sensor
        uint32_t eeprom : 1;       // bit 2 - no eeprom
        uint32_t calibration : 1;  // bit 3 - EEPROM does not have at least one calibration
        uint32_t wdt : 1;          // bit 4 - Wdt reset occured
        uint32_t battery : 1;      // bit 5 - battery voltage went beyond 4.2-2.7v
        uint32_t resistor : 1;     // bit 6 - not used
        uint32_t blackglobe : 1;   // bit 7 - no black sphere
        uint32_t p : 1;            // bit 8 - no pressure sensor
        uint32_t cal_vc : 1;       // bit 9 - calibration error of wind velocity sensor
        uint32_t cal_reserved : 1; // bit 10 - reserved
        uint32_t cal_ta : 1;       // bit 11 - calibration error of Air temperature sensor
        uint32_t cal_rh : 1;       // bit 12 - calibration error of humidity sensor
        uint32_t cal_p : 1;        // bit 13 - calibration error of pressure sensor
        uint32_t cal_tg : 1;       // bit 14 - calibration error of temperature inside black sphere - reserved
    } bv;
#pragma pack(pop)
    uint32_t b;
} MeteoErrors_t;

typedef union u_derivatives
{
    uint32_t dword;
    struct
    {
        int32_t ta : 2;   // 11 - Air temperature is decreasing , 01 - Air temperature is increasing , 00 - Air temperature is stable, 10 - reserved
        int32_t rh : 2;   // 11 - Relative humidity is decreasing , 01 - Relative humidity is increasing , 00 - Relative humidity is stable, 10 - reserved
        int32_t td : 2;   // 11 - Dew point is decreasing , 01 - Dew point is increasing , 00 - Dew point is stable, 10 - reserved
        int32_t tw : 2;   // 11 - wet bulb temperature is decreasing , 01 - wet bulb temperature is increasing , 00 - wet bulb temperature is stable, 10 - reserved
        int32_t u : 2;    // reserved, not used
        int32_t tg : 2;   // 11 - Temperature inside black sphere is decreasing , 01 - Temperature inside black sphere is increasing , 00 - Temperature inside black sphere is stable, 10 - reserved
        int32_t wbgt : 2; // 11 - Wet-Bulb Globe Temperature is decreasing , 01 - Wet-Bulb Globe Temperature is increasing ,
        // 00 - Wet-Bulb Globe Temperature is stable, 10 - reserved
        int32_t wbgts : 2; // 11 - is decreasing , 01 - is increasing , 00 - is stable, 10 - reserved
        int32_t tr : 2;    // 11 - is decreasing , 01 - is increasing , 00 - is stable, 10 - reserved
        int32_t w : 2;     // 11 - is decreasing , 01 - is increasing , 00 - is stable, 10 - reserved
        int32_t p : 2;     // 11 - pressure is decreasing , 01 - pressure is increasing , 00 - pressure is stable, 10 - reserved
        int32_t to : 2;    // 11 - Resulting temperature is decreasing , 01 - Resulting temperature is increasing , 00 - Resulting temperature is stable, 10 - reserved
        int32_t reserved_area : 8;
    } bits;
} derivatives_t;

#pragma pack(push, 1)
typedef struct
{
    // timestap in ms
    int64_t ts;
    struct
    {
        // Flag indication (1 - is error)
        union
        {
            uint32_t dwordval;
            struct
            {
                uint32_t ta : 1;             // 1 - no temp sensor
                uint32_t rh : 1;             // 1 - no humidity sensor
                uint32_t td : 1;             // 1 - error when calculating td
                uint32_t tw : 1;             // 1 - error when calculating tw
                uint32_t u : 1;              // 1 - no wind velocity sensor
                uint32_t tg : 1;             // 1 - no black sphere
                uint32_t wbgt : 1;           // 1 - error when calculating wbgt index
                uint32_t wbgts : 1;          // 1 - error when calculating wbgts index
                uint32_t tr : 1;             // 1 - error when calculating tr
                uint32_t w : 1;              // 1 - error when calculating w
                uint32_t p : 1;              // 1 - no pressure sensor
                uint32_t to : 1;             // 1 - error when calculating to
                uint32_t reserved_area : 15; // reserved for future use
                uint32_t rh_heater : 1;      // 1 - humidity sensor heater is on, all indications may be distorted
            } bitval;
        } state;
        // timer (in seconds) of wind velocity sensor heating:
        // 255 in RPC_METEO_IDLE, RPC_METEO_LIMITED modes
        // 0..10 in RPC_METEO_UNLIMITED mode indicates
        // number of seconds left until the end of the wind
        // velocity sensor warm-up
        uint8_t heater_timer;
        // timer (in seconds) of air temperature averaging (reserved)
        uint32_t ta_mean_timer;
        // timer (in seconds) of wind speed averaging (reserved)
        uint32_t u_mean_timer;
    } flags;
    struct
    {
        // Air temperature
        float ta;
        // Relative humidity
        float rh;
        // Dew point
        float td;
        // wet bulb temperature
        float tw;
        // Wind velocity
        float u;
        // Temperature inside black sphere
        float tg;
        // Wet-Bulb Globe Temperature
        float wbgt;
        // Wet-Bulb Globe Temperature taking into account solar load
        float wbgts;
        // radiation temperature at blowing speeds less than 1 m/s
        float tr;
        // thermal radiation density
        float w;
        // Pressure
        float p;
        // Resulting temperature
        float to;
        // reserved
        float reserved1;
        float reserved2;
    } data;
    // Indication flags
    derivatives_t derivatives;
} MeteoLiveData_t;

typedef struct
{
    uint32_t old_value; // reserved
    uint32_t new_value;
    uint64_t change_date; // reserved
} CrcInfo_t;

typedef struct
{
    char software_name[64];
    char software_id[32];
    CrcInfo_t FirmwareCrc;    // reserved
    CrcInfo_t CalibrationCrc; // Calibration crc
    uint8_t reserved[64];

} SoftwareInfo_t;

#pragma pack(1)
typedef struct
{
    uint16_t min_code; // minimal state
    uint16_t cur_code; // current state
    uint16_t max_code; // max state
    union
    {
        uint8_t byteval;
        struct
        {
            uint8_t battery_attached : 1;
            uint8_t aux_power : 1;
            uint8_t reserved : 1;
            uint8_t charging : 1;
            uint8_t reserved2 : 3;
            uint8_t fast_charging : 1;
        } bitval;
    } flags;
} PowerStatus_t;

typedef union
{
    uint32_t dword;
    struct
    {
        uint32_t logging_enabled : 1;   // logger 1 - on | 0 - off | default - 0
        uint32_t logging_interval : 28; // logger interval in ms from 1000 to 86400000 | default - 5000
        uint32_t display_sleep : 1;     // 1 - Sets display off timeout to 10 seconds | 0 - display is always on | default - 0
        uint32_t heater_enabled_1 : 1;  // 1 - Force Heater / Adc to be on after device restart on probe 1 | default - 0
        uint32_t heater_enabled_2 : 1;  // 1 - Force Heater / Adc to be on after device restart on probe 2 | default - 0
    } bits;
} Settings_t;

typedef struct
{
    uint16_t result;
    uint32_t file_size;
    int64_t ts;
    uint8_t f_attrs;
    uint8_t fname[30];
} FsItem_t;
typedef struct
{
    uint16_t result;
    uint32_t chunks;
} FsItemReadRequest_t;

typedef enum e_FsMemoryUnits
{
    BYTES = 0,
    KBYTES = 1,
    MBYTES = 2,
    GBYTES = 3
} FsMemoryUnits_t;

typedef struct s_FsMemSpaceInfo
{
    uint16_t count;
    uint16_t frac;
    uint8_t unit;
    uint8_t dummy;
} FsMemSpaceInfo_t;

typedef struct s_FsInfo
{
    uint16_t result;
    FsMemSpaceInfo_t total;
    FsMemSpaceInfo_t free;
} FsInfo_t;

typedef struct
{
	int64_t milis; // ts of a file
	uint32_t node_count; // node count in one file, each node contains MeteoLiveData_t[2] struct
}node_date_info_t;

typedef struct
{
    uint32_t number;
    uint16_t year;
    bool invalid;
} ProbeSerial_t;
#pragma pack(pop)

#endif
