#include "Comment.h"
#include "HelperFunctions.h"
#include <iostream>

std::ostream& operator << (std::ostream& out, const Vote& vote) {
    out << vote.userId << " " << vote.amount;
    return out;
}

std::istream& operator >> (std::istream& in, Vote& vote) {
    in >> vote.userId >> vote.amount;
    return in;
}
CommentTree::CommentTree(String content, String creator)
{
    this->id = genetateId();
    this->content = content;
    this->vote = 0;
    this->creator = creator;
    this->childs = Vector<CommentTree>();
    this->votedUsers = Vector<Vote>();
}

CommentTree::CommentTree(std::istream& in)
{
    in >> id;
    readString(in, this->content);
    readString(in, this->creator);
    in >> vote;
    childs = Vector<CommentTree>();
    votedUsers = Vector<Vote>();
    size_t votesCount;
    in >> votesCount;

    for (size_t i = 0; i < votesCount; i++)
    {
        Vote vote;
        in >> vote;
        votedUsers.pushBack(vote);
    }

    size_t commentCount;
    in >> commentCount;
    for (size_t i = 0; i < commentCount; i++)
    {
        childs.pushBack(CommentTree(in));
    }
}

bool CommentTree::checkId(unsigned id) const
{
    return this->id == id;
}

CommentTree* CommentTree::DFS(unsigned id)
{
    if (this->id == id)
    {
        return this;
    }
    for (size_t i = 0; i < this->childs.getSize(); i++)
    {
        CommentTree* temp = childs[i].DFS(id);
        if (temp != nullptr)
        {
            return temp;
        }
    }
    return nullptr;
}

void CommentTree::addReply(String content, String creator)
{
    this->childs.pushBack(CommentTree(content, creator));
}

void CommentTree::changeVote(int amount, unsigned userId)
{
    for (size_t i = 0; i < this->votedUsers.getSize(); i++)
    {
        if (userId == this->votedUsers[i].userId) {
            bool sameAction = this->votedUsers[i].amount == amount;
            this->vote -= this->votedUsers[i].amount;
            this->votedUsers.popAt(i);
            if (sameAction)return;
        }
    }

    this->votedUsers.pushBack(Vote{ userId, amount });
    this->vote += amount;
}

void CommentTree::print(std::ostream& out, unsigned depth) const
{
    for (size_t i = 0; i < depth; i++)
    {
        out << " ";
    }
    out << " >> " << content << " {id:" << id << "}" << std::endl;
    for (size_t i = 0; i < childs.getSize(); i++)
    {
        childs[i].print(out, depth + 1);
    }
}

std::ostream& operator<<(std::ostream& out, const CommentTree& comment)
{
    out << comment.id << " ";
    out << comment.content.length() << " " << comment.content << " ";
    out << comment.creator.length() << " " << comment.creator << " ";
    out << comment.vote << " ";
    out << comment.votedUsers.getSize() << " ";
    for (size_t i = 0; i < comment.votedUsers.getSize(); i++)
    {
        out << comment.votedUsers[i] << " ";
    }

    out << comment.childs.getSize() << std::endl;
    for (size_t i = 0; i < comment.childs.getSize(); i++)
    {
        out << comment.childs[i];
    }
    return out;
}