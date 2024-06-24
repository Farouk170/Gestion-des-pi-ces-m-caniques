#include <stdbool.h>
#define Set_Low(pin){pin=0;}
#define Set_High(pin){pin=1;}
#define poids Porta.RA0
#define capt_f portb.RB0
#define capt_p portb.RB1
#define f_b portb.RB2
#define f_a portb.RB3
#define PBD Portb.RB4
#define PBS Portb.RB5
#define PB2 Portb.RB6
#define PBC Portb.RB7
#define panne Portc.RC0
#define Led_G Portc.RC1
#define Led_B Portc.RC2
#define BUZZER Portc.RC7
// LCD module connections
sbit LCD_RS at RD4_bit;
sbit LCD_EN at RD5_bit;
sbit LCD_D4 at RD0_bit;
sbit LCD_D5 at RD1_bit;
sbit LCD_D6 at RD2_bit;
sbit LCD_D7 at RD3_bit;
sbit LCD_RS_Direction at TRISD4_bit;
sbit LCD_EN_Direction at TRISD5_bit;
sbit LCD_D4_Direction at TRISD0_bit;
sbit LCD_D5_Direction at TRISD1_bit;
sbit LCD_D6_Direction at TRISD2_bit;
sbit LCD_D7_Direction at TRISD3_bit;
// End LCD module connections
int repos=1;
int forme=0;
int PBS1=0;
int PBD1=0;
int PBC1=0;
int PB2_1=0;
int nbr_piece_a=0;
int nbr_piece_b=0;
int panne_compt=0;
unsigned int adc_value;
float voltage;
unsigned int percentage;
unsigned int valeur;
int compteur=0;
void interrupt(){
    if(INTCON.INTF==1){
        INTCON.INTF=0;
    }
             //interruption port B
        if (INTCON.RBIF) {
        if (Portb.RB5 == 1 ) {
           PBS1 = 1;
    }
      if (Portb.RB4 == 1 ) {
           PBD1 = 1;
    }
    if (Portb.RB7 == 1 ) {
           PBC1 = 1;
    }
    if (Portb.RB6 == 1 ) {
           PB2_1 = 1;
    }
    
    
 INTCON.RBIF  = 0 ;

  }
}
int main(){
    int i=0;
    INTCON.GIE=1;
    INTCON.RBIE=1;
    INTCON.EEIE = 1;
    INTCON.PEIE = 1;
    TRISA.RA0=1;
    TRISB.RB0=1;
    TRISB.RB1=1;
    TRISB.RB2=1;
    TRISB.RB3=1;
    TRISB.RB4=1;
    TRISB.RB5=1;
    TRISB.RB6=1;
    TRISB.RB7=1;
    TRISC.RC0=1;
    TRISC.RC1=0;
    TRISC.RC2=0;
    TRISC.RC3=0;
    TRISC.RC4=0;
    TRISC.RC5=0;
    TRISC.RC6=0;
    TRISC.RC7=0;
    TRISD.RD6=0;
    TRISD.RD7=0;
    Set_Low(Led_G);
    Set_Low(Led_B);
    LCD_Init();
    EEPROM_Write(0x0,0);
    EEPROM_Write(0x20,0);
    EEPROM_Write(0x30,0);
    portc.RC3=1;
    portc.RC4=1;
    portc.RC5=1;
    portc.RC6=1;
    portd.RD6=1;
    portd.RD7=1;
    while(1){
        if(capt_p==1){
            adc_value = ADC_Read(0);
            voltage = adc_value * 5.0 / 1023.0;
            percentage = voltage / 5.0 * 100;
            valeur = percentage *10;
            Lcd_Out(1,1,"Poids: Qualite_P");
            if(valeur>250){
                Lcd_Out(2,1,"Insatisfaisante");
                Lcd_Cmd(_LCD_CURSOR_OFF);
            }
            else{
                Lcd_Out(2,1," Satisfaisante   ");
                Lcd_Cmd(_LCD_CURSOR_OFF);
            }
        }
        // Partie nejbed if nombre piece mel eeprom w najouti fih lel eeprom
        if (f_a==1){
            nbr_piece_a =  EEPROM_Read(0x0)  ;
            nbr_piece_a++;
            EEPROM_Write(0x0,nbr_piece_a);
        }
        if(f_b==1){
            nbr_piece_b =  EEPROM_Read(0x20)  ;
            nbr_piece_b++;
            EEPROM_Write(0x20,nbr_piece_b);
        }
            //PBS1 varbale njib feha mel interruption
        if(PBS1==1){
            repos=1;
            Lcd_Cmd(_LCD_CLEAR);
            Lcd_Out(1,1,"STOP");
            Lcd_Cmd(_LCD_CURSOR_OFF);
            delay_ms(1000);
            Lcd_Cmd(_LCD_CLEAR);
            PBS1=0;
            PBD1=0;
            repos=1;
        }
        //PBD1 variable njib feha mel interruption
        if(PBD1==1){
            repos=0;
            if(capt_f==0 && capt_p==0 && PBS==0 && PBD==0){
                repos=1;
            }
            else{
                repos=0;
            }
            if(capt_f==1){
                if(f_a==0 && f_b==0){
                    Lcd_Cmd(_LCD_CLEAR);
                    Lcd_Out(1,1,"  Forme ");
                    Lcd_Cmd(_LCD_CURSOR_OFF);
                    delay_ms(2000);
                }
                else if(f_a==1){
                    Lcd_Cmd(_LCD_CLEAR);
                    Lcd_Out(1,1,"Qualite_P&FA :");
                    Lcd_Out(2,1,"Satisfaisante");
                    Lcd_Cmd(_LCD_CURSOR_OFF);
                    for(i=0;i<3;i++){
                        Set_High(Led_B);
                        delay_ms(150);
                        Set_Low(Led_B);
                    }
                    delay_ms(2000);
                }
                else{
                    Lcd_Cmd(_LCD_CLEAR);
                    Lcd_Out(1,1,"Qualite_P&FB :");
                    Lcd_Out(2,1,"Satisfaisante");
                    Lcd_Cmd(_LCD_CURSOR_OFF);
                    for(i=0;i<3;i++){
                        Set_High(Led_G);
                        delay_ms(150);
                        Set_Low(Led_G);
                    }
                    delay_ms(2000);
                }
            }
            if(panne==1){
                panne_compt =  EEPROM_Read(0x30)  ;
                Lcd_Cmd(_LCD_CLEAR);
                Lcd_Out(1,1,"PANNE");
                Lcd_Cmd(_LCD_CURSOR_OFF);
                panne_compt++;
                EEPROM_Write(0x30,panne_compt);
                Set_High(BUZZER);
                portc.RC7=1;
                delay_ms(1000);//1000*60*5
                Lcd_Cmd(_LCD_CLEAR);
                portc.RC7=0;
                Set_Low(BUZZER);
            }
            
        }
        if(PB2_1==1){
            nbr_piece_a=0;
            nbr_piece_b=0;
        }
        if(PBC1==1){
            Lcd_Cmd(_LCD_CLEAR);
            Lcd_Out(1,1,panne_compt);
            Lcd_Cmd(_LCD_CURSOR_OFF);
        }
        if(repos==1){
            Lcd_Out(1,1,"Gestion Qualite ");
            Lcd_Out(2,1,"Emballage");
            Lcd_Cmd(_LCD_CURSOR_OFF);

        }
    }
    return 0;
}