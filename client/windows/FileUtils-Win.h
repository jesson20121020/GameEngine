#ifndef __FS_FILEUTILS_WIN_H__
#define __FS_FILEUTILS_WIN_H__

#include "../FileUtils.h"

class FileUtilsWin: public FileUtils
{
	friend class FileUtils;
	FileUtilsWin();

public:
	virtual bool isAbsolutePath(const std::string& filePath) const override;
	virtual long getFileSize(const std::string& filePath) override;
protected:
	virtual bool isFileExistInternal(const std::string& filePath) const override;
	virtual std::string convertToPlatformPath(const std::string& filePath) const override;
};

#endif // !__FS_FILEUTILS_WIN_H__
