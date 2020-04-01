//----------------------------------------------------------------------------------------------------------------------------------------------------------------
void ManageRele3(bool StRele) {
  if (relay3Level == 0) StRele = !StRele;
  MydigitalWrite(swt3_pin, StRele);
}
//----------------------------------------------------------------------------------------------
void ManageRele4(bool StRele) {
  if (relay4Level == 0) StRele = !StRele;
  MydigitalWrite(swt4_pin, StRele);
}
//------------------------------------------------------------------------------------------------
double read_correct(double tmpC, double tmpC_now, int number_sens) {
  if (abs(tmpC - tmpC_now) > jamp_t) {
    if ((tmpC_now != -127) && (tmpC != -127)) {
      error_read_correct_ds[number_sens]++;
      error_read_correct_ds_all++;
      if (error_read_correct_ds[number_sens] > error_read_ds_Max)  {
        //на error_read_ds_Max раз принимаем как есть))
        error_read_correct_ds[number_sens] = 0;
        //Serial.println(" clear error_read_correct_ds ["+String(number_sens)+"]");
        return tmpC_now;
      }
    }
    else {
      return tmpC_now;
    }
  }
  else  {
    error_read_correct_ds[number_sens] = 0;
    return tmpC_now;
  }
  return tmpC;
}

//-------------------------------------
void working_other() {
  uint32_t Other_control_now = millis();
  bool StatusDP;
  uint32_t t_prom;

  t_prom = millis(); //текущее время

  if (t_msec_get_ds == 0) t_msec_get_ds = 2000;
  if (error_read_ds_Max == 0) error_read_ds_Max = 5;
  if (jamp_t == 0) jamp_t = 10;
  if (Zaderj == 0) Zaderj = 10;

  //if (((Other_control_now - t_control ) >= t_msec_get_ds) || (Other_control_now < t_msec_get_ds))
  if (((Other_control_now - t_control ) >= t_msec_get_ds) || (t_control == 0))
  { //выполняем замер
    if (Zaderj > 100) Zaderj = 1;
    if (Zaderj < 0) Zaderj = 0;
    delay(Zaderj);
    sensors.requestTemperatures();

    for (byte i = 0; i <= NSenseFact; i++) {
      delay(Zaderj);
      if (t[i] == 1) {//датчик активен (0-не использ,1-активен,2-используется но не активен)
        tempC_now[i] = sensors.getTempC(insideThermometer[i]);

        //проверяем показания
        if (tempC_now[i] == -127) { //датчик не зашарился
          error_read_ds[i]++; error_read_ds_all++;
          if (error_read_ds[i] == error_read_ds_Max) {
            //пишем что есть
            tempC[i] = tempC_now[i];
            error_read_ds[i] = 0;
          }
        }
        else {//датчик зашарился, проверяем показания
          error_read_ds[i] = 0;//обнуляем ошибки
          tempC[i] = read_correct(tempC[i], tempC_now[i], i);
        }

        if (NsenseDrainagePump == i) TDrainagePumpContr_now = tempC[i];
        if (NsenseWaterPump == i) TWaterPumpContr_now = tempC[i];
      }
    }
    if (useMQTT && mqttClient.connected()) {
      for (uint8_t i = 0; i < NSenseMax; i++)  {
        if ((t[i] == 1) && tempC[i] != tempC_mqtt[i]) {
          tempC_mqtt[i] = tempC[i];
          delay(25);
          mqttClient.publish(("temp/t" + String(i)).c_str(), String(tempC_mqtt[i]).c_str(), true);
        }
      }
    }

    t_control = Other_control_now;
  }
  //----------------логи по температуре------------------------------
  if ((setTimeAccompl == 1) && (writeSenseLog == 1)) {
    if (log_t == 0) log_t = 60;
    if (((Other_control_now - t_control_log_t ) >= log_t * 60 * 1000) || (t_control_log_t == 0)) {
      String message;
      for (byte i = 0; i <= NSenseFact; i++) {
        if (t[i] == 1) {//датчик активен (0-не использ,1-активен,2-используется но не активен)
          message += tNameSens[i] + " " + String(tempC[i]); message += F(":");
        }
      }

      if (message.length() > 0) addStringToLog(NameMesureLogFile, timeDateToStr(now_timeUnx), message);

      t_control_log_t = Other_control_now;
    }
  }

#ifdef USE_DHT
  if (((Other_control_now - DHT_control ) > 2500) || (Other_control_now < 2500))
  { //выполняем
    int8_t h_dht_tek, t_dht_tek;
    h_dht_tek = dht.readHumidity();   //Считываем влажность
    t_dht_tek = dht.readTemperature();// Считываем температуру

    if ((h_dht_tek < 110) && (h_dht_tek != -1))  h_dht = h_dht_tek;
    if ((t_dht_tek < 110) && (h_dht_tek != -1))  t_dht = t_dht_tek;

#ifdef USE_LOG
    if (isnan(h_dht) || isnan(t_dht))  {
      Serial.println(F("Засада с DHT"));
#endif
    }
    else {

#ifdef USE_LOG
      //  Serial.print("Влажность: "); Serial.print(h_dht); Serial.println(" %\t");
      //  Serial.print("Температура: "); Serial.print(t_dht); Serial.println(" C");
#endif

    }
    DHT_control = Other_control_now;
  }
#endif

  if (((Other_control_now - Other_control ) > 1000) || (Other_control_now < 1000))
  { //выполняем
    //Serial.print("аналог ");Serial.println(analogRead(A0));
    uint16_t input_Lev;

    str_info = "";

#ifdef USE_DHT
    str_info += F(" В: "); str_info += String(h_dht) + F("%,");;
    str_info += F(" Т: ");  str_info += String(t_dht) + F("&#176С");
#endif

    now_relay1 = digitalRead(swt1_pin);
    if (!relay1Level) now_relay1 = !now_relay1;

    now_relay2 = digitalRead(swt2_pin);
    if (!relay2Level) now_relay2 = !now_relay2;

    now_relay3 = digitalRead(swt3_pin);
    if (!relay3Level) now_relay3 = !now_relay3;

    now_relay4 = digitalRead(swt4_pin);
    if (!relay4Level) now_relay4 = !now_relay4;

    //читаем состояния датчиков и реле
    //lev1 = digitalRead(pinLev1);
    //lev2 = digitalRead(pinLev2);

    //---------

    input_Lev = analogRead(A0);
    str_info += F(" АЦП: "); str_info += String(input_Lev);
    str_info += F(" D7: ");str_info += String(digitalRead(D7));

    if ((input_Lev >= 0) && (input_Lev <= U_delta)) {
      lev1 = LOW; lev2 = LOW; errA0 = false;
    }
    else if ((input_Lev > U_lev1 - U_delta) && (input_Lev <= U_lev1 + U_delta)) {
      lev1 = HIGH; lev2 = LOW; errA0 = false;
    }
    else if ((input_Lev > U_lev2 - U_delta) && (input_Lev <= U_lev2 + U_delta)) {
      lev1 = LOW; lev2 = HIGH; errA0 = false;
    }
    else if ((input_Lev > U_lev12 - U_delta) && (input_Lev <= U_lev12 + U_delta)) {
      lev1 = HIGH; lev2 = HIGH; errA0 = false;
    }
    else {
      //ошибка
      errA0 = true;
    }

    //str_info += F(" errA0: "); str_info += String(errA0);

    //первый датчик
    if (lev1 == HIGH)  {
      if (prev_lev1 != lev1) {
        prev_lev1 = lev1;
        t_lev1_on = Other_control_now;//засекаем время срабатывания датчика уровня низ
        Serial.println("lev1 = " + String(lev1));


        addStringToLog(NameSysLogFile, timeDateToStr(now_timeUnx), "ON lev1");
        if (useMQTT && mqttClient.connected()) {
          delay(25);
          mqttClient.publish("lev/1", String(lev1).c_str(), true);
        }
      }
    }
    else {
      if (prev_lev1 != lev1)    {
        prev_lev1 = lev1;
        t_lev1_off = Other_control_now;//засекаем время срабатывания датчика уровня низ
        Serial.println("  lev1 = " + String(lev1));

        addStringToLog(NameSysLogFile, timeDateToStr(now_timeUnx), "OFF lev1");
        if (useMQTT && mqttClient.connected()) {
          delay(25);
          mqttClient.publish("lev/1", String(lev1).c_str(), true);
        }
      }
    }
    //второй датчик
    if (lev2 == HIGH)  {
      if (prev_lev2 != lev2) {
        prev_lev2 = lev2;
        t_lev2_on = Other_control_now;//засекаем время срабатывания датчика уровня верх
        Serial.println("  lev2 = " + String(lev2));

        addStringToLog(NameSysLogFile, timeDateToStr(now_timeUnx), "ON lev2");
        if (useMQTT && mqttClient.connected()) {
          delay(25);
          mqttClient.publish("lev/2", String(lev2).c_str(), true);
        }
      }
    }
    else {
      if (prev_lev2 != lev2)    {
        Serial.println("  lev2 = " + String(lev2));
        prev_lev2 = lev2;
        t_lev2_off = Other_control_now;//засекаем время срабатывания датчика уровня верх

        addStringToLog(NameSysLogFile, timeDateToStr(now_timeUnx), "OFF lev2");
        if (useMQTT && mqttClient.connected()) {
          delay(25);
          mqttClient.publish("lev/2", String(lev2).c_str(), true);
        }
      }
    }
    Other_control  = Other_control_now;
  }

  if ((setTimeAccompl == 1) && (writeSysLog == 1)) {
    if (systemStarted == 0) {

      addStringToLog(NameSysLogFile, timeDateToStr(now_timeUnx), "System start");
      systemStarted = 1;
    }
  }

  //---------------------- swt3_pin D5 Клапан вода на баню -------------------
  bool StatusKlapBany;
  if (swt3 == true) {
    StatusKlapBany = HIGH;
    if (prev_swt3 != swt3) {
      prev_swt3 = swt3;

      addStringToLog(NameSysLogFile, timeDateToStr(now_timeUnx), "ON Klapan bany");
      if (useMQTT && mqttClient.connected()) {
        delay(25);
        mqttClient.publish("swt/3", String(swt3).c_str(), true);
      }
    }
  }
  else {
    StatusKlapBany = LOW;
    if (prev_swt3 != swt3)   {
      prev_swt3 = swt3;

      addStringToLog(NameSysLogFile, timeDateToStr(now_timeUnx), "OFF Klapan bany");
      if (useMQTT && mqttClient.connected()) {
        delay(25);
        mqttClient.publish("swt/3", String(swt3).c_str(), true);
      }
    }
  }
  ManageRele3(StatusKlapBany);

  //---------------------- swt4_pin D6 Клапан слив на баню --------------------
  bool StatusKlapSliv;
  if (swt4 == true) {
    StatusKlapSliv = HIGH;
    if (prev_swt4 != swt4) {
      prev_swt4 = swt4;
      addStringToLog(NameSysLogFile, timeDateToStr(now_timeUnx), "ON Klapan sliv");
      if (useMQTT && mqttClient.connected()) {
        delay(25);
        mqttClient.publish("swt/4", String(swt4).c_str(), true);
      }
    }
  }
  else {
    StatusKlapSliv = LOW;
    if (prev_swt4 != swt4)   {
      prev_swt4 = swt4;
      addStringToLog(NameSysLogFile, timeDateToStr(now_timeUnx), "OFF Klapan sliv");
      if (useMQTT && mqttClient.connected()) {
        delay(25);
        mqttClient.publish("swt/4", String(swt4).c_str(), true);
      }
    }
  }
  ManageRele4(StatusKlapSliv);

  if ((!ApMode) && (WiFi.status() == WL_CONNECTED)) {
    if (useMQTT && !mqttClient.connected()) {
      if (mqttReconnectSec == 0) mqttReconnectSec = 120;
      if ((Other_control_now - nextTimeMQTT) > mqttReconnectSec * 1000)   {
        mqttConnect();
        nextTimeMQTT = Other_control_now;
      }
    }
  }

  if (((Other_control_now - mqtt_control ) > 60000) || (mqtt_control == 0)) { //выполняем
    if (useMQTT && mqttClient.connected()) {
      mqttClient.publish("time/on", String(uint32_t(Other_control_now / 1000/60)).c_str(), true); delay(50);
      mqtt_control = Other_control_now;
    }
  }

  if (useMQTT) mqttClient.loop();
}
//------------------------------------------------------------------------------------------------------------------
