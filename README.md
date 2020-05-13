# Arduino-Color-Sound
Projects for Scientific Research Seminar at HSE.

### Look at this beauty!
![Image alt](https://github.com/mskKote/Arduino-Color-Sound/raw/master/look.png)

### Improvised scheme
![Image alt](https://github.com/mskKote/Arduino-Color-Sound/raw/master/scheme.png)

## How does it work?

Let's make a overview:
1. String <String> = ColorRecognizion() - use tcs3200 library for take RGB, 
                                       after that work my alghorithm for recognize 13 colors, it returns color name;   
2. MakeSound(<String>) - take color name and search appropriate sound tone, then play this tone;
  
3. RedAlert(int alertTime=3000) - arises when color name equals "Unknown." and bring to user time to think about this;
 
4. MakeTextAnimation(String message, int delayVal=25, String ending="") - used for make text in console user-friendly, allow show animation slowler and make ending like "\n";
 
 
Color - in model it is RBGA, but RGB - it's not a color hue, thats relevant values [All questions about to tcs3200.h]
Sound - try use values at notes for good effect.

## Used details

| Number | Detail                    | appointment            |
| -------|:-------------------------:| ----------------------:|
| 1.     | Arduino Uno R3            |                        |
| 2.     | tcs3200                   | Color recognizion      |
| 3.     | Passive buzzer module     | Sound                  |
| 4.     | Cables                    |                        |
| 5.     | Pieces of color paper     | For testing            |
| 6.     | Arduino Shield Prototype.5| For red LED and button |

## Programms

Arduino IDE and library tcs3200.h
