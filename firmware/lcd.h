#include "globalvar.h"
#include "tiles.h"
#include "homespun_font.h"

#define CHAR_WIDTH 7
#define CHAR_HEIGHT 8

#define FONT_COLOR 0x0000
#define BACKGROUND_COLOR 0x86c0
#define ERROR_COLOR 0xF800

static uint16_t convert(uint8_t number)
{
    if (number==0x0)return 0x86c0;
    if (number==0x1)return 0x7bef;
    if (number==0x2)return 0xce59;
    if (number==0x3)return 0x0000;
    if (number==0xf)return 0x0BB0;
    return 0x0000;
}

static void lcd_write_Oaddr(unsigned char address){
    lcd_core_ADDR_write(address);
    lcd_core_DATA_write(0x00);
    lcd_core_OPTION_write(0);
    lcd_core_START_write(1);
    lcd_core_START_write(0);
    while(lcd_core_BUSY_read()==1);
    busy_wait(0); //ojo con esto, demora mucho la vaina
}

static void lcd_write_Odata(unsigned short int value)
{
    lcd_core_ADDR_write(0x00);
    lcd_core_DATA_write(value);
    lcd_core_OPTION_write(1);
    lcd_core_START_write(1);
    lcd_core_START_write(0);
    while(lcd_core_BUSY_read()==1);
    busy_wait(0); //ojo con esto, demora mucho la vaina
}


static void lcd_initialize(void)
{
//**********INICIALIZACION***********//
//   Ili9341
    lcd_write_Oaddr(0x01);//Software reset
    busy_wait(0.06);

    lcd_write_Oaddr(0x28);//Display off

    lcd_write_Oaddr(0xc0);//Power control 1
    lcd_write_Odata(0x23);//5.05V

    lcd_write_Oaddr(0xc1);//Power control 2
    lcd_write_Odata(0x10);//VCIx2

    lcd_write_Oaddr(0xc5);//VCOM Control 1
    lcd_write_Odata(0x2b);
    lcd_write_Odata(0x2b);

    lcd_write_Oaddr(0xc7);//VCOM Control 1
    lcd_write_Odata(0xc0);

    lcd_write_Oaddr(0x36);//Memory Access Control
    lcd_write_Odata(0x88);

    lcd_write_Oaddr(0x3a);//Pixel Format Set
    lcd_write_Odata(0x55);//16 bits / pixel

    lcd_write_Oaddr(0xb1);//Frame Rate Control (In Normal Mode / Full colors)
    lcd_write_Odata(0x1b);

    lcd_write_Oaddr(0xb7);//Entry Mode Set
    lcd_write_Odata(0x07);

    lcd_write_Oaddr(0x11);//Sleep out

    lcd_write_Oaddr(0x21);//Inversion ON (?)

    lcd_write_Oaddr(0x29);//Display ON

    busy_wait(1.5);
    busy_wait(5);

//**********MODO VENTANA 30X30 TILES***********//
    //lcd_write_Oaddr(0x12);//Partial mode ON
    
    //lcd_write_Oaddr(0x30);//Partial area
    //lcd_write_Odata(0x00);
    //lcd_write_Odata(0x29);
    //lcd_write_Odata(0x01);
    //lcd_write_Odata(0x18);
    //printf("\nLCD ready\n");
}
//Added by Luis Carlos

static void preparePrint(uint16_t posx, uint16_t posy, uint8_t width, uint8_t height){
    uint16_t xcord=8*(posx-1);
    uint16_t ycord=8*(posy-1);
    
    lcd_write_Oaddr(0x2a);
    lcd_write_Odata(xcord>>8);
    lcd_write_Odata(xcord);
    lcd_write_Odata((xcord+width-0x1)>>8);
    lcd_write_Odata(xcord+width-0x1);

    lcd_write_Oaddr(0x2b);
    lcd_write_Odata(ycord>>8);
    lcd_write_Odata(ycord);
    lcd_write_Odata((ycord+height-0x1)>>8);
    lcd_write_Odata(ycord+height-0x1);

    lcd_write_Oaddr(0x2c);

}

static void drawPixel(uint16_t color){
    lcd_write_Odata(color>>8);
    lcd_write_Odata(color);
}

static void print_tile(uint8_t number, uint16_t posx, uint16_t posy){
    uint16_t data[8];

    for(uint8_t i=0;i<8;i++){
    data[i]=tiles[number][i];
    }  

    preparePrint(posx, posy, 8, 8);

    for (int i=0;i<=7;i++)
    {
        for (int j=0;j<=7;j++)
        {
            drawPixel(convert((data[i]>>(14-(j*2)))&0x3));
        }
    }
}

static void printCharacter(uint8_t c, uint16_t posx, uint16_t posy, uint16_t fontColor, uint16_t background){
    uint8_t i, j;
    uint16_t chr[7];
    
    posx = 20-posx;
    // Convert the character to an index
    c = c & 0x7F;
    if (c < ' ') {
        c = 0;
    } else {
        c -= ' ';
    }

    // 'font' is a multidimensional array of [96][char_width]
    // which is really just a 1D array of size 96*char_width.
    for(uint8_t i=0;i<7;i++){
        chr[i]=font[c][i];
    }  

    // Draw pixels
    preparePrint(posy*2, posx*2, CHAR_HEIGHT*2, CHAR_WIDTH*2);
    
    for (j=CHAR_WIDTH*2; j>0; j--) {
        for (i=0; i<CHAR_HEIGHT*2; i++) {
            if (chr[j/2-1] & (1<<i/2)) {
                drawPixel(fontColor);
            }else{
                drawPixel(background);
            }
        }
    }
}

static void printString(char *c, uint16_t posx, uint16_t posy, uint16_t fontColor, uint16_t background){
    uint8_t i=0;
    while(1){
        if(c[i]==NULL)return;
        printCharacter(c[i], posx+i, posy, fontColor, background);
        i++;
    }
}

static void printWholeScreen(char *c, uint16_t fontColor, uint16_t background){
    uint8_t i=0;
    uint16_t x=1, y=1;
    while(1){
        if(c[i]==NULL)return;
        
        switch (c[i]){
            case '/':
            x=1;
            y++;
            break;
            case '_':
                printCharacter(' ', x, y, fontColor, background);
                x++;
            break;
            default:
                printCharacter(c[i], x, y, fontColor, background);
                x++;
        }
        i++;
    }
}

static void fillScreen(void)
{
    for (int i=1;i<=30;i++)
    {
        for (int j=1;j<=40;j++)
        {
            print_tile(GROUND,i,j);
        }
    }
}

static void initHMI(void){
        lcd_initialize();
		fillScreen();
			
        printString("RecycleAnalytics UN", 1, 1, 0x0000, 0x86c0);
        
        printString("Hora", 10, 3, 0x0000, 0x86c0);
        
        printString("Peso:", 1, 5, 0x0000, 0x86c0);
        printString("Humedad:", 1, 6, 0x0000, 0x86c0);
        printString("Temperatura:", 1, 7, 0x0000, 0x86c0);
        
        printString("Gas:", 1, 9, 0x0000, 0x86c0);
        printString("Fuego:", 1, 10, 0x0000, 0x86c0);
        
        printString("Ruta:X105-1", 9, 12, 0x0000, 0x86c0);
        printString("-2", 18, 13, 0x0000, 0x86c0);
        printString("-3", 18, 14, 0x0000, 0x86c0);
        
        printString("ID:", 1, 14, 0x0000, 0x86c0);
}

static void printData(char *c){
    uint8_t i=0, nData=0, deltaX=0;
    while(1){
        switch(c[i]){
            case '}':
                return;
            break;
            case ',':
                switch(nData){
                    case 3:
                        //Peso
                        printString("Kg   ", 6+deltaX, 5, FONT_COLOR, BACKGROUND_COLOR);
                    break;
                    case 4:
                        //Humedad
                        printString("%    ", 9+deltaX, 6, FONT_COLOR, BACKGROUND_COLOR);
                    break;
                    case 5:
                        //Temperatura
                        printString("^C     ", 13+deltaX, 7, FONT_COLOR, BACKGROUND_COLOR);
                    break;
                }
                nData++;
                deltaX=0;
            break;
            case '{':
            case ' ':
            break;
            default:
                switch(nData){
                    case 0:
                        //Id
                        printCharacter(c[i], 4+deltaX, 14, FONT_COLOR, BACKGROUND_COLOR);
                        deltaX++;
                    break;
                    case 2:
                        //Hora
                        if(deltaX>4)break;
                        printCharacter(c[i], 15+deltaX, 3, FONT_COLOR, BACKGROUND_COLOR);
                        deltaX++;
                    break;
                    case 3:
                        //Peso
                        printCharacter(c[i], 6+deltaX, 5, FONT_COLOR, BACKGROUND_COLOR);
                        deltaX++;
                    break;
                    case 4:
                        //Humedad
                        printCharacter(c[i], 9+deltaX, 6, FONT_COLOR, BACKGROUND_COLOR);
                        deltaX++;
                    break;
                    case 5:
                        //Temperatura
                        printCharacter(c[i], 13+deltaX, 7, FONT_COLOR, BACKGROUND_COLOR);
                        deltaX++;
                    break;
                    case 6:
                        //Gas
                        switch(c[i]){
                            case '1':
                                printCharacter('X', 5, 9, ERROR_COLOR, BACKGROUND_COLOR);
                            break;
                            default:
                                printCharacter('@', 5, 9, FONT_COLOR, BACKGROUND_COLOR);
                        }
                    break;
                    case 7:
                        //Fuego
                        switch(c[i]){
                            case '1':
                                printCharacter('X', 7, 10, ERROR_COLOR, BACKGROUND_COLOR);
                            break;
                            default:
                                printCharacter('@', 7, 10, FONT_COLOR, BACKGROUND_COLOR);
                        }
                    break;
                    }
        }
        i++;
    }
}

static void printOffScreen(void){
		fillScreen();
			
        printString("RecycleAnalytics UN", 1, 1, FONT_COLOR, BACKGROUND_COLOR);
        
        printString("Hora 20:20", 10, 3, FONT_COLOR, BACKGROUND_COLOR);
        
        printString("OFF", 8, 7, ERROR_COLOR, BACKGROUND_COLOR);
}

static void fontTest(void){
    fillScreen();
    char c=' ';
    for (int i=0;i<=30;i++)
    {
        for (int j=0;j<=30;j++)
        {
            if(i*j>98)return;
            printCharacter(c+i*j, i, j, 0x0000, 0x86c0);
        }
    }
}

static void lcd_wall(void)
{
    for (int i=1; i<=30; i++)
    {
        for (int j=3; j<=30; j++)
        {
            if((i==1)|(j==3)|(i==30)|(j==30))print_tile(BLOCK,i,j);
        }
    }
}

static void print_frame(void){

    fillScreen();
    lcd_wall();
    
    print_tile(LetterU,28,2);
    print_tile(LetterN,29,2);

    print_tile(LetterS,2,1);
    print_tile(LetterC,3,1);
    print_tile(LetterO,4,1);
    print_tile(LetterR,5,1);
    print_tile(LetterE,6,1);

    print_tile(N_0,2,2);
    print_tile(N_0,3,2);
    print_tile(N_0,4,2);
    print_tile(N_0,5,2);
}
