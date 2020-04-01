void LoginContr()
{
  if (AccessMode == true)
  {
    char _AccessLogin[sizeof(AccessLogin)], _AccessPassword[sizeof(AccessPassword)];
    AccessLogin.toCharArray(_AccessLogin, sizeof(_AccessLogin));
    AccessPassword.toCharArray(_AccessPassword, sizeof(_AccessPassword));
    if (!server.authenticate(_AccessLogin, _AccessPassword)) return server.requestAuthentication();
  }
}
//---------------------------------------------------------------------------
String refreshTempMessage(String url)
{
  String message;
  message = F("function refreshTempMessage(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/data_tempMess', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("if (data.nom_mess != 255) {location.href ='/tempMess?nom_mess='+data.nom_mess+'&url="); message += url; message += F("'}}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");
  message += F("setInterval(refreshTempMessage, 1000);\n");

  return message;
}
//---------------------------------------------------------------------------
String textStyle()
{
  String message;

  message = F(".textStyle1 {");
  message += F("width: 25px; height: 20px; text-align: center;");
  message += F("text-align: center;");
  message += F("}");
  message += F(".textStyle2 {");
  message += F("width: 45px; height: 20px; text-align: center;");
  message += F("text-align: center;");
  message += F("}");

  return message;
}
//--------------------------------------------
String fillTimer()
{
  String message;


  return message;
}
//---------------------------------------------------------------------------
void handleRoot()
{
  LoginContr();

  String message;
  message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\">");
  message += F("<title>Управление скважиной на ESP</title>");
  message += F("<style type=\"text/css\">");
  message += F(".menu_but {width: 200px; text-align: center; padding: 5px;}");

  message += F(".checkboxRed {vertical-align:top; margin:0 3px 0 0; width:17px; height:17px;}");
  message += F(".checkboxRed + label {cursor:pointer;}");
  message += F(".checkboxRed:not(checked) {position:absolute; opacity:0; }");
  message += F(".checkboxRed:not(checked) + label {position:relative; padding:0 0 0 50px;}");
  message += F(".checkboxRed:not(checked) + label:before {content:''; position:absolute; top:-4px; left:0; width:50px; height:26px; border-radius:13px; background:#CDD1DA;box-shadow:inset 0 2px 3px rgba(0,0,0,.2);}");
  message += F(".checkboxRed:not(checked) + label:after {content:''; position:absolute; top:-2px; left:2px; width:22px; height:22px; border-radius:10px; background:#FFF; box-shadow:0 2px 5px rgba(0,0,0,.3); transition:all .1s;}");
  message += F(".checkboxRed:checked + label:before {background:#ec1212;}");
  message += F(".checkboxRed:checked + label:after {left:26px;}");

  message += F(".checkboxGreen {vertical-align:top; margin:0 3px 0 0; width:17px; height:17px;}");
  message += F(".checkboxGreen + label {cursor:pointer;}");
  message += F(".checkboxGreen:not(checked) {position:absolute; opacity:0; }");
  message += F(".checkboxGreen:not(checked) + label {position:relative; padding:0 0 0 50px;}");
  message += F(".checkboxGreen:not(checked) + label:before {content:''; position:absolute; top:-4px; left:0; width:50px; height:26px; border-radius:13px; background:#CDD1DA;box-shadow:inset 0 2px 3px rgba(0,0,0,.2);}");
  message += F(".checkboxGreen:not(checked) + label:after {content:''; position:absolute; top:-2px; left:2px; width:22px; height:22px; border-radius:10px; background:#FFF; box-shadow:0 2px 5px rgba(0,0,0,.3); transition:all .1s;}");
  message += F(".checkboxGreen:checked + label:before {background:#41d233;}");
  message += F(".checkboxGreen:checked + label:after {left:26px;}");

  message += F(".LevelPinGreen {vertical-align:top; margin:0 3px 0 0; width:17px; height:17px;}");
  message += F(".LevelPinGreen:not(checked) {position:absolute; opacity:0; }");
  message += F(".LevelPinGreen:not(checked) + label {position:relative; padding:0 0 0 26px;}");
  message += F(".LevelPinGreen:not(checked) + label:before {content:''; position:absolute; top:-4px; left:0; width:26px; height:26px; border-radius:13px; background:#CDD1DA;}");
  message += F(".LevelPinGreen:checked + label:before {background:#41d233;}");
  message += F(".LevelPinGreen:checked + label:after {left:26px;}");

  message += F(".LevelPinRed {vertical-align:top; margin:0 3px 0 0; width:17px; height:17px;}");
  message += F(".LevelPinRed:not(checked) {position:absolute; opacity:0; }");
  message += F(".LevelPinRed:not(checked) + label {position:relative; padding:0 0 0 26px;}");
  message += F(".LevelPinRed:not(checked) + label:before {content:''; position:absolute; top:-4px; left:0; width:26px; height:26px; border-radius:13px; background:#CDD1DA;}");
  message += F(".LevelPinRed:checked + label:before {background:#ec1212;}");
  message += F(".LevelPinRed:checked + label:after {left:26px;}");

  message += F(".column-1 {height: 26px; text-align: left; vertical-align: middle;background-color: lightyellow;}");
  message += F(".column-2 {text-align: center; vertical-align: middle;}");

  message += F("</style>");
  message += F("<script type=\"text/javascript\">\n");
  message += F("function openUrl(url) {\n");
  message += F("var request = new XMLHttpRequest();\n");
  message += F("request.open('GET', url, true);\n");
  message += F("request.send(null);\n ");
  message += F("};\n ");
  message += F("function refreshData(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/data_mainPage', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("document.getElementById('autoMode').checked = data.autoMode;\n");
  message +=         F("document.getElementById('relay1').checked = data.relay1;\n");
  message +=         F("document.getElementById('relay2').checked = data.relay2;\n");
  message +=         F("document.getElementById('relay3').checked = data.relay3;\n");
  message +=         F("document.getElementById('relay4').checked = data.relay4;\n");
  message +=         F("document.getElementById('lev1').checked = data.lev1;\n");
  message +=         F("document.getElementById('lev2').checked = data.lev2;\n");
  message +=         F("document.getElementById('now_relay1').checked = data.now_relay1;\n");
  message +=         F("document.getElementById('now_relay2').checked = data.now_relay2;\n");
  message +=         F("document.getElementById('now_relay3').checked = data.now_relay3;\n");
  message +=         F("document.getElementById('now_relay4').checked = data.now_relay4;\n");

  message +=         F("document.getElementById('str_t_working_WaterPump').innerHTML = data.str_t_working_WaterPump;\n");
  message +=         F("document.getElementById('str_t_next_start_WaterPump').innerHTML = data.str_t_next_start_WaterPump;\n");
  message +=         F("document.getElementById('str_t_working_DrainagePump').innerHTML = data.str_t_working_DrainagePump;\n");
  message +=         F("document.getElementById('str_t_next_start_DrainagePump').innerHTML = data.str_t_next_start_DrainagePump;\n");
  message +=         F("document.getElementById('strtworkBanyWater').innerHTML = data.strtworkBanyWater;\n");
  message +=         F("document.getElementById('strtworkBanySliv').innerHTML = data.strtworkBanySliv;\n");
  message +=         F("document.getElementById('t_lev1_on').innerHTML = data.t_lev1_on;\n");
  message +=         F("document.getElementById('t_lev2_on').innerHTML = data.t_lev2_on;\n");
  message +=         F("document.getElementById('t_lev1_off').innerHTML = data.t_lev1_off;\n");
  message +=         F("document.getElementById('t_lev2_off').innerHTML = data.t_lev2_off;\n");


  for (byte i = 0; i < NSenseFact; i++) {
    if (t[i] == 1) {
      message += F("document.getElementById('tempC"); message += String(i); message += F("').innerHTML = data.tempC"); message += String(i); message += F(";\n");
    }
  }
  message +=         F("document.getElementById('TimeOn').innerHTML = data.TimeOn;\n");
  message +=         F("document.getElementById('timeStr').innerHTML = data.timeStr;\n");
  message +=         F("document.getElementById('MQTT').innerHTML = data.MQTT;\n");
  message +=         F("document.getElementById('info').innerHTML = data.info;\n");
  message +=         F("}};\n");
  //message +=         F("if (data.beepeep > 0) {document.location.href = \"/alert\"}}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");
  message += F("setInterval(refreshData, 1000);\n");

  message += F("</script>\n");
  message += F("</head>\n");
  message += F("<body>\n");
  message += F("<form>\n");

  message += F("<h2>Управление скважиной <a href=\"http://www.simple-automation.ru/publ/proekty/kontroller_dlja_skvazhiny_na_esp8266_nodemcu_lua/kontroller-dlja-skvazhiny-na-esp8266-nodemcu-v3-lua/19-1-0-15\" target=\"_blank\">v.1.2</a></h2><p>\n");

  message +=  F("<input type=\"checkbox\" class=\"checkboxGreen\" id=\"autoMode\" onchange=\"openUrl('/switch?autoMode=' + this.checked);\" ");
  if (autoMode == HIGH) message += F("checked");
  message += F("/><label for=\"autoMode\">Автоматический режим работы</label></p>");

  message += F("<span id=\"timeStr\">.</span><br>\n");
  message += F("Время работы: <span id=\"TimeOn\">.</span><br>\n");
  message += F("MQTT: <span id=\"MQTT\">.</span></p>\n");

  message += F("<table cellspacing=\"1\" border=\"0\" style=\"vertical-align:middle; align:left\" >");
  message += F("<tr>");
  message +=  F("<th></th>");
  message +=  F("<th></th>");
  message +=  F("<th>Pin</th>");
  message +=  F("<th>В работе</th>");
  message +=  F("<th>След вкл</th>");
  message += F("</tr>");

  message += F("<tr>");
  message +=  F("<th class=\"column-1\">");
  message += F("Водян.насос");
  message +=  F("</th>");

  message +=  F("<td class=\"column-2\">");
  message +=  F("<input type=\"checkbox\" class=\"checkboxGreen\" id=\"relay1\" onchange=\"openUrl('/switch?swt1=' + this.checked);\" ");
  if (swt1 == HIGH) message += F("checked");
  message += F("/><label for=\"relay1\"></label>");
  message +=  F("</td>");

  message +=  F("<td class=\"column-2\">");
  message +=  F("<input type=\"checkbox\" class=\"LevelPinGreen\" id=\"now_relay1\" ");
  if (now_relay1 == HIGH) message += F("checked");
  message += F("/><label for=\"now_relay1\"></label>");
  message +=  F("</td>");
  message +=  F("<td class=\"column-2\"><span id=\"str_t_working_WaterPump\">.</span></td>");
  message +=  F("<td class=\"column-2\"><span id=\"str_t_next_start_WaterPump\">.</span></td>");
  message += F("</tr>");

  message += F("<tr>");
  message +=  F("<th class=\"column-1\">Дренаж.насос</th>");
  message +=  F("<td class=\"column-2\">");
  message += F("<input type = \"checkbox\" class=\"checkboxGreen\" id=\"relay2\" onchange=\"openUrl('/switch?swt2=' + this.checked);\" ");
  if (swt2 == HIGH) message += F("checked ");
  message += F("/><label for=\"relay2\"></label>");
  message +=  F("</td>");
  message +=  F("<td class=\"column-2\">");
  message +=  F("<input type=\"checkbox\" class=\"LevelPinRed\" id=\"now_relay2\" ");
  if (now_relay2 == HIGH) message += F("checked");
  message += F("/><label for=\"now_relay2\"></label>");
  message +=  F("</td>");
  message +=  F("<td class=\"column-2\"><span id=\"str_t_working_DrainagePump\">.</span></td>");
  message +=  F("<td class=\"column-2\"><span id=\"str_t_next_start_DrainagePump\">.</span></td>");
  message += F("</tr>");

  message += F("<tr>");
  message +=  F("<th class=\"column-1\">Датчик ур.верх</th>");
  message +=  F("<td></td>");
  message +=  F("<td class=\"column-2\">");
  message += F("<input type = \"checkbox\" class=\"LevelPinRed\" id=\"lev2\" disabled=\"true\" ");
  if (lev2 == HIGH) message += F("checked ");
  message += F("/><label for=\"lev2\"></label>");
  message +=  F("</td>");
  message +=  F("<td class=\"column-2\"><span id=\"t_lev2_on\">.</span></td>");
  message +=  F("<td class=\"column-2\"><span id=\"t_lev2_off\">.</span></td>");
  message += F("</tr>");

  message += F("<tr align=\"left\">");
  message +=  F("<th class=\"column-1\">Датчик ур.низ</th>");
  message +=  F("<td></td>");
  message +=  F("<td class=\"column-2\">");
  message += F("<input type = \"checkbox\" class=\"LevelPinRed\" id=\"lev1\" disabled=\"true\" ");
  if (lev1 == HIGH) message += F("checked ");
  message += F("/><label for=\"lev1\"></label>");
  message +=  F("</td>");
  message +=  F("<td class=\"column-2\"><span id=\"t_lev1_on\">.</span></td>");
  message +=  F("<td class=\"column-2\"><span id=\"t_lev1_off\">.</span></td>");
  message += F("</tr>");

  message += F("<tr>");
  message +=  F("<th class=\"column-1\">Клапан (подача)</th>");
  message +=  F("<td class=\"column-2\">");
  message += F("<input type = \"checkbox\" class=\"checkboxRed\" id=\"relay3\" onchange=\"openUrl('/switch?swt3=' + this.checked);\" ");
  if (swt3 == HIGH) message += F("checked ");
  message += F("/><label for = \"relay3\"></label>");
  message +=  F("</td>");

  message +=  F("<td class=\"column-2\">");
  message +=  F("<input type=\"checkbox\" class=\"LevelPinRed\" id=\"now_relay3\" ");
  if (now_relay3 == HIGH) message += F("checked");
  message += F("/><label for=\"now_relay3\"></label>");
  message +=  F("</td>");
  message +=  F("<td class=\"column-2\"><span id=\"strtworkBanyWater\">.</span></td>");
  message +=  F("<td class=\"column-2\"></td>");
  message += F("</tr>");

  message += F("<tr>");
  message +=  F("<th class=\"column-1\">Клапан (слив)</th>");
  message +=  F("<td class=\"column-2\">");
  message += F("<input type = \"checkbox\" class=\"checkboxRed\" id=\"relay4\" onchange=\"openUrl('/switch?swt4=' + this.checked);\" ");
  if (swt4 == HIGH) message += F("checked ");
  message += F("/><label for = \"relay4\"></label>");
  message +=  F("</td>");
  message +=  F("<td class=\"column-2\">");
  message +=  F("<input type=\"checkbox\" class=\"LevelPinRed\" id=\"now_relay4\" ");
  if (now_relay4 == HIGH) message += F("checked");
  message += F("/><label for=\"now_relay4\"></label>");
  message +=  F("</td>");
  message +=  F("<td class=\"column-2\"><span id=\"strtworkBanySliv\">.</span></td>");
  message +=  F("<td class=\"column-2\"></td>");
  message += F("</tr>");

  message += F("<tr align=\"left\">");
  message +=  F("<td colspan=\"5\">");
  for (byte i = 0; i < NSenseFact; i++) {
    if (t[i] == 1) {
      message += F("<span id=\"tempC"); message += String(i); message += F("\">.</span> &#176С ");
      if (tNameSens[i].length() > 0) {
        message += F(" /"); message += tNameSens[i] + F("/");
      }
      message += F("<br />\n");
    }
  }

  message += F("<p>\n");

  message += F("Инфо: <span id=\"info\">.</span></p>\n");

  message += F("<input type = \"button\" class=\"menu_but\" id=\"butt_adjWaterPump\" value=\"Управление водяным насосом\" onclick=\"location.href='/WaterPump';\" /><br>\n");
  message += F("<input type = \"button\" class=\"menu_but\" id=\"butt_adjDrainagePump\" value=\"Управление дренажным насосом\" onclick=\"location.href='/DrainagePump';\" /><br>\n");
  message += F("<input type = \"button\" class=\"menu_but\" id=\"butt_adjContr\" value=\"Реле и датчики\" onclick=\"location.href='/select';\" /><br>\n");

  message += F("<p>");
  message += F("<input type = \"button\" class=\"menu_but\" id=\"butt_adjWifi\" value=\"Настройка Wi-fi\" onclick=\"location.href='/wifi';\" /><br>\n");
  message += F("<input type = \"button\" class=\"menu_but\" id=\"butt_adjMQTT\" value=\"Настройка MQTT\" onclick=\"location.href='/mqtt';\" /><br>\n");
  message += F("<input type = \"button\" class=\"menu_but\" id=\"butt_adjTime\" value=\"Настройка времени\" onclick=\"location.href='/timeConf';\" /><br>\n");
  message += F("<input type = \"button\" class=\"menu_but\" id=\"butt_adjDevPrg\" value=\"Обновление прошивки\" onclick=\"location.href='/update';\" /><br>\n");
  message += F("<input type = \"button\" class=\"menu_but\" value=\"Менеджер файлов\" onclick=\"location.href='/spiffs';\" /><br>\n");
  message += F("<p>");
  message += F("<input type = \"button\" class=\"menu_but\" value=\"Перезагрузка\" id=\"butt_reboot\" onclick=\"if (confirm('Перезагрузить модуль?') == true) location.href='/reboot'\" /><br>\n");



  message +=  F("</td>");
  message += F("</tr>");
  message += F("</table>");


  message += F("</form>\n");
  message += F(" </body>\n");
  message += F(" </html>\n");
  server.send(200, F("text/html"), message);
}

//---------------------------------------------------------------------------------
void save_ResumeStateFile()
{
  Serial.print("Try save " + NameResumeStateFile);
  File f = SPIFFS.open("/" + NameResumeStateFile, "w");
  if (!f)
  {
    Serial.println(F("....failed"));
  }
  else
  {
    Serial.println(F("..... Writing SPIFFS file "));

    String strM;
    strM = F("{");
    strM += F("\"autoMode\":"); strM += String(autoMode) + F(",");
    strM += F("\"rele1\":"); strM += String(swt1) + F(",");
    strM += F("\"rele2\":"); strM += String(swt2) + F(",");
    strM += F("\"rele3\":"); strM += String(swt3) + F(",");
    strM += F("\"rele4\":"); strM += String(swt4);
    strM += F("}");
    Serial.println(strM); f.println(strM);
    f.print(F("END"));
    f.close();
    Serial.println(F(" done."));
  }
}
//-----------------------------------------------------------------------------------------------------------------------------

void save_SensorConfFile()
{
  Serial.println("Try open " + SensorConfFile);
  File f = SPIFFS.open("/" + SensorConfFile, "w");
  if (!f)
  {
    Serial.println(F("file open failed"));
  }
  else
  {
    Serial.println(F(" Writing SPIFFS file "));
    String strM;

    for (int i = 0; i < NSenseFact; i++) {
      strM = F("{\"t\":"); strM += String(t[i]) + ",";
      strM += F("\"frame\":[");
      for (uint8_t k = 0; k < 8; k++) {
        strM += String(insideThermometer[i][k]);
        if (k != 7) strM += F(",");
      }
      strM += F("],");
      strM += F("\"tNameSens\":\""); strM += String(tNameSens[i]) + F("\"");
      strM += F("}");
      Serial.println(strM);
      f.println(strM);
    }

    f.print(F("END"));
    f.close();
    Serial.println(F(" done."));

  }
}
//-----------------------------------------------------------------------------------------

void save_CfgFile()
{
  Serial.print("Try save " + NameSettingsFile);
  File f = SPIFFS.open("/" + NameSettingsFile, "w");
  if (!f) {
    Serial.println(F("....failed"));
  }
  else {
    Serial.println(F("..... Writing SPIFFS file "));

    String strM;
    strM = F("{\"Vol\":"); strM += F("0,");
    strM += F("\"DrainagePumpOnTime\":["); strM += String(DrainagePumpOnHour) + F(","); strM += String(DrainagePumpOnMin) + F(","); strM += String(DrainagePumpOnSec) + F("],");
    strM += F("\"DrainagePumpOffTime\":["); strM += String(DrainagePumpOffHour) + F(","); strM += String(DrainagePumpOffMin) + F(","); strM += String(DrainagePumpOffSec) + F("],");
    strM += F("\"DrainagePumpTime\":["); strM += String(DrainagePumpHour) + F(","); strM += String(DrainagePumpMin) + F(","); strM += String(DrainagePumpSec) + F("],");
    strM += F("\"TDrainagePumpContr\":"); strM += String(TDrainagePumpContr) + F(",");
    strM += F("\"NsenseDrainagePumpContr\":"); strM += String(NsenseDrainagePumpContr) + F(",");;

    for (byte i = 0; i < NomPrerDrainagePumpAll; i++) {
      PrerDrainagePump[i].PrerPumpStUnx = combineUnixTime(PrerDrainagePump[i].PrerPumpHourSt, PrerDrainagePump[i].PrerPumpMinSt, 0, 1, 1, 1970); // Собрать время в формат UNIX-time
      PrerDrainagePump[i].PrerPumpEndUnx = combineUnixTime(PrerDrainagePump[i].PrerPumpHourEnd, PrerDrainagePump[i].PrerPumpMinEnd, 0, 1, 1, 1970); // Собрать время в формат UNIX-time

      strM += F("\"Avail"); strM +=   String(i) + F("\":"); strM += String(PrerDrainagePump[i].Avail) + F(",");
      strM += F("\"PrerDrainagePumpStUnx"); strM +=  String(i) + F("\":"); strM += String(PrerDrainagePump[i].PrerPumpStUnx) + F(",");
      strM += F("\"PrerDrainagePumpEndUnx"); strM +=  String(i) + F("\":"); strM += String(PrerDrainagePump[i].PrerPumpEndUnx) + F(",");
    }

    TimerDrainagePumpStUnx = combineUnixTime(TimerDrainagePumpHourSt, TimerDrainagePumpMinSt, TimerDrainagePumpSecSt, TimerDrainagePumpDaySt, TimerDrainagePumpMonthSt, TimerDrainagePumpYearSt); // Собрать время в формат UNIX-time
    TimerDrainagePumpEndUnx = combineUnixTime(TimerDrainagePumpHourEnd, TimerDrainagePumpMinEnd, TimerDrainagePumpSecEnd, TimerDrainagePumpDayEnd, TimerDrainagePumpMonthEnd, TimerDrainagePumpYearEnd); // Собрать время в формат UNIX-time

    strM += F("\"TimerDrainagePumpAvailSt\":"); strM += String(TimerDrainagePumpAvailSt) + F(",");
    strM += F("\"TimerDrainagePumpStUnx\":"); strM += String(TimerDrainagePumpStUnx) + F(",");
    strM += F("\"TimerDrainagePumpAvailEnd\":"); strM += String(TimerDrainagePumpAvailEnd) + F(",");
    strM += F("\"TimerDrainagePumpEndUnx\":"); strM += String(TimerDrainagePumpEndUnx) + F(",");

    strM += F("\"over_t_lev1_on\":"); strM += String(over_t_lev1_on) + F(",");
    strM += F("\"over_t_lev2_on\":"); strM += String(over_t_lev2_on) + F(",");
    strM += F("\"over_t_lev1_off\":"); strM += String(over_t_lev1_off) + F(",");
    strM += F("\"over_t_lev2_off\":"); strM += String(over_t_lev2_off);

    strM += F("}");
    Serial.println(strM); f.println(strM);
    //-------------------------
    strM = F("{\"Vol\":"); strM += F("1,");
    strM += F("\"WaterPumpOnTime\":["); strM += String(WaterPumpOnHour) + F(","); strM += String(WaterPumpOnMin) + F(","); strM += String(WaterPumpOnSec) + F("],");
    strM += F("\"WaterPumpOffTime\":["); strM += String(WaterPumpOffHour) + F(","); strM += String(WaterPumpOffMin) + F(","); strM += String(WaterPumpOffSec) + F("],");
    strM += F("\"WaterPumpTime\":["); strM += String(WaterPumpHour) + F(","); strM += String(WaterPumpMin) + F(","); strM += String(WaterPumpSec) + F("],");
    strM += F("\"TWaterPumpContr\":"); strM += String(TWaterPumpContr) + F(",");
    strM += F("\"NsenseWaterPumpContr\":"); strM += String(NsenseWaterPumpContr) + F(",");;

    for (byte i = 0; i < NomPrerWaterPumpAll; i++) {
      PrerWaterPump[i].PrerPumpStUnx = combineUnixTime(PrerWaterPump[i].PrerPumpHourSt, PrerWaterPump[i].PrerPumpMinSt, 0, 1, 1, 1970); // Собрать время в формат UNIX-time
      PrerWaterPump[i].PrerPumpEndUnx = combineUnixTime(PrerWaterPump[i].PrerPumpHourEnd, PrerWaterPump[i].PrerPumpMinEnd, 0, 1, 1, 1970); // Собрать время в формат UNIX-time

      strM += F("\"Avail"); strM +=   String(i) + F("\":"); strM += String(PrerWaterPump[i].Avail) + F(",");
      strM += F("\"PrerWaterPumpStUnx"); strM +=  String(i) + F("\":"); strM += String(PrerWaterPump[i].PrerPumpStUnx) + F(",");
      strM += F("\"PrerWaterPumpEndUnx"); strM +=  String(i) + F("\":"); strM += String(PrerWaterPump[i].PrerPumpEndUnx) + F(",");
    }

    TimerWaterPumpStUnx = combineUnixTime(TimerWaterPumpHourSt, TimerWaterPumpMinSt, TimerWaterPumpSecSt, TimerWaterPumpDaySt, TimerWaterPumpMonthSt, TimerWaterPumpYearSt); // Собрать время в формат UNIX-time
    TimerWaterPumpEndUnx = combineUnixTime(TimerWaterPumpHourEnd, TimerWaterPumpMinEnd, TimerWaterPumpSecEnd, TimerWaterPumpDayEnd, TimerWaterPumpMonthEnd, TimerWaterPumpYearEnd); // Собрать время в формат UNIX-time

    strM += F("\"TimerWaterPumpAvailSt\":"); strM += String(TimerWaterPumpAvailSt) + F(",");
    strM += F("\"TimerWaterPumpStUnx\":"); strM += String(TimerWaterPumpStUnx) + F(",");
    strM += F("\"TimerWaterPumpAvailEnd\":"); strM += String(TimerWaterPumpAvailEnd) + F(",");
    strM += F("\"TimerWaterPumpEndUnx\":"); strM += String(TimerWaterPumpEndUnx);


    strM += F("}");
    Serial.println(strM); f.println(strM);
    //----------------------------------
    /* strM = F("{\"Vol\":"); strM += F("2,");

      strM += F("}");
      Serial.println(strM); f.println(strM);*/
    strM = F("{\"Vol\":"); strM += F("3,");

    strM += F("\"resumeState\":"); strM += String(resumeState) + F(",");
    strM += F("\"autoMode\":"); strM += String(autoMode) + F(",");
    strM += F("\"relayLevel\":["); strM += String(relay1Level) + F(","); strM += String(relay2Level) + F(","); strM += String(relay3Level) + F(","); strM += String(relay4Level) + F("],");

    strM += F("\"U_lev1\":"); strM += String(U_lev1) + F(",");
    strM += F("\"U_lev2\":"); strM += String(U_lev2) + F(",");
    strM += F("\"U_lev12\":"); strM += String(U_lev12) + F(",");
    strM += F("\"U_delta\":"); strM += String(U_delta) + F(",");

    strM += F("\"Zaderj\":"); strM += String(Zaderj) + F(",");
    strM += F("\"jamp_t\":"); strM += String(jamp_t) + F(",");
    strM += F("\"error_read_ds_Max\":"); strM += String(error_read_ds_Max) + F(",");
    strM += F("\"t_msec_get_ds\":"); strM += String(t_msec_get_ds) + F(",");

    strM += F("\"ntpServer\":[\""); strM += ntpServer1 + F("\",\""); strM += ntpServer2 + F("\",\""); strM += ntpServer3 + F("\"],");
    strM += F("\"updateInterval\":"); strM += String(updateInterval) + F(",");
    strM += F("\"timeZone\":"); strM += String(timeZone) + F(",");
    strM += F("\"ntpUpd\":"); strM += String(ntpUpd) + F(",");
    strM += F("\"useMQTT\":"); strM += String(useMQTT) + F(",");
    strM += F("\"mqttServer\":\""); strM += mqttServer + F("\",");

    strM += F("\"mqttServerPort\":"); strM += String(mqttServerPort) + F(",");
    strM += F("\"mqttUser\":\""); strM += mqttUser + F("\",");
    strM += F("\"mqttUserPassword\":\""); strM += mqttUserPassword + F("\",");
    strM += F("\"mqttClientId\":\""); strM += mqttClientId + F("\",");
    strM += F("\"mqttReconnectSec\":"); strM += String(mqttReconnectSec) + F(",");

    strM += F("\"log_t\":"); strM += String(log_t) + F(",");
    strM += F("\"logFileSize\":"); strM += String(logFileSize) + F(",");
    strM += F("\"writeSysLog\":"); strM += String(writeSysLog) + F(",");
    strM += F("\"writeSenseLog\":"); strM += String(writeSenseLog);
    strM += F("}");


    
    Serial.println(strM); f.println(strM);
    f.print(F("END"));
    f.close();
    Serial.println(F(" done."));
  }
}
//------------------------------------------------------------

//---------------------------------------------------------------------------------------------
void h_save() //save
{
  LoginContr();
  String argName, argValue;
  Serial.println("module save");
  Serial.print("args()=");
  Serial.println(server.args());
  for (byte i = 0; i < server.args(); i++)
  {
    argName = server.argName(i);
    Serial.print(argName);
    Serial.print("=\"");
    argValue = server.arg(i);
    Serial.print(argValue);
    Serial.println("\"");

    if (argName == F("ssid"))                  ssid = argValue;
    else if (argName == F("password"))     password = argValue;
    else if (argName == F("AccessLogin"))     AccessLogin = argValue;
    else if (argName == F("AccessPassword"))     AccessPassword = argValue;

    else if (argName == F("ip1"))               ip1 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("ip2"))               ip2 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("ip3"))               ip3 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("ip4"))               ip4 = constrain(argValue.toInt(), 0, 255);

    else if (argName == F("ms1"))               ms1 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("ms2"))               ms2 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("ms3"))               ms3 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("ms4"))               ms4 = constrain(argValue.toInt(), 0, 255);

    else if (argName == F("gt1"))               gt1 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("gt2"))               gt2 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("gt3"))               gt3 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("gt4"))               gt4 = constrain(argValue.toInt(), 0, 255);

    else if (argName == F("dn1"))               dn1 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("dn2"))               dn2 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("dn3"))               dn3 = constrain(argValue.toInt(), 0, 255);
    else if (argName == F("dn4"))               dn4 = constrain(argValue.toInt(), 0, 255);

    else if (argName == F("WaterPumpOnHour"))   WaterPumpOnHour = constrain(argValue.toInt(), 0, 23);
    else if (argName == F("WaterPumpOnMin"))     WaterPumpOnMin = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("WaterPumpOnSec"))     WaterPumpOnSec = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("WaterPumpOffHour")) WaterPumpOffHour = constrain(argValue.toInt(), 0, 23);
    else if (argName == F("WaterPumpOffMin"))   WaterPumpOffMin = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("WaterPumpOffSec"))   WaterPumpOffSec = constrain(argValue.toInt(), 0, 59);

    else if (argName == F("WaterPumpHour"))     WaterPumpHour = constrain(argValue.toInt(), 0, 23);
    else if (argName == F("WaterPumpMin"))       WaterPumpMin = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("WaterPumpSec"))       WaterPumpSec = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("TWaterPumpContr")) TWaterPumpContr = argValue.toInt();
    else if (argName == F("NsenseWaterPumpContr")) NsenseWaterPumpContr = argValue.toInt();


    else if (argName == F("DrainagePumpOnHour"))   DrainagePumpOnHour = constrain(argValue.toInt(), 0, 23);
    else if (argName == F("DrainagePumpOnMin"))     DrainagePumpOnMin = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("DrainagePumpOnSec"))     DrainagePumpOnSec = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("DrainagePumpOffHour")) DrainagePumpOffHour = constrain(argValue.toInt(), 0, 23);
    else if (argName == F("DrainagePumpOffMin"))   DrainagePumpOffMin = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("DrainagePumpOffSec"))   DrainagePumpOffSec = constrain(argValue.toInt(), 0, 59);

    else if (argName == F("DrainagePumpHour"))     DrainagePumpHour = constrain(argValue.toInt(), 0, 23);
    else if (argName == F("DrainagePumpMin"))       DrainagePumpMin = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("DrainagePumpSec"))       DrainagePumpSec = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("TDrainagePumpContr")) TDrainagePumpContr = argValue.toInt();
    else if (argName == F("NsenseDrainagePumpContr")) NsenseDrainagePumpContr = argValue.toInt();

    else if (argName == F("mqttServer"))             mqttServer = argValue;
    else if (argName == F("mqttServerPort"))     mqttServerPort = constrain(argValue.toInt(), 1024, 65535);
    else if (argName == F("mqttUser"))                 mqttUser = argValue;
    else if (argName == F("mqttUserPassword")) mqttUserPassword = argValue;
    else if (argName == F("mqttClientId"))         mqttClientId = argValue;
    else if (argName == F("mqttReconnectSec")) mqttReconnectSec = constrain(argValue.toInt(), 60, 65535);

    else if (argName == F("Zaderj"))                        Zaderj = constrain(argValue.toInt(), 0, 1000);
    else if (argName == F("jamp_t"))                        jamp_t = constrain(argValue.toInt(), 0, 99);
    else if (argName == F("error_read_ds_Max"))  error_read_ds_Max = constrain(argValue.toInt(), 2, 99);
    else if (argName == F("t_msec_get_ds"))          t_msec_get_ds = constrain(argValue.toInt(), 100, 40000);
    else if (argName == F("log_t"))                          log_t = constrain(argValue.toInt(), 1, 1440);
     else if (argName == F("logFileSize"))             logFileSize = constrain(argValue.toInt(), 20, 250);


    else if (argName == F("ntpServer1"))     ntpServer1 = argValue;
    else if (argName == F("ntpServer2"))     ntpServer2 = argValue;
    else if (argName == F("ntpServer3"))     ntpServer3 = argValue;
    else if (argName == F("updateInterval"))     updateInterval = constrain(argValue.toInt(), 3600, 72*3600);
    else if (argName == F("timeZone"))     timeZone = argValue.toInt();


    //---------------
    else if (argName == F("TimerWaterPumpDaySt"))  TimerWaterPumpDaySt = constrain(argValue.toInt(), 1, 31);
    else if (argName == F("TimerWaterPumpMonthSt"))  TimerWaterPumpMonthSt = constrain(argValue.toInt(), 1, 12);
    else if (argName == F("TimerWaterPumpYearSt"))  TimerWaterPumpYearSt = constrain(argValue.toInt(), 2018, 2040);
    else if (argName == F("TimerWaterPumpHourSt"))  TimerWaterPumpHourSt = constrain(argValue.toInt(), 0, 23);
    else if (argName == F("TimerWaterPumpMinSt"))  TimerWaterPumpMinSt = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("TimerWaterPumpSecSt"))  TimerWaterPumpSecSt = constrain(argValue.toInt(), 0, 59);


    else if (argName == F("TimerWaterPumpDayEnd"))  TimerWaterPumpDayEnd = constrain(argValue.toInt(), 1, 31);
    else if (argName == F("TimerWaterPumpMonthEnd"))  TimerWaterPumpMonthEnd = constrain(argValue.toInt(), 1, 12);
    else if (argName == F("TimerWaterPumpYearEnd"))  TimerWaterPumpYearEnd = constrain(argValue.toInt(), 2018, 2040);
    else if (argName == F("TimerWaterPumpHourEnd"))  TimerWaterPumpHourEnd = constrain(argValue.toInt(), 0, 23);
    else if (argName == F("TimerWaterPumpMinEnd"))  TimerWaterPumpMinEnd = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("TimerWaterPumpSecEnd"))  TimerWaterPumpSecEnd = constrain(argValue.toInt(), 0, 59);

    //---------------
    else if (argName == F("TimerDrainagePumpDaySt"))  TimerDrainagePumpDaySt = constrain(argValue.toInt(), 1, 31);
    else if (argName == F("TimerDrainagePumpMonthSt"))  TimerDrainagePumpMonthSt = constrain(argValue.toInt(), 1, 12);
    else if (argName == F("TimerDrainagePumpYearSt"))  TimerDrainagePumpYearSt = constrain(argValue.toInt(), 2018, 2040);
    else if (argName == F("TimerDrainagePumpHourSt"))  TimerDrainagePumpHourSt = constrain(argValue.toInt(), 0, 23);
    else if (argName == F("TimerDrainagePumpMinSt"))  TimerDrainagePumpMinSt = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("TimerDrainagePumpSecSt"))  TimerDrainagePumpSecSt = constrain(argValue.toInt(), 0, 59);


    else if (argName == F("TimerDrainagePumpDayEnd"))  TimerDrainagePumpDayEnd = constrain(argValue.toInt(), 1, 31);
    else if (argName == F("TimerDrainagePumpMonthEnd"))  TimerDrainagePumpMonthEnd = constrain(argValue.toInt(), 1, 12);
    else if (argName == F("TimerDrainagePumpYearEnd"))  TimerDrainagePumpYearEnd = constrain(argValue.toInt(), 2018, 2040);
    else if (argName == F("TimerDrainagePumpHourEnd"))  TimerDrainagePumpHourEnd = constrain(argValue.toInt(), 0, 23);
    else if (argName == F("TimerDrainagePumpMinEnd"))  TimerDrainagePumpMinEnd = constrain(argValue.toInt(), 0, 59);
    else if (argName == F("TimerDrainagePumpSecEnd"))  TimerDrainagePumpSecEnd = constrain(argValue.toInt(), 0, 59);

    else if (argName == F("U_lev1"))  U_lev1 = constrain(argValue.toInt(), 0, 1023);
    else if (argName == F("U_lev2"))  U_lev2 = constrain(argValue.toInt(), 0, 1023);
    else if (argName == F("U_lev12"))  U_lev12 = constrain(argValue.toInt(), 0, 1023);
    else if (argName == F("U_delta"))  U_delta = constrain(argValue.toInt(), 0, 100);

    else if (argName == F("over_t_lev1_on")) over_t_lev1_on = constrain(argValue.toInt(), 0, 1000);
    else if (argName == F("over_t_lev2_on")) over_t_lev2_on = constrain(argValue.toInt(), 0, 1000);
    else if (argName == F("over_t_lev1_off")) over_t_lev1_off = constrain(argValue.toInt(), 0, 1000);
    else if (argName == F("over_t_lev2_off")) over_t_lev2_off = constrain(argValue.toInt(), 0, 1000);

    String _argName;
    for (byte i = 0; i < NomPrerWaterPumpAll; i++) {

      _argName = F("PrerWaterPumpHourSt"); _argName += String(i);
      if (argName == _argName) {
        PrerWaterPump[i].PrerPumpHourSt = argValue.toInt();
      }

      _argName = F("PrerWaterPumpMinSt"); _argName += String(i);
      if (argName == _argName) {
        PrerWaterPump[i].PrerPumpMinSt = argValue.toInt();
      }

      _argName = F("PrerWaterPumpHourEnd"); _argName += String(i);
      if (argName == _argName) {
        PrerWaterPump[i].PrerPumpHourEnd = argValue.toInt();
      }

      _argName = F("PrerWaterPumpMinEnd"); _argName += String(i);
      if (argName == _argName) {
        PrerWaterPump[i].PrerPumpMinEnd = argValue.toInt();
      }
    }


    for (byte i = 0; i < NomPrerDrainagePumpAll; i++) {

      _argName = F("PrerDrainagePumpHourSt"); _argName += String(i);
      if (argName == _argName) {
        PrerDrainagePump[i].PrerPumpHourSt = argValue.toInt();
      }

      _argName = F("PrerDrainagePumpMinSt"); _argName += String(i);
      if (argName == _argName) {
        PrerDrainagePump[i].PrerPumpMinSt = argValue.toInt();
      }

      _argName = F("PrerDrainagePumpHourEnd"); _argName += String(i);
      if (argName == _argName) {
        PrerDrainagePump[i].PrerPumpHourEnd = argValue.toInt();
      }

      _argName = F("PrerDrainagePumpMinEnd"); _argName += String(i);
      if (argName == _argName) {
        PrerDrainagePump[i].PrerPumpMinEnd = argValue.toInt();
      }
    }



    for (uint8_t k = 0; k < NSenseMax; k++)  {
      String argN;
      argN = F("tNameSens"); argN += String(k);
      if (argName == argN) tNameSens[k] = argValue;
    }
  }
  writeConfig();
  save_SensorConfFile();
  save_CfgFile();
  String message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<title>Store Setup</title>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\" http-equiv=\"refresh\" content=\"0; /index.html\">");
  message += F("</head>");
  message += F("<body>");
  message += F("Настройи сохранены успешно.");
  message += F("<p>Ждите 1 сек. или нажмите <a href=\"/index.html\">сюда</a> для перехода в главное меню.");
  message += F("</body>");
  message += F("</html>");

  server.send(200, F("text/html"), message);

}
//-------------------------------------------------------------------------

void h_select()//select
{
  LoginContr();
  String message;
  message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<title>Управление контролем</title>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\">");
  message += F("<style type=\"text/css\">");
  message += F(".checkbox {vertical-align:top; margin:0 3px 0 0; width:17px; height:17px;}");
  message += F(".checkbox + label {cursor:pointer;}");
  message += F(".checkbox:not(checked) {position:absolute; opacity:0; }");
  message += F(".checkbox:not(checked) + label {position:relative; padding:0 0 0 60px;}");
  message += F(".checkbox:not(checked) + label:before {content:''; position:absolute; top:-4px; left:0; width:50px; height:26px; border-radius:13px; background:#CDD1DA;box-shadow:inset 0 2px 3px rgba(0,0,0,.2);}");
  message += F(".checkbox:not(checked) + label:after { content:''; position:absolute; top:-2px; left:2px; width:22px; height:22px; border-radius:10px; background:#FFF; box-shadow:0 2px 5px rgba(0,0,0,.3); transition:all .2s;}");
  message += F(".checkbox:checked + label:before {background:#9FD468;}");
  message += F(".checkbox:checked + label:after {left:26px;}");
  message += textStyle();
  message += F("</style>");
  message += F("<script type=\"text/javascript\">");
  message += F("function openUrl(url) {");
  message += F("var request = new XMLHttpRequest();");
  message += F("request.open('GET', url, true);");
  message += F("request.send(null);");
  message += F("}");
  message += F("function PowChange(Powval,k){");
  message += F("var ret;");
  message += F("if (isNaN(Powval)==true) return 0;");
  message += F("ret=(parseFloat(Powval,10)+k);");
  message += F("if (ret>100) ret=100;");
  message += F("if (ret<0) ret=0;");
  message += F("return ret;}");
  message += F("function CheckVal(obj){");
  message += F("var ret;");
  message += F("ret=(parseFloat(document.getElementById(obj).value,10));");
  message += F("if (isNaN(ret)==true) document.getElementById(obj).value=0;");
  message += F("if (isNaN(ret)==false) document.getElementById(obj).value=ret;}");
  message += F("function refreshSens(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/data_mainPage', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("document.getElementById('relay1Level').checked = data.relay1Level;\n");
  message +=         F("document.getElementById('relay2Level').checked = data.relay2Level;\n");
  message +=         F("document.getElementById('relay3Level').checked = data.relay3Level;\n");
  message +=         F("document.getElementById('relay4Level').checked = data.relay4Level;\n");
  message +=         F("if (data.beepeep > 0) {document.location.href = \"/alert\"}}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");
  message += F("setInterval(refreshSens, 1000);\n");
  message += F("</script>");
  message += F("</head>");
  message += F("<body>");
  message += F("<form method=\"get\" action=\"/save\">");
  message += F("<h3>Управление контролем</h3>");
  //message += "<br>";

  message += F("&nbsp;<fieldset style=\"width: 304px\">");
  message += F("<legend><b>Настройки реле</b></legend>");

  message += F("<input type=\"checkbox\" name=\"resumeState\" class=\"checkbox\" id=\"resumeState\" onchange=\"openUrl('/switch?resumeState=' + this.checked);\" ");
  if (resumeState == 1) message += F("checked ");
  message += F("/><label for=\"resumeState\">Восстанавливать сотояния реле</label>");

  message += F("<br>");
  message += F("<br>");
  message += F("<b>Активация реле высоким уровнем</b>");
  message += F("<br>");
  message += F("<br>");

  message += F("<input type=\"checkbox\" name=\"relay1Level\" class=\"checkbox\" id=\"relay1Level\" onchange=\"openUrl('/switch?relay1Level=' + this.checked);\" ");
  if (relay1Level == 1) message += F("checked ");
  message += F("/><label for=\"relay1Level\">Водяной насос</label><p>");

  message += F("<input type=\"checkbox\" name=\"relay2Level\" class=\"checkbox\" id=\"relay2Level\" onchange=\"openUrl('/switch?relay2Level=' + this.checked);\" ");
  if (relay2Level == 1) message += F("checked ");
  message += F("/><label for=\"relay2Level\">Дренажный насос</label><p>");

  message += F("<input type=\"checkbox\" name=\"relay3Level\" class=\"checkbox\" id=\"relay3Level\" onchange=\"openUrl('/switch?relay3Level=' + this.checked);\" ");
  if (relay3Level == 1) message += F("checked ");
  message += F("/><label for=\"relay3Level\">Клапан (вода на баню)</label><p>");

  message += F("<input type=\"checkbox\" name=\"relay4Level\" class=\"checkbox\" id=\"relay4Level\" onchange=\"openUrl('/switch?relay4Level=' + this.checked);\" ");
  if (relay4Level == 1) message += F("checked ");
  message += F("/><label for=\"relay4Level\">Клапан (слив с бани)</label>");

  message += F("</fieldset>");

  message += F("&nbsp;<fieldset style=\"width: 304px\">");
  message += F("<legend><b>Датчики температуры</b></legend>");
  message += F("<br>");

  for (byte i = 0; i < NSenseFact; i++) {
    if (t[i] != 0) {
      message += F("<input type=\"checkbox\" name=\"t"); message += String(i); message += F("\" class=\"checkbox\" id=\"t"); message += String(i);
      message += F("\" onchange=\"openUrl('/switch?SenseStatus"); message += String(i); message += F("=' + this.checked);\" ");
      if (t[i] == 1) message += F("checked ");
      message += F("/><label for=\"t"); message += String(i); message += F("\">Датчик "); message += String(i); message += F(" </label>");
      message += F("<input type=\"text\" name=\"tNameSens"); message += String(i); message += F("\" id=\"tNameSens"); message += String(i) + (" maxlength=\"30\" value=\"");
      message += tNameSens[i]; message += F("\" />");

      message += F("<p>");
    }
  }

  message += F("<b>Настройка чтения</b><br>");

  message += F("<input name = \"error_read_ds_Max\" id=\"error_read_ds_Max\" type=\"text\" value=\"");
  message += String(error_read_ds_Max) + F("\" class=\"textStyle2\" title=\"Разрешенное количество ошибок (подряд) при опросе датчиков температуры\" maxlength=\"2\"");
  message += F("/> Кол.ошибок (подряд) при опросе<br />");

  message += F("<input name=\"t_msec_get_ds\" id=\"t_msec_get_ds\" type=\"text\" value=\"");
  message += String(t_msec_get_ds) + F("\" class=\"textStyle2\" title=\"Интервал опроса датчиков,мСек\" maxlength=\"5\""); message += F("/> Интервал опроса,мСек<br />");

  message += F("<input name=\"Zaderj\" id=\"Zaderj\" type=\"text\" value=\"");
  message += String(Zaderj) + F("\" class=\"textStyle2\" title=\"задержка опроса датчиков,мСек\" maxlength=\"5\""); message += F("/> Задержка опроса,мСек<br />");

  message += F("<input name=\"jamp_t\" id=\"jamp_t\" type=\"text\" value=\"");
  message += String(jamp_t) + F("\" class=\"textStyle2\" title=\"Максимальная значение изменния температуры за опрос\" maxlength=\"2\""); message += F("/> Макс.скор.измен темп.,С/опрос<br />");

  message += F("<input name=\"log_t\" id=\"log_t\" type=\"text\" value=\"");
  message += String(log_t) + F("\" class=\"textStyle2\" title=\"Записывать температуру в лог файл mesure.log через заданное количество минут\" maxlength=\"4\""); message += F("/> Фиксир.температ через, мин<br />");

  message += F("<input type=\"button\" id=\"butt_search_sense\" value=\"Поиск\" onclick=\"openUrl('/switch?Srch=' + '1'); location.href='/selectProm'; \" >\n");
  message += F("<br />");

  if ((error_read_ds > 0) || (error_read_ds_all > 0)) {
    message += F("Ошибок при чтении t (всего): "); message += String(error_read_ds_all) + F("<br />");
  }
  if (error_read_correct_ds_all > 0) {
    message += F("Корректность чтения t (всего): "); message += String(error_read_correct_ds_all) + F("<br />");
  }

  message += F("</fieldset>");

  message += F("<p>");

  message += F("<fieldset style=\"width: 304px\">");
  message += F("<legend><b>Датчики через АЦП</b></legend>");
  message += F("<input name=\"U_lev1\" id=\"U_lev1\" type=\"text\" value=\""); message += String(U_lev1) + F("\" class=\"textStyle2\" title=\"Сигнал читаемый с АЦП при замыкании геркона нижнего датчика в диапазоне от 0 до 1023\" maxlength=\"4\"/> АЦП (датчик нижн.0-1023)<br>");
  message += F("<input name=\"U_lev2\" id=\"U_lev2\" type=\"text\" value=\""); message += String(U_lev2) + F("\" class=\"textStyle2\" title=\"Сигнал читаемый с АЦП при замыкании геркона верхнего датчика в диапазоне от 0 до 1023\" maxlength=\"4\"/> АЦП (датчик верх.0-1023)<br>");
  message += F("<input name=\"U_lev12\" id=\"U_lev12\" type=\"text\" value=\""); message += String(U_lev12) + F("\" class=\"textStyle2\" title=\"Сигнал читаемый с АЦП когда замыкаются герконы на верхнем и нижнем датчиках, т.е. сработали оба два в диапазоне от 0 до 1023\" maxlength=\"4\"/> АЦП (вместе верх.и низ.0-1023)<br>");
  message += F("<input name=\"U_delta\" id=\"U_delta\" type=\"text\" value=\""); message += String(U_delta) + F("\" class=\"textStyle2\" title=\"Допустимое отклонение сигнал читаемого с АЦП в диапазоне от 0 до 100\" maxlength=\"3\"/> Допустимое отклонение (0-100)<br>");

  message += F("</fieldset>");


  message += F("<br />");

  message += F("<fieldset style=\"width: 304px\">");
  message += F("<legend><b>Логи</b></legend>");

  message += F("<input type=\"checkbox\" name=\"writeSysLog\" class=\"checkbox\" id=\"writeSysLog\" onchange=\"openUrl('/switch?writeSysLog=' + this.checked);\" ");
  if (writeSysLog == 1) message += F("checked ");
  message += F("/><label for=\"writeSysLog\">Записывать системные логи</label><p>");
  message += F("<input type=\"checkbox\" name=\"writeSenseLog\" class=\"checkbox\" id=\"writeSenseLog\" onchange=\"openUrl('/switch?writeSenseLog=' + this.checked);\" ");
  if (writeSenseLog == 1) message += F("checked ");
  message += F("/><label for=\"writeSenseLog\">Записывать темпер. логи</label><p>");

  message += F("<input name=\"logFileSize\" id=\"logFileSize\" type=\"text\" value=\""); message += String(logFileSize) + F("\" class=\"textStyle2\" title=\"Размер файла лога в kBytes (файлов будет четыре system.log, mesure.log, кода будет превышен размер произойдет копирование в system01.log и mesure01.log, а исходные файлы начнутся сначала) от 20 до 250\" maxlength=\"3\"/> Размер файла,kBytes (20-250)<br>");

  message += F("</fieldset>");

  message += F("<input type=\"button\" value=\"Назад\" onclick=\"location.href='/'\"><input type=\"submit\" value=\"Сохранить\" />");

  message += F("</form>");
  message += F("</body>");
  message += F("</html>");
  server.send(200, F("text/html"), message);
}
//-------------------------------------------------------------------------------
void h_selectProm()//selectProm
{
  LoginContr();

  String message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<title>Store Setup</title>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\" http-equiv=\"refresh\" content=\"0; /select\">");
  message += F("</head>");
  message += F("<body>");
  message += F("Поиск датчиков выполнен.");
  message += F("<p>Ждите 1 сек. или нажмите <a href=\"/select\">сюда</a> для перехода в настройку сообщений.");
  message += F("</body>");
  message += F("</html>");
  server.send(200, F("text/html"), message);
}
//---------------------------------------------------------------------------------
void h_data_mainPage()//data_mainPage
{
  LoginContr();
  String message;
  message += F("{");

  message += F("\"autoMode\":");
  if (autoMode) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"relay1\":");
  if (swt1) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"relay2\":");
  if (swt2) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"relay3\":");
  if (swt3) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"relay4\":");
  if (swt4) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"relay1Level\":");
  if (relay1Level) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"relay2Level\":");
  if (relay2Level) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"relay3Level\":");
  if (relay3Level) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"relay4Level\":");
  if (relay4Level) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"lev1\":");
  if (lev1) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"lev2\":");
  if (lev2) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"now_relay1\":");
  if (now_relay1) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"now_relay2\":");
  if (now_relay2) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"now_relay3\":");
  if (now_relay3) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"now_relay4\":");
  if (now_relay4) message += 1;
  else message += 0;
  message += F(",");

  message += F("\"str_t_working_WaterPump\":\""); message += String(str_t_working_WaterPump) + F("\",");
  message += F("\"str_t_next_start_WaterPump\":\""); message += String(str_t_next_start_WaterPump) + F("\",");
  message += F("\"str_t_working_DrainagePump\":\""); message += String(str_t_working_DrainagePump) + F("\",");
  message += F("\"str_t_next_start_DrainagePump\":\""); message += String(str_t_next_start_DrainagePump) + F("\",");


  message += F("\"t_lev1_on\":"); message += String(t_OnLevel_1) + F(",");
  message += F("\"t_lev2_on\":"); message += String(t_OnLevel_2) + F(",");

  message += F("\"t_lev1_off\":"); message += String(t_OffLevel_1) + F(",");
  message += F("\"t_lev2_off\":"); message += String(t_OffLevel_2) + F(",");


  message += F("\"strtworkBanyWater\":\""); message += String(strtworkBanyWater) + F("\",");
  message += F("\"strtworkBanySliv\":\""); message += String(strtworkBanySliv) + F("\",");

  for (byte i = 0; i <= NSenseFact; i++) {
    if (t[i] == 1) {//датчик активен (0-не использ,1-активен,2-используется но не активен)
      message += F("\"tempC"); message += String(i); message += F("\":"); message += tempC[i]; message += F(",");
    }
  }
  message += F("\"timeStr\":\""); message += String(timeStr) + F("\"");
  message += F(",");
  message += F("\"TimeOn\":\""); message += String(TimeOn) + F("\"");
  message += F(",");
  message += F("\"MQTT\":\"");
  if (useMQTT) {
    if (mqttClient.connected()) {
      message += F("Соединено");
      message += F("\"");
    }
    else {
      message += F("Разорвано");
      message += F("\"");
    }
  }
  else {
    message += F("Выключено");
    message += F("\"");
  }
  message += F(",");
  message += F("\"info\":\""); message += String(str_info) + F("\"");
  message += F("}");

  server.send(200, F("text/html"), message);
}
//---------------------------------------------------------------------------------------------------
void handleGetTimer() {

  LoginContr();
  int8_t R_hour, R_min, R_sec, R_day, R_month;
  uint8_t R_wd;
  int16_t R_year;

  parseUnixTime(startTime, R_hour, R_min, R_sec, R_wd, R_day, R_month, R_year);
  server.send(200, F("text/html"), "ok");
}
//-------------------------------------
void handleSetTimer() {
  LoginContr();

  int8_t R_hour, R_min, R_sec, R_day, R_month;
  uint8_t R_wd;
  int16_t R_year;
  String message;

  parseUnixTime(now_timeUnx, R_hour, R_min, R_sec, R_wd, R_day, R_month, R_year);

  message += F("{");
  message += F("\"R_hour\":"); message += String(R_hour) + F(",");
  message += F("\"R_min\":"); message += String(R_min) + F(",");
  message += F("\"R_sec\":"); message += String(R_sec) + F(",");

  message += F("\"R_day\":"); message += String(R_day) + F(",");
  message += F("\"R_month\":"); message += String(R_month) + F(",");
  message += F("\"R_year\":"); message += String(R_year);
  message += F("}");

  server.send(200, F("text/html"), message);
}

