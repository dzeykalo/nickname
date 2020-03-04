#include <iostream>
#include <array>
#include <memory>
#include <vector>
#include <algorithm>

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

class RadixTrie
{
private:
  struct Node
  {
    std::string label;
    bool is_end{};
    std::array<std::unique_ptr<Node>, 26> children;
  };
  std::unique_ptr<Node> root;
public:
  RadixTrie():root(new Node){}

  bool counting(std::string& s1, std::string& s2)
  {
    auto old_size = s1.size();
    if (s1.size() > s2.size())
      s1.swap(s2);

    auto pair = std::mismatch (s1.begin(), s1.end(), s2.begin(), s2.end());
    s1.erase(pair.first,s1.end());
    s2.erase(s2.begin(),pair.second);
    return  s1.size() < old_size;
  }

  void nick_show(std::unique_ptr<Node> &node, std::string nick)
  {
    for(auto &i:node->children)
    {
      if(i != nullptr)
      {
        if (i->is_end)
          std::cout << nick + i->label << "\t" << nick + i->label[0] <<  std::endl;
        nick_show(i, nick + i->label);
      }
    }
  }

  void show(std::unique_ptr<Node> &node, std::string sign)
  {
    for(auto &i:node->children)
    {
      if(i != nullptr)
      {
        std::cout << sign << i->label;
        i->is_end ? std::cout << "$" << std::endl : std::cout << std::endl;
        show(i, sign+"-");
      }
    }
  }

  void append(std::unique_ptr<Node> &node, const std::string &label)
  {
    int ind = label[0]-'a';
    if (node->children[ind] != nullptr)
    {
      std::string end = label;
      std::string node_label = node->children[ind]->label;
      if (counting(node->children[ind]->label,end))
      {
        std::unique_ptr<Node> no(new Node);
        no->is_end = true;
        no->label = node_label.substr(node->children[ind]->label.size());
        no->children = std::move(node->children[ind]->children);

        node->children[ind]->is_end = false;
        node->children[ind]->children[no->label[0]-'a'] = std::move(no);
        if (node->children[ind]->label != end && !end.empty())
          append(node->children[ind], end);
      }
      else if (!end.empty())
      {
        if ((node->children[ind]->children[end[0]-'a']) != nullptr)
          append(node->children[ind], end);
        else
        {
          std::unique_ptr<Node> no(new Node);
          no->is_end = true;
          no->label = end;
          node->children[ind]->children[end[0]-'a'] = std::move(no);
        }
      }
    }
    else
    {
      std::unique_ptr<Node> no(new Node);
      no->is_end = true;
      no->label = label;
      node->children[ind] = std::move(no);
    }
  }
  void show()
  {
    show(root,"-");
  }
  void nick_show()
  {
    nick_show(root,"");
  }
  void append(const std::string &label)
  {
    append(root,label);
//    show();
//    std::cout << "-----------------" << std::endl;
  }
};


int main()
{
  RadixTrie RT;
//  RT.append("aleksey");
//  RT.append("sasha");
//  RT.append("aleks");
//  RT.append("alek");
//  RT.append("alesha");
//  RT.append("maksim");
//  RT.append("sanek");
//  RT.append("sanchez");
//  RT.show();
//  RT.nick_show();

  std::vector<std::vector<std::string>> v;

  for(std::string line; std::getline(std::cin, line);)
    v.push_back(split(line, '$'));

  for (auto &i:v){
    for (auto &s:i)
      RT.append(s);
  }

  RT.show();
  RT.nick_show();
  return 0;
}