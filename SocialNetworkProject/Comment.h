#pragma once
#include "Unique.h"
#include "String.h"
#include <iostream>
#include <fstream>
#include "Vector.hpp"
struct Vote
{
    unsigned userId;
    int amount;
};

class CommentTree : public Unique
{
private:
    unsigned id;
    String content;
    int vote;
    Vector<CommentTree> childs;
    String creator;
    Vector<Vote> votedUsers;
public:
    CommentTree() = default;
    CommentTree(String content, String creator);
    CommentTree(std::istream& in);
    bool checkId(unsigned id) const;
    CommentTree* DFS(unsigned id);
    void addReply(String content, String creator);
    void changeVote(int amount, unsigned userId);
    void print(std::ostream& out, unsigned depth = 0) const;
    friend std::ostream& operator<<(std::ostream& out, const CommentTree& comment);
};
