#include "lighting.h"

Lighting::Lighting() {}

AmbientLight& Lighting::getAmbientLight() { return m_ambientLight; }

glm::vec3 AmbientLight::getColor() { return m_color; }

void AmbientLight::setColor(glm::vec3 color) { m_color = color;}

float AmbientLight::getStrength() { return m_strength; }

void AmbientLight::setStrength(float strength) { m_strength = strength; }
