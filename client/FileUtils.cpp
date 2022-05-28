#include "FileUtils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <regex>

FileUtils* FileUtils::s_sharedFileUtils = nullptr;

FileUtils::FileUtils() : _defaultSearchPath("") {}

FileUtils::~FileUtils() {}

void FileUtils::destroyInstance() {
  delete s_sharedFileUtils;
  s_sharedFileUtils = nullptr;
}

void FileUtils::setDelegate(FileUtils *delegate) {
  if (s_sharedFileUtils)
    delete s_sharedFileUtils;
  s_sharedFileUtils = delegate;
}

void FileUtils::addSearchPath(const std::string &searchPath, const bool front) {
  std::string prefix;
  if (!isAbsolutePath(searchPath))
    prefix = _defaultSearchPath;
  std::string path = prefix + searchPath;
  if (!path.empty() && path[path.length() - 1] != '/')
    path += '/';
  if (front)
    _searchPaths.insert(_searchPaths.begin(), path);
  else
    _searchPaths.push_back(path);
}

const std::vector<std::string> &FileUtils::getSearchPaths() const {
  return _searchPaths;
}

std::string FileUtils::getStringFromFile(const std::string &fileName) {
  if (fileName.empty())
    return nullptr;
  unsigned char *buffer = nullptr;
  size_t size = 0;
  size_t readsize;
  const char *mode = "rt";
  do {
    // Read the file from hardware
    std::string fullPath = getFullFilePath(fileName);
    FILE *fp = std::fopen(fullPath.c_str(), mode);
    if (!fp)
      return nullptr;
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    buffer = (unsigned char *)malloc(sizeof(unsigned char) * (size + 1));
    buffer[size] = '\0';
    readsize = fread(buffer, sizeof(unsigned char), size, fp);
    fclose(fp);
    if (readsize < size) {
      buffer[readsize] = '\0';
    }
  } while (0);
  if (nullptr == buffer || 0 == readsize)
    std::cout << "Get data from file %s failed" << fileName.c_str()
              << std::endl;
  std::string ret((const char *)buffer);
  return ret;
}

std::string FileUtils::getFullFilePath(const std::string &fileName) const {
  if (fileName.empty())
    return "";

  if (isAbsolutePath(fileName))
    return fileName;

  // TODO: need use cache optimize
  std::string filePath = "";
  std::string file = fileName;
  std::string fullPath = "";

  size_t pos = fileName.rfind('/');
  if (pos != std::string::npos) {
    filePath = fileName.substr(0, pos);
    file = fileName.substr(pos + 1);
  }

  for (const auto &searchPath : _searchPaths) {
    fullPath = searchPath + filePath + file;
    fullPath = convertToPlatformPath(fullPath);
    if (isFileExistInternal(fullPath))
      return fullPath;
  }
  return "";
}

bool FileUtils::isFileExist(const std::string &filePath) const {
  if (isAbsolutePath(filePath))
    return isFileExistInternal(filePath);
  else
    return !getFullFilePath(filePath).empty();
}

bool FileUtils::isAbsolutePath(const std::string &filePath) const {
  return !filePath.empty() && filePath[0] != '/';
}

long FileUtils::getFileSize(const std::string &filePath) { return 0; }

std::string FileUtils::convertToPlatformPath(const std::string& filePath) const
{
    return filePath;
}