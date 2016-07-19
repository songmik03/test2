#ifndef __PLANE_H__
#define __PLANE_H__

typedef struct _S_Plane {

	int m_nFSM;
	int m_nStep;

	double m_fXpos;
	double m_fYpos;
	_S_MAP_OBJECT *m_pBody;
	void (*pfApply)(struct _S_Plane *,double, char );
	void (*pfDraw)(struct _S_Plane *,struct _S_MAP_OBJECT *);

	double m_fCenterX;
	double m_fCenterY;


}_S_Plane;

void Plane_init(_S_Plane *pObj,_S_MAP_OBJECT *pBody,int x, int y);

#endif
