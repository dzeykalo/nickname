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
      std::string n_label = node->children[ind]->label;
      counting(n_label,end);
      int e_ind = end[0]-'a';
      if (n_label.size() < node->children[ind]->label.size())
      {
        std::unique_ptr<Node> no(new Node);
        no->is_end = true;
        no->label = node->children[ind]->label.substr(n_label.size());
        no->children = std::move(node->children[ind]->children);
        node->children[ind]->is_end = false;
        int l_ind = no->label[0]-'a';
        node->children[ind]->children[l_ind] = std::move(no);
        node->children[ind]->label = n_label;
        if (n_label != end && !end.empty())
          append(node->children[ind], end);
        return;
      }
      node->children[ind]->label = n_label;
      if (end.empty()) return;
      if ((node->children[ind]->children[e_ind]) != nullptr)
      {
        append(node->children[ind], end);
      }
      else
      {
        std::unique_ptr<Node> no(new Node);
        no->is_end = true;
        no->label = end;
        node->children[ind]->children[e_ind] = std::move(no);
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
  RT.append("aleksey");
  RT.append("sasha");
  RT.append("aleks");
  RT.append("alek");
  RT.append("alesha");
  RT.append("maksim");
  RT.append("sanek");
  RT.append("sanchez");
  RT.show();
  return 0;
}