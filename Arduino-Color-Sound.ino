#include <tcs3200.h>

#define SOUNDPIN 13
#define BtnPIN 12
#define AlertPIN 11
#define ColorPIN 9
#define S0 4
//         (S0, S1, S2, S3, output pin);
tcs3200 tcs(S0, S0+1, S0+2, S0+3, S0+4); 

int R, G, B, white, average, recogIteration=0;
bool pause = true;
String resultColor;

// Элемент - ноты в Гц
int colorsValueByID[10] = {
  523, //0
  831, //1
  1175,//2
  1480,//3
  1760,//4
  2093,//5
  2349,//6
  2637,//7
  2960,//8
  3322 //9
};
// Названия цветов для активации
String colors[10] = {
  "Чёрный",//0
  "Белый",//1
  "Тёмно серый",//2
  "Светло серый",//3
  "Красный",//4
  "Синий",//5
  "Зелёный",//6
  "Жёлтый",//7
  "Фиолетовый",//8
  "Голубой"//9
};
/*
  Ищет в массиве цветов определённый.
*/ 
int ColorsSearcher(String color)
{
  for (int i=0; i < colors; i++)
   if (color == colors[i])
     return i;
}
/*
  Красочно выводит текст.
*/ 
void MakeTextAnimation(String message, int delayVal=25, String ending=""){
  Serial.print("  ");
  for (int i = 0; i < message.length(); i++)
  {
    Serial.print(message[i]);
    delay(delayVal);
  }  
  Serial.print(ending); // Для \n \t итд
}
/*
  Оповещает об необработанном цвете
  Триггер: "Unknown."
  запускает красную лампу.
*/ 
void RedAlert(int alertTime=3000)
{
  digitalWrite(AlertPIN, HIGH); 
  MakeTextAnimation("Обнаружен неизвестный цвет.", 25,"\n");
  delay(alertTime);  
  digitalWrite(AlertPIN, LOW);
}
/*
  Работает со звуком
*/ 
void MakeSound(String color, int soundTime=1000){
  int colorID = ColorsSearcher(color);  
  if (colorsValueByID[colorID] == 0) return;
  MakeTextAnimation("Sound tone: " + String(colorsValueByID[colorID]) + "\t");
  tone(SOUNDPIN, colorsValueByID[colorID], soundTime + 350);
       
  MakeTextAnimation("start");
  MakeTextAnimation("▄▄▄▄▄▄▄▄▄▄", 35);
  MakeTextAnimation("Sound end");
  delay(1000); 
  Serial.println("\n");
}
/*
  Распознавание цвета.
  Возвращает наименование.
*/ 
String ColorRecognizion()
{
  white = tcs.colorRead('c');
  R = tcs.colorRead('r');
  G = tcs.colorRead('g');
  B = tcs.colorRead('b');
  average = (R + G + B)/3;
  
  //xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\\
  // Чёрный и белый
  if      (white <= 15) {resultColor = "Чёрный"; }
  else if (white >= 85) {resultColor = "Белый";  }
  else if (abs(average - R) <= 2 && abs(average - G) <= 1 && abs(average - B) <= 2 && white < 50) {resultColor = "Тёмно серый";  } 
  else if (abs(average - R) <= 2 && abs(average - G) <= 1 && abs(average - B) <= 2 && white >= 50){resultColor = "Светло серый"; } 
  // RGB
  else if (R - G - B >= 0) {resultColor = "Красный"; }
  else if (B - G - R >= 0) {resultColor = "Синий";   }
  else if (G - R - B >= -3){resultColor = "Зелёный"; }
  // RG, RB, GB
  else if (R > B && G > B && abs((R+G)/2 - B) >= 1) {resultColor = "Жёлтый";     } // RG
  else if (B > G && R > G && abs((B+R)/2 - G) >= 1) {resultColor = "Фиолетовый"; } // RB
  else if (G > R && B > R && abs((B+G)/2 - R) >= 1) {resultColor = "Голубой";    } // GB
  // Дополнительные цвета.
  else if (R > B && R > G && abs((B+G)/2 - B) <= 5 && abs((B+G)/2 - G) <= 5) {resultColor = "Розовый";    } // !R! BG - average 
  else if (G > B && G > R && abs((B+R)/2 - B) <= 5 && abs((B+R)/2 - R) <= 5) {resultColor = "Салатовый";  } // !G! BR - average 
  else if (B > R && B > G && abs((R+G)/2 - R) <= 5 && abs((R+G)/2 - G) <= 5) {resultColor = "Лавандовый"; } // !B! RG - average 
  
  else {resultColor = "Unknown.";}

  MakeTextAnimation("Цвет и RGBA: " + resultColor + "  ||  R=" + String(R) + "  G=" + String(G)+ "  B=" + String(B)+ "  прозрачность= " + String(white), 20, "\n");
  return resultColor;
}

void setup() {
  pinMode(SOUNDPIN, OUTPUT);
  pinMode(AlertPIN, OUTPUT);
  pinMode(ColorPIN, OUTPUT);
  digitalWrite(ColorPIN, LOW);
  pinMode(BtnPIN, INPUT_PULLUP);
  Serial.begin(9600);
  
  Serial.println("\n");
  Serial.println("  ////=================================================\\\\\\\\");
  Serial.println("  -|.|                                                 |.|- ");
  Serial.println("  -|.| Машина для распознавания цвета и звука готова,  |.|- ");
  Serial.println("  -|.| нажмите на кнопку на корпусе для активации кода |.|- ");
  Serial.println("  -|.|                                                 |.|- ");
  Serial.println("\n");
}
/*
  В начале каждой итерации цикла программы смотрим, 
  нажал ли пользователь на паузу
*/ 
void PauseStatus()
{
  if (digitalRead(12) == 0)
  {
    pause = !pause;
    digitalWrite(ColorPIN, !pause);
    delay(300);
    Serial.println("\n");
    if (pause) {MakeTextAnimation("ПАУЗА", 25, "\n\n"); delay(500);}
    else        MakeTextAnimation("Запуск датчика", 25, "\n\n");
    
  }
}
void loop() {
  // Не начинаем, пока пользователь не нажал кнопку.
  PauseStatus();
  if (pause) return;
  
  Serial.println("\n  ||=======================| " + String(++recogIteration) + " |=======================||");
  String res = ColorRecognizion();
  if (res == "Unknown.") RedAlert(); 
  else {
    delay(200);
    MakeSound(resultColor);
  }
}
