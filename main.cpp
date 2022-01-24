#include "RawSerial.h"
#include "mbed.h"
#include "string.h"
#include "TextLCD.h"
#define MAX_VUELTAS 2

void display ();
void enviar_bt ();
void sensar ();
void modo_automatico ();
float temperatura();

DigitalOut led_verde(LED_GREEN);
DigitalOut led_rojo(LED_RED);
DigitalIn Sensor_Fuego(PTE19);
DigitalIn Sensor_Mov(PTE31);
DigitalIn Motor_Izq_IN(PTE18);
DigitalOut Motor_Izq_adelante_OUT(PTE17);
DigitalOut Motor_Izq_retroceso_OUT(PTE3);
DigitalIn Motor_Der_IN(PTE16);
DigitalOut Motor_Der_adelante_OUT(PTE6);
DigitalOut Motor_Der_retroceso_OUT(PTE2);
AnalogIn entrada_temp(PTB0);

RawSerial pc(PTE0, PTE1); //TX,RX 
TextLCD lcd(PTA13, PTD2, PTD4, PTD6, PTD7, PTD5);//RS,E,D4-D7

int modo_v = 1, vueltas = 0, eventos = 0, valor = 0;

///////////////////////////////////////////////////////////////////////////////////////

int main()
{   led_rojo = 0;
    led_verde = 0;
 int elec=0, enter=0, mov=0, sig=0; 
    
    lcd.cls();
    lcd.printf("Proyecto integ\n");
    lcd.printf("4R1 Electronica");
    wait(1.5); 
    
    lcd.cls();
    lcd.printf("4R1 Electronica\n");
    lcd.printf("UTN FRC 2015");
    wait(1.5); 
    
    lcd.cls();
    lcd.printf("UTN FRC 2015\n");
    lcd.printf("Integrantes");
    wait(1.5); 
    
    lcd.cls();
    lcd.printf("Integrantes\n");
    lcd.printf("CHIOSSO,CONDORI");
    wait(1.5); 
    
    lcd.cls();
    lcd.printf("CHIOSSO,CONDORI\n");
    lcd.printf("ZALAZAR\n");
    wait(3); 
    
    lcd.cls();
    lcd.printf("Bienvenido\n");
    lcd.printf("a ARMando\n");
                        

while(true){ 
 
    lcd.printf("Bienvenido\n");
    lcd.printf("a ARMando\n");
            
    pc.putc(13);
    pc.printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    pc.putc(13);
    pc.printf("  **** Bienvenido a ARMando ****  \n\n");
    do  {
    pc.putc(13);
    pc.printf("  1_MODO AUTOMATICO        \n");
    pc.putc(13);
    pc.printf("  2_MODO MANUAL            \n");
    pc.putc(13);
    pc.printf("  3_OBTENER DATOS          \n");
    elec=pc.getc();
    pc.putc(13);
    pc.putc(elec);
    enter=pc.getc();}
    
    while(52<elec||enter!=127||elec<49);
          
switch(elec){
        case 49 :{//Ingresa la opcion uno  
            lcd.cls();
            lcd.printf("Modo AUTOMATICO.\n");
            pc.putc(13);  
            pc.printf("->  MODO AUTOMATICO  \n");
            wait(1);                      
            modo_automatico(); //LLAMA A LA FUNCION MODO AUTOMATICO                       
            break;}
            
 ///////////////////////////////////////////////////////////////////////////////////////          
  
        case 50:{  //Ingresa la opcion dos 
            
            lcd.cls();
            lcd.printf("Modo MANUAL.\n");
     
            pc.putc(13);
            pc.printf("->  MODO MANUAL \n");
            
            do{   
                mov=pc.getc();
            
            switch(mov){
                
            case 97 :{ //a   //los caracteres estan escritos en codigo ASCII
                while(mov==97){
                lcd.cls();
                lcd.printf("GIRO IZQUIERDA.");
                //GIRO IZQUIERDA : Motor derecho ↑  Motor izquierdo ↓
                Motor_Der_adelante_OUT = 1; 
                Motor_Der_retroceso_OUT = 0;
                
                Motor_Izq_adelante_OUT = 0; 
                Motor_Izq_retroceso_OUT = 1; 
                
                
                mov=pc.getc();}
                
                break;}
                
            
            case 119 :{ //w
                while(mov==119){
                lcd.cls();
                lcd.printf("AVANCE.");
               //ADELANTE : Motor derecho ↑  Motor izquierdo ↑
                Motor_Der_adelante_OUT = 1; 
                Motor_Der_retroceso_OUT = 0;
                
                Motor_Izq_adelante_OUT = 1; 
                Motor_Izq_retroceso_OUT = 0; 
                mov=pc.getc();}
                break;}
                
            case 100:{//d
                //Apaga el derecho y prende el izquierdo 
                while(mov==100){
                lcd.cls();
                lcd.printf("GIRO DERECHA.");
               //GIRO DERECHA: Motor derecho ↓  Motor izquierdo ↑
                Motor_Der_adelante_OUT = 0; 
                Motor_Der_retroceso_OUT = 1;
                
                Motor_Izq_adelante_OUT = 1; 
                Motor_Izq_retroceso_OUT = 0; 
                mov=pc.getc();}
                break;}
                
            case 115:{//s
                //Apaga el derecho y prende el izquierdo 
                while(mov==115){
                lcd.cls();
                lcd.printf("RETROCESO.");
               //ATRAS : Motor derecho ↓  Motor izquierdo ↓
                Motor_Der_adelante_OUT = 0; 
                Motor_Der_retroceso_OUT = 1;
                
                Motor_Izq_adelante_OUT = 0; 
                Motor_Izq_retroceso_OUT = 1; 
                mov=pc.getc();}
                break;}
            
            case 127:{//q
            sig=127;
           //MOTOR DETENIDO
                lcd.cls();
                lcd.printf("DETENIDO.");
                Motor_Der_adelante_OUT = 0; 
                Motor_Der_retroceso_OUT = 0;
                
                Motor_Izq_adelante_OUT = 0; 
                Motor_Izq_retroceso_OUT = 0; 
            break;}
            
            default:
            {//MOTOR DETENIDO
                lcd.cls();
                lcd.printf("DETENIDO.");
                Motor_Der_adelante_OUT = 0; 
                Motor_Der_retroceso_OUT = 0;
                
                Motor_Izq_adelante_OUT = 0; 
                Motor_Izq_retroceso_OUT = 0; 
            //apague los dos motores
            break;}    
                        
            }
            
            
            }while(sig!=127); 
            
            break; 
            }
            
 ///////////////////////////////////////////////////////////////////////////////////////
            
        case 51:{ //opcion tres
            pc.putc(13);     
            pc.printf("\n\n  A elegido Datos\n");
            sensar();
            enviar_bt ();
            pc.putc(13);
            pc.printf("  Pulse cualquier tecla para continuar...\n");
            pc.getc(); 
            lcd.cls(); 
            break;}
            
  ///////////////////////////////////////////////////////////////////////////////////////     
                    
        /*case 52:{  //opcion cuatro
        pc.putc(13);     
        pc.printf("A elegido SALIR\n");
        wait(2);                
        break;}  */ 
        
   /////////////////////////////////////////////////////////////////////////////////////// 
                 
        default:{  //ninguna opcion es la correcta
        do {
        pc.putc(13);
        pc.printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        pc.putc(13);
        pc.printf("  **** Bienvenido a ARMando ****  \n\n");
        pc.putc(13);
        pc.printf("  1_MODO AUTOMATICO          \n");
        pc.putc(13);
        pc.printf("  2_MODO MANUAL              \n");
        pc.putc(13);
        pc.printf("  3_OBTENER DATOS               \n");
        pc.putc(13);
        elec=pc.getc();
        pc.putc(elec);
        enter=pc.getc();
        
        }while(52<elec||enter!=127||elec<49);
        break;
        }
         }//FIN switch
         
         eventos = 0;
     }//FIN while
}

void display (){
lcd.cls();
    
    if (valor == 0)
        lcd.printf("Situacion controlada\n");
    if (valor == 1)
        lcd.printf("Movimiento detectado\n");
    if (valor == 2)
        lcd.printf("Fuego detectado\n");
    if (valor == 3)
        lcd.printf("Fuego y Mov. detectado\n");

}

void enviar_bt (){
int x = 0;
float valor_temperatura;
    pc.putc(13);
    pc.printf("\n\n");
    pc.putc(13);
    pc.printf("  Transmitiendo estado...           \n");
    pc.putc(13);
    pc.printf("  Se registraron %d eventos en la vuelta %d:\n      ", eventos, vueltas);
    
    pc.putc(13);

    if (valor == 0)
    pc.printf("  Situacion controlada.                              \n");
    
    if (valor == 1)
    pc.printf("  Movimiento detectado.                              \n");

    if (valor == 2)
    pc.printf("  Fuego detectado.                                   \n");
        
    if (valor == 3)
    pc.printf("  Fuego y movimiento detectado.                      \n");
    
    pc.putc(13);
    valor_temperatura = temperatura();
    pc.printf("  La temperatura es de %.3f grados.        \n\n", valor_temperatura);
    
    for (x = 0; x < vueltas; x++)
        led_verde = !led_verde; 

    wait_ms(1000);
    led_verde = 0;
      
}

void sensar (){
    
static int ok = 0, movimiento = 1, fuego = 2, alarma = 3;

    lcd.cls();
    lcd.printf("Sensando...");
            
    if ((Sensor_Fuego == 1) && (Sensor_Mov == 0)) // OK
        {valor = ok;
        wait_ms(2500);}

    if ((Sensor_Fuego == 0) && (Sensor_Mov == 0)) // SI HAY FUEGO
        {valor = fuego;
        wait_ms(2500);
        eventos += 1;}

    if ((Sensor_Fuego == 1) && (Sensor_Mov == 1)) // SI HAY MOVIMIENTO
        {valor = movimiento;
        wait_ms(2500);
        eventos += 1;}

    if ((Sensor_Fuego == 0) && (Sensor_Mov == 1)) // SI HAY FUEGO Y MOVIMIENTO
        {
        valor = alarma;
        wait_ms(2500);
        eventos += 1;
        }
     
        display();
}
    
void modo_automatico (){
  for ( ; vueltas < MAX_VUELTAS; vueltas++) {
        
        for (;;){ //"y" es el tiempo hasta que para a sensar
        
             if (Motor_Izq_IN == 1 && Motor_Der_IN == 1){
                 Motor_Izq_adelante_OUT = 1;
                 Motor_Izq_retroceso_OUT = 0;
                 
                 Motor_Der_adelante_OUT = 1;
                 Motor_Der_retroceso_OUT = 0;}
             
             if (Motor_Izq_IN == 1 && Motor_Der_IN == 0){
                 Motor_Izq_adelante_OUT = 1;
                 Motor_Izq_retroceso_OUT = 0;
                 
                 Motor_Der_adelante_OUT = 0;
                 Motor_Der_retroceso_OUT = 1;}
                 
             if (Motor_Izq_IN == 0 && Motor_Der_IN == 1){
                 Motor_Izq_adelante_OUT = 0;
                 Motor_Izq_retroceso_OUT = 1;
             
                 Motor_Der_adelante_OUT = 1;
                 Motor_Der_retroceso_OUT = 0;}
        
        
           if (Motor_Der_IN == 0 && Motor_Izq_IN == 0) //ver si es cero o uno por la modificacion que hicimos!
                { // SI SE DETECTA UNA FRANJA HORIZONTAL ESPERA 10 segundos y envia el estado por bluetooth
    
                Motor_Izq_adelante_OUT = 0;
                Motor_Der_adelante_OUT = 0;
                
                Motor_Izq_retroceso_OUT = 0;
                Motor_Der_retroceso_OUT = 0;
                
                wait_ms(250);
                pc.putc(13);
                sensar();
                enviar_bt ();
                pc.putc(13);
                pc.printf("  Vehiculo en movimiento, Vuelta %d   \n\n\n", vueltas);
                
                    for (int x=0; x < 30; x++){
                 
                    led_rojo = !led_rojo;
                 
                    wait_ms(50);}
                
                Motor_Izq_adelante_OUT = 1;
                Motor_Der_adelante_OUT = 1;
                
                Motor_Izq_retroceso_OUT = 0;
                Motor_Der_retroceso_OUT = 0;
                
                wait_ms(500);
                break;
                
                 // Si detecta una linea, interrumpe el conteo de treinta segundos
            
            }//cierro if         
           
        }//cierro for (;;)

    }
    

       Motor_Izq_adelante_OUT = 0;
       Motor_Der_adelante_OUT = 0;
            
       Motor_Izq_retroceso_OUT = 0;
       Motor_Der_retroceso_OUT = 0;
       vueltas = 0; 
       
      lcd.cls();
      lcd.printf("Fin modo AUTO\n");
      lcd.printf("%d eventos\n", eventos);
    
      pc.putc(13);
      pc.printf("  Pulse cualquier tecla para continuar...\n");
      
      pc.getc();
      lcd.cls();
}

float temperatura (void){
    float temp, temp1, temp2, temp3;

    temp1 = entrada_temp.read() * 100;
    wait_ms(100);
    temp2 = entrada_temp.read() * 100;
    wait_ms(100);
    temp3 = entrada_temp.read() * 100;
    wait_ms(100);
    
    temp = (temp1+temp2+temp3) / 3;
    
    return temp;
}