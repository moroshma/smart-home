void h_switch()//switch
{
  LoginContr();
  String message = F("ok");
  uint16_t resp = 200;
  String argName, argValue;
  for (byte i = 0; i < server.args(); i++)
  {
    argName = server.argName(i);
    Serial.print(argName);
    Serial.print("=");
    argValue = server.arg(i);
    Serial.println(argValue);


    if (argName == F("autoMode")) {
      if (argValue == F("true")) autoMode = HIGH;
      else autoMode = LOW;
      if (resumeState == 1) {
        save_ResumeStateFile();
      }
    }
    else if (argName == F("swt1")) {
      if (argValue == F("true")) swt1 = HIGH;
      else swt1 = LOW;
      if (resumeState == 1) {
        save_ResumeStateFile();
      }
    }
    else if (argName == F("swt2")) {
      if (argValue == F("true")) swt2 = HIGH;
      else swt2 = LOW;
      if (resumeState == 1) {
        save_ResumeStateFile();
      }
    }
    else if (argName == F("swt3")) {
      if (argValue == F("true")) swt3 = HIGH;
      else swt3 = LOW;
      if (resumeState == 1) {
        save_ResumeStateFile();
      }
    }

    else if (argName == F("swt4")) {
      if (argValue == F("true")) swt4 = HIGH;
      else swt4 = LOW;
      if (resumeState == 1) {
        save_ResumeStateFile();
      }
    }

    else if (argName == F("resumeState")) {
      if (argValue == F("true")) {
        resumeState = HIGH; save_ResumeStateFile();
      }
      else resumeState = LOW;

    }

    else if (argName == F("relay1Level")) {
      if (argValue == F("true")) relay1Level = 1;
      else relay1Level = 0;
    }
    else if (argName == F("relay2Level")) {
      if (argValue == F("true")) relay2Level = 1;
      else relay2Level = 0;
    }
    else if (argName == F("relay3Level")) {
      if (argValue == F("true")) relay3Level = 1;
      else relay3Level = 0;
    }
    else if (argName == F("relay4Level")) {
      if (argValue == F("true")) relay4Level = 1;
      else relay4Level = 0;
    }

    else if (argName == F("ApMode")) {
      if (argValue == F("true")) ApMode  = 1;
      else ApMode = 0;
    }
    else if (argName == F("AccessMode")) {
      if (argValue == F("true")) AccessMode  = 1;
      else AccessMode = 0;
    }

    else if (argName == F("Srch"))//поиск датчиков
    {
      //------------------------

      //byte insideThermometer[6][8];
      bool ex_sense;


      NSenseFact = 0;

      for (int i = 0; i < NSenseMax; i++) {
        if (!sensors.getAddress(insideThermometer[i], i))  {
          //Serial.println("Unable to find address for Device 0");
          Serial.print(F("DeviceAddress insideThermometer")); Serial.print(i); Serial.println(";");
          ex_sense = 0;
          t[i] = 0;
        }
        else
        {
          t[i] = 1;
          NSenseFact++;
        }
      }
    }

    else if (argName == F("SaveSense")) {
      save_SensorConfFile();
    }

    else if (argName == F("ntpUpd")) {
      if (argValue == F("true")) {
        ntpUpd = 1;
        countFailNtp=0;
      }
      else ntpUpd = 0;
    }
    else if (argName == F("TimerDrainagePumpAvailEnd")) {
      if (argValue == F("true")) TimerDrainagePumpAvailEnd = 1;
      else TimerDrainagePumpAvailEnd = 0;
    }
    else if (argName == F("TimeDrainagePumpAvailSt")) {
      if (argValue == F("true")) TimerDrainagePumpAvailSt = 1;
      else TimerDrainagePumpAvailSt = 0;
    }

    else if (argName == F("TimerWaterPumpAvailEnd")) {
      if (argValue == F("true")) TimerWaterPumpAvailEnd = 1;
      else TimerWaterPumpAvailEnd = 0;
    }
    else if (argName == F("TimerWaterPumpAvailSt")) {
      if (argValue == F("true")) TimerWaterPumpAvailSt = 1;
      else TimerWaterPumpAvailSt = 0;
    }
    else if (argName == F("writeSysLog")) {
      if (argValue == F("true")) writeSysLog = 1;
      else writeSysLog = 0;
    }
    else if (argName == F("writeSenseLog")) {
      if (argValue == F("true")) writeSenseLog = 1;
      else writeSenseLog = 0;
    }

    else if (argName == F("useMQTT")) {
      if (argValue == F("true")) {
        useMQTT  = 1;
        nextTimeMQTT = millis();
      }
      else useMQTT = 0;
    }
    else if (argName == F("mqtt_conn")) {
      countFailMqtt=0;
      mqttConnect();
    }

    String _argName;
    for (byte i = 0; i < NomPrerDrainagePumpAll; i++) {
      _argName = F("PrerDrainagePumpAvail"); _argName += String(i);
      if (argName == _argName) {
        if (argValue == F("true")) PrerDrainagePump[i].Avail = HIGH;
        else PrerDrainagePump[i].Avail = LOW;
      }
    }
    for (byte i = 0; i < NomPrerWaterPumpAll; i++) {
      _argName = F("PrerWaterPumpAvail"); _argName += String(i);
      if (argName == _argName) {
        if (argValue == F("true")) PrerWaterPump[i].Avail = HIGH;
        else PrerWaterPump[i].Avail = LOW;
      }
    }

    _argName = F("SenseStatus");
    for (byte i = 0; i < NSenseFact; i++) {
      _argName = F("SenseStatus"); _argName += String(i);
      Serial.println(_argName);

      if (argName == _argName)
      {
        if (argValue == F("true")) t[i] = 1;
        else t[i] = 2;
        Serial.print(argValue); Serial.print(i);
      }
    }

  }
  server.send(resp, F("text/html"), message);
}
//----------------------------------------------------------------------------------------------

