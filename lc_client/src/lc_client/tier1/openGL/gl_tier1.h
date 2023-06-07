#pragma once

#include "lc_client/tier1/tier1.h"



class Tier1Gl : public Tier1 {
public:
	Tier1Gl(eng::IResource* pResource, Tier0* pTier0);
	~Tier1Gl() = default;

protected:
private:
};
