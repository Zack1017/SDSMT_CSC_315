//
// Created by ckarlsso on 8/15/2022.
//
#ifndef LIST_CLASS_LINKLIST_H
#define LIST_CLASS_LINKLIST_H

typedef int node_type;
class node {
    node_type num{};
    node *next = nullptr;
public:
    node() = default;
    explicit node(node_type d) : num(d) {};
    ~node() = default;

    friend class LinkList;
};

typedef node *node_ptr;
class LinkList {
private:
    node_ptr headptr;
public:
    explicit LinkList() = default;
    explicit LinkList(int n, node_type key);
    LinkList(LinkList const &original_list);
    ~LinkList();
    int insert(node_type add_num);
    int delete_num(node_type del_num);
    int find_num(node_type find_num);
    void print();
    void erase();
};

#endif //LIST_CLASS_LINKLIST_H
