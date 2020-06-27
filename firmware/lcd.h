#include "globalvar.h"
#include "tiles.h"
#include "homespun_font.h"

#define CHAR_WIDTH 7
#define CHAR_HEIGHT 8

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
    lcd_write_Odata(0x10);

    lcd_write_Oaddr(0xc5);
    lcd_write_Odata(0x2b);
    lcd_write_Odata(0x2b);    

    lcd_write_Oaddr(0xc7);
    lcd_write_Odata(0xc0);

    lcd_write_Oaddr(0x36);
    lcd_write_Odata(0x88);

    lcd_write_Oaddr(0x3a);
    lcd_write_Odata(0x55);

    lcd_write_Oaddr(0xb1);
    lcd_write_Odata(0x1b);

    lcd_write_Oaddr(0xb7);
    lcd_write_Odata(0x07);

    lcd_write_Oaddr(0x11);

    lcd_write_Oaddr(0x21);

    lcd_write_Oaddr(0x29);

    busy_wait(1.5);
    busy_wait(5);

//**********MODO VENTANA 30X30 TILES***********//
    lcd_write_Oaddr(0x12);
    lcd_write_Oaddr(0x30);
    lcd_write_Odata(0x00);
    lcd_write_Odata(0x29);
    lcd_write_Odata(0x01);
    lcd_write_Odata(0x18);
    //printf("\nLCD ready\n");
}
//Added by Luis Carlos

static void preparePrint(uint16_t posx, uint16_t posy, uint8_t width, uint8_t height){
    uint16_t xcord=8*(posx-1);
    uint16_t ycord=8*(posy-1)+0x27;


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

    // Convert the character to an index
    c = c & 0x7F;
    if (c < ' ') {
        c = 0;
    } else {
        c -= ' ';
    }

    // 'font' is a multidimensional array of [96][char_width]
    // which is really just a 1D array of size 96*char_width.
    const uint8_t* chr = font[c*CHAR_WIDTH];

    // Draw pixels
    preparePrint(posx, posy, CHAR_WIDTH, CHAR_HEIGHT);
    
    for (j=0; j<CHAR_WIDTH; j++) {
        for (i=0; i<CHAR_HEIGHT; i++) {

            if (chr[j] & (1<<i)) {
                drawPixel(fontColor);
            }else{
                drawPixel(background);
            }
        }
    }
}

static void fillScreen(void)
{
    for (int i=1;i<=30;i++)
    {
        for (int j=1;j<=30;j++)
        {
            print_tile(GROUND,i,j);
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
