#include "FileAppend.h"


template <typename T>
void FileAppend::writeToFile(T data, const std::string& filename) {
	std::ofstream file(filename, std::ios::app);
	file << data << '\n';
}
