#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <iostream>

bool identical_file(const std::string path1, const std::string &path2);

int main(int argc, char **argv) {
  if (argc != 5) {
    std::cerr << "Usage: ./test <executable> <inputs> <outputs> <logs>\n";
    std::exit(EXIT_FAILURE);
  }

  std::string exec_file{argv[1]};
  std::string in_dir{argv[2]};
  std::string out_dir{argv[3]};
  std::string log_dir{argv[4]};

  int total = 0;
  int failed = 0;

  for (const auto &file : std::filesystem::directory_iterator(in_dir)) {
    std::string in_path{file.path().string()};
    std::string in_file{file.path().filename().string()};

    std::string testcase{in_file.substr(0, in_file.size() - 3)};

    std::string log_file = fmt::format("{}.out", testcase);
    std::string log_path = fmt::format("{}/{}", log_dir, log_file);

    std::string command =
        fmt::format("./{} < {} > {}", exec_file, in_path, log_path);

    auto time_begin = std::chrono::steady_clock::now();
    std::system(command.c_str());
    auto time_end = std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                        time_end - time_begin)
                        .count();

    std::string out_file = fmt::format("{}.out", testcase);
    std::string out_path = fmt::format("{}/{}", out_dir, out_file);

    if (identical_file(log_path, out_path)) {
      std::cout << fmt::format("Test {} passed! {} msec\n", testcase, duration);
    } else {
      std::cout << fmt::format("Test {} failed! {} msec\n", testcase, duration);
      failed++;
    }

    total++;
  }

  float rate = std::round((total - failed) * 100.0 / total);

  std::cout << "\n";
  std::cout << fmt::format("{}% tests passed, {} tests failed out of {}\n",
                           rate, failed, total);
}

bool identical_file(const std::string path1, const std::string &path2) {
  std::ifstream file1{path1, std::ifstream::binary | std::ifstream::ate};
  std::ifstream file2{path2, std::ifstream::binary | std::ifstream::ate};

  if (file1.fail() || file2.fail()) {
    return false;
  }

  if (file1.tellg() != file2.tellg()) {
    return false;
  }

  file1.seekg(0, std::ifstream::beg);
  file2.seekg(0, std::ifstream::beg);

  return std::equal(std::istreambuf_iterator<char>{file1.rdbuf()},
                    std::istreambuf_iterator<char>{},
                    std::istreambuf_iterator<char>{file2.rdbuf()});
}
