#include "shaders.h"

#include <iostream>
#include <vector>

#include "lc_client/util/resource_loading.h"
#include "lc_client/util/directories.h"

CMRC_DECLARE(eng_resources);


ShaderManager::ShaderManager() {};

ShaderManager::~ShaderManager() {
}

void ShaderManager::loadShaders() {

    cmrc::embedded_filesystem fileSystem = eng::getFileSystem();

    auto loadShader = [](std::string path, std::string fileName) {
        std::cout << fileName << std::endl;
    };


    iterateDirectoryRecursive(fileSystem,"dev/shaders", loadShader);
    iterateDirectoryRecursive(fileSystem, "game/shaders", loadShader);

}


