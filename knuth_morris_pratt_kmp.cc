#include <iostream>
#include <string>
#include <vector>

#define DEBUG

std::vector<int> preprocess(std::string pattern) {
  std::vector<int> kmp_arr(pattern.size());
  int j = 0;
  int i = 1;
  kmp_arr[0] = 0;
  for (i = 1; i < pattern.size(); i++) {
    while (true) {
      if (pattern[j] == pattern[i]) {
        kmp_arr[i] = j + 1;
        j++;
        break;
      } else {
        if (j == 0) {
          kmp_arr[i] = 0;
          break;
        }
        j = kmp_arr[j - 1];
      }
    }
  }
  return kmp_arr;
}

std::vector<int> match(std::string text,
                       std::string pattern,
                       std::vector<int> kmp_arr) {
  if (kmp_arr.size() != pattern.size()) {
    std::cout << "ERROR: KMP array size doesn't match pattern string size"
              << std::endl;
    return std::vector<int>();
  }

  std::vector<int> res;
  int p = 0;
  for (int t = 0; t < text.size(); t++) {
    while (true) {
      if (text[t] == pattern[p]) {
        if (p == pattern.size() - 1) {
          res.push_back(t - p);
          p = kmp_arr[p];
        } else {
          p++;
        }
        break;
      } else {
        if (p == 0) {
          break;
        } else {
          p = kmp_arr[p - 1];
        }
      }
    }
  }
  return res;
}

int main() {
  std::string text = "abcxabcdabxabcdabcdabcyabcabcdabcyy";
  std::string pattern = "abcdabcy";
  std::vector<int> kmp_array = preprocess(pattern);

#ifdef DEBUG
  std::cout << "KMP preprocessed array for pattern(" << pattern << ") : ";
  for (int i = 0; i < kmp_array.size(); i++) {
    std::cout << kmp_array[i] << " ";
  }
  std::cout << std::endl;
#endif

  std::cout << "match positions : ";
  std::vector<int> match_indexes = match(text, pattern, kmp_array);
  for (int i = 0; i < match_indexes.size(); i++) {
    std::cout << match_indexes[i] << " ";
  }
  std::cout << std::endl;
}
