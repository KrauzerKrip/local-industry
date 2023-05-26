#include "tier0.h"
#include "tier0.h"

#include <imgui.h>

#include "conpar/conpars_init.h"
#include "conpar/parameters.h"

#include "console/console.h"


Tier0::Tier0() {
	m_pParameters = new Parameters();
	initParameters(*m_pParameters);
	
	m_pConsole = new Console(m_pParameters);

	ImGui::CreateContext();

	m_pImGuiFonts = new ImGuiFonts();

	m_pIConsole = m_pConsole;
}

Tier0::~Tier0() {
	delete m_pParameters;
	delete m_pConsole;
}

Parameters* Tier0::getParameters() { return m_pParameters; }

Console* Tier0::getConsole() { return m_pConsole; }

ImGuiFonts* Tier0::getImGuiFonts() { return m_pImGuiFonts; }

IConsole* Tier0::getIConsole() { return m_pIConsole; }

IConsole* Tier0::m_pIConsole = nullptr;
