#ifndef _RIGIDBODY2DHEADER
#define _RIGIDBODY2DHEADER

#include "mymath.h"

#define	 _THRUSTFORCE				20.0f/2
#define	 _MAXTHRUST					80.0f/2
#define	 _MINTHRUST					0.0f
#define	 _DTHRUST					0.01f
#define  _STEERINGFORCE				6.0f
#define  _LINEARDRAGCOEFFICIENT		0.3f
#define  _ANGULARDRAGCOEFFICIENT	5000.0f
#define _DEFAULT 0xfefefefe // default value
#define _DRAWHEIGHT 5.0f  // z index for draw

//------------------------------------------------------------------------//
// Rigid body structure (2D only)
//------------------------------------------------------------------------//
class RigidBody2D {
public:
	float	fMass;				// total mass (constant), 质量,质量是惯性的量度
	float	fInertia;			// mass moment of inertia in body coordinates (constant), 转动惯量
	
	Vector	vPosition;			// position in earth coordinates, 位置
	Vector	vVelocity;			// velocity in earth coordinates, 速度-世界坐标
	Vector	vVelocityBody;		// velocity in body coordinates, 速度-自我坐标 
	Vector	vAngularVelocity;	// angular velocity in body coordinates, 角速度
		
	float	fSpeed;				// speed (magnitude of the velocity), 速度大小
	float	fOrientation;		// orientation , 角度	

	Vector	vForces;			// total force on body 推力，产生加速度
	Vector	vMoment;			// total moment (torque) on body (2D: about z-axis only) 力矩,产生角加速度

	float	ThrustForce;		// Magnitude of the thrust force, 推力大小
	Vector	PThrust, SThrust;	// bow thruster forces, 两个扭力

	// 形状相关
	float	fWidth;				// bounding dimensions
	float	fLength;
	float	ProjectedArea;

	Vector	CD; // 自我坐标系中心
	Vector	CT; // 推力所在点
	Vector	CPT;// P扭力所在点
	Vector	CST;// S扭力所在点

	Vector	Fa;// other applied force
	Vector  Pa;// location of other applied force

	//Vector	vCollisionPoint;	// point of impact in local coordinates	

	RigidBody2D(void);
	void	CalcLoads(void);
	void	UpdateBodyEuler(double dt);
	void	SetThrusters(bool p, bool s);
	void	ModulateThrust(bool up);
	void	CrossBound(float w, float h);

	void	SetMass(float mass, float inertia=_DEFAULT);
	void	SetProjected(float w, float l); // draw shape
	void	SetPosistion(float x, float y, float ori);
};

Vector	VRotate2D( float angle, Vector u);

#endif
