#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

int main()
{
    std::ifstream file("./stackFile1.txt"); // 替换为您的文件路径

    if (!file.is_open())
    {
        std::cout << "无法打开文件" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::cout << "\n"<< std::endl;

        std::cout << "line：" << line << std::endl;

        std::istringstream iss(line);
        std::vector<std::string> result;
        for (std::string s; iss >> s;)
        {
            result.push_back(s);
        }

        // 输出分割后的结果
        for (const auto &word : result)
        {
            size_t pos = word.find("0x"); // 查找包含 "0x" 的位置
            if (pos != std::string::npos)
            {
                std::cout << "在文件中找到以 0x 开头的字符串：" << word << std::endl;
                // 如果需要找到所有匹配项，可以继续在这里执行操作
            }
        }
    }

    file.close();
    return 0;
}