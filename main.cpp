#include "radix_trie.h"

int main()
{
  RadixTrie rt;

  for(std::string line; std::getline(std::cin, line);)
    rt.append(line);

  rt.nick_show();
  rt.show();

  return 0;
}