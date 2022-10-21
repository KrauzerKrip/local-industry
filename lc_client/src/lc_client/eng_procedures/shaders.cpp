#include "shaders.h"

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "lc_client/util/resource_loading.h"
#include "lc_client/util/directories.h"

CMRC_DECLARE(eng_resources);


ShaderManager::ShaderManager() {
    m_pVertexShaders = new std::unordered_map<std::string, int>(); 
    m_pFragmentShaders = new std::unordered_map<std::string, int>();
};

ShaderManager::~ShaderManager() {
    delete(m_pVertexShaders);
    delete(m_pFragmentShaders);
}

void ShaderManager::loadShaders() {

    cmrc::embedded_filesystem fileSystem = eng::getFileSystem();

    auto loadVertexShader = [&](std::string path, std::string fileName) {

        auto shaderSourceIterator = eng::getResource(path + "/" + fileName);
        auto shaderSourceBegin = shaderSourceIterator.begin();

        unsigned int shader;
        shader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(shader, 1, &shaderSourceBegin, 0);
    
        compileShader(shader, fileName);
    };

    auto loadFragmentShader = [&](std::string path, std::string fileName) {
        auto shaderSourceIterator = eng::getResource(path + "/" + fileName);
        auto shaderSourceBegin = shaderSourceIterator.begin();

        unsigned int shader;
        shader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(shader, 1, &shaderSourceBegin, 0);

        compileShader(shader, fileName);
    };


    iterateDirectoryRecursive(fileSystem,"dev/shaders/vert", loadVertexShader);
    iterateDirectoryRecursive(fileSystem, "dev/shaders/frag", loadFragmentShader);
    
    iterateDirectoryRecursive(fileSystem, "game/shaders", loadVertexShader);

}

void ShaderManager::compileShader(int shader, std::string shaderName){
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success)
    {
        std::cout << "shaders: shader compiled: " << shaderName << std::endl;
    }
    else {
        glGetShaderInfoLog(shader, 512, 0, infoLog);
        std::cerr << "shaders: shader compilation failure: \n" <<
            infoLog << std::endl;
    }
}


