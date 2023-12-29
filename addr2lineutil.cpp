#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// 构建并执行 addr2line 命令
void addr2line(const std::string& address, const std::string& binary_path) {
    std::ostringstream command;


    // brew install binutils
    // export PATH="/usr/local/opt/binutils/bin:$PATH" 到bash_profile
    command << "/usr/local/Cellar/binutils/2.41_1/bin/addr2line -p -f -e " << binary_path << " " << address;

    // command << "/Users/caoxing/Library/Android/sdk/ndk/21.3.6528147/toolchains/aarch64-linux-android-4.9/prebuilt/darwin-x86_64/bin/aarch64-linux-android-addr2line -e " << binary_path << " " << address;

    // 调用 addr2line 并输出结果
    std::cout << "Resolving address: " << address << std::endl;
    int result = std::system(command.str().c_str());
    if (result != 0) {
        std::cerr << "Error: addr2line failed for address " << address << std::endl;
    }
}

int main() {
    // 示例：栈地址列表
    std::vector<std::string> stack_addresses = {
       "001acd9c","001adb84"
    };

    // // 二进制文件的路径，必须包含调试符号
    std::string binary_path = "so路径";

    for (const auto& address : stack_addresses) {
        addr2line(address, binary_path);
    }

    // addr2line("001acd9c", binary_path);


    return 0;
}
