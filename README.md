## 1. Windows平台
```bash
    # 生成vs工程 
	cmake.exe -G "Visual Studio 16 2019" -B build/windows .
    # cmake编译
    cmake.exe --build build/windows --target client --config Debug
    # 运行
    ./build/windows/bin/Debug/client.exe
```

## 2. Mac平台
```bash
    cmaek -G "Xcode" -B build/mac .
```
