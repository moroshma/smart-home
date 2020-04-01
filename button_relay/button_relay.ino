/*
   базовый скетч отработки нажатия кнопки с фильтром дребезга контактов
   и включением выключением реле / светодиода по нажатию на кнопку
   к уроку #6
*/

#define button_pin 3   // пин кнопки
#define relay_pin 6    // пин реле

boolean butt_flag = 0;      // флажок нажатия кнопки
boolean butt;               // переменная, харнящая состояние кнопки
boolean flag = 0;           // флажок режима
unsigned long last_press;   // таймер для фильтра дребезга
void setup() {
  pinMode(button_pin, INPUT_PULLUP);   // кнопка подтянута внутренним резистором (урок 5)
  pinMode(relay_pin, OUTPUT);          // пин реле как выход
}

void loop() {
  butt = !digitalRead(button_pin);  // считать текущее положение кнопки

  if (butt == 1 && butt_flag == 0 && millis() - last_press > 100) {  // если кнопка НАЖАТА, до этого была была ОТПУЩЕНА
    butt_flag = 1;                    // запоминаем, что нажимали кнопку
    flag = !flag;                     // инвертируем флажок
    last_press = millis();            // запоминаем время

    digitalWrite(relay_pin, flag);    // подаём сигнал на пин реле / светодиода
  }
  if (butt == 0 && butt_flag == 1) {  // если кнопка ОТПУЩЕНА, и до этого была НАЖАТА
    butt_flag = 0;                    // запоминаем, что отпустили кнопку
  }
}
