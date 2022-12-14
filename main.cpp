#include "TXLib.h"
//????????? ????????
struct Pictures
{
    int x;
    int y;
    HDC image;
    int w;
    int h;
    int w_scr;
    int h_scr;
    bool visible;
    string category;
};
//????????? ??????
struct Button
{
  int x;
  int y;
  const char* text;
  string category;
};
//??????? ????????? ??????

void drawButton(Button btn)
{
    //x=30 y=30
        txSetColor(TX_BLACK);
        txSetFillColor(TX_WHITE);
        Win32::RoundRect (txDC(), btn.x, btn.y, btn.x+150, btn.y+40, 30, 30);
        txSetFillColor(TX_BLACK);

        txSetColor(TX_BLACK);
        txSelectFont("Times  New Roman", 32);
        txDrawText(btn.x, btn.y, btn.x+150,btn.y+40, btn.text);
}

bool click(Button btn)
{
   return( txMouseButtons() == 1 &&
           txMouseX()>=btn.x &&
           txMouseX()<=btn.x+170 &&
           txMouseY()>=btn.y &&
           txMouseY()<=btn.y+70);
}

void drawPicture(Pictures pct)
{
if(pct.visible)
{
    Win32::TransparentBlt(txDC(), pct.x, pct.y, pct.w_scr, pct.h_scr, pct.image, 0, 0, pct.w, pct.h, TX_WHITE);
}

};

int main()
{
    txCreateWindow (1200, 800);
    txDisableAutoPause();
    txTextCursor (false);

    HDC Fon3 = txLoadImage("img/fon3.bmp");
    char str[100];
    int COUNT_BTN = 5;
    int COUNT_PIC = 17;
    int vybor = -1;
    bool mouse_free = false;
    int nCentralPic = 0;

    //??????
        Button btn[COUNT_BTN];
        btn[0] = {30,30,"????? ????","?????"};
        btn[1] = {200,30,"?????","?????"};
        btn[2] = {370,30,"?????","?????"};
        btn[3] = {540,30,"????","????"};
        btn[4] = {710,30,"?????","?????"};

        //???????? ????
        Pictures menuPic[COUNT_PIC];
        menuPic[0] = {1000, 400, txLoadImage("img/Building/Wall_A_02.bmp"), 320, 320, 90,90, false,"?????"};
        menuPic[1] = {1000, 300, txLoadImage("img/Building/Wall_B_02.bmp"), 320, 320, 90,90, false,"?????"};
        menuPic[2] = {1000, 200, txLoadImage("img/Building/Wall_C_02.bmp"), 320, 320, 90,90, false,"?????"};
        menuPic[3] = {1000, 400, txLoadImage("img/Platformer/Ground_10.bmp"), 128, 128, 90,90, false,"?????"};
        menuPic[4] = {1000, 300, txLoadImage("img/Platformer/Ground_11.bmp"), 128, 128, 90,90, false,"?????"};
        menuPic[5] = {1000, 200, txLoadImage("img/Platformer/Ground_12.bmp"), 128, 128, 90,90, false,"?????"};
        menuPic[6] = {1000, 400, txLoadImage("img/Building/Roof_A_04.bmp"), 352, 160, 90,40, false,"?????"};
        menuPic[7] = {1000, 300, txLoadImage("img/Building/Roof_A_05.bmp"), 352, 160, 90,40, false,"?????"};
        menuPic[8] = {1000, 200, txLoadImage("img/Building/Roof_B_04.bmp"), 352, 160, 90,40, false,"?????"};
        menuPic[9] = {1000, 100, txLoadImage("img/Building/Roof_B_05.bmp"), 352, 160, 90,40, false,"?????"};
        menuPic[10] = {1000, 400, txLoadImage("img/Building/Window_01.bmp"), 128, 128, 64,64, false,"????"};
        menuPic[11] = {1000, 300, txLoadImage("img/Building/Window_02.bmp"), 128, 128, 64,64, false,"????"};
        menuPic[12] = {1000, 200, txLoadImage("img/Building/Window_03.bmp"), 128, 128, 64,64, false,"????"};
        menuPic[13] = {1000, 100, txLoadImage("img/Building/Door_01.bmp"), 128, 256, 64,128, false,"?????"};
        menuPic[14] = {1000, 250, txLoadImage("img/Building/Door_02.bmp"), 128, 256, 64,128, false,"?????"};
        menuPic[15] = {1000, 400, txLoadImage("img/Building/Door_03.bmp"), 128, 256, 64,128, false,"?????"};
        menuPic[16] = {1000, 550, txLoadImage("img/Building/Door_04.bmp"), 128, 256, 64,128, false,"?????"};

         //??????????? ????????
        Pictures centralPic[100];


    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        txBegin();
        txSetColor(TX_WHITE);
        txClear();
        txBitBlt(txDC(), 0, 0, 1200, 900, Fon3);

        //????????? ??????
        for(int nk=0; nk<5; nk++)
        {
            drawButton(btn[nk]);
        }
        //????????? ???????? ????
        for(int npic=0; npic < COUNT_PIC; npic++)
        {
            drawPicture(menuPic[npic]);
        }
        //????????? ??????????? ????????
        for(int npic=0; npic < COUNT_PIC; npic++)
        {
            drawPicture(centralPic[npic]);
        }

        //????????? ???????? ???? ??  ?????????
        for(int nk=0; nk<5; nk++)
        {
            if(click(btn[nk]))
            {
                for(int npic=0; npic < COUNT_PIC; npic++)
                {
                    menuPic[npic].visible= false;
                    if(menuPic[npic].category == btn[nk].category)
                    {
                        menuPic[npic].visible=true;
                    }
                }
            }
        }

        //????????? ??????????? ???????? ??  ?????????
        for(int npic=0; npic < COUNT_PIC; npic++)
        {
          if( txMouseButtons() == 1 &&
           menuPic[npic].visible &&
           txMouseX()>=menuPic[npic].x &&
           txMouseX()<=menuPic[npic].x + menuPic[npic].w_scr &&
           txMouseY()>=menuPic[npic].y &&
           txMouseY()<=menuPic[npic].y + menuPic[npic].h_scr)
             {
                while(txMouseButtons() == 1)
                {
                    txSleep(10);
                }
                centralPic[nCentralPic] = { 250,
                                            200,
                                            menuPic[npic].image,
                                            menuPic[npic].w,
                                            menuPic[npic].h,
                                            menuPic[npic].w,
                                            menuPic[npic].h,
                                            menuPic[npic].visible,
                                            menuPic[npic].category
                                          };
                nCentralPic++;
             }
         }


        //????? ??????????? ????????
        for(int npic=0; npic < COUNT_PIC; npic++)
        {
          if(  txMouseButtons() == 1 &&
               centralPic[npic].visible &&
               txMouseX()>=centralPic[npic].x &&
               txMouseX()<=centralPic[npic].x + centralPic[npic].w &&
               txMouseY()>=centralPic[npic].y &&
               txMouseY()<=centralPic[npic].y + centralPic[npic].h)
             {
               vybor=npic;
               mouse_free = false;
             }
        }

        sprintf(str, "????? = %d nCentralPic = %d", vybor, nCentralPic);
        txTextOut(0,0, str);

        // ???????????? ???????? ??????????? ????????
        if(vybor>=0)
        {
          if(GetAsyncKeyState(VK_RIGHT)) centralPic[vybor].x += 3;
          if(GetAsyncKeyState(VK_LEFT)) centralPic[vybor].x -= 3;
          if(GetAsyncKeyState(VK_UP)) centralPic[vybor].y -= 3;
          if(GetAsyncKeyState(VK_DOWN)) centralPic[vybor].y += 3;
        }

        if(vybor>=0)
        {
              if(txMouseButtons() == 1 && !mouse_free)
                {
                    centralPic[vybor].x = txMouseX() - centralPic[vybor].w/2;
                    centralPic[vybor].y = txMouseY() - centralPic[vybor].h/2;
                }
              else
                {
                    if(!(txMouseButtons() == 1) && !mouse_free)
                    {
                        mouse_free = true;
                    }
                }
        }

        // ???????? ??????????? ???????? ? ??????
        if(vybor>=0 && GetAsyncKeyState(VK_DELETE))
        {
            centralPic[vybor] = centralPic[nCentralPic - 1];
            nCentralPic--;
            vybor=-1;
            mouse_free = true;
        }


        txSleep(50);
        txEnd();

    }

            for(int npic=0; npic < COUNT_PIC; npic++)
            {
                txDeleteDC(menuPic[npic].image);
            }




    return 0;
}

