#include "directories.h"

#include <iostream>
#include <memory>

CMRC_DECLARE(eng_resources);

void iterateDirectoryRecursive(cmrc::embedded_filesystem fileSystem, std::string path, const std::function<void(std::string path, std::string fileName)>& func) {
    try {
        std::unique_ptr<std::vector<std::string>> pFileNames = getDirFileNames(fileSystem, path);
        std::unique_ptr<std::vector<std::string>> pDirNames = getDirDirNames(fileSystem, path);

        for (auto&& fileName : *pFileNames) {
            func(path, fileName);
        }

        for (auto&& dirName : *pDirNames) {
            iterateDirectoryRecursive(fileSystem, path + "/" + dirName, func);
        }
    }
    catch(std::system_error e) {
        std::cout << "eng_io_recursive: " + (std::string) e.what() << std::endl;  // if you change it to "std::cout << "eng_io_recursive: std::errc:directories " + *e.what() << std::endl;" it will write "ale".
    }

}


std::unique_ptr<std::vector<std::string>> getDirFileNames(cmrc::embedded_filesystem fileSystem, std::string path) {
    std::unique_ptr<std::vector<std::string>> pFiles = std::make_unique<std::vector<std::string>>();

    for (auto&& entry : fileSystem.iterate_directory(path)) {
        if (!entry.is_directory()) {
            pFiles->push_back(entry.filename());
        }
    }

    return pFiles;
}

std::unique_ptr<std::vector<std::string>> getDirDirNames(cmrc::embedded_filesystem fileSystem, std::string path) {
    std::unique_ptr<std::vector<std::string>> pDirs = std::make_unique<std::vector<std::string>>();

    for (auto&& entry : fileSystem.iterate_directory(path)) {
        if (entry.is_directory()) {
            pDirs->push_back(entry.filename());
        }
    }

    return pDirs;
}
