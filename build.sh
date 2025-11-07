#!/bin/bash

# CppMQSpark 跨平台构建脚本 (Linux/macOS)
echo "=== CppMQSpark 构建脚本 ==="

# 检查CMake版本
CMAKE_VERSION=$(cmake --version | grep -oP 'version \K[0-9]+\.[0-9]+\.[0-9]+')
REQUIRED_VERSION="3.28.0"

# 比较版本号
version_ge() {
    [ "$(printf '%s\n' "$1" "$2" | sort -V | head -n1)" != "$1" ]
}

echo "当前CMake版本: $CMAKE_VERSION"
if ! version_ge "$CMAKE_VERSION" "$REQUIRED_VERSION"; then
    echo "警告: CMake版本低于推荐版本 $REQUIRED_VERSION"
    echo "某些功能可能无法正常工作，但将尝试继续构建..."
fi

# 创建构建目录
BUILD_DIR="build"
if [ ! -d "$BUILD_DIR" ]; then
    echo "创建构建目录..."
    mkdir -p "$BUILD_DIR"
fi

# 进入构建目录
cd "$BUILD_DIR"

# 配置项目
echo "配置项目..."
cmake ..

# 编译项目
echo "编译项目..."
cmake --build . --config Release

# 检查编译是否成功
if [ $? -eq 0 ]; then
    echo "构建成功！"
    
    # 运行测试（可选）
    read -p "是否运行测试？(y/n) " run_test
    if [ "$run_test" = "y" ] || [ "$run_test" = "Y" ]; then
        echo "运行测试..."
        # 尝试在不同位置查找可执行文件
        if [ -f "./mqspark_tests" ]; then
            ./mqspark_tests
        elif [ -f "../bin/mqspark_tests" ]; then
            ../bin/mqspark_tests
        else
            echo "错误: 找不到测试可执行文件"
            echo "请手动在以下位置查找并运行:"
            find .. -name "mqspark_tests*"
        fi
    fi
    
    # 安装（可选）
    read -p "是否安装库？(需要管理员权限)(y/n) " install_lib
    if [ "$install_lib" = "y" ] || [ "$install_lib" = "Y" ]; then
        echo "安装库..."
        # 尝试使用sudo安装，如果失败则给出提示
        if sudo cmake --install .; then
            echo "安装成功！"
        else
            echo "安装失败，可能是CMake版本问题或权限不足"
            echo "提示: 您可以手动复制lib目录下的库文件到系统库路径"
        fi
    fi
else
    echo "构建失败！"
    exit 1
fi