//---------------------------------------------------------------------------------------------
void h_DrainagePump()//DrainagePump
{
  LoginContr();
  String message;
  message = F("<!DOCTYPE html>");
  message += F("<html>");
  message += F("<head>");
  message += F("<title>Режим работы ДРЕНАЖНОГО насоса</title>");
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
  message +=         F("document.getElementById('TimerDrainagePumpDaySt').value = data.R_day;\n");
  message +=         F("document.getElementById('TimerDrainagePumpMonthSt').value = data.R_month;\n");
  message +=         F("document.getElementById('TimerDrainagePumpYearSt').value = data.R_year;\n");
  message +=         F("document.getElementById('TimerDrainagePumpHourSt').value = data.R_hour;\n");
  message +=         F("document.getElementById('TimerDrainagePumpMinSt').value = data.R_min;\n");
  message +=         F("document.getElementById('TimerDrainagePumpSecSt').value = data.R_sec;}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");

  message += F("function filEndTimer(){\n");
  message +=   F("var request = new XMLHttpRequest();\n");
  message +=   F("request.open('GET', '/data_settimer', true);\n");
  message +=   F("request.onreadystatechange = function(){\n");
  message +=       F("if (request.readyState == 4) {\n");
  message +=         F("var data = JSON.parse(request.responseText);\n ");
  message +=         F("document.getElementById('TimerDrainagePumpDayEnd').value = data.R_day;\n");
  message +=         F("document.getElementById('TimerDrainagePumpMonthEnd').value = data.R_month;\n");
  message +=         F("document.getElementById('TimerDrainagePumpYearEnd').value = data.R_year;\n");
  message +=         F("document.getElementById('TimerDrainagePumpHourEnd').value = data.R_hour;\n");
  message +=         F("document.getElementById('TimerDrainagePumpMinEnd').value = data.R_min;\n");
  message +=         F("document.getElementById('TimerDrainagePumpSecEnd').value = data.R_sec;}};\n");
  message +=   F("request.send(null);\n");
  message +=   F("}\n");


  message += F("</script>");
  message += F("</head>");
  message += F("<body>");
  message += F("<form method=\"get\" action=\"/save\">");
  message += F("<h3>Режим работы дренажного насоса</h3><p>");

  message += F("ЧЧ : ММ : СС ");
  message += F("<br>");
  message += F("<input name=\"DrainagePumpOnHour\" type=\"text\" value=\""); message += String(DrainagePumpOnHour) + F("\" class=\"textStyle1\" maxlength=\"2\"/>");
  message += F("<input name=\"DrainagePumpOnMin\" type=\"text\" value=\""); message += String(DrainagePumpOnMin) + F("\" class=\"textStyle1\" maxlength=\"2\"/>");
  message += F("<input name=\"DrainagePumpOnSec\" type=\"text\" value=\""); message += String(DrainagePumpOnSec) + F("\" class=\"textStyle1\" maxlength=\"2\"/>");
  message += F("Работа");
  message += F("<br>");
  message += F("<input name=\"DrainagePumpOffHour\" type=\"text\" value=\""); message += String(DrainagePumpOffHour) + F("\" class=\"textStyle1\" maxlength=\"2\"/>");
  message += F("<input name=\"DrainagePumpOffMin\" type=\"text\" value=\""); message += String(DrainagePumpOffMin) + F("\" class=\"textStyle1\" maxlength=\"2\"/>");
  message += F("<input name=\"DrainagePumpOffSec\" type=\"text\" value=\""); message += String(DrainagePumpOffSec) + F("\" class=\"textStyle1\" maxlength=\"2\"/>");
  message += F("Простой");
  message += F("<br>");
  message += F("<p>");
  message += F("Остановка при достижении");
  message += F("<br />");
  message += F("<input type=\"button\" value=\"-\" onclick=\"document.getElementById('TDrainagePumpContr').value=PowChange(document.getElementById('TDrainagePumpContr').value,-1)\" />");
  message += F("<input id=\"TDrainagePumpContr\" name=\"TDrainagePumpContr\" type=\"text\" maxlength=\"6\" value=\"");
  message += String(TDrainagePumpContr) + F("\" onchange=\"CheckVal('TDrainagePumpContr')\" style=\"text-align: center; width: 45px\" />");
  message += F("<input type=\"button\" value=\"+\" onclick=\"document.getElementById('TDrainagePumpContr').value=PowChange(document.getElementById('TDrainagePumpContr').value,1)\" /> Температура,С");
  message += F("<br />");

  message += F("<select name=\"NsenseDrainagePumpContr\" title=\"Использовать датчик \">");

  for (byte i = 0; i < NSenseFact; i++) {
    if (t[i] != 0) {
      message += F("<option value="); message += String(i);
      if (NsenseDrainagePumpContr == i) message += F(" selected ");
      if (tNameSens[i].length() > 0) {
        message += F("> "); message += tNameSens[i] + F("</option>");
      }
      else {
        message += F(">Датчик "); message += String(i) + F("</option>");
      }
    }
  }

  message += F("</select>");
  message += F(" для контроля за нагревом<p>");

  

  message += F("<fieldset style=\"width: 304px\">");
  message += F("<legend><b>Таймеры</b></legend>");

  message += F("Через <input name=\"over_t_lev1_on\" id=\"over_t_lev1_on\" type=\"text\" value=\""); message += String(over_t_lev1_on) + F("\" class=\"textStyle2\" title=\"Время через которое включится дренажный насос после замыкании геркона нижнего датчика в секундах от 0 до 1000\" maxlength=\"4\"/> сек. после активации нижн.датчика включить помпу<br>");
  message += F("Через <input name=\"over_t_lev1_off\" id=\"over_t_lev1_off\" type=\"text\" value=\""); message += String(over_t_lev1_off) + F("\" class=\"textStyle2\" title=\"Время через которое выключится дренажный насос после размыкании геркона нижнего датчика в секундах от 0 до 1000\" maxlength=\"4\"/> сек. после деактивации нижн.датчика выключить помпу<br>");
  message += F("Через <input name=\"over_t_lev2_on\" id=\"over_t_lev2_on\" type=\"text\" value=\""); message += String(over_t_lev2_on) + F("\" class=\"textStyle2\" title=\"Время через которое включится дренажный насос после замыкании геркона верхнего датчика в секундах от 0 до 1000\" maxlength=\"4\"/> сек. после активации верхн.датчика включить помпу<br>");
  message += F("Через <input name=\"over_t_lev2_off\" id=\"over_t_lev2_off\" type=\"text\" value=\""); message += String(over_t_lev2_off) + F("\" class=\"textStyle2\" title=\"Время через которое выключится дренажный насос после размыкании геркона верхнего датчика в секундах от 0 до 1000\" maxlength=\"4\"/> сек. после деактивации верхн.датчика выключить помпу<br>");
  message += F("<br>");
  
  if (NomPrerDrainagePumpAll > 0) {
    message += F("Перерывы в работе водяной помпы (ЧЧ:ММ):<br>");
  }
  for (byte i = 0; i < NomPrerDrainagePumpAll; i++) {

    message += F("<input type=\"checkbox\" id=\"PrerDrainagePumpAvail"); message += String(i); message += F("\" onchange=\"openUrl('/switch?PrerDrainagePumpAvail"); message += String(i); message += F("=' + this.checked);\" ");
    if (PrerDrainagePump[i].Avail == HIGH) message += F("checked");
    message += F("/><label for=\"PrerDrainagePumpAvail"); message += String(i) + F("\">Исп.</label>");
    message += F(" Нач.");
    message += F("<input name=\"PrerDrainagePumpHourSt"); message += String(i) + F("\" type=\"text\" value=\""); message += String(PrerDrainagePump[i].PrerPumpHourSt) + F("\" class=\"textStyle1\" title=\"час начала паузы\" maxlength=\"2\"/>");
    message += F("<input name=\"PrerDrainagePumpMinSt"); message += String(i) + F("\" type=\"text\" value=\""); message += String(PrerDrainagePump[i].PrerPumpMinSt) + F("\" class=\"textStyle1\" title=\"минута начала паузы\" maxlength=\"2\"/>");
    message += F(" Кон.");
    message += F("<input name=\"PrerDrainagePumpHourEnd"); message += String(i) + F("\" type=\"text\" value=\""); message += String(PrerDrainagePump[i].PrerPumpHourEnd) + F("\" class=\"textStyle1\" title=\"час завершения паузы\" maxlength=\"2\"/>");
    message += F("<input name=\"PrerDrainagePumpMinEnd"); message += String(i) + F("\" type=\"text\" value=\""); message += String(PrerDrainagePump[i].PrerPumpMinEnd) + F("\" class=\"textStyle1\" title=\"минута завершения паузы\" maxlength=\"2\"/>");
    message += F("<br>");
  }
  message += F("<br>");
  //------------
  message += F(" Запуск в ДД:ММ:ГГГГ ЧЧ:MM:CC ");
  message += F("<br>");
  message += F("<input type=\"checkbox\" id=\"TimerDrainagePumpAvailSt\" onchange=\"openUrl('/switch?TimerDrainagePumpAvailSt=' + this.checked);\" ");
  if (TimerDrainagePumpAvailSt == HIGH) message += F("checked");
  message += F("/><label for=\"TimerDrainagePumpAvailSt\">Исп.</label>");

  message += F("<input name=\"TimerDrainagePumpDaySt\" id=\"TimerDrainagePumpDaySt\" type=\"text\" value=\""); message += String(TimerDrainagePumpDaySt) + F("\" class=\"textStyle1\" title=\"день запуска\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerDrainagePumpMonthSt\" id=\"TimerDrainagePumpMonthSt\" type=\"text\" value=\""); message += String(TimerDrainagePumpMonthSt) + F("\" class=\"textStyle1\" title=\"месяц запуска\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerDrainagePumpYearSt\" id=\"TimerDrainagePumpYearSt\" type=\"text\" value=\""); message += String(TimerDrainagePumpYearSt) + F("\" class=\"textStyle2\" title=\"год запуска\" maxlength=\"4\"/>");
  message += F(" : ");

  message += F("<input name=\"TimerDrainagePumpHourSt\" id=\"TimerDrainagePumpHourSt\" type=\"text\" value=\""); message += String(TimerDrainagePumpHourSt) + F("\" class=\"textStyle1\" title=\"час запуска\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerDrainagePumpMinSt\" id=\"TimerDrainagePumpMinSt\" type=\"text\" value=\""); message += String(TimerDrainagePumpMinSt) + F("\" class=\"textStyle1\" title=\"минута запуска\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerDrainagePumpSecSt\" id=\"TimerDrainagePumpSecSt\" type=\"text\" value=\""); message += String(TimerDrainagePumpSecSt) + F("\" class=\"textStyle1\" title=\"секунда запуска\" maxlength=\"2\"/>");
  message += F("&nbsp;");
  message += F("<input type=\"button\" value=\"<\" onclick=\"filStTimer();\" title=\"Заполнить поля текущими датой и временем\">");

  message += F("<br>");

  //------------
  message += F(" Остан. в ДД:ММ:ГГГГ ЧЧ:MM:CC ");
  message += F("<br>");
  message += F("<input type=\"checkbox\" id=\"TimerDrainagePumpAvailEnd\" onchange=\"openUrl('/switch?TimerDrainagePumpAvailEnd=' + this.checked);\" ");
  if (TimerDrainagePumpAvailEnd == HIGH) message += F("checked");
  message += F("/><label for=\"TimerDrainagePumpAvailEnd\">Исп.</label>");

  message += F("<input name=\"TimerDrainagePumpDayEnd\" id=\"TimerDrainagePumpDayEnd\" type=\"text\" value=\""); message += String(TimerDrainagePumpDayEnd) + F("\" class=\"textStyle1\" title=\"день останова\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerDrainagePumpMonthEnd\" id=\"TimerDrainagePumpMonthEnd\" type=\"text\" value=\""); message += String(TimerDrainagePumpMonthEnd) + F("\" class=\"textStyle1\" title=\"месяц останова\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerDrainagePumpYearEnd\" id=\"TimerDrainagePumpYearEnd\" type=\"text\" value=\""); message += String(TimerDrainagePumpYearEnd) + F("\" class=\"textStyle2\" title=\"год останова\" maxlength=\"4\"/>");
  message += F(" : ");
  message += F("<input name=\"TimerDrainagePumpHourEnd\" id=\"TimerDrainagePumpHourEnd\" type=\"text\" value=\""); message += String(TimerDrainagePumpHourEnd) + F("\" class=\"textStyle1\" title=\"час останова\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerDrainagePumpMinEnd\" id=\"TimerDrainagePumpMinEnd\" type=\"text\" value=\""); message += String(TimerDrainagePumpMinEnd) + F("\" class=\"textStyle1\" title=\"минута останова\" maxlength=\"2\"/>");
  message += F("<input name=\"TimerDrainagePumpSecEnd\" id=\"TimerDrainagePumpSecEnd\" type=\"text\" value=\""); message += String(TimerDrainagePumpSecEnd) + F("\" class=\"textStyle1\" title=\"секунда останова\" maxlength=\"2\"/>");
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
void ManageRele2(bool StRele)
{
  if ((swt2 == true) || (autoMode == true)){
    if (relay2Level == 0) StRele = !StRele;
    MydigitalWrite(swt2_pin, StRele);
  }
  else {
    if (relay2Level == 1)
      MydigitalWrite(swt2_pin, LOW);
    else
      MydigitalWrite(swt2_pin, HIGH);
  }
}
//----------------------------------------------------------------------------------------------------
void working_DrainagePump() {
  uint32_t t_prom;
  bool StatusDrainagePump = LOW;
  bool now_StatusDrainagePump = LOW;

  t_prom = millis(); //текущее время
  if ((autoMode == true) && (errA0 == false))  {
    //первый датчик уровня низ
    if (lev1 == HIGH) {
      t_OnLevel_1 = (t_prom - t_lev1_on) / 1000;
      if ((t_prom - t_lev1_on) > over_t_lev1_on*1000) { //надо включать дренажный насос 
        StatusDrainagePump = HIGH;
      }
    }

    if ((lev1 == LOW) && ((t_prom - t_lev1_off) < over_t_lev1_off*1000)) { //надо удерживать вкл дренажный насос
      t_OffLevel_1 = (t_prom - t_lev1_off) / 1000;                         //но только когда между вкл и выкл датчика прошло больше over_t_lev1_on*1000 секунд
      if (t_lev1_off - t_lev1_on > over_t_lev1_on*1000) StatusDrainagePump = HIGH; 
      
    }

    //второй датчик уровня верх
    if (lev2 == HIGH) {
      t_OnLevel_2 = (t_prom - t_lev2_on) / 1000;
      if ((lev1 == LOW) && ((t_prom - t_lev2_on) > over_t_lev2_on*1000)) {//надо включать дренажный насос
        StatusDrainagePump = HIGH;
      }
    }

    if ((lev1 == LOW) && (lev2 == LOW) && ((t_prom - t_lev2_off) < over_t_lev2_off*1000)) {//надо удерживать вкл дренажный насос
      t_OffLevel_2 = (t_prom - t_lev2_off) / 1000;
      if (t_lev2_off - t_lev2_on > over_t_lev2_on*1000) StatusDrainagePump = HIGH;
    }
  }
  else {
    if ((autoMode == true) && (errA0 == true)) {
      swt2 = true;
    }

    if (swt2 == true)  {
      if (prev_swt2 != swt2) {
        prev_swt2 = swt2;
        t_DrainagePump = t_prom/1000;
        t_pow_on_DrainagePump = 0;
        t_pow_off_DrainagePump = 0;
        Serial.println("  swt2 true = " + String(swt2));
      }
    }
    else {
      if (prev_swt2 != swt2)    {
        Serial.println("  swt2 false = " + String(swt2));
        prev_swt2 = swt2;
      }
    }

    if (swt2 == true)  {
      t_work_DrainagePump = t_prom / 1000 - t_DrainagePump;
      if ((t_work_DrainagePump >= DrainagePumpTime) && (DrainagePumpTime != 0))
      { //отключение по таймеру
        swt2 = false; prev_swt2 = LOW; StatusDrainagePump = LOW;
      }
      if (DrainagePumpWorkTime != 0) {//если установлено время "включен"
        if ((t_pow_on_DrainagePump == 0) && (t_pow_off_DrainagePump == 0)) t_pow_on_DrainagePump = t_prom / 1000;
        if (((t_prom / 1000 - t_pow_on_DrainagePump) < DrainagePumpWorkTime) && (t_pow_off_DrainagePump == 0)) StatusDrainagePump = HIGH;
        if (((t_prom / 1000 - t_pow_on_DrainagePump) >= DrainagePumpWorkTime) && (t_pow_off_DrainagePump == 0)) {
          t_pow_on_DrainagePump = 0;
          if (DrainagePumpStopTime != 0) t_pow_off_DrainagePump = t_prom / 1000;
          else {
            swt2 = LOW; prev_swt2 = LOW; StatusDrainagePump = LOW;
          }
        }
        if (DrainagePumpStopTime != 0) { //если установлено время "выключен"
          if (((t_prom / 1000 - t_pow_off_DrainagePump) < DrainagePumpStopTime) && (t_pow_on_DrainagePump == 0)) {
            StatusDrainagePump = LOW;
            t_next_start_DrainagePump = DrainagePumpStopTime + t_pow_off_DrainagePump - t_prom / 1000;
          }
          if (((t_prom / 1000 - t_pow_off_DrainagePump) >= DrainagePumpStopTime) && (t_pow_on_DrainagePump == 0)) {
            t_pow_on_DrainagePump = t_prom / 1000;
            t_pow_off_DrainagePump = 0;
            t_next_start_DrainagePump = 0;
          }
        }
      }
      else {//иначе просто включен
        StatusDrainagePump = HIGH;
      }
      // управление таймерами/перерывами
      now_StatusDrainagePump = HIGH;
      if (now_year > 1970) {
        //считаем время установлено
        parseUnixTime(now_timeUnx, now_hour, now_min, now_sec, now_wd, now_day, now_month, now_year);
        for (byte i = 0; i < NomPrerDrainagePumpAll; i++) {
          //перебираем все интервалы
          if ((PrerDrainagePump[i].PrerPumpStUnx < PrerDrainagePump[i].PrerPumpEndUnx) && (PrerDrainagePump[i].Avail == 1))
          { //проверяем интервал, время начала должно быть меньше времени окончания и интервал активен
            //получаем юникс время тек.интервала
            PrerDrainagePump[i].PrerPumpStUnx = combineUnixTime(PrerDrainagePump[i].PrerPumpHourSt, PrerDrainagePump[i].PrerPumpMinSt, 0, now_day, now_month, now_year); // Собрать время в формат UNIX-time
            PrerDrainagePump[i].PrerPumpEndUnx = combineUnixTime(PrerDrainagePump[i].PrerPumpHourEnd, PrerDrainagePump[i].PrerPumpMinEnd, 0, now_day, now_month, now_year); // Собрать время в формат UNIX-time

            if ((now_timeUnx > PrerDrainagePump[i].PrerPumpStUnx) && (now_timeUnx < PrerDrainagePump[i].PrerPumpEndUnx)) {
              //время попадает в выбранный интервал - отключаем, ставим статус
              now_StatusDrainagePump = now_StatusDrainagePump & LOW;
            }
          }
        }
        if ((TimerDrainagePumpStUnx > 0) && (TimerDrainagePumpAvailSt == 1)) { //время отсроченного старта установлено
          if (now_timeUnx > TimerDrainagePumpStUnx) {//сейчас время больше чем время вкл, значит включаем
            now_StatusDrainagePump = now_StatusDrainagePump & HIGH;
          } else { //выключаем
            now_StatusDrainagePump = now_StatusDrainagePump & LOW;
          }
        }
        if ((TimerDrainagePumpEndUnx > 0) && (TimerDrainagePumpAvailEnd == 1)) { //время отсроченного выключения установлено
          if (now_timeUnx > TimerDrainagePumpEndUnx) {//сейчас время больше чем время откл, значит выключаем
            now_StatusDrainagePump = now_StatusDrainagePump & LOW;
          } else { //включаем
            now_StatusDrainagePump = now_StatusDrainagePump & HIGH;
          }
        }
      }
    }
    else {//если движок выключен
      StatusDrainagePump = LOW;
    }
    StatusDrainagePump = StatusDrainagePump & now_StatusDrainagePump;
  }
  ManageRele2(StatusDrainagePump);
}
//------------------------------------------------------------------------------------------------------------------


