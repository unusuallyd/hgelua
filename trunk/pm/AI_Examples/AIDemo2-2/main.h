#ifndef _MAINHEADER
#define _MAINHEADER

#include "winmain.h"
#include "mymath.h"
#include "RigidBody2D.h"


#define	_RENDER_FRAME_COUNT		330


void	UpdateSimulation(void);
bool	Initialize(void);
void	DrawCraft(RigidBody2D	craft, COLORREF clr);
void	DoCraft2Chase(void);
void	DoCraft2Evade(void);
void	DoCraft2Intercept(void);

int		GetRandomNumber(int min, int max, bool seed=false);
Vector	GetVelocityIntersection(void);
void	DoCraft2ModulateThrust(void);

void	DoCraft2InterceptAlt(void);

//兰纳-琼斯势（Lennard-Jones potential function, 又称L-J势能函数或6-12势能函数）
//是计算化学中用来模拟两分子间作用势能的一个函数。
// 让其互相吸引，而又在靠近时表现出突然离开
void	DoAttractCraft2(void);

#endif