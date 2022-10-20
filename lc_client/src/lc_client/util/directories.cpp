#include "directories.h"

#include <memory>


void iterateDirectoryRecursive(cmrc::embedded_filesystem fileSystem, std::string path, std::function<void(std::string path, std::string fileName)>& func) {
    std::unique_ptr<std::vector<std::string>> pFileNames = getDirFileNames(fileSystem, path);
    std::unique_ptr<std::vector<std::string>> pDirNames = getDirDirNames(fileSystem, path);

    for (auto&& fileName : *pFileNames) {
        func(path, fileName);
    }

    for (auto&& dirName : *pDirNames) {
        iterateDirectoryRecursive(fileSystem, path + "/" + dirName, func);
    }
}


static std::unique_ptr<std::vector<std::string>> getDirFileNames(cmrc::embedded_filesystem fileSystem, std::string path) {
    std::unique_ptr<std::vector<std::string>> pFiles = std::make_unique<std::vector<std::string>>();

    for (auto&& entry : fileSystem.iterate_directory(path)) {
        if (!entry.is_directory()) {
            pFiles->push_back(entry.filename());
        }
    }

    return pFiles;
}

static std::unique_ptr<std::vector<std::string>> getDirDirNames(cmrc::embedded_filesystem fileSystem, std::string path) {
    std::unique_ptr<std::vector<std::string>> pDirs = std::make_unique<std::vector<std::string>>();

    for (auto&& entry : fileSystem.iterate_directory(path)) {
        if (entry.is_directory()) {
            pDirs->push_back(entry.filename());
        }
    }

    return pDirs;
}
