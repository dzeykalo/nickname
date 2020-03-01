#include <iostream>
#include <array>
#include <memory>

class RadixTrie
{
  struct Node
  {
    std::string label;
    bool is_end{};
    std::array<std::unique_ptr<Node>, 26> children;
  };
  std::unique_ptr<Node> root;
public:
  RadixTrie():root(new Node){}
  void counting(std::string& s1, std::string& s2)
  {
    if (s1.size() > s2.size())
      s1.swap(s2);
    int n;
    for(n = 1; n < s1.size(); n++)
    {
      if (s1[n]!=s2[n]) break;
    }
    s1 = s1.substr(0,n);
    s2 = s2.substr(n);
  }
  void show(std::unique_ptr<Node> &node, std::string sign)
  {
    for(auto &i:node->children)
    {
      if(i != nullptr)
      {
        std::cout << sign << i->label;
        if (!i->is_end)
        {
          std::cout << std::endl;
          show(i, sign+"-");
        }
        else
        {
          std::cout << "$" << std::endl;
        }
      }
    }
  }
  void append(std::unique_ptr<Node> &node, const std::string &label)
  {
    int ind = label[0]-'a';
    if (node->children[ind] != nullptr)
    {
      std::string end = label;
      std::string la = node->children[ind]->label;
      counting(la,end);
      if (la.size() < node->children[ind]->label.size())
      {
        std::unique_ptr<Node> no(new Node);
        no->is_end = false;
        no->label = node->children[ind]->label.substr(la.size());
        no->children = std::move(node->children[ind]->children);
        node->children[ind]->children[no->label[0]-'a'] = std::move(no);
      }
      node->children[ind]->label = la;
      if (!node->children[ind]->is_end)
      {
        append(node->children[ind], end);
      }
      else
      {
        node->children[ind]->is_end = false;
        std::unique_ptr<Node> no(new Node);
        no->is_end = true;
        no->label = end;
        node->children[ind]->children[end[0]-'a'] = std::move(no);
      }
    }
    else
    {
      node->is_end = false;
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
  void append(const std::string &label)
  {
    append(root,label);
  }
};


int main()
{
  RadixTrie RT;
  RT.append("aleksey");
  RT.append("sasha");
  RT.append("aleks");
  RT.append("alek");
  RT.append("alesha");
  RT.append("maksim");
  RT.show();
  return 0;
}