#pragma once

#include <functional>

#include <cmrc/cmrc.hpp>


void iterateDirectoryRecursive(cmrc::embedded_filesystem fileSystem, std::string path, const std::function<void(std::string path, std::string fileName)>& func);


std::unique_ptr<std::vector<std::string>> getDirFileNames(cmrc::embedded_filesystem fileSystem, std::string path);

std::unique_ptr<std::vector<std::string>> getDirDirNames(cmrc::embedded_filesystem fileSystem, std::string path);