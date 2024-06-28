#pragma once
#include <iostream>
#include <vector>
#include<reactphysics3d/reactphysics3d.h>

class rayCastCallBack : public rp3d::RaycastCallback
{
public:

	rayCastCallBack() 
	{
	
	};
	
	~rayCastCallBack()
	{
	
	}

	virtual rp3d::decimal notifyRaycastHit(const rp3d::RaycastInfo& info)
	{
		std::cout << "Hit point : " <<
			info.worldPoint.x << " , " <<
			info.worldPoint.y << " , " <<
			info.worldPoint.z <<
			std::endl;

		// Return a fraction of 1.0 to gather all hits
		return rp3d::decimal(0.0);
	}

private:

};

