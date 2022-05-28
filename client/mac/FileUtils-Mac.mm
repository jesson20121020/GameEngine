#include "FileUtils-Mac.h"
#import <Foundation/Foundation.h>


static NSFileManager* s_fileManager = [NSFileManager defaultManager];

FileUtilsMac::FileUtilsMac() {

}

FileUtils* FileUtils::getInstance()
{
	if (s_sharedFileUtils == nullptr)
	{
		s_sharedFileUtils = new FileUtilsMac();
	}
	return s_sharedFileUtils;
}


bool FileUtilsMac::isFileExistInternal(const std::string& strFilePath) const
{
	if (strFilePath.empty())
	{
		return false;
	}
	if (!isAbsolutePath(strFilePath))
	{
        return false;
	}
	else
		return [s_fileManager fileExistsAtPath:[NSString stringWithUTF8String:strFilePath.c_str()]];
}
