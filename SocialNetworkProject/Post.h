#pragma once
#include "Unique.h"
#include "Comment.h"
#include "String.h"
#include <iostream>
#include <fstream>
#include "Vector.hpp"

class Post : public Unique
{
private:
    unsigned id;
    String title;
    String content;
    String creator;
    Vector<CommentTree> tree;
    CommentTree* DFS(unsigned id);

public:
    Post() = default;
    Post(String title, String content, String creator);
    Post(std::istream& in);
    bool checkId(unsigned id) const;
    bool checkTitle(String title) const;
    void print(std::ostream& out) const;
    void printComments(std::ostream& out) const;
    void comment(String content, String creator);
    bool reply(unsigned id, String content, String creator);
    bool upvote(unsigned id, unsigned userId);
    bool downvote(unsigned id, unsigned userId);
    String getTitle()const;
    friend std::ostream& operator<<(std::ostream& out, const Post& post);
};

