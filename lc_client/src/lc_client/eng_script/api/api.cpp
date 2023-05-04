#include "api.h"

Api::Api(GraphicsEntitiesUtil* pGraphicsEntitiesUtil) : m_sceneApi(pGraphicsEntitiesUtil) {

}
SceneApi& Api::getSceneApi(){ return m_sceneApi; };
