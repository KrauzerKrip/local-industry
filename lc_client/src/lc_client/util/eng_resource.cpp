#include "eng_resource.h"

#include <fstream>
#include <lc_client/exceptions/io_exceptions.h>
#include <thread>
#include <future>
#include <algorithm>


namespace eng {

	Resource::Resource(std::string resourceRootPath) { m_resourceRootPath = resourceRootPath; }

	auto Resource::getFile(std::string path) const -> cmrc::file {
		auto fileSystem = cmrc::eng_resources::get_filesystem();
		auto file = fileSystem.open(path);

		return file;
	}

	auto Resource::getFileSystem() const -> cmrc::embedded_filesystem { return cmrc::eng_resources::get_filesystem(); }

	auto Resource::getFileResource(std::string path) const -> std::vector<unsigned char> {
		std::ifstream binaryFile(m_resourceRootPath + path, std::ios::binary);

		if (binaryFile.good()) {
			/*Read Binary data using streambuffer iterators.*/
			std::vector<unsigned char> buffer(
				(std::istreambuf_iterator<char>(binaryFile)), (std::istreambuf_iterator<char>()));
			binaryFile.close();
			return buffer;
		}
		else {
			throw ResourceFileNotFoundException(path);
		}
	}

	auto Resource::getFileResources(std::vector<std::string>& paths) const -> std::vector<std::vector<unsigned char>> {
		std::vector<std::vector<std::string>> chunks;

		if (paths.size() < 3) {
			for (std::string path : paths) {
				chunks.push_back(std::vector<std::string>(1, path));
			}
		}

		int i = 0;
		for (std::vector<std::string>::iterator it = paths.begin(); it != paths.end(); it++, i++) {
			int lastDivisableElement = 0;

			if ((i + 1) % 3 == 0) {
				std::vector<std::string> chunk;
				chunk.push_back(paths.at(i - 2));
				chunk.push_back(paths.at(i - 1));
				chunk.push_back(paths.at(i - 0));

				lastDivisableElement = i;

				chunks.push_back(chunk);
			}
			else if ((i + 1) == paths.size()) {
				int remainingElementsCount = i - lastDivisableElement;

				if (remainingElementsCount == 0) {
					break;
				}

				for (int j = i - remainingElementsCount; j < paths.size(); j++) {
					std::vector<std::string> chunk;
					chunk.push_back(paths.at(j));
					chunks.push_back(chunk);
				}
			}
			else {
				assert("eng_resource chunk dividing error.");
			}
		}


		std::vector<std::future<std::vector<std::vector<unsigned char>>>> futures(paths.size());

		for (decltype(futures)::size_type i = 0; i < chunks.size(); ++i) {
			futures[i] = std::async(
				[this, i](std::vector<std::string> chunk) -> std::vector<std::vector<unsigned char>> {
					std::vector<std::vector<unsigned char>> bufs;

					for (const std::string path : chunk) {
						bufs.emplace_back(getFileResource(path));
					}

					return bufs;
				},
				chunks.at(i));
		}
		std::vector<std::vector<unsigned char>> buffers;

		for (decltype(futures)::size_type i = 0; i < chunks.size(); ++i) {
			std::vector<std::vector<unsigned char>> bufsOfBufs = futures[i].get();
			for (std::vector<unsigned char> buf : bufsOfBufs) {
				buffers.push_back(buf);
			}
		}

		return buffers;
	}
}
