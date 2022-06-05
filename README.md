## 0. 先更新
```bash
    git submodule update --init --recursive
```
## 1. Windows平台
```bash
    # 生成vs工程 
	cmake.exe -G "Visual Studio 16 2019" -B build/windows -T ClangCL -A x64 .
    # cmake编译
    cmake.exe --build build/windows --target client --config Debug
    # 运行
    ./build/windows/bin/Debug/client.exe
```

## 2. Mac平台
```bash
    cmaek -G "Xcode" -B build/mac .
```
```bash
cd build/mac/GameEngine.xcodeproj
xcodebuild clean
xcodebuild -workspace project.xcworkspace -scheme client -configuration Release | tee xcodebuild.log | xcpretty --report json-compilation-database --output compile_commands.json
```
