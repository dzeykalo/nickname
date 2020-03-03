#include <iostream>
#include <array>
#include <memory>

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
    int n;
    for(n = 1; n < s1.size(); n++)
    {
      if (s1[n]!=s2[n]) break;
    }
    s1 = s1.substr(0,n);
    s2 = s2.substr(n);
    return  s1.size() < old_size;
  }

  void nick_show(std::unique_ptr<Node> &node, std::string nick)
  {
    for(auto &i:node->children)
    {
      if(i != nullptr)
      {
        if (!i->is_end)
        {
          std::cout << nick + i->label;
          nick_show(i, nick + i->label);
        }
        else
        {
          std::cout << nick + i->label << std::endl;
        }
        std::cout << std::endl;
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
  RT.append("aleksey");
  RT.append("sasha");
  RT.append("aleks");
  RT.append("alek");
  RT.append("alesha");
  RT.append("maksim");
  RT.append("sanek");
  RT.append("sanchez");
//  RT.show();
  RT.nick_show();
  return 0;
}