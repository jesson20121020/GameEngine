#ifndef __FS_FILEUTILS_H__
#define __FS_FILEUTILS_H__

#include <string>
#include <vector>

class FileUtils
{

public:
	static FileUtils* getInstance();
	static void destroyInstance();
	static void setDelegate(FileUtils *delegate);

	virtual ~FileUtils();
	void addSearchPath(const std::string& searchPath, const bool front);
	const std::vector<std::string>& getSearchPaths() const;

	virtual std::string getStringFromFile(const std::string& fileName);
	virtual std::string getFullFilePath(const std::string& fileName) const;
	virtual bool writeStringToFile(std::string dataStr, const std::string& filePath) const;
	bool isFileExist(const std::string& filePath) const;
	virtual bool isFileExistInternal(const std::string& filePath) const = 0;
	virtual bool isAbsolutePath(const std::string& filePath) const;
	virtual bool createDirectory(const std::string& dirPath);
	virtual bool removeDirectory(const std::string& dirPath);
	virtual bool removeFile(const std::string& filePath);
	virtual bool renameFile(const std::string& filePath, const std::string& newFilePath);
	virtual long getFileSize(const std::string& filePath);
protected:
	FileUtils();

	std::vector<std::string> _searchPaths;
	std::string _defaultSearchPath;
	static FileUtils* s_sharedFileUtils;
};

#endif // __FS_FILEUTILS_H__
