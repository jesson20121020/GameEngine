#ifndef __FS_FILEUTILS_MAC_H__
#define __FS_FILEUTILS_MAC_H__

#include "../FileUtils.h"

class FileUtilsMac: public FileUtils
{
	friend class FileUtils;
	FileUtilsMac();

protected:
	virtual bool isFileExistInternal(const std::string& filePath) const override;
};

#endif // !__FS_FILEUTILS_MAC_H__
