#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <termios.h>

#include "../engine/engine2d.h"
#include "../mapEditor/map.h"
#include "bullet.h"
#include "plane.h"
#include <math.h>
#include "alien.h"


//invader game
//try mainTitle


struct timespec work_timer;
double acc_tick,last_tick;

int bLoop = 1;
static int nFSM = 0;
static int nStep = 0;

int wall_xpos[2] = {0,59};
static int score = 0;

_S_MAP_OBJECT gScreenBuf[2];

_S_MAP_OBJECT gPlayerModel;
_S_MAP_OBJECT gBulletModel;
_S_MAP_OBJECT gAlienModel;
_S_MAP_OBJECT gPbulletModel;
_S_MAP_OBJECT gBoxModel;


_S_Plane gPlayerObject;
_S_BULLET_OBJECT gBulletObjects[5];
_S_ALIEN_OBJECT gAlienObjects[6];
_S_BULLET_OBJECT gPbulletObject[32];
_S_BULLET_OBJECT gBoxObject;

double getDist(_S_BULLET_OBJECT *pBullet,_S_Plane *pPlane)
{
    double bullet_pos_x = pBullet->m_fXpos;
    double bullet_pos_y = pBullet->m_fYpos;

    double target_pos_x = pPlane->m_fXpos;
    double target_pos_y = pPlane->m_fYpos;

    double vx = target_pos_x - bullet_pos_x;

    double vy = target_pos_y - bullet_pos_y;

    double dist = sqrt(vx*vx+vy*vy);

    return dist;
}
double AgetDist(_S_BULLET_OBJECT *pBullet,_S_ALIEN_OBJECT *pPlane)
{
    double bullet_pos_x = pBullet->m_fXpos;
    double bullet_pos_y = pBullet->m_fYpos;

    double target_pos_x = pPlane->m_fXpos;
    double target_pos_y = pPlane->m_fYpos;

    double vx = target_pos_x - bullet_pos_x;

    double vy = target_pos_y - bullet_pos_y;

    double dist = sqrt(vx*vx+vy*vy);

    return dist;
}
double APgetDist(_S_ALIEN_OBJECT *pAlien,_S_Plane *pPlane)
{
    double bullet_pos_x = pAlien->m_fXpos;
    double bullet_pos_y = pAlien->m_fYpos;

    double target_pos_x = pPlane->m_fXpos;
    double target_pos_y = pPlane->m_fYpos;

    double vx = target_pos_x - bullet_pos_x;

    double vy = target_pos_y - bullet_pos_y;

    double dist = sqrt(vx*vx+vy*vy);

    return dist;
}
void mainTitle()
{
    switch(nStep) {
        case 0:

        puts("\r\n \r\n");
        puts("\r\n \r\n");
        setColor(31,40);
        puts("\r\n \r\n                   INVADER GAME\r\n");
        setColor(0,0);


        puts("\r\n \r\n");
        puts("\r\n \r\n            < press any key to start >");
        puts("\r\n \r\n");
        puts("\r\n \r\n");
        puts("\r\n      ------------control keys------------");
        puts("\r\n          W = UP");
        puts("\r\n          A = LEFT  ");
        puts("\r\n          D = RIGHT");
        puts("\r\n          S = DOWN");
        puts("\r\n       ** J = SHOOT");


        nStep = 1;
        break;

        case 1:
        if(kbhit() != 0) {
            char ch = getch();
            nFSM = 1;
            nStep = 0;
            system("clear");
        }
        break;

    }

}
int main()
{
    srand(time(NULL));

    for(int i=0;i<2;i++) {
        map_init(&gScreenBuf[i]);
        map_new(&gScreenBuf[i],60,30);

    }

    map_init(&gPlayerModel);
    map_load(&gPlayerModel, "plasma.dat");

    map_init(&gBulletModel);
    map_load(&gBulletModel, "bullet2.dat");

    map_init(&gAlienModel);
    map_load(&gAlienModel,"small.dat");

    map_init(&gPbulletModel);
    map_load(&gPbulletModel,"bullet3.dat");

    map_init(&gBoxModel);
    map_load(&gBoxModel,"box.dat");

    //---------------------------------------------------player plane
    Plane_init(&gPlayerObject,&gPlayerModel,23,25);
    gPlayerObject.m_nFSM = 1;

    //-----------------------------------box
    bullet_init(&gBoxObject,0,0,0,&gBoxModel);
    gBoxObject.m_nFSM = 1;

    //---------------------------------player bullet
    for(int i=0;i<32;i++)
    {
        _S_BULLET_OBJECT *pObj = &gPbulletObject[i];
        bullet_init(pObj,0,0,0,&gPbulletModel);
        pObj->m_nFSM = 1;
    }
     //--------------------------------alien bullet
    for(int i=0;i<5;i++)
    {   _S_BULLET_OBJECT *pObj = &gBulletObjects[i];
        bullet_init(pObj,0,0,0,&gBulletModel);
        pObj->m_nFSM = 1;
    }

    //--------------------------------------------------alien objects
    double TablePosition_x[] = {0,6,12,18,24,30,36,42,48,54};
    double TablePosition_y[] = {0,2,0,2,0,2,0,2,0,2};

    for(int i=0;i<6;i++)
    {
        _S_ALIEN_OBJECT *pObj = &gAlienObjects[i];
        alien_init(pObj,&gAlienModel);
        pObj->m_fXpos = TablePosition_x[i];
        pObj->m_fYpos = TablePosition_y[i]+3;
        pObj->m_nFSM = 1;
        pObj->m_pBullet = &gBulletObjects[i];
    }
//============================
    system("clear");
    set_conio_terminal_mode();
    acc_tick = last_tick = 0;
    //============================ loop starts
    while(bLoop) {


        //타이밍 처리
        clock_gettime(CLOCK_MONOTONIC,&work_timer);
        double cur_tick = work_timer.tv_sec + (double)(work_timer.tv_nsec * 1e-9);
        double delta_tick = cur_tick - last_tick;

        last_tick = cur_tick;

        if(nFSM == 0) {
            mainTitle(delta_tick);

        }
        else if(nFSM == 1) {



            //실시간 입력
            if(kbhit() != 0) {

                char ch = getch();
                if(ch == 'q') {

                    bLoop=0;
                    puts("bye~ \r");
                }

            //Pbullet fire -J
                else if (ch == 'j') {

                    for(int i=0;i<32;i++)
                    {
                        _S_BULLET_OBJECT *pObj = &gPbulletObject[i];
                        if(pObj->m_nFSM == 0) {
                            pObj->pfFire(pObj,gPlayerObject.m_fXpos,gPlayerObject.m_fYpos,10,0,-1,10);
                        break;
                        }
                    }

                }
            //player apply
                gPlayerObject.pfApply(&gPlayerObject,delta_tick,ch);
            }
            //alien apply
            double randPosition[] = {0,2,6,4,8,2,1,4,0,2};
            for(int i=0;i<6;i++)
            {

                double randNumber = randPosition[i];

                _S_ALIEN_OBJECT *pObj = &gAlienObjects[i];
                pObj->pfApply(pObj,delta_tick,randNumber);

                if(pObj->m_nFSM !=0) {
                    double dist[10];
                    dist[i] = APgetDist(pObj,&gPlayerObject);


                    if(dist[i]<1.25) {
                        //pObj->m_nFSM = 0;
                        gPlayerObject.m_nFSM = 0;



                    }

                }
            }

            //alien bullet apply
            for(int i=0;i<5;i++)
            {

                _S_BULLET_OBJECT *pObj = &gBulletObjects[i];
                pObj->pfApply(pObj,delta_tick);

            //alien bullet --> player plane 충돌
                if(pObj->m_nFSM !=0) {
                    double dist[2];
                    dist[i] = getDist(pObj,&gPlayerObject);


                    if(dist[i]<0.25) {
                        pObj->m_nFSM = 0;
                        gPlayerObject.m_nFSM = 0;

                    }

                }

            }
            //Pb apply
            for(int i=0;i<32;i++) {
                _S_BULLET_OBJECT *pObj = &gPbulletObject[i];
                pObj->pfApply(pObj,delta_tick);

            //player bullet ---> alien 충돌
                if(pObj->m_nFSM != 0) {
                    for(int i=0;i<10;i++) {
                        double dist[10];
                        dist[i] = AgetDist(pObj,&gAlienObjects[i]);


                        if(dist[i]<2) {
                            pObj->m_nFSM = 0;
                            gAlienObjects[i].m_nFSM = 0;
                            //score += 10;

                            if(gBoxObject.m_nFSM ==0) {
                                double boxposition[] = {30,22,16,10,28,30,15,24,20,22};
                                gBoxObject.pfFire(&gBoxObject,boxposition[i],10,5,0,1,5);
                            }
                            if(gAlienObjects[0].m_nFSM == 0 && gAlienObjects[1].m_nFSM == 0 &&
                            gAlienObjects[2].m_nFSM == 0 && gAlienObjects[3].m_nFSM == 0 &&
                            gAlienObjects[4].m_nFSM == 0 && gAlienObjects[5].m_nFSM == 0 ) {
                                nFSM = 2;
                            }
                        }

                    }

                }

            }

            if(gPlayerObject.m_nFSM ==0) {
                system("clear");
                puts("\r\n \r\n");
                puts("\r\n \r\n");
                printf("\r\n -----------------------------\r\n");
                setColor(32,40);
                printf("          GAME OVER");
                setColor(0,0);
                printf("\r\n -----------------------------\r\n");
                puts("\r\n \r\n");
                puts("\r\n \r\n");
                bLoop =0;

            }
            gBoxObject.pfApply(&gBoxObject,delta_tick);
            if(gBoxObject.m_nFSM !=0) {
                double distb;
                distb = getDist(&gBoxObject,&gPlayerObject);


                if(distb<1.25) {
                    gBoxObject.m_nFSM = 0;
                    score += 100;
                    //gPlayerObject.m_nFSM = 0;

                }

            }

            //타이밍 계산
            acc_tick += delta_tick;


            if(acc_tick>0.1) {
            gotoxy(0,0);
            map_drawTile(&gScreenBuf[0],0,0,&gScreenBuf[1]);


            for(int i=0;i<2;i++) {
                for(int a=0; a<60;a++) {

                    map_put(&gScreenBuf[0],wall_xpos[i],a,8);

                }

            }


            printf("\r\n                                        score : %d\r\n",score);


            gBoxObject.pfDraw(&gBoxObject,&gScreenBuf[1]);

            //player draw
            gPlayerObject.pfDraw(&gPlayerObject,&gScreenBuf[1]);


            //player bullet draw
            for(int i=0;i<32;i++) {
                _S_BULLET_OBJECT *pObj = &gPbulletObject[i];
                pObj->pfDraw(pObj,&gScreenBuf[1]);
            }



            //alien draw
            for(int i=0;i<6;i++)
            {
                _S_ALIEN_OBJECT *pObj = &gAlienObjects[i];
                pObj->pfDraw(pObj,&gScreenBuf[1]);
            }

            //alien bullet draw
            for(int i=0;i<5;i++)
            {
                _S_BULLET_OBJECT *pObj = &gBulletObjects[i];
                pObj->pfDraw(pObj,&gScreenBuf[1]);
            }
            //map dump
            map_dump(&gScreenBuf[1],Default_Tilepalette);
            acc_tick = 0;

            }

        }
        else if(nFSM == 2) {
        bLoop = 0;
        system("clear");
        puts("\r\n \r\n");
        puts("\r\n \r\n");

        printf("                   GG :)");

        puts("\r\n \r\n");
        printf("           TOTAL GAME SCORE : %d", score);
        puts("\r\n \r\n");
        puts("\r\n \r\n");
        }

    }

    return 0;
}

