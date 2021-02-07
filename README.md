# Arduino-Color-Sound
A projects for Scientific Research Seminar at HSE.

### Look at this beauty!
![Image alt](https://github.com/mskKote/Arduino-Color-Sound/raw/master/look.jpg)

## How does it works?

Let's make an overview:
1. ```String <String> = ColorRecognizion()``` - uses tcs3200 library for take hue, 
                                       after that my alghorithm separates 13 colors and returns color's name;   
2. ```MakeSound(<String>)``` - takes color's name and search appropriate sound tone, then plays this tone;
  
3. ```RedAlert(int alertTime=3000)``` - arises when color's name equals "Unknown" and bring to user a little time to think about that;
 
4. ```MakeTextAnimation(String message, int delayVal=25, String ending="")``` - used for make a text in console more user-friendly, allows showing animation slowler and make ending like "\n" or whatever else;
 
 
Color - in model it is RBGA, but RGB - is not a color hue, thats relevant values [All questions about it redirect to tcs3200.h]
Sound - try to use values at notes for good effect.

## Used details

| №  | Detail                    | Purpose                  |
| ---|:-------------------------:| ------------------------:|
| 1. | Arduino Uno R3            |                          |
| 2. | Cables                    |                          |
| 3. | tcs3200                   | Color recognizion        |
| 4. | Passive buzzer module     | Sound                    |
| 5. | Pieces of color paper     | Testing                  |
| 6. | Arduino Shield Prototype.5| For red LED and a button |

### Improvised scheme
![Image alt](https://github.com/mskKote/Arduino-Color-Sound/raw/master/Scheme.jpg)

### cover
![Image alt](https://github.com/mskKote/Arduino-Color-Sound/raw/master/cover.jpg)
It was created by https://github.com/D1scoDancer
