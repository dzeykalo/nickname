#include "radix_trie.h"

std::vector<std::string> split(const std::string &str, char d)
{
  std::vector<std::string> r;

  std::string::size_type start = str.find_first_of("\"");
  std::string::size_type stop = str.find_first_of(d, start);
  while(stop != std::string::npos)
  {
    r.push_back(str.substr(start + 1, stop - start - 2));

    start = str.find_first_of("\"", stop);
    stop = str.find_first_of(d, start);
  }

  return r;
}


int main()
{
  RadixTrie rt;

  std::vector<std::vector<std::string>> v;

  for(std::string line; std::getline(std::cin, line);)
    v.push_back(split(line, '$'));

  for (auto &i:v){
    for (auto &s:i)
      rt.append(s);
  }

  rt.nick_show();
  rt.show();

  return 0;
}