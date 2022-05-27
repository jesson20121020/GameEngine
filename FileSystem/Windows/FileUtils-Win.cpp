#include "FileUtils-Win.h"

FileUtils* FileUtils::getInstance()
{
    if (s_sharedFileUtils == nullptr)
    {
        s_sharedFileUtils = new FileUtilsWin32();
        if(!s_sharedFileUtils->init())
        {
          delete s_sharedFileUtils;
          s_sharedFileUtils = nullptr;
          CCLOG("ERROR: Could not init CCFileUtilsWin32");
        }
    }
    return s_sharedFileUtils;
}
