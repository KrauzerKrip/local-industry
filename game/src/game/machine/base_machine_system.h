#pragma once

#include <entt/entt.hpp>
#include "physics/physical_constants.h"


class BaseMachineSystem {
public:
	BaseMachineSystem(entt::registry* pRegistry, PhysicalConstants* pPhysicalConstants) { 
		m_pRegistry = pRegistry;
		m_pPhysicalConstants = pPhysicalConstants;
	}

	virtual ~BaseMachineSystem() {
	    delete m_pRegistry;
		delete m_pPhysicalConstants;
	}

    /**
     * \brief 
     * \param deltaTime time between updates
     */
	virtual void update(double updateInterval) = 0;

    /**
     * \brief 
     * \param deltaTime time between machine updates
     */
    virtual void machineUpdate(double updateInterval) = 0;

protected:
	entt::registry* m_pRegistry = nullptr;
	PhysicalConstants* m_pPhysicalConstants = nullptr;
};