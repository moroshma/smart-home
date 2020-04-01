//---------------------------------------------------------------------------------------------
void h_WaterPump()//WaterPump
{
  LoginContr();
  String message;
  message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<title>Режим работы водяного насоса</title>");
  message += F("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  message += F("<meta charset=\"utf-8\">");
  message += F("<style type=\"text/css\">");
  message += F(".style1 {");
  message += F("border-style: solid;");
  message += F("border-width: 1px;");
  message += F("text-align: center;");
  message += F("}");
  message += textStyle();
  message += F("</style>");
  message += F("<script type=\"text/javascript\">");
  message += F("function openUrl(url) {\n");
  message += F("var request = new XMLHttpRequest();\n");
  message += F("request.open('GET', url, true);\n");
  message += F("request.send(null);\n ");
  message += F("};\n ");
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

  message += F("function filStTimer(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/data_settimer', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("document.getElementById('TimerWaterPumpDaySt').value = data.R_day;\n");
  message +=         F("document.getElementById('TimerWaterPumpMonthSt').value = data.R_month;\n");
  message +=         F("document.getElementById('TimerWaterPumpYearSt').value = data.R_year;\n");
  message +=         F("document.getElementById('TimerWaterPumpHourSt').value = data.R_hour;\n");
  message +=         F("document.getElementById('TimerWaterPumpMinSt').value = data.R_min;\n");
  message +=         F("document.getElementById('TimerWaterPumpSecSt').value = data.R_sec;}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");

  message += F("function filEndTimer(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/data_settimer', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("document.getElementById('TimerWaterPumpDayEnd').value = data.R_day;\n");
  message +=         F("document.getElementById('TimerWaterPumpMonthEnd').value = data.R_month;\n");
  message +=         F("document.getElementById('TimerWaterPumpYearEnd').value = data.R_year;\n");
  message +=         F("document.getElementById('TimerWaterPumpHourEnd').value = data.R_hour;\n");
  message +=         F("document.getElementById('TimerWaterPumpMinEnd').value = data.R_min;\n");
  message +=         F("document.getElementById('TimerWaterPumpSecEnd').value = data.R_sec;}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");


  message += F("</script>");
  message += F("</head>");
  message += F("<body>");
  message += F("<form method=\"get\" action=\"/save\">");
  message += F("<h3>Режим работы водяного насоса</h3><p>");

  message += F("ЧЧ : ММ : СС ");
  message += F("<br>");
  message += F("<input name=\"WaterPumpOnHour\" type=\"text\" value=\""); message += String(WaterPumpOnHour) + F("\" class=\"textStyle1\" maxlength=\"2\"/>");
  message += F("<input name=\"WaterPumpOnMin\" type=\"text\" value=\""); message += String(WaterPumpOnMin) + F("\" class=\"textStyle1\" maxlength=\"2\"/>");
  message += F("<input name=\"WaterPumpOnSec\" type=\"text\" value=\""); message += String(WaterPumpOnSec) + F("\" class=\"textStyle1\" maxlength=\"2\"/>");
  message += F("Работа");
  message += F("<br>");
  message += F("<input name=\"WaterPumpOffHour\" type=\"text\" value=\""); message += String(WaterPumpOffHour) + F("\" class=\"textStyle1\" maxlength=\"2\"/>");
  message += F("<input name=\"WaterPumpOffMin\" type=\"text\" value=\""); message += String(WaterPumpOffMin) + F("\" class=\"textStyle1\" maxlength=\"2\"/>");
  message += F("<input name=\"WaterPumpOffSec\" type=\"text\" value=\""); message += String(WaterPumpOffSec) + F("\" class=\"textStyle1\" maxlength=\"2\"/>");
  message += F("Простой");
  message += F("<br>");
  message += F("<p>");
  message += F("Остановка при достижении");
  message += F("<br />");
  message += F("<input type=\"button\" value=\"-\" onclick=\"document.getElementById('TWaterPumpContr').value=PowChange(document.getElementById('TWaterPumpContr').value,-1)\" />");
  message += F("<input id=\"TWaterPumpContr\" name=\"TWaterPumpContr\" type=\"text\" maxlength=\"6\" value=\"");
  message += String(TWaterPumpContr) + F("\" onchange=\"CheckVal('TWaterPumpContr')\" style=\"text-align: center; width: 45px\" />");
  message += F("<input type=\"button\" value=\"+\" onclick=\"document.getElementById('TWaterPumpContr').value=PowChange(document.getElementById('TWaterPumpContr').value,1)\" /> Температура,С");
  message += F("<br />");

  message += F("<select name=\"NsenseWaterPumpContr\" title=\"Использовать датчик \">");

  for (byte i = 0; i < NSenseFact; i++) {
    if (t[i] != 0) {
      message += F("<option value="); message += String(i);
      if (NsenseWaterPumpContr == i) message += F(" selected ");
      if (tNameSens[i].length() > 0) {
        message += F("> "); message += tNameSens[i] + F("</option>");
      }
      else {
        message += F(">Датчик "); message += String(i) + F("</option>");
      }
    }
  }

  message += F("</select>");
  message += F(" для контроля за перегревом<p>");

  message += F("<fieldset style=\"width: 304px\">");
  message += F("<legend><b>Таймеры</b></legend>");
  message += F("Перерывы в работе водяного насоса (ЧЧ:ММ):<br>");
  for (byte i = 0; i < NomPrerWaterPumpAll; i++) {

    message += F("<input type=\"checkbox\" id=\"PrerWaterPumpAvail"); message += String(i); message += F("\" onchange=\"openUrl('/switch?PrerWaterPumpAvail"); message += String(i); message += F("=' + this.checked);\" ");
    if (PrerWaterPump[i].Avail == HIGH) message += F("checked");
    message += F("/><label for=\"PrerWaterPumpAvail"); message += String(i) + F("\">Исп.</label>");

    message += F(" Нач.");

    message += F("<input name=\"PrerWaterPumpHourSt"); message += String(i) + F("\" type=\"text\" value=\""); message += String(PrerWaterPump[i].PrerPumpHourSt) + F("\" class=\"textStyle1\" title=\"час начала паузы\" maxlength=\"2\"/>");
    message += F("<input name=\"PrerWaterPumpMinSt"); message += String(i) + F("\" type=\"text\" value=\""); message += String(PrerWaterPump[i].PrerPumpMinSt) + F("\" class=\"textStyle1\" title=\"минута начала паузы\" maxlength=\"2\"/>");
    message += F(" Кон.");
    message += F("<input name=\"PrerWaterPumpHourEnd"); message += String(i) + F("\" type=\"text\" value=\""); message += String(PrerWaterPump[i].PrerPumpHourEnd) + F("\" class=\"textStyle1\" title=\"час завершения паузы\" maxlength=\"2\"/>");
    message += F("<input name=\"PrerWaterPumpMinEnd"); message += String(i) + F("\" type=\"text\" value=\""); message += String(PrerWaterPump[i].PrerPumpMinEnd) + F("\" class=\"textStyle1\" title=\"минута завершения паузы\" maxlength=\"2\"/>");
    message += F("<br>");
  }
  message += F("<br>");

  //------------
  message += F(" Запуск в ДД:ММ:ГГГГ ЧЧ:MM:CC ");
  message += F("<br>");
  message += F("<input type=\"checkbox\" id=\"TimerWaterPumpAvailSt\" onchange=\"openUrl('/switch?TimerWaterPumpAvailSt=' + this.checked);\" ");
  if (TimerWaterPumpAvailSt == HIGH) message += F("checked");
  message += F("/><label for=\"TimerWaterPumpAvailSt\">Исп.</label>");

  message += F("<input name=\"TimerWaterPumpDaySt\" id=\"TimerWaterPumpDaySt\" type=\"text\" value=\""); message += String(TimerWaterPumpDaySt) + F("\" class=\"textStyle1\" title=\"день запуска\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerWaterPumpMonthSt\" id=\"TimerWaterPumpMonthSt\" type=\"text\" value=\""); message += String(TimerWaterPumpMonthSt) + F("\" class=\"textStyle1\" title=\"месяц запуска\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerWaterPumpYearSt\" id=\"TimerWaterPumpYearSt\" type=\"text\" value=\""); message += String(TimerWaterPumpYearSt) + F("\" class=\"textStyle2\" title=\"год запуска\" maxlength=\"4\"/>");
  message += F(" : ");

  message += F("<input name=\"TimerWaterPumpHourSt\" id=\"TimerWaterPumpHourSt\" type=\"text\" value=\""); message += String(TimerWaterPumpHourSt) + F("\" class=\"textStyle1\" title=\"час запуска\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerWaterPumpMinSt\" id=\"TimerWaterPumpMinSt\" type=\"text\" value=\""); message += String(TimerWaterPumpMinSt) + F("\" class=\"textStyle1\" title=\"минута запуска\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerWaterPumpSecSt\" id=\"TimerWaterPumpSecSt\" type=\"text\" value=\""); message += String(TimerWaterPumpSecSt) + F("\" class=\"textStyle1\" title=\"секунда запуска\" maxlength=\"2\"/>");
  message += F("&nbsp;");
  message += F("<input type=\"button\" value=\"<\" onclick=\"filStTimer();\" title=\"Заполнить поля текущими датой и временем\">");

  message += F("<br>");

  //------------
  message += F(" Остан. в ДД:ММ:ГГГГ ЧЧ:MM:CC ");
  message += F("<br>");
  message += F("<input type=\"checkbox\" id=\"TimerWaterPumpAvailEnd\" onchange=\"openUrl('/switch?TimerWaterPumpAvailEnd=' + this.checked);\" ");
  if (TimerWaterPumpAvailEnd == HIGH) message += F("checked");
  message += F("/><label for=\"TimerWaterPumpAvailEnd\">Исп.</label>");

  message += F("<input name=\"TimerWaterPumpDayEnd\" id=\"TimerWaterPumpDayEnd\" type=\"text\" value=\""); message += String(TimerWaterPumpDayEnd) + F("\" class=\"textStyle1\" title=\"день останова\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerWaterPumpMonthEnd\" id=\"TimerWaterPumpMonthEnd\" type=\"text\" value=\""); message += String(TimerWaterPumpMonthEnd) + F("\" class=\"textStyle1\" title=\"месяц останова\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerWaterPumpYearEnd\" id=\"TimerWaterPumpYearEnd\" type=\"text\" value=\""); message += String(TimerWaterPumpYearEnd) + F("\" class=\"textStyle2\" title=\"год останова\" maxlength=\"4\"/>");
  message += F(" : ");
  message += F("<input name=\"TimerWaterPumpHourEnd\" id=\"TimerWaterPumpHourEnd\" type=\"text\" value=\""); message += String(TimerWaterPumpHourEnd) + F("\" class=\"textStyle1\" title=\"час останова\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerWaterPumpMinEnd\" id=\"TimerWaterPumpMinEnd\" type=\"text\" value=\""); message += String(TimerWaterPumpMinEnd) + F("\" class=\"textStyle1\" title=\"минута останова\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerWaterPumpSecEnd\" id=\"TimerWaterPumpSecEnd\" type=\"text\" value=\""); message += String(TimerWaterPumpSecEnd) + F("\" class=\"textStyle1\" title=\"секунда останова\" maxlength=\"2\"/>");
  message += F("&nbsp;");
  message += F("<input type=\"button\" value=\"<\" onclick=\"filEndTimer();\" title=\"Заполнить поля текущими датой и временем\">");
  message += F("</fieldset>");
  message += F("<br>");
  message += F("<p>");
  message += F("<input type=\"button\" value=\"Назад\"  onclick=\"location.href='/'\"><input type=\"submit\" value=\"Сохранить\" />");
  message += F("</form>");
  message += F("</body>");
  message += F("</html>");

  server.send(200, "text/html", message);
}
//--------------------------------------------------------------------
void ManageRele1(boolean StRele)
{
  if (swt1 == true) {
    if (relay2Level == 0) StRele = !StRele;
    MydigitalWrite(swt1_pin, StRele);
  }
  else {
    if (relay2Level == 1)
      MydigitalWrite(swt1_pin, LOW);
    else
      MydigitalWrite(swt1_pin, HIGH);
  }
}
//----------------------------------------------------------------------------------------------------------------------------------------------------------------
void working_WaterPump()
{
  uint32_t t_prom;
  bool StatusWaterPump, now_StatusWaterPump;

  TWaterPumpContr_now = -128;
  for (byte i = 0; i < NSenseFact; i++) {
    if (NsenseWaterPumpContr == i) TWaterPumpContr_now = tempC[i];
  }
  t_prom = millis(); //текущее время
  if (swt1 == true) {
    if (prev_swt1 != swt1) {
      prev_swt1 = swt1;
      t_WaterPump = t_prom / 1000;
      t_pow_on_WaterPump = 0;
      t_pow_off_WaterPump = 0;
      Serial.println("  swt1 true = " + String(swt1));
      if (useMQTT && mqttClient.connected()) {
        delay(25);
        mqttClient.publish("swt/1", String(swt1).c_str(), true);
      }
    }
  }
  else {
    if (prev_swt1 != swt1)   {
      Serial.println("  swt1 false = " + String(swt1));
      prev_swt1 = swt1;
      if (useMQTT && mqttClient.connected()) {
        delay(25);
        mqttClient.publish("swt/1", String(swt1).c_str(), true);
      }
    }
  }

  if (swt1 == true) {
    t_work_WaterPump = t_prom / 1000 - t_WaterPump;

    if ((t_work_WaterPump >= WaterPumpTime) && (WaterPumpTime != 0))
    { //отключение по таймеру
      swt1 = false; prev_swt1 = LOW; StatusWaterPump = LOW;
    }
    if (WaterPumpWorkTime != 0) {//если установлено время "Миксер включен"
      if ((t_pow_on_WaterPump == 0) && (t_pow_off_WaterPump == 0)) t_pow_on_WaterPump = t_prom / 1000;
      if (((t_prom / 1000 - t_pow_on_WaterPump) < WaterPumpWorkTime) && (t_pow_off_WaterPump == 0)) StatusWaterPump = HIGH;
      if (((t_prom  / 1000 - t_pow_on_WaterPump) >= WaterPumpWorkTime) && (t_pow_off_WaterPump == 0)) {
        t_pow_on_WaterPump = 0;
        if (WaterPumpStopTime != 0) t_pow_off_WaterPump = t_prom / 1000;
        else {
          swt1 = LOW; prev_swt1 = LOW; StatusWaterPump = LOW;
        }
      }
      if (WaterPumpStopTime != 0) { //если установлено время "Миксер выключен"
        if (((t_prom / 1000 - t_pow_off_WaterPump) < WaterPumpStopTime) && (t_pow_on_WaterPump == 0)) {
          StatusWaterPump = LOW;
          t_next_start_WaterPump = WaterPumpStopTime + t_pow_off_WaterPump - t_prom / 1000;
        }
        if (((t_prom / 1000 - t_pow_off_WaterPump) >= WaterPumpStopTime) && (t_pow_on_WaterPump == 0)) {
          t_pow_on_WaterPump = t_prom / 1000;
          t_pow_off_WaterPump = 0;
          t_next_start_WaterPump = 0;
        }
      }
    }
    else {//иначе просто включен
      StatusWaterPump = HIGH;
    }

    if ((TWaterPumpContr_now >= TWaterPumpContr) && (TWaterPumpContr != 0))
    { //останов по превышению разреш температуры обычно до 55 чтоб не было пены
      StatusWaterPump = LOW;
      Serial.println(F("module working_WaterPump: WaterPump stop, overwarm"));
    }

    // управление таймерами/перерывами
    now_StatusWaterPump = HIGH;
    if (now_year > 1970) {
      //считаем время установлено
      parseUnixTime(now_timeUnx, now_hour, now_min, now_sec, now_wd, now_day, now_month, now_year);
      for (byte i = 0; i < NomPrerWaterPumpAll; i++) {
        //перебираем все интервалы
        if ((PrerWaterPump[i].PrerPumpStUnx < PrerWaterPump[i].PrerPumpEndUnx) && (PrerWaterPump[i].Avail == 1))
        { //проверяем интервал, время начала должно быть меньше времени окончания и интервал активен
          //получаем юникс время тек.интервала
          PrerWaterPump[i].PrerPumpStUnx = combineUnixTime(PrerWaterPump[i].PrerPumpHourSt, PrerWaterPump[i].PrerPumpMinSt, 0, now_day, now_month, now_year); // Собрать время в формат UNIX-time
          PrerWaterPump[i].PrerPumpEndUnx = combineUnixTime(PrerWaterPump[i].PrerPumpHourEnd, PrerWaterPump[i].PrerPumpMinEnd, 0, now_day, now_month, now_year); // Собрать время в формат UNIX-time

          if ((now_timeUnx > PrerWaterPump[i].PrerPumpStUnx) && (now_timeUnx < PrerWaterPump[i].PrerPumpEndUnx)) {
            //время попадает в выбранный интервал - миксер отключаем, ставим статус
            now_StatusWaterPump = now_StatusWaterPump & LOW;
          }
        }
      }

      if ((TimerWaterPumpStUnx > 0) && (TimerWaterPumpAvailSt == 1)) { //время отсроченного старта установлено
        if (now_timeUnx > TimerWaterPumpStUnx) {//сейчас время больше чем время вкл, значит включаем
          now_StatusWaterPump = now_StatusWaterPump & HIGH;
        } else { //выключаем
          now_StatusWaterPump = now_StatusWaterPump & LOW;
        }
      }
      if ((TimerWaterPumpEndUnx > 0) && (TimerWaterPumpAvailEnd == 1)) { //время отсроченного выключения установлено
        if (now_timeUnx > TimerWaterPumpEndUnx) {//сейчас время больше чем время откл, значит выключаем
          now_StatusWaterPump = now_StatusWaterPump & LOW;
        } else { //включаем
          now_StatusWaterPump = now_StatusWaterPump & HIGH;
        }
      }
    }
  }
  else {//если движок миксер выключен
    StatusWaterPump = LOW;
  }
  StatusWaterPump = StatusWaterPump & now_StatusWaterPump;

  //второй датчик уровня верх
  if (lev2 == HIGH) {
    if ((t_prom - t_lev2_on) > 5000) {//надо выключать водяной насос
      StatusWaterPump = LOW;
    }
  }
  
  ManageRele1(StatusWaterPump);
}
//------------------------------------------------------------------------------------------------------------------


