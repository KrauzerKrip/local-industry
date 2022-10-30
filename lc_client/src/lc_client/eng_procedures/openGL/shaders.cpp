#include "shaders.h"

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "lc_client/util/resource_loading.h"
#include "lc_client/util/directories.h"
#include "lc_client/util/file_util.h"

CMRC_DECLARE(eng_resources);


ShaderManagerGl::ShaderManagerGl() {
    m_pVertexShaders = new std::unordered_map<std::string, int>(); 
    m_pFragmentShaders = new std::unordered_map<std::string, int>();
};

ShaderManagerGl::~ShaderManagerGl() {

    for (auto const& [name, id] : *m_pVertexShaders) {
        glDeleteShader(id);
    }

    for (auto const& [name, id] : *m_pFragmentShaders) {
        glDeleteShader(id);
    }

    delete(m_pVertexShaders);
    delete(m_pFragmentShaders);
} 

/**
 * \brief Loads shaders, comp  iles them and adds them into the storage so its possible to access shaders with theirs ids. 
 */
void ShaderManagerGl::loadShaders() {

    cmrc::embedded_filesystem fileSystem = eng::getFileSystem();

    auto loadVertexShader = [&](std::string path, std::string fileName) {

        auto shaderSourceIterator = eng::getResource(path + "/" + fileName);
        auto shaderSourceBegin = shaderSourceIterator.begin();

        unsigned int shader;
        shader = glCreateShader(GL_VERTEX_SHADER);
          
        glShaderSource(shader, 1, &shaderSourceBegin, 0);
    
        compileShader(shader, fileName);

        std::string shaderName = eng::getFileNameWithoutExtension(fileName);

        m_pVertexShaders->emplace(shaderName, shader);
    }; 

    auto loadFragmentShader = [&](std::string path, std::string fileName) {
        auto shaderSourceIterator = eng::getResource(path + "/" + fileName);
        auto shaderSourceBegin = shaderSourceIterator.begin();

        unsigned int shader;
        shader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(shader, 1, &shaderSourceBegin, 0);

        compileShader(shader, fileName);

        std::string shaderName = eng::getFileNameWithoutExtension(fileName);

        m_pFragmentShaders->emplace(shaderName, shader);
    };


    iterateDirectoryRecursive(fileSystem,"dev/shaders/vert", loadVertexShader);
    iterateDirectoryRecursive(fileSystem, "dev/shaders/frag", loadFragmentShader);
    
    iterateDirectoryRecursive(fileSystem, "game/shaders", loadVertexShader);

}

/**
 *  \returns OpenGL vertex shader ID.
 *  \throws std::out_of_range if shader is not found.
 */
int ShaderManagerGl::getVertexShader(std::string shaderName) const {
    try {
        return m_pVertexShaders->at(shaderName);
    } 
    catch (std::out_of_range) {
        throw new std::out_of_range("ShaderManagerGl: shader not found: " + shaderName);
    }
}

/**
 * \returns OpenGL fragment shader ID.
 * \throws std::out_of_range if shader is not found.
 */
int ShaderManagerGl::getFragmentShader(std::string shaderName) const {
    try {
        return m_pFragmentShaders->at(shaderName);
    }
    catch (std::out_of_range) {
        throw new std::out_of_range("ShaderManagerGl: shader not found: " + shaderName);
    }
}

void ShaderManagerGl::compileShader(int shader, std::string fileName){
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (success)
    {
        std::cout << "shaders: shader compiled: " << fileName << std::endl;
    }
    else {
        glGetShaderInfoLog(shader, 512, 0, infoLog);
        std::cerr << "shaders: shader compilation failure: \n" <<
            infoLog << std::endl;
    }
}

