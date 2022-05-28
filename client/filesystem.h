#if defined(__cplusplus) && __cplusplus >= 201703L && defined(__has_include)
#if __has_include(<filesystem>)
#define GHC_USE_STD_FS
#include <filesystem>
namespace fs = std::filesystem;
#endif
#endif
#ifndef GHC_USE_STD_FS
#include <ghc/filesystem.hpp>
namespace fs = ghc::filesystem;
#endif


inline const char* getResPath(const std::string name)
{
	auto x = fs::current_path();
	auto y = x.parent_path().append("bin/Debug" + name);
	return y.string().c_str();
}