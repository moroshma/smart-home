//Тестировалось на Arduino IDE 1.0.5
#include <dht11.h>      // Добавляем библиотеку DHT11
#include <Servo.h>
Servo myservo;
dht11 DHT;               // Объявление переменной класса dht11

#define smokePin A0  
#define PIN_RELAY 3 // Определяем пин, используемый для подключения реле
#define DHT11_PIN 12     // Датчик DHT11 подключен к цифровому пину номер 12


boolean floog = 0;
boolean pos;
int sensorThres = 200;




void setup(){

  Serial.begin(9600);   // Скорость работы порта
  //Serial.println("DHT TEST PROGRAM "); // Выводим текст
 // Serial.print("LIBRARY VERSION: ");   // Выводим текст
 // Serial.println(DHT11LIB_VERSION);
 //Serial.println();                    // Пустая строка 
  myservo.attach(13);
  pinMode(PIN_RELAY, OUTPUT); // Объявляем пин реле как выход
  digitalWrite(PIN_RELAY, HIGH); // Выключаем реле - посылаем высокий сигнал
}



void loop(){
  int analogSensor = analogRead(smokePin);  
  int chk;

  
  Serial.print (analogSensor); 
  // Мониторинг ошибок
  chk = DHT.read(DHT11_PIN);    // Чтение данных
  switch (chk){
  case DHTLIB_OK:  
    break;
  case DHTLIB_ERROR_CHECKSUM:
    Serial.println("Checksum error, \t");
    break;
  case DHTLIB_ERROR_TIMEOUT:
    Serial.println("Time out error, \t");
    break;
  default:
    Serial.println("Unknown error, \t");
    break;
  }


  
  // Выводим показания влажности и температуры
  Serial.print("Humidity = ");
  Serial.print(DHT.humidity, 1);
  Serial.print(", Temp = ");
  Serial.println(DHT.temperature,1);
  delay(1000);



  //если температура > 29
  if (DHT.temperature > 29 && floog == 1)
  {
    
   myservo.write(60);
   floog = 0;
   digitalWrite(PIN_RELAY, LOW); // Включаем реле - посылаем низкий уровень сигнала
   delay(10000);

    
  }


  //если температура < 28
  if (DHT.temperature <= 28 && floog == 0)
  { 
    digitalWrite(PIN_RELAY, HIGH); // Отключаем реле - посылаем высокий уровень сигнала
    myservo.write(0); 
    floog = 1;
    delay(200);
  }


  //газаанализатор
  if (analogSensor > sensorThres) {  // если значение больше допустимого...
    Serial.println(" Gaz!");    
    Serial.println(analogSensor); // выводим в порт надпись, что газ есть
    digitalWrite(PIN_RELAY, LOW); // Включаем реле - посылаем низкий уровень сигнала
    delay(2000); 
  }
  
  else {                             // иначе...
   Serial.println(" normal");
   Serial.println(analogSensor); // выводим в порт надпись, что газа нет
   digitalWrite(PIN_RELAY, HIGH); // Отключаем реле - посылаем высокий уровень сигнала
  }
  delay(500);  // задержка в 500 миллисекунд.

}
