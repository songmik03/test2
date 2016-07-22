#ifndef __ALIEN_H__
#define __ALIEN_H__

typedef struct _S_ALIEN_OBJECT {


	int m_nFSM;
	int m_nStep;

	double m_fXpos;
	double m_fYpos;

	double m_fSpeed;

	_S_MAP_OBJECT *m_pBody;
	struct _S_BULLET_OBJECT *m_pBullet;

	void (*pfApply)(struct _S_ALIEN_OBJECT *,double ,double);
	void (*pfDraw)(struct _S_ALIEN_OBJECT *,struct _S_MAP_OBJECT *);

	double m_fCenterX;
	double m_fCenterY;

} _S_ALIEN_OBJECT;

void alien_init(_S_ALIEN_OBJECT *pObj,_S_MAP_OBJECT *pBody);

#endif
