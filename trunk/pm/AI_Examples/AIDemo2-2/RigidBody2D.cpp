#include "RigidBody2D.h"

RigidBody2D::RigidBody2D(void)
{
	
	
}

void	RigidBody2D::CalcLoads(void) // 求推力，扭力矩
{
	Vector	Fb;				// stores the sum of forces
	Vector	Mb;				// stores the sum of moments
	Vector	Thrust;			// thrust vector
	
	// reset forces and moments:
	vForces.x = 0.0f;
	vForces.y = 0.0f;
	vForces.z = 0.0f;	// always zero in 2D

	vMoment.x = 0.0f;	// always zero in 2D
	vMoment.y = 0.0f;	// always zero in 2D
	vMoment.z = 0.0f;

	Fb.x = 0.0f;	
	Fb.y = 0.0f;	
	Fb.z = 0.0f;	

	Mb.x = 0.0f;
	Mb.y = 0.0f;
	Mb.z = 0.0f;

	// Define the thrust vector, which acts through the craft's CG
	// 计算推力向量,自我坐标系
	Thrust.x = 0.0f;
	Thrust.y = 1.0f;
	Thrust.z = 0.0f;  // zero in 2D
	Thrust *= ThrustForce;
	
	// Calculate forces and moments in body space:
	Vector	vLocalVelocity;
	float	fLocalSpeed;
	Vector	vDragVector;	
	float	tmp;
	Vector	vResultant;	
	Vector	vtmp;	

	// Calculate the aerodynamic drag force:
		// Calculate local velocity:
		// The local velocity includes the velocity due to linear motion of the craft, 
		// plus the velocity at each element due to the rotation of the craft.
		vtmp = vAngularVelocity^CD; // rotational part
		vLocalVelocity = vVelocityBody + vtmp; 

		// Calculate local air speed
		fLocalSpeed = vLocalVelocity.Magnitude();

		// Find the direction in which drag will act.
		// Drag always acts inline with the relative velocity but in the opposing direction
		if(fLocalSpeed > tol) 
		{
			vLocalVelocity.Normalize();
			vDragVector = -vLocalVelocity;		

			// Determine the resultant force on the element.
			double f;
			if((Thrust * vLocalVelocity)/(Thrust.Magnitude() * vLocalVelocity.Magnitude()) > 0)
				f = 2;	
			else
				f = 1;

			tmp = 0.5f * rho * fLocalSpeed*fLocalSpeed * ProjectedArea * f;		
			vResultant = vDragVector * _LINEARDRAGCOEFFICIENT * tmp; // simulate fuselage drag

			// Keep a running total of these resultant forces (total force)
			Fb += vResultant;
		
			// Calculate the moment about the CG of this element's force
			// and keep a running total of these moments (total moment)
			vtmp = CD^vResultant; 
			Mb += vtmp;
		}

		// Calculate the Port & Starboard bow thruster forces:
		// Keep a running total of these resultant forces (total force)
		Fb += 3*PThrust;
		

		// Calculate the moment about the CG of this element's force
		// and keep a running total of these moments (total moment)
		vtmp = CPT^PThrust; 
		Mb += vtmp;

		// Keep a running total of these resultant forces (total force)
		Fb += 3*SThrust;

		// Calculate the moment about the CG of this element's force
		// and keep a running total of these moments (total moment)
		vtmp = CST^SThrust; 		
		Mb += vtmp;

		// do other applied forces here
		Fb += Fa;
		vtmp = Pa ^ Fa;
		Mb += vtmp;

		// Calculate rotational drag
		if(vAngularVelocity.Magnitude() > tol)
		{
			vtmp.x = 0;
			vtmp.y = 0;
			tmp = 0.5f * rho * vAngularVelocity.z*vAngularVelocity.z * ProjectedArea;
			if(vAngularVelocity.z > 0.0)
				vtmp.z = -_ANGULARDRAGCOEFFICIENT * tmp;		
			else
				vtmp.z = _ANGULARDRAGCOEFFICIENT * tmp;		

			Mb += vtmp;
		}


	// Now add the propulsion thrust
	Fb += Thrust; // no moment since line of action is through CG

	// Convert forces from model space to earth space
	vForces = VRotate2D(fOrientation, Fb);

	vMoment += Mb;	
}

void	RigidBody2D::UpdateBodyEuler(double dt)
{
		Vector a;
		Vector dv;
		Vector ds;
		float  aa;
		float  dav;
		float  dr;
	
		// Calculate forces and moments:
		CalcLoads();
		
		// Integrate linear equation of motion:
		a = vForces / fMass; // a = F / m
		
		dv = a * dt;
		vVelocity += dv;

		ds = vVelocity * dt;
		vPosition += ds;

		// Integrate angular equation of motion:
		// 角加速度 = 力矩 / 转动惯量
		aa = vMoment.z / fInertia; // Aa = M / I  

		dav = aa * dt;
		
		vAngularVelocity.z += dav;
		
		dr = RadiansToDegrees(vAngularVelocity.z * dt);
		fOrientation += dr; 
		
		// Misc. calculations:
		fSpeed = vVelocity.Magnitude();		
		vVelocityBody = VRotate2D(-fOrientation, vVelocity);	
}

void	RigidBody2D::SetThrusters(bool p, bool s)
{
	PThrust.x = 0;
	PThrust.y = 0;
	SThrust.x = 0;
	SThrust.y = 0;
	
	if(p)
		PThrust.x = -_STEERINGFORCE;
	if(s)
		SThrust.x = _STEERINGFORCE;
}


Vector	VRotate2D( float angle, Vector u)
{
	float	x,y;

	x = u.x * cos(DegreesToRadians(-angle)) + u.y * sin(DegreesToRadians(-angle));
	y = -u.x * sin(DegreesToRadians(-angle)) + u.y * cos(DegreesToRadians(-angle));

	return Vector( x, y, 0);
}

void	RigidBody2D::ModulateThrust(bool up)
{
	double	dT = up ? _DTHRUST:-_DTHRUST;

	ThrustForce += dT;

	if(ThrustForce > _MAXTHRUST) ThrustForce = _MAXTHRUST;
	if(ThrustForce < _MINTHRUST) ThrustForce = _MINTHRUST;
}


void	RigidBody2D::CrossBound(float w, float h)
{
	if(vPosition.x > w) vPosition.x = 0;
	else if(vPosition.x < 0) vPosition.x = w;
	if(vPosition.y > h) vPosition.y = 0;
	else if(vPosition.y < 0) vPosition.y = h;
}

void	RigidBody2D::SetProjected(float w, float l)
{
	fWidth = w;
	fLength = l;
	ProjectedArea = (fLength + fWidth) * _DRAWHEIGHT;

	CD.y = -0.12*fLength;		CD.x = 0.0f;			// coordinates of the body center of drag
	CT.y = -0.50*fLength;		CT.x = 0.0f;			// coordinates of the propeller thrust vector
	CPT.y = 0.5*fLength;		CPT.x = -0.5*fWidth;	// coordinates of the port bow thruster
	CST.y = 0.5*fLength;		CST.x = 0.5*fWidth;	// coordinates of the starboard bow thruster
}

void	RigidBody2D::SetMass(float mass, float inertia/* =_DEFAULT */)
{
	if (inertia == _DEFAULT)
	{
		inertia = mass;
	}
	fMass = mass;
	fInertia = inertia;
}

void	RigidBody2D::SetPosistion(float x, float y, float ori)
{
	vPosition.x = x;
	vPosition.y = y;
	fOrientation = ori;
}
