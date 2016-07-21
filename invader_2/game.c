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
//한발
struct timespec work_timer;
double acc_tick,last_tick;
int bLoop = 1;

_S_MAP_OBJECT gScreenBuf[2];

_S_MAP_OBJECT gPlayerModel;
_S_MAP_OBJECT gBulletModel;
_S_MAP_OBJECT gAlienModel;
_S_MAP_OBJECT gPbulletModel;

_S_Plane gPlayerObject;
_S_BULLET_OBJECT gBulletObjects[2];
_S_ALIEN_OBJECT gAlienObjects[8];
_S_BULLET_OBJECT gPbulletObject;

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
int main()
{

    for(int i=0;i<2;i++) {
        map_init(&gScreenBuf[i]);
        map_new(&gScreenBuf[i],50,30);

    }

    map_init(&gPlayerModel);
    map_load(&gPlayerModel, "plasma.dat");

    map_init(&gBulletModel);
    map_load(&gBulletModel, "missile.dat");

    map_init(&gAlienModel);
    map_load(&gAlienModel,"alien.dat");

    map_init(&gPbulletModel);
    map_load(&gPbulletModel,"bullet1.dat");

    Plane_init(&gPlayerObject,&gPlayerModel,23,25);
    gPlayerObject.m_nFSM = 1;


    //bullet_init(&gPbulletObject,0,0,10,&gPbulletModel);
    //gPbulletObject.m_nFSM = 1;

    for(int i=0;i<2;i++)
    {   _S_BULLET_OBJECT *pObj = &gBulletObjects[i];
        bullet_init(pObj,0,0,0,&gBulletModel);
        pObj->m_nFSM = 1;
    }

    bullet_init(&gPbulletObject,0,0,0,&gPbulletModel);
    gPbulletObject.m_nFSM = 1;


    double TablePosition[] = {0,6,12};

    for(int i=0;i<3;i++)
    {
        _S_ALIEN_OBJECT *pObj = &gAlienObjects[i];
        alien_init(pObj,&gAlienModel);
        pObj->m_fXpos = TablePosition[i];
        pObj->m_fYpos = 2;
        pObj->m_nFSM = 1;
        pObj->m_pBullet = &gBulletObjects[i];
    }

    system("clear");
    set_conio_terminal_mode();
    acc_tick = last_tick = 0;

    while(bLoop) {

        //타이밍 처리
        clock_gettime(CLOCK_MONOTONIC,&work_timer);
        double cur_tick = work_timer.tv_sec + (double)(work_timer.tv_nsec * 1e-9);
        double delta_tick = cur_tick - last_tick;

        last_tick = cur_tick;

        //실시간 입력
        if(kbhit() != 0) {

            char ch = getch();
            if(ch == 'q') {

                bLoop=0;
                puts("bye~ \r");
            }
            else if (ch == 'j') {

                gPbulletObject.pfFire(&gPbulletObject,gPlayerObject.m_fXpos,gPlayerObject.m_fYpos,10,0,-1,10);

                //gPbulletObject.pfFire(&gPbulletObject,gPlayerObject.m_fXpos,gPlayerObject.m_fYpos,10,0,-1,10);


            }
            gPlayerObject.pfApply(&gPlayerObject,delta_tick,ch);
        }
        for(int i=0;i<3;i++)
        {
            _S_ALIEN_OBJECT *pObj = &gAlienObjects[i];
            pObj->pfApply(pObj,delta_tick);
        }
        for(int i=0;i<2;i++)
        {
            _S_BULLET_OBJECT *pObj = &gBulletObjects[i];
            pObj->pfApply(pObj,delta_tick);
        }

        if(gBulletObjects[0].m_nFSM !=0) {
            double dist1 = getDist(&gBulletObjects[0],&gPlayerObject);
            double dist2 = getDist(&gBulletObjects[1],&gPlayerObject);

            if(dist1<0.25) {
                gBulletObjects[0].m_nFSM = 0;
                gPlayerObject.m_nFSM = 0;
            }
            else if(dist2<0.25) {
                gBulletObjects[1].m_nFSM = 0;
                gPlayerObject.m_nFSM = 0;
            }
        }

        gPbulletObject.pfApply(&gPbulletObject,delta_tick);
        if(gPbulletObject.m_nFSM != 0) {
            double dist1 = AgetDist(&gPbulletObject,&gAlienObjects[0]);
            double dist2 = AgetDist(&gPbulletObject,&gAlienObjects[1]);
            double dist3 = AgetDist(&gPbulletObject,&gAlienObjects[2]);

            if(dist1<2) {
                gPbulletObject.m_nFSM = 0;
                gAlienObjects[0].m_nFSM = 0;
            }
            else if(dist2<2) {
                gPbulletObject.m_nFSM = 0;
                gAlienObjects[1].m_nFSM = 0;
                }
            else if(dist3<2) {
                gPbulletObject.m_nFSM = 0;
                gAlienObjects[2].m_nFSM = 0;
                }
            }

            //타이밍 계산
            acc_tick += delta_tick;


            if(acc_tick>0.1) {
                gotoxy(0,0);
                map_drawTile(&gScreenBuf[0],0,0,&gScreenBuf[1]);
                gPlayerObject.pfDraw(&gPlayerObject,&gScreenBuf[1]);

                //gPbulletObject.pfDraw(&gPbulletObject,&gScreenBuf[1]);

                gPbulletObject.pfDraw(&gPbulletObject,&gScreenBuf[1]);

                //gTestBullet.pfDraw(&gTestBullet,&gScreenBuf[1]);
                for(int i=0;i<3;i++)
                {
                    _S_ALIEN_OBJECT *pObj = &gAlienObjects[i];
                    pObj->pfDraw(pObj,&gScreenBuf[1]);
                }
                for(int i=0;i<2;i++)
                {
                    _S_BULLET_OBJECT *pObj = &gBulletObjects[i];
                    pObj->pfDraw(pObj,&gScreenBuf[1]);
                }
                map_dump(&gScreenBuf[1],Default_Tilepalette);
                acc_tick = 0;
            }
    }

    return 0;
}

