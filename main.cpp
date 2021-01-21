#include "hcsr04.h"
#include "mbed.h"
#include "StepperMotorUni.h"
#include "Keypad.h"
#include "TextLCD.h"
#include <stdlib.h>
#include <stdio.h>
//#include "HT1632_LedMatrix.h"
#include "font_5x7_p.h"


//#include "PCA9622_LED8x8.h"



HCSR04  usensor(PTD7,PTD6);
StepperMotorUni mymotor(PTA17, PTA16, PTC17, PTC16);
Keypad kpad( PTC4, PTC3, PTC0, PTC7, PTC11, PTC10, PTC6, PTC5);
TextLCD lcd(PTB8, PTB9, PTB10, PTB11, PTE2, PTE3, TextLCD::LCD16x2); // rs, e, d4-d7
//PCA9622_LED8x8  matrix( PTE21, PTE20 );     //  for 40pin type mbed
//PCA9622_LED8x8  matrix( D14, D15 );   //  for Arduino type mbed
//PCA9622_LED8x8  matrix( dp5, dp27 );  //  for mbed LPC1114
//float func( float x, float y, float t );    //  function to make 8x8 image
// HT1632_LedMatrix led( PTE5, PTE21, PTE20, PTE30 , PTE29, PTE23);






int dist;
DigitalOut myled(LED1);
int i = 2;
char key;
char radardis[2];
int j =0;
int range;
int rem;
int quot;
int dire = 2;
long countd = 0;









SPI spi(PTD2, PTD3, PTD1);          // Arduino compatible MOSI, MISO, SCLK
DigitalOut cs(PTD0);                // Chip select

const unsigned char led1[]= {
    0xFF,0x18,0x18,0x18,0x18,0x18,0x18,0xFF
};  //H
const unsigned char led2[]= {
    0x1F,0x60,0x80,0x40,0x40,0x80,0x60,0x1F
};  //W

/// Send two bytes to SPI bus
void SPI_Write2(unsigned char MSB, unsigned char LSB)
{
    cs = 0;                         // Set CS Low
    spi.write(MSB);                 // Send two bytes
    spi.write(LSB);
    cs = 1;                         // Set CS High
}

/// MAX7219 initialisation
void Init_MAX7219(void)
{
    SPI_Write2(0x09, 0x00);         // Decoding off
    SPI_Write2(0x0A, 0x08);         // Brightness to intermediate
    SPI_Write2(0x0B, 0x07);         // Scan limit = 7
    SPI_Write2(0x0C, 0x01);         // Normal operation mode
    SPI_Write2(0x0F, 0x0F);         // Enable display test
    wait_ms(500);                   // 500 ms delay
    SPI_Write2(0x01, 0x00);         // Clear row 0.
    SPI_Write2(0x02, 0x00);         // Clear row 1.
    SPI_Write2(0x03, 0x00);         // Clear row 2.
    SPI_Write2(0x04, 0x18);         // Clear row 3.
    SPI_Write2(0x05, 0x18);         // Clear row 4.
    SPI_Write2(0x06, 0x00);         // Clear row 5.
    SPI_Write2(0x07, 0x00);         // Clear row 6.
    SPI_Write2(0x08, 0x00);         // Clear row 7.
    SPI_Write2(0x0F, 0x00);         // Disable display test
    wait_ms(500);                   // 500 ms delay
}


void Init_clear(void)
{
    SPI_Write2(0x01, 0x00);         // Clear row 0.
    SPI_Write2(0x02, 0x00);         // Clear row 1.
    SPI_Write2(0x03, 0x00);         // Clear row 2.
    SPI_Write2(0x04, 0x18);         // Clear row 3.
    SPI_Write2(0x05, 0x18);         // Clear row 4.
    SPI_Write2(0x06, 0x00);         // Clear row 5.
    SPI_Write2(0x07, 0x00);         // Clear row 6.
    SPI_Write2(0x08, 0x00);         // Clear row 7.


}



/*

 float func( float x, float y, float t )
   {
   //#define     DISPLAY_OFFSET  3.5
   #define     DISPLAY_OFFSET  0
   #define     SIZE            0.3
 
       float   s;
 
       x   = (x - DISPLAY_OFFSET) * SIZE;
       y   = (y - DISPLAY_OFFSET) * SIZE;
 
       s   = cos( powf( x * x + y * y, 0.5 ) - t );
       return ( powf( s, 4.0 ) ); 
 
 }

*/





int main()
{
    unsigned char count=0;
    mymotor.set_pps( 500);   
  //  led.displayOn();
    
    char key;
    int released = 1;
    lcd.printf("%Range is ", key );
 
 
 
 
 
 
 
 
    cs = 1;                         // CS initially High
    spi.format(8,0);                // 8-bit format, mode 0,0
    spi.frequency(1000000);         // SCLK = 1 MHz
    Init_MAX7219();                 // Initialize the LED controller
 //   while (1) {
//        for(int i=1; i<9; i++)      // Write first character (8 rows)
//            SPI_Write2(i,led1[i-1]);
//        wait(1);                    // 1 sec delay
//        for(int i=1; i<9; i++)      // Write second character
//            SPI_Write2(i,led2[i-1]);
//        wait(1);                    // 1 sec delay
//    }
//
// 
 
 
 
 
    //while(1){
//        led.plot(0, 0, '.');
//        
//        }      
// 
 
 
 
/*    float   image[ 8 ][ 8 ];  //
       int     countn   = 0;
 
       matrix.start();
 
       while(1) {
 
           //  making 8x8 image to "image" array
           for ( int a = 0; a < 8; a++ )
               for ( int b = 0; b < 8; b++ )
                    image[ a ][ b ]   = func( 1, 2, 3 );
                   //image[ a ][ b ]   = func( a, b, countn * 0.2 );
 
           matrix.set_data( image );
 
           countn++;
           wait( 0.05 );
       }
   
 */
  
 
 
 
 
 
 
 
 
      while(j!= 2){
          key = kpad.ReadKey();                   //read the current key pressed
          //radardis =  key + radardis;
            
          if(key == '\0')
              released = 1;                       //set the flag when all keys are released
             
          if((key != '\0') && (released == 1)) {  //if a key is pressed AND previous key was released
              lcd.printf("%c", key);
              radardis[j] = key;            
              released = 0; 
              j++;                      //clear the flag to indicate that key is still pressed
          }
    }
    
    range = atoi(radardis);
    //lcd.printf("%c", "range is");
    quot = range / 10;
    rem = range % 10;
    //lcd.printf("%d", quot);
    lcd.printf("%c", 'c');
    lcd.printf("%m", key);
    while(1) {
        usensor.start();
      //wait_ms(500); 
        dist=usensor.get_dist_cm();
        
        if ( dist < range){
           
           /* if ( i == 1){} else{
           mymotor.move_steps( 24 ); 
           wait( 1 ); }
            */
            i = 1;
            myled = 1;
            
            
            if (dire%2==0 ){
                     if (countd>=0 && countd <=35000){
                     Init_clear(); 
                     SPI_Write2(0x01, 0x20);}else 
                     if(countd>=35000 && countd <=70000){
                     Init_clear();
                     SPI_Write2(0x03, 0x80);} else   
                     if(countd>=70000 && countd <=105000){
                     Init_clear();
                     SPI_Write2(0x06, 0x80);}
                     if(countd>=105000 && countd <=140000){
                     Init_clear();
                     SPI_Write2(0x08, 0x20);} else
                     if(countd>=140000 && countd <=175000){
                     Init_clear();
                     SPI_Write2(0x08, 0x04);} else
                     if(countd>=175000 && countd <=205000){
                     Init_clear();
                     SPI_Write2(0x06, 0x01);} else
                     if(countd>=205000 && countd <=240000){
                          Init_clear();
                     SPI_Write2(0x03, 0x01);} else
                     if(countd>=240000 && countd <=275000){
                          Init_clear();
                     SPI_Write2(0x01, 0x04);}
                     
                     else{
                      Init_clear();
                      }
                     
           } else {
                     
                     
                     
                     
                     if (countd>=0 && countd <=35000){
                     Init_clear(); 
                     SPI_Write2(0x01, 0x04);
                     }else 
                     if(countd>=35000 && countd <=70000){
                     Init_clear();
                     SPI_Write2(0x03, 0x01);
                     } else   
                     if(countd>=70000 && countd <=105000){
                     Init_clear();
                     SPI_Write2(0x06, 0x01);
                     }
                     if(countd>=105000 && countd <=140000){
                     Init_clear();
                     SPI_Write2(0x08, 0x04);
                     } else
                     if(countd>=140000 && countd <=175000){
                     Init_clear();
                     SPI_Write2(0x08, 0x20);
                     } else
                     if(countd>=175000 && countd <=205000){
                     Init_clear();
                     SPI_Write2(0x06, 0x80);
                     } else
                     if(countd>=205000 && countd <=240000){
                          Init_clear();
                     SPI_Write2(0x03, 0x80);} else
                     if(countd>=240000 && countd <=275000){
                          Init_clear();
                     SPI_Write2(0x01, 0x20);}
                     else{
                      Init_clear();
                      }
                     
                     
                     
                     
                     }          
                     
                      
        }
      //    mymotor.step(0, 10000, 60);
      
             else
           { 
          // Init_clear();
           
           myled = 0;
           
          //f (i == 0) {} else{
           
           if (countd ==280000){ 
           dire++;
           countd = 0;
           wait_ms(1000);
           }
           
           if(dire%2==0){
               
               
               
           mymotor.move_steps(1);
           countd++;
           }else{
               mymotor.move_steps(-1);
               countd++;
               }
           
           //wait(1);
           //}
           
           i = 0;
           
            }   
    }
}



/*include "StepperMotorUni.h"
 *
 *  StepperMotorUni motor( p26, p25, p24, p23 );
 *
 *  int main()
 *  {
 *      motor.set_pps( 50 );
 *
 *      while ( 1 ) {
 *          motor.move_steps( 24 );
 *          wait( 1 );
 *
 *          motor.move_steps( -24 );
 *          wait( 1 );
 *      }
 *  }
 */
 
