#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>

using namespace std;

// 构建并执行 addr2line 命令
void addr2line(const std::string &address, const std::string &binary_path)
{
    std::ostringstream command;

    // brew install binutils
    // export PATH="/usr/local/opt/binutils/bin:$PATH" 到bash_profile
    command << "/usr/local/Cellar/binutils/2.41_1/bin/addr2line -p -f -e " << binary_path << " " << address;

    // command << "/Users/caoxing/Library/Android/sdk/ndk/21.3.6528147/toolchains/aarch64-linux-android-4.9/prebuilt/darwin-x86_64/bin/aarch64-linux-android-addr2line -e " << binary_path << " " << address;

    // 调用 addr2line 并输出结果
    std::cout << "Resolving address: " << address << std::endl;
    int result = std::system(command.str().c_str());
    if (result != 0)
    {
        std::cerr << "Error: addr2line failed for address " << address << std::endl;
    }
}

// 执行 addr2line 命令返回结果
std::string execAddr2line(const std::string &address, const std::string &binary_path)
{
    std::ostringstream command;
    command << "/usr/local/Cellar/binutils/2.41_1/bin/addr2line -p -f -e " << binary_path << " " << address;

    std::array<char, 256> buffer;
    std::string result;
    // 使用 popen 开始管道，执行 addr2line 命令
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.str().c_str(), "r"), pclose);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed");
    }

    // 读取addr2line 命令输出
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
    {
        result += buffer.data();
    }

    std::cout << "Resolving address: " << address << " " << result << std::endl;

    return result;
}

void parseStackTraceFile(const std::string &stackTraceFile, const std::string &binary_path)
{
    std::ifstream inFile(stackTraceFile);
    if (!inFile.is_open())
    {
        std::cerr << "Error opening stack trace file: " << stackTraceFile << std::endl;
        return;
    }
    std::string line;
    while (std::getline(inFile, line))
    {
        // 假设每行都是一个地址
        std::string output = execAddr2line(line, binary_path);
    }
}

int main(int argc, char *argv[])
{

    // 示例：栈地址列表
    std::vector<std::string> stack_addresses = {
        "001acd9c", "001adb84"};

    std::string stack_path = "";
    std::string binary_path = "";
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <binary_path> <stack_trace_file>" << std::endl;
        stack_path = "./stackFile.txt";
        // 二进制文件的路径，必须包含调试符号
        binary_path = "/Users/caoxing/AndroidStudioProjects/AndroidNavigationSDK/navi_2167/engine/output/android/armeabi-v7a/Open/tk-out-v1/AMapOpenNavi/build/bin/libAMapOpenNavi.so";
    }
    else
    {
        stack_path = argv[1];
        binary_path = argv[2];
    }

    // for (const auto& address : stack_addresses) {
    //     addr2line(address, binary_path);
    // }

    // std::string res = execAddr2line("001acd9c", binary_path);

    parseStackTraceFile(stack_path, binary_path);

    return 0;
}
