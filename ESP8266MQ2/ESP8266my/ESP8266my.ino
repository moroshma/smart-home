//------------------------------------------------------------------------------------------------------------------------------------
//управление скважиной v.1.2 (добавлено: ведение логов, mqtt)
//основной канал автора на ютубе  "НеОбзор58"            https://www.youtube.com/channel/UC6mMZ4GGXMdpSGEy-j1EnxQ
//второй   канал автора на ютубе  "Доступная автоматика" https://www.youtube.com/channel/UCxfwRP66zE4zwn6lgvS6wQg
//сайт и страница проекта                                http://www.simple-automation.ru/publ/proekty/kontroller_dlja_skvazhiny_na_esp8266_nodemcu_lua/kontroller-dlja-skvazhiny-na-esp8266-nodemcu-v3-lua/19-1-0-15
//
//     желающим поддержать автора: карта Сбера 676280489001157828 получатель Григорий Валерьевич Ц.
//
//------------------------------------------------------------------------------------------------------------------------------------

#define USE_LOG
//#define USE_DHT

//пины на датчики
const byte  pinOneWire PROGMEM = D1;

//const byte pinLev1 PROGMEM = D7;
//const byte pinLev2 PROGMEM = D8;
//пины на управление реле
const byte swt1_pin PROGMEM = D0; // Основной насос
const byte swt2_pin PROGMEM = D2; // Дренажный насос
const byte swt3_pin PROGMEM = D5; // Клапан вода на баню
const byte swt4_pin PROGMEM = D6; // Клапан слив на баню
//файлы настроек
const String SensorConfFile = "sensor.cfg";
const String NameMsgFile = "message.cfg";
const String NameSettingsFile = "settings.cfg";


const byte pinBuiltinLed PROGMEM = D4;

extern "C" {
#include <sntp.h>
}
#include "Date.h";
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <EEPROM.h>
#include <FS.h>
#include <ArduinoJson.h>

#ifdef USE_DHT
#include <DHT.h>
int8_t t_dht, h_dht;
const byte  pinDHT PROGMEM = D3;
#endif

#define ONE_WIRE_BUS pinOneWire
#define TEMPERATURE_PRECISION 9
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

ESP8266WebServer server(80);
WiFiClient espClient;

#ifdef USE_DHT
DHT dht(pinDHT, DHT11);
uint32_t DHT_control;
#endif
//----MQTT----------------------------------------------------------------------------------------------------------------
//1. бесплатный mqtt сервер после регистрации www.cloudmqtt.com
//2. после регистрации нужно добавить двух пользователей, одного для есп, дрогого для телеф
//3. клиент для андроид в гугл плей (IoT MQTT Dashboard) https://play.google.com/store/apps/details?id=com.thn.iotmqttdashboard&hl=ru
//4. клиенту нужно разрешить/подписать на temp/# (temp/t0, temp/t1....) и добавить значения в subscribe
//5. клиенту нужно разрешить/подписать на swt/# (swt/0, swt/1,swt/3,swt/4) и добавить движки в publish

#include <PubSubClient.h>// MQTT library

PubSubClient mqttClient(espClient);
bool useMQTT;
String mqttServer, mqttUser, mqttUserPassword, mqttClientId;
uint16_t mqttServerPort;
uint16_t mqttReconnectSec;
uint32_t nextTimeMQTT, mqtt_control;

//---------------------------------------------------
bool resumeState;
const String NameResumeStateFile = "resumeState.cfg";
//---------------------------------------------------настройки Wi-Fi------------------------
const char* const ssidAP PROGMEM = "ESP_Well";
const char* const passwordAP PROGMEM = "Pa$$w0rd";

bool ApMode, AccessMode;
String AccessLogin, AccessPassword;
String ssid, password, domain;
uint8_t ip1, ip2, ip3, ip4;
uint8_t ms1, ms2, ms3, ms4;
uint8_t gt1, gt2, gt3, gt4;
uint8_t dn1, dn2, dn3, dn4;
byte arduino_mac[] = { 0xDE, 0xEE, 0xAA, 0xEE, 0xFD, 0xDD };

//--------------------------------------------------разные константы и переменные --------
String NameProg;//для с
const byte maxStrParamLength = 32;
const char configSign[4] = { '#', 'G', 'R', 'S' };
char PerevodStr = 0x0D;
char VozvrStr = 0x0A;
String str_info;
uint32_t Other_control, t_control;

bool writeSysLog, writeSenseLog;
bool systemStarted;
const String NameSysLogFile = "system.log";
const String NameMesureLogFile = "mesure.log";
uint32_t logFileSize;//размер файла лога (файлов будет четыре system.log, mesure.log, кода будет превышен размер произойдет
// копирование в system01.log и mesure01.log, а исходные файлы начнутся сначала)
uint16_t log_t;//колич минут через котор пишется в лог температура
uint32_t t_control_log_t;//таймер на лог по температуре

//-------------------------------------------------датчик температуры DS18B20-------------
const uint8_t NSenseMax = 4;
uint8_t NSenseFact;
byte insideThermometer[NSenseMax][8];
float tempC[NSenseMax], tempC_now[NSenseMax], tempC_mqtt[NSenseMax];
int8_t t[NSenseMax];
String tNameSens[NSenseMax];
uint8_t error_read_ds_Max;//количество ошибок (подряд) при опросе
uint16_t t_msec_get_ds;//интервал опроса датчиков, Мсек
uint8_t Zaderj, jamp_t;
uint16_t error_read_ds[NSenseMax], error_read_ds_all, error_read_correct_ds[NSenseMax], error_read_correct_ds_all;
char chGrad;
String stGrad;


//------------------------------------------------исполнительные устройства--------------
bool autoMode;
bool swt1, swt2, swt3, swt4;
bool prev_swt1, prev_swt2, prev_swt3, prev_swt4;
bool relay1Level, relay2Level, relay3Level, relay4Level;
bool now_relay1, now_relay2, now_relay3, now_relay4;//настоящее состояние реле

//--------------------------общая структура для насоса и помпы---------------------------
struct prerPump {
  bool    Avail;
  uint8_t PrerPumpHourSt;
  uint8_t PrerPumpHourEnd;
  uint8_t PrerPumpMinSt;
  uint8_t PrerPumpMinEnd;
  uint32_t PrerPumpStUnx;
  uint32_t PrerPumpEndUnx;
};
//-----------------------------------WaterPump---водяной насос---------------------------
String str_t_working_WaterPump, str_t_next_start_WaterPump;
uint32_t t_work_WaterPump, t_WaterPump, t_pow_on_WaterPump, t_pow_off_WaterPump, t_next_start_WaterPump;
uint8_t WaterPumpOnHour, WaterPumpOnMin, WaterPumpOnSec, WaterPumpOffHour, WaterPumpOffMin, WaterPumpOffSec, WaterPumpHour, WaterPumpMin, WaterPumpSec, TWaterPumpContr, NsenseWaterPumpContr;
uint32_t WaterPumpWorkTime, WaterPumpStopTime, WaterPumpTime;
float TWaterPumpContr_now;

uint8_t NsenseWaterPump;

//таймер на включение WaterPump
bool TimerWaterPumpAvailSt;
int8_t TimerWaterPumpDaySt, TimerWaterPumpMonthSt, TimerWaterPumpHourSt, TimerWaterPumpMinSt, TimerWaterPumpSecSt;
int16_t TimerWaterPumpYearSt;
uint32_t TimerWaterPumpStUnx;

//таймер на включение WaterPump
bool TimerWaterPumpAvailEnd;
int8_t TimerWaterPumpDayEnd, TimerWaterPumpMonthEnd, TimerWaterPumpHourEnd, TimerWaterPumpMinEnd, TimerWaterPumpSecEnd;
int16_t TimerWaterPumpYearEnd;
uint32_t TimerWaterPumpEndUnx;
const uint8_t NomPrerWaterPumpAll = 5; //количество остановов водяного насоса
prerPump PrerWaterPump[NomPrerWaterPumpAll];

//-------------------------------------DrainagePump---помпа для откачки воды-------------
String str_t_working_DrainagePump, str_t_next_start_DrainagePump;
uint32_t t_work_DrainagePump, t_DrainagePump, t_pow_on_DrainagePump, t_pow_off_DrainagePump, t_next_start_DrainagePump;
uint8_t DrainagePumpOnHour, DrainagePumpOnMin, DrainagePumpOnSec, DrainagePumpOffHour, DrainagePumpOffMin, DrainagePumpOffSec, DrainagePumpHour, DrainagePumpMin, DrainagePumpSec, TDrainagePumpContr, NsenseDrainagePumpContr;
uint32_t DrainagePumpWorkTime, DrainagePumpStopTime, DrainagePumpTime;
float TDrainagePumpContr_now;
uint8_t NsenseDrainagePump;

//таймер на включение DrainagePump
bool TimerDrainagePumpAvailSt;
int8_t TimerDrainagePumpDaySt, TimerDrainagePumpMonthSt, TimerDrainagePumpHourSt, TimerDrainagePumpMinSt, TimerDrainagePumpSecSt;
int16_t TimerDrainagePumpYearSt;
uint32_t TimerDrainagePumpStUnx;

//таймер на включение DrainagePump
bool TimerDrainagePumpAvailEnd;
int8_t TimerDrainagePumpDayEnd, TimerDrainagePumpMonthEnd, TimerDrainagePumpHourEnd, TimerDrainagePumpMinEnd, TimerDrainagePumpSecEnd;
int16_t TimerDrainagePumpYearEnd;
uint32_t TimerDrainagePumpEndUnx;
const uint8_t NomPrerDrainagePumpAll = 0; //количество остановов помпы для откачки
prerPump PrerDrainagePump[NomPrerDrainagePumpAll];

String strtworkBanyWater, strtworkBanySliv;

//-------------------поплавки---------------------------------------------------------------
bool lev1, lev2;//настоящее состояние датчиков уровня воды
bool prev_lev1, prev_lev2;//предыдущее состояние датчиков уровня воды
uint32_t t_lev1_on, t_lev2_on; //время срабатывания датчиков (поплавок всплыл / поднялся)
uint16_t over_t_lev1_on, over_t_lev2_on; //период в сек после срабатывания датчиков (поплавок всплыл / поднялся) до включения помпы
uint16_t over_t_lev1_off, over_t_lev2_off; //период в сек после срабатывания датчиков (поплавок стал на место / опустился) до выключения помпы

uint32_t t_lev1_off, t_lev2_off; //время срабатывания датчиков (поплавок стал на место / опустился)
uint32_t t_OnLevel_1, t_OnLevel_2;
uint32_t t_OffLevel_1, t_OffLevel_2;
uint16_t U_lev1, U_lev2, U_lev12, U_delta; //вых ацп
bool errA0;
//------------------------------------------------------------работа со временем-------------
String TimeOn;//прошло времени с момента включения контроллера
uint32_t startTime, startMs, nextTime;
String ntpServer1, ntpServer2, ntpServer3;
uint32_t updateInterval;
int8_t timeZone;
const char* const strNever PROGMEM = "NoNTP";
const char* const defNtpServer1 PROGMEM = "pool.ntp.org";
const char* const defNtpServer2 PROGMEM = "ntp1.stratum1.ru";
const char* const defNtpServer3 PROGMEM = "ntp1.vniiftri.ru";

const uint32_t defUpdateInterval = 3600; // 1 hour
const int8_t defTimeZone = 3; // GMT+3 Moscow TZ
String timeStr;
const uint32_t noTime = (uint32_t)0;
const char* const noDef = '\0';

bool ntpUpd, setTimeAccompl;
int8_t now_hour, now_min, now_sec, now_day, now_month;
uint8_t now_wd;
int16_t now_year;
uint32_t now_timeUnx;
uint8_t countFailNtp;
uint8_t countFailMqtt;
//-----------------------------------------------------------------------------------------------------------------------
void addStringToLog(String logFile, String timeDate, String logMessage, String openMode = "a") {

  if (((writeSysLog) && (logFile == NameSysLogFile)) || ((writeSenseLog) && (logFile == NameMesureLogFile))) {
    if (setTimeAccompl == 1) {
      Serial.print("Try write log to " + logFile);
      File f = SPIFFS.open("/" + logFile, openMode.c_str());

      if (!f)  {
        Serial.println(F("....failed"));
      }
      else  {

        Serial.print(F("(")); Serial.print(f.size()); Serial.print(F(")")); Serial.print(F("Open mode ")); Serial.print(openMode);
        if (openMode == "w") {
          Serial.println(F("....open Ok"));
        }
        else {
          if (f.size() > logFileSize * 1024) {
            f.close();
            String logFileRez = logFile.substring(0, logFile.length() - 4) + "01.log";

            if (SPIFFS.exists("/" + logFileRez))  {
              SPIFFS.remove("/" + logFileRez);
              Serial.println(F("....old removed"));
            }
            if (!SPIFFS.rename("/" + logFile, "/" + logFileRez))  {
              Serial.println(F("....rename failed"));
              return;
            }
            else {
              Serial.println(F("....rename Ok"));
              addStringToLog(logFile, timeDate, logMessage, "w");
            }
          }
        }

        Serial.println(F("..... Writing log file "));
        String strM;
        strM = timeDate + " " + logMessage;
        Serial.print(strM);
        f.println(strM);
        f.close();
        Serial.println(F(" ....done."));
      }
    }
  }
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void MydigitalWrite(int pin, bool state) {
  String messLog;
  if (digitalRead(pin) != state) {
    digitalWrite(pin, state);

    if (pin == swt1_pin ) {
      //const byte swt1_pin PROGMEM = D0; // Основной насос
      if (relay1Level == 0) state = !state;
      if (state == 1) messLog = F("ON Water pump");
      else messLog = F("OFF Water pump");
      addStringToLog(NameSysLogFile, timeDateToStr(now_timeUnx), messLog);
    }
    if (pin == swt2_pin ) {
      //const byte swt2_pin PROGMEM = D2; // Дренажный насос
      if (relay2Level == 0) state = !state;
      if (state == 1) messLog = F("ON Drainage pump");
      else messLog = F("OFF Drainage pump");
      addStringToLog(NameSysLogFile, timeDateToStr(now_timeUnx), messLog);
    }

  }
}
//--------------------------------------------------------------
String quoteEscape(const String& str)
{
  String result = "";
  int start = 0, pos;

  while (start < str.length()) {
    pos = str.indexOf('"', start);
    if (pos != -1) {
      result += str.substring(start, pos) + F("&quot;");
      start = pos + 1;
    } else {
      result += str.substring(start);
      break;
    }
  }
  return result;
}
//---------------------------------------------
bool readConfig()
{
  uint16_t offset = 0;
  Serial.println(F("Reading config from EEPROM"));
  for (byte i = 0; i < sizeof(configSign); i++)
  {
    if (EEPROM.read(offset + i) != configSign[i])
      return false;
  }
  offset += sizeof(configSign);
  offset = readEEPROMString(offset, ssid);
  offset = readEEPROMString(offset, password);
  offset = readEEPROMString(offset, AccessLogin);
  offset = readEEPROMString(offset, AccessPassword);
  offset = readEEPROMString(offset, NameProg);

  EEPROM.get(offset, ApMode); offset += sizeof(ApMode);
  EEPROM.get(offset, AccessMode); offset += sizeof(AccessMode);

  EEPROM.get(offset, ip1);       offset += sizeof(ip1);
  EEPROM.get(offset, ip2);       offset += sizeof(ip2);
  EEPROM.get(offset, ip3);       offset += sizeof(ip3);
  EEPROM.get(offset, ip4);       offset += sizeof(ip4);

  EEPROM.get(offset, ms1);       offset += sizeof(ms1);
  EEPROM.get(offset, ms2);       offset += sizeof(ms2);
  EEPROM.get(offset, ms3);       offset += sizeof(ms3);
  EEPROM.get(offset, ms4);       offset += sizeof(ms4);

  EEPROM.get(offset, gt1);       offset += sizeof(gt1);
  EEPROM.get(offset, gt2);       offset += sizeof(gt2);
  EEPROM.get(offset, gt3);       offset += sizeof(gt3);
  EEPROM.get(offset, gt4);       offset += sizeof(gt4);

  EEPROM.get(offset, dn1);       offset += sizeof(dn1);
  EEPROM.get(offset, dn2);       offset += sizeof(dn2);
  EEPROM.get(offset, dn3);       offset += sizeof(dn3);
  EEPROM.get(offset, dn4);       offset += sizeof(dn4);

  return true;
}
//-------------------------------------
void writeConfig()
{
  uint16_t offset = 0;

  Serial.println(F("Writing config to EEPROM"));
  EEPROM.put(offset, configSign);

  offset += sizeof(configSign);
  offset = writeEEPROMString(offset, ssid);
  offset = writeEEPROMString(offset, password);
  offset = writeEEPROMString(offset, AccessLogin);
  offset = writeEEPROMString(offset, AccessPassword);
  offset = writeEEPROMString(offset, NameProg);

  EEPROM.put(offset, ApMode); offset += sizeof(ApMode);
  EEPROM.put(offset, AccessMode); offset += sizeof(AccessMode);

  EEPROM.put(offset, ip1); offset += sizeof(ip1);
  EEPROM.put(offset, ip2); offset += sizeof(ip2);
  EEPROM.put(offset, ip3); offset += sizeof(ip3);
  EEPROM.put(offset, ip4); offset += sizeof(ip4);

  EEPROM.put(offset, ms1);       offset += sizeof(ms1);
  EEPROM.put(offset, ms2);       offset += sizeof(ms2);
  EEPROM.put(offset, ms3);       offset += sizeof(ms3);
  EEPROM.put(offset, ms4);       offset += sizeof(ms4);

  EEPROM.put(offset, gt1);       offset += sizeof(gt1);
  EEPROM.put(offset, gt2);       offset += sizeof(gt2);
  EEPROM.put(offset, gt3);       offset += sizeof(gt3);
  EEPROM.put(offset, gt4);       offset += sizeof(gt4);

  EEPROM.put(offset, dn1);       offset += sizeof(dn1);
  EEPROM.put(offset, dn2);       offset += sizeof(dn2);
  EEPROM.put(offset, dn3);       offset += sizeof(dn3);
  EEPROM.put(offset, dn4);       offset += sizeof(dn4);

  EEPROM.commit();
}
//-----------------------------------------------------------------------
uint16_t readEEPROMString(uint16_t offset, String& str)
{
  char buffer[maxStrParamLength + 1];
  buffer[maxStrParamLength] = 0;
  for (byte i = 0; i < maxStrParamLength; i++) {
    if (! (buffer[i] = EEPROM.read(offset + i)))
      break;
  }
  str = String(buffer);
  return offset + maxStrParamLength;
}
//-----------------------------------------------------------------------
uint16_t writeEEPROMString(uint16_t offset, const String& str) {
  for (byte i = 0; i < maxStrParamLength; i++) {
    if (i < str.length())
      EEPROM.write(offset + i, str[i]);
    else
      EEPROM.write(offset + i, 0);
  }
  return offset + maxStrParamLength;
}

//---------------------------------------------------WiFi setup functions--------------------------------------------------
bool setupWiFiAsStation() {
  const uint32_t timeout = 40000;
  uint32_t maxtime = millis() + timeout;

  Serial.println(F("Connecting to "));
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);

  if (ssid.length() == 0) return false;

  WiFi.begin(ssid.c_str(), password.c_str());

  if ((ip1 + ip2 + ip3 + ip4) != 0) {
    IPAddress ip(ip1, ip2, ip3, ip4);
    IPAddress subnet(ms1, ms2, ms4, ms4);
    IPAddress dns(dn1, dn2, dn3, dn4);
    IPAddress gateway(gt1, gt2, gt3, gt4);
    WiFi.config(ip, gateway, subnet, dns);
  }
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(pinBuiltinLed, LOW);
    delay(500);
    digitalWrite(pinBuiltinLed, HIGH);
    Serial.print(".");
    if (millis() >= maxtime) {
      Serial.println();
      Serial.println(ssid);
      //Serial.println(password);
      Serial.println(F(" fail!"));
      return false;
    }
  }
  Serial.println();
  Serial.println(F("WiFi connected"));
  Serial.print(F("IP address: "));
  Serial.println(WiFi.localIP());

  return true;
}
//----------------------------------------------------------------
void setupWiFiAsAP() {
  Serial.print(F("Configuring access point "));
  Serial.println(ssidAP);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssidAP, passwordAP);

  Serial.print(F("IP address: "));
  Serial.println(WiFi.softAPIP());
}
//----------------------------------------------------------------
void setupWiFi() {
  if (ApMode || (! setupWiFiAsStation())) setupWiFiAsAP();

  server.begin();
  Serial.println(F("HTTP server started (use '/update' url to OTA update)"));
}
//------------------------------------
String AddNull (String StrForAdd)
{
  if (StrForAdd.length() == 1)
    return "0" + StrForAdd;
  if (StrForAdd.length() == 0)
    return "00" + StrForAdd;

  return StrForAdd;
}
//--------------------------------------------------------------------------------------

#include "handles.h"
#include "h_switch.h"
#include "Ctr_WaterPump.h"
#include "Ctr_DrainagePump.h"
#include "upg_spiffs.h"
#include "Control_other.h"
//---------------------------------------------------------------------------------------
void openSettingsFile () {
  if (!SPIFFS.exists("/" + NameSettingsFile))
  { //файл настроек не существует
  } else {
    Serial.println(F("Открываем ")); Serial.println(NameSettingsFile);
    File f = SPIFFS.open("/" + NameSettingsFile, "r");
    if (!f) {
      Serial.println(F("..не получилось открыть файл"));
    } else {
      Serial.println(F("..читаем файл"));
      String s;
      uint16_t st_start, st_end, st_len;
      for (uint8_t i = 0; i < 20; i++)  {
        s = f.readStringUntil(PerevodStr); s.replace(F("\n"), "");
        //s.remove(s.length() - 1);
        st_start = s.indexOf("{"); st_end = s.indexOf("}") + 1;

        if (s.indexOf(F("END")) == -1) {
          if ((st_start != -1) && (st_end != -1)) {
            s = s.substring(st_start, st_end); st_len = s.length();
#ifdef USE_LOG
            Serial.println(s);
#endif
            DynamicJsonBuffer jsonBuffer;   //Memory pool
            JsonObject& root = jsonBuffer.parseObject(s);
            if (root.success()) {
              int8_t hh, mm, ss;
              uint8_t wd;
              int8_t d, m;
              int16_t y;

              if (root["Vol"] == 0) {
                DrainagePumpOnHour = root["DrainagePumpOnTime"][0];
                DrainagePumpOnMin = root["DrainagePumpOnTime"][1];
                DrainagePumpOnSec = root["DrainagePumpOnTime"][2];
                DrainagePumpOffHour = root["DrainagePumpOffTime"][0];
                DrainagePumpOffMin = root["DrainagePumpOffTime"][1];
                DrainagePumpOffSec = root["DrainagePumpOffTime"][2];
                DrainagePumpHour = root["DrainagePumpTime"][0];
                DrainagePumpMin = root["DrainagePumpTime"][1];
                DrainagePumpSec = root["DrainagePumpTime"][2];
                TDrainagePumpContr = root["TDrainagePumpContr"];
                NsenseDrainagePumpContr = root["NsenseDrainagePumpContr"];
                for (byte i = 0; i < NomPrerDrainagePumpAll; i++) {
                  PrerDrainagePump[i].Avail = root["Avail" + String(i)];
                  PrerDrainagePump[i].PrerPumpStUnx = root["PrerDrainagePumpStUnx" + String(i)];
                  PrerDrainagePump[i].PrerPumpEndUnx = root["PrerDrainagePumpEndUnx" + String(i)];
                  parseUnixTime(PrerDrainagePump[i].PrerPumpStUnx, hh, mm, ss, wd, d, m, y);
                  PrerDrainagePump[i].PrerPumpHourSt = hh;
                  PrerDrainagePump[i].PrerPumpMinSt = mm;
                  parseUnixTime(PrerDrainagePump[i].PrerPumpEndUnx, hh, mm, ss, wd, d, m, y);
                  PrerDrainagePump[i].PrerPumpHourEnd = hh;
                  PrerDrainagePump[i].PrerPumpMinEnd = mm;
                }
                TimerDrainagePumpAvailSt = root["TimerDrainagePumpAvailSt"];
                TimerDrainagePumpAvailEnd = root["TimerDrainagePumpAvailEnd"];
                TimerDrainagePumpStUnx = root["TimerDrainagePumpStUnx"];
                TimerDrainagePumpEndUnx = root["TimerDrainagePumpEndUnx"];

                parseUnixTime(TimerDrainagePumpStUnx, TimerDrainagePumpHourSt, TimerDrainagePumpMinSt, TimerDrainagePumpSecSt, wd, TimerDrainagePumpDaySt, TimerDrainagePumpMonthSt, TimerDrainagePumpYearSt);
                parseUnixTime(TimerDrainagePumpEndUnx, TimerDrainagePumpHourEnd, TimerDrainagePumpMinEnd, TimerDrainagePumpSecEnd, wd, TimerDrainagePumpDayEnd, TimerDrainagePumpMonthEnd, TimerDrainagePumpYearEnd);

                over_t_lev1_on = root["over_t_lev1_on"];
                over_t_lev2_on = root["over_t_lev2_on"];
                over_t_lev1_off = root["over_t_lev1_off"];
                over_t_lev2_off = root["over_t_lev2_off"];
              }

              else if (root["Vol"] == 1) {
                //Serial.println("Vol1");
                WaterPumpOnHour = root["WaterPumpOnTime"][0];
                WaterPumpOnMin = root["WaterPumpOnTime"][1];
                WaterPumpOnSec = root["WaterPumpOnTime"][2];
                WaterPumpOffHour = root["WaterPumpOffTime"][0];
                WaterPumpOffMin = root["WaterPumpOffTime"][1];
                WaterPumpOffSec = root["WaterPumpOffTime"][2];
                WaterPumpHour = root["WaterPumpTime"][0];
                WaterPumpMin = root["WaterPumpTime"][1];
                WaterPumpSec = root["WaterPumpTime"][2];
                TWaterPumpContr = root["TWaterPumpContr"];
                NsenseWaterPumpContr = root["NsenseWaterPumpContr"];

                for (byte i = 0; i < NomPrerWaterPumpAll; i++) {
                  PrerWaterPump[i].Avail = root["Avail" + String(i)];
                  PrerWaterPump[i].PrerPumpStUnx = root["PrerWaterPumpStUnx" + String(i)];
                  PrerWaterPump[i].PrerPumpEndUnx = root["PrerWaterPumpEndUnx" + String(i)];
                  parseUnixTime(PrerWaterPump[i].PrerPumpStUnx, hh, mm, ss, wd, d, m, y);
                  PrerWaterPump[i].PrerPumpHourSt = hh;
                  PrerWaterPump[i].PrerPumpMinSt = mm;
                  parseUnixTime(PrerWaterPump[i].PrerPumpEndUnx, hh, mm, ss, wd, d, m, y);
                  PrerWaterPump[i].PrerPumpHourEnd = hh;
                  PrerWaterPump[i].PrerPumpMinEnd = mm;
                }
                TimerWaterPumpAvailSt = root["TimerWaterPumpAvailSt"];
                TimerWaterPumpAvailEnd = root["TimerWaterPumpAvailEnd"];
                TimerWaterPumpStUnx = root["TimerWaterPumpStUnx"];
                TimerWaterPumpEndUnx = root["TimerWaterPumpEndUnx"];

                parseUnixTime(TimerWaterPumpStUnx, TimerWaterPumpHourSt, TimerWaterPumpMinSt, TimerWaterPumpSecSt, wd, TimerWaterPumpDaySt, TimerWaterPumpMonthSt, TimerWaterPumpYearSt);
                parseUnixTime(TimerWaterPumpEndUnx, TimerWaterPumpHourEnd, TimerWaterPumpMinEnd, TimerWaterPumpSecEnd, wd, TimerWaterPumpDayEnd, TimerWaterPumpMonthEnd, TimerWaterPumpYearEnd);
              }
              /*else if (root["Vol"] == 2) {
                Serial.println("Vol2");
                  PercOtb = root["PercOtb"];
                  TimeOtbPeriod = root["TimeOtbPeriod"];
                  TstOtb = root["TstOtb"];
                  TendOtb = root["TendOtb"];
                  NsenseOtbContr = root["NsenseOtbContr"];
                }*/
              else if (root["Vol"] == 3) {
                Serial.println("Vol3");

                resumeState = root["resumeState"];
                relay1Level = root["relayLevel"][0];
                relay2Level = root["relayLevel"][1];
                relay3Level = root["relayLevel"][2];
                relay4Level = root["relayLevel"][3];

                U_lev1 = root["U_lev1"];
                U_lev2 = root["U_lev2"];
                U_lev12 = root["U_lev12"];
                U_delta = root["U_delta"];

                const char* ntpServer = root["ntpServer"][0]; if (ntpServer != noDef) ntpServer1 = String(ntpServer);
                ntpServer = root["ntpServer"][1]; if (ntpServer != noDef) ntpServer2 = String(ntpServer);
                ntpServer = root["ntpServer"][2]; if (ntpServer != noDef) ntpServer3 = String(ntpServer);
                updateInterval = root["updateInterval"];
                timeZone = root["timeZone"];
                ntpUpd = root["ntpUpd"];

                Zaderj = root["Zaderj"];
                jamp_t = root["jamp_t"];

                writeSysLog = root["writeSysLog"];
                writeSenseLog = root["writeSenseLog"];
                log_t = root["log_t"];
                logFileSize = root["logFileSize"];

                error_read_ds_Max = root["error_read_ds_Max"];
                t_msec_get_ds = root["t_msec_get_ds"];

                useMQTT = root["useMQTT"];
                const char* mqttS = root["mqttServer"]; if (mqttS != noDef) mqttServer = String(mqttS);
                mqttServerPort = root["mqttServerPort"];
                mqttReconnectSec = root["mqttReconnectSec"];

                const char* mqttU = root["mqttUser"]; if (mqttU != noDef) mqttUser = String(mqttU);
                const char* mqttUP = root["mqttUserPassword"]; if (mqttUP != noDef) mqttUserPassword = String(mqttUP);
                const char* mqttC = root["mqttClientId"]; if (mqttC != noDef) mqttClientId = String(mqttC);

              }
            } else {
              Serial.println(F("..Проблемы с парсингом файла"));
            }
          } else {
            Serial.println(F("..Не форматная строка в файле"));
          }
        } else { //нашли слово END в конце файла
          Serial.println(F("..дошли до конца файла"));
          break;
        }
      }
      f.close();
    }
  }
}
//------------------------------------------------------
void openSensorConfFile() {
  if (!SPIFFS.exists("/" + SensorConfFile))
  { //файл настроек не существует

  }
  else {
    Serial.println(F("Открываем ")); Serial.println(SensorConfFile);
    File f = SPIFFS.open("/" + SensorConfFile, "r");
    if (!f) {
      Serial.println(F(" не получилось открыть файл адресов датчиков"));
    }
    else {
      Serial.println(F(" читаем файл адресов датчиков "));
      String s;
      uint8_t st_start, st_end, st_len;
      for (uint8_t i = 0; i <= NSenseMax; i++)  {
        s = f.readStringUntil(PerevodStr); s.replace(F("\n"), "");
        st_start = s.indexOf(F("{")); st_end = s.indexOf(F("}")) + 1;
        Serial.println(s);
        if (s.indexOf(F("END")) == -1) {
          Serial.println("есть");
          if ((st_start != -1) && (st_end != -1)) {
            s = s.substring(st_start, st_end); st_len = s.length();
            DynamicJsonBuffer jsonBuffer;   //Memory pool
            JsonObject& root = jsonBuffer.parseObject(s);
            if (root.success()) {
              t[i] = root["t"];
              for (uint8_t k = 0; k < 8; k++) {
                insideThermometer[i][k] = root["frame"][k];
              }
              const char* tNameS = root["tNameSens"]; if (tNameS != noDef) tNameSens[i] = String(tNameS);
            }
            else {
              Serial.println(F("Проблемы с парсингом (адресов датчиков)"));
            }
          }
          else {
            Serial.println(F("Не форматная строка (адресов датчиков)"));
          }
        }
        else { //нашли слово END в конце файла
          NSenseFact = i;
          Serial.println(F("Дошли до конца файла адресов датчиков"));
          Serial.print(F("Всего датчиков в файле адресов = ")); Serial.println(NSenseFact);
          break;
        }
      }
      f.close();
    }
  }
}
//------------------------------------------------------
void openResumeStateFile() {
  if (resumeState == 1) {
    if (!SPIFFS.exists("/" + NameResumeStateFile))
    { //файл настроек не существует
    }
    else {
      Serial.println(F("Открываем ")); Serial.println(NameResumeStateFile);
      File f = SPIFFS.open("/" + NameResumeStateFile, "r");
      if (!f) {
        Serial.println(F("..не получилось открыть файл"));
      }
      else {
        Serial.println(F("..читаем файл"));
        String s;
        uint8_t st_start, st_end, st_len;
        for (uint8_t i = 0; i < 20; i++)  {
          s = f.readStringUntil(PerevodStr); s.replace(F("\n"), "");
          st_start = s.indexOf(F("{")); st_end = s.indexOf(F("}")) + 1;
#ifdef USE_LOG
          Serial.println(s);
#endif
          if (s.indexOf(F("END")) == -1) {
            if ((st_start != -1) && (st_end != -1)) {
              s = s.substring(st_start, st_end); st_len = s.length();
              DynamicJsonBuffer jsonBuffer;   //Memory pool
              JsonObject& root = jsonBuffer.parseObject(s);
              if (root.success()) {
                autoMode = root["autoMode"];
                swt1 = root["rele1"];
                swt2 = root["rele2"];
                swt3 = root["rele3"];
                swt4 = root["rele4"];
              }
              else {
                Serial.println(F("..проблемы с парсингом"));
              }
            }
            else {
              Serial.println(F("..не форматная строка"));
            }
          }
          else { //нашли слово END в конце файла

            Serial.println(F("..дошли до конца файла"));
            Serial.println(F("..состояние реле восстановлено"));
            break;
          }
        }
        f.close();

      }
    }
  }
}
//-----------------------------------------------------------------------------------------
void mqttConnect() {
  //if (countFailMqtt < 20) {
  if (useMQTT && !mqttClient.connected()) {
    Serial.println();
    Serial.print(F("Trying to connect MQTT... "));
    Serial.print(mqttServer);
    Serial.print(F(":"));
    Serial.println(String(mqttServerPort));
    mqttClient.setServer(mqttServer.c_str(), mqttServerPort);
    mqttClient.setCallback(mqttCallback);

    //for (uint8_t i = 0; i < 3; i++) {
    Serial.println(F("..Connecting to MQTT..."));
    if (mqttClient.connect(mqttClientId.c_str(), mqttUser.c_str(), mqttUserPassword.c_str())) {
      mqttClient.subscribe("swt/#");
      countFailMqtt = 0;
      Serial.println("connected. ");
      //break;
    } else {
      Serial.print(F("failed with state = ")); Serial.println(mqttClient.state());
      countFailMqtt++;
    }
    //}
  }
  //}
}

//-----------------------------------------------------------------------------------------
void setup() {
  pinMode(A0, INPUT);
  pinMode(swt1_pin, OUTPUT);
  pinMode(swt2_pin, OUTPUT);
  pinMode(swt3_pin, OUTPUT);
  pinMode(swt4_pin, OUTPUT);
  pinMode(D7, INPUT);
  
  //-------- для себя чтоб не ждать установки --------------
  digitalWrite(swt1_pin, !LOW);
  digitalWrite(swt2_pin, !LOW);
  digitalWrite(swt3_pin, !LOW);
  digitalWrite(swt4_pin, !LOW);
  //--------------------------------------------------------
  Serial.begin(115200);
  Serial.println();

#ifdef USE_DHT
  dht.begin();
#endif

  chGrad = (char)49840; stGrad = chGrad; stGrad = stGrad + F("C");

  //pinMode(pinLev1, INPUT);
  //pinMode(pinLev2, INPUT);

  pinMode(pinBuiltinLed, OUTPUT);

  prev_swt1 = LOW;
  prev_swt2 = LOW;
  prev_swt3 = LOW;
  prev_swt4 = LOW;

  for (byte i = 0; i < NSenseMax; i++) {
    tempC[i] = -127;
    tempC_now[i] = -127;
  }

  error_read_ds_all = 0;
  error_read_correct_ds_all = 0;

  EEPROM.begin(1024);
  if (! readConfig()) {
    Serial.println(F("EEPROM is empty!"));
    digitalWrite(swt1_pin, !LOW);
    digitalWrite(swt2_pin, !LOW);
    digitalWrite(swt3_pin, !LOW);
    digitalWrite(swt4_pin, !LOW);
  }

  setupWiFi();

  if (! SPIFFS.begin()) {
    Serial.println(F("Unable to mount SPIFFS!"));
    return;
  }
  else {
    FSInfo fs_info;
    SPIFFS.info(fs_info);
    Serial.print(F("SPIFFS    totalBytes ")); Serial.println(fs_info.totalBytes);
    Serial.print(F("SPIFFS     usedBytes ")); Serial.println(fs_info.usedBytes);
    Serial.print(F("SPIFFS     blockSize ")); Serial.println(fs_info.blockSize);
    Serial.print(F("SPIFFS      pageSize ")); Serial.println(fs_info.pageSize);
    Serial.print(F("SPIFFS  maxOpenFiles ")); Serial.println(fs_info.maxOpenFiles);
    Serial.print(F("SPIFFS maxPathLength ")); Serial.println(fs_info.maxPathLength);
    /*      struct FSInfo {
          size_t totalBytes;
          size_t usedBytes;
          size_t blockSize;
          size_t pageSize;
          size_t maxOpenFiles;
          size_t maxPathLength;
      };*/


    openSettingsFile();
    openSensorConfFile();
    openResumeStateFile();
  }

  if (U_lev1 == 0) U_lev1 = 490;
  if (U_lev2 == 0) U_lev2 = 680;
  if (U_lev12 == 0) U_lev12 = 756;
  if (U_delta == 0) U_delta = 30;
  errA0 = false;

  if (over_t_lev1_on == 0) over_t_lev1_on = 5;
  if (over_t_lev2_on == 0) over_t_lev2_on = 5;

  if (over_t_lev1_off == 0) over_t_lev1_off = 15;
  if (over_t_lev2_off == 0) over_t_lev2_off = 40;

  server.begin();
  Serial.println(F("HTTP server started"));

  server.on("/", handleRoot);
  server.on("/index.html", handleRoot);
  server.on("/switch", h_switch);
  server.on("/select", h_select);
  server.on("/selectProm", h_selectProm);
  server.on("/WaterPump", h_WaterPump);
  server.on("/DrainagePump", h_DrainagePump);
  server.on("/save", h_save);

  server.on("/reboot", h_reboot);
  server.on("/wifi", h_wifi);
  server.on("/data_mainPage", HTTP_GET, h_data_mainPage);

  server.onNotFound(handleNotFound);
  server.on("/spiffs", HTTP_GET, handleSPIFFS);
  server.on("/spiffs", HTTP_POST, handleFileUploaded, handleFileUpload);
  server.on("/spiffs", HTTP_DELETE, handleFileDelete);
  server.on("/update", HTTP_GET, handleUpdate);
  server.on("/update", HTTP_POST, handleSketchUpdated, handleSketchUpdate);
  server.on("/timeConf", handleTimeConfig);
  server.on("/settime", handleSetTime);
  server.on("/gettimer", handleGetTimer);
  server.on("/data_settimer", handleSetTimer);
  server.on("/mqtt", h_mqtt);

  if (ntpServer1.length() < 2) ntpServer1 = FPSTR(defNtpServer1);
  if (ntpServer2.length() < 2) ntpServer2 = FPSTR(defNtpServer2);
  if (ntpServer3.length() < 2) ntpServer3 = FPSTR(defNtpServer3);
  
  if (updateInterval < 60) updateInterval = defUpdateInterval;

  sntp_set_timezone(timeZone);
  if (ntpServer1.length()) sntp_setservername(0, (char*)ntpServer1.c_str());
  if (ntpServer2.length()) sntp_setservername(1, (char*)ntpServer2.c_str());
  if (ntpServer3.length()) sntp_setservername(2, (char*)ntpServer3.c_str());
  sntp_init();
  startTime = noTime;
  startMs = millis();
  now_timeUnx = 0;
  setTimeAccompl = 0;
  systemStarted = 0;
  t_control_log_t = 0;
  nextTimeMQTT = 0;
  mqtt_control = 0;
  if (logFileSize == 0) logFileSize = 50;
  countFailNtp = 0;
  countFailMqtt = 0;
}
//----------------------------------------------------------------------------
void loop() {
  const uint32_t timeout = 300000; // 30сек
  static uint32_t nextTime = timeout;
  uint32_t t_sec, vol_hour, vol_min, vol_sec;

  if ((!ApMode) && (WiFi.status() != WL_CONNECTED) && ((WiFi.getMode() == WIFI_STA) || ((int32_t)(millis() - nextTime) >= 0)))  {
    setupWiFi();
    nextTime = millis() + timeout;
  }
  server.handleClient();

  t_sec = millis() / 1000;
  vol_hour = t_sec / 60 / 60;
  vol_min = t_sec / 60 - vol_hour * 60;
  vol_sec = t_sec - vol_hour * 60 * 60 - vol_min * 60;
  TimeOn = AddNull(String(vol_hour)) + ":" + AddNull(String(vol_min)) + ":" + AddNull(String(vol_sec));
  //----------------
  vol_hour = t_work_WaterPump / 60 / 60;
  vol_min = t_work_WaterPump / 60 - vol_hour * 60;
  vol_sec = t_work_WaterPump - vol_hour * 60 * 60 - vol_min * 60;
  str_t_working_WaterPump  = AddNull(String(vol_hour)) + ":" + AddNull(String(vol_min)) + ":" + AddNull(String(vol_sec));

  vol_hour = t_next_start_WaterPump / 60 / 60;
  vol_min = t_next_start_WaterPump / 60 - vol_hour * 60;
  vol_sec = t_next_start_WaterPump - vol_hour * 60 * 60 - vol_min * 60;
  str_t_next_start_WaterPump  = AddNull(String(vol_hour)) + ":" + AddNull(String(vol_min)) + ":" + AddNull(String(vol_sec));
  //----------------
  vol_hour = t_work_DrainagePump / 60 / 60;
  vol_min = t_work_DrainagePump / 60 - vol_hour * 60;
  vol_sec = t_work_DrainagePump - vol_hour * 60 * 60 - vol_min * 60;
  str_t_working_DrainagePump  = AddNull(String(vol_hour)) + ":" + AddNull(String(vol_min)) + ":" + AddNull(String(vol_sec));

  vol_hour = t_next_start_DrainagePump / 60 / 60;
  vol_min = t_next_start_DrainagePump / 60 - vol_hour * 60;
  vol_sec = t_next_start_DrainagePump - vol_hour * 60 * 60 - vol_min * 60;
  str_t_next_start_DrainagePump  = AddNull(String(vol_hour)) + ":" + AddNull(String(vol_min)) + ":" + AddNull(String(vol_sec));
  //----------------


  //---DrainagePump---
  DrainagePumpWorkTime = DrainagePumpOnHour * 60 * 60 + DrainagePumpOnMin * 60 + DrainagePumpOnSec;
  DrainagePumpStopTime = DrainagePumpOffHour * 60 * 60 + DrainagePumpOffMin * 60 + DrainagePumpOffSec;
  DrainagePumpTime = DrainagePumpHour * 60 * 60 + DrainagePumpMin * 60 + DrainagePumpSec;
  NsenseDrainagePumpContr = NsenseDrainagePumpContr;
  TDrainagePumpContr = TDrainagePumpContr;

  //---WaterPump---
  WaterPumpWorkTime = WaterPumpOnHour * 60 * 60 + WaterPumpOnMin * 60 + WaterPumpOnSec;
  WaterPumpStopTime = WaterPumpOffHour * 60 * 60 + WaterPumpOffMin * 60 + WaterPumpOffSec;
  WaterPumpTime = WaterPumpHour * 60 * 60 + WaterPumpMin * 60 + WaterPumpSec;
  NsenseWaterPumpContr = NsenseWaterPumpContr;
  TWaterPumpContr = TWaterPumpContr;


  working_WaterPump();
  working_DrainagePump();
  working_other();

  delay (10);

  //синхронизация времени
  //if (countFailNtp < 20) {
  if ((WiFi.getMode() == WIFI_STA) && (WiFi.status() == WL_CONNECTED) && (ntpUpd)) {
    static uint32_t nextTime = millis();
    if ((nextTime != noTime) && (millis() >= nextTime)) {
      Serial.print(F("Getting time from NTP server(s)... "));
      uint32_t now = sntp_get_current_timestamp();
      if (now == noTime) {
        nextTime = millis() + 90 * 1000; //при наличии интернета, но неудаче обновления повтор через 90 сек
        Serial.println(F("FAIL!"));
        countFailNtp++;
      }
      else {
        countFailNtp = 0;
        Serial.println(F("success"));
        setTimeAccompl = 1;
        startTime = now;
        startMs = millis();
        if (updateInterval)
          nextTime = startMs + updateInterval * 1000;
        else
          nextTime = noTime;
      }
    }
  }
  else {

  }
  //}
  now_timeUnx = startTime + (millis() - startMs) / 1000;
  parseUnixTime(now_timeUnx, now_hour, now_min, now_sec, now_wd, now_day, now_month, now_year);
  timeStr = dateWdTimeToStr(now_timeUnx);

}
//--------------------------------------------------------------------------------------
