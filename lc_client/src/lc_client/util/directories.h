#pragma once

#include <functional>

#include <cmrc/cmrc.hpp>

CMRC_DECLARE(eng_resources);


void iterateDirectoryRecursive(cmrc::embedded_filesystem fileSystem, std::string path, const std::function<void(std::string path, std::string fileName)>& func);


static std::unique_ptr<std::vector<std::string>> getDirFileNames(cmrc::embedded_filesystem fileSystem, std::string path);

static std::unique_ptr<std::vector<std::string>> getDirDirNames(cmrc::embedded_filesystem fileSystem, std::string path);