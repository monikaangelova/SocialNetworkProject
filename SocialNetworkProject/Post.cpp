#include "Post.h"
#include "HelperFunctions.h"

Post::Post(String title, String content, String creator)
{
    this->id = genetateId();
    this->title = title;
    this->content = content;
    this->creator = creator;
    this->tree = Vector<CommentTree>();
}
Post::Post(std::istream& in)
{
    in >> id;
    readString(in, this->title);
    readString(in, this->content);
    readString(in, this->creator);
    tree = Vector<CommentTree>();
    size_t commentCount;
    in >> commentCount;
    for (size_t i = 0; i < commentCount; i++)
    {
        tree.pushBack(CommentTree(in));
    }
}

bool Post::checkId(unsigned id) const
{
    return this->id == id;
}
bool Post::checkTitle(String title) const
{
    return this->title==title;
}

CommentTree* Post::DFS(unsigned id)
{
    for (size_t i = 0; i < this->tree.getSize(); i++)
    {
        CommentTree* temp = this->tree[i].DFS(id);
        if (temp != nullptr)
        {
            return temp;
        }
    }
    return nullptr;
}

void Post::print(std::ostream& out) const
{
    out << " >> " << title << " {id:" << id << "}" << std::endl;
}

void Post::printComments(std::ostream& out) const
{
    for (size_t i = 0; i < this->tree.getSize(); i++)
    {
        this->tree[i].print(out);
    }
}

void Post::comment(String content, String creator)
{
    this->tree.pushBack(CommentTree(content, creator));
}

bool Post::reply(unsigned id, String content, String creator)
{
    CommentTree* comment = DFS(id);
    if (comment == nullptr) {
        return false;
    }
    comment->addReply(content, creator);
    return true;
}

bool Post::upvote(unsigned id, unsigned userId)
{
    CommentTree* comment = DFS(id);
    if (comment == nullptr) {
        return false;
    }
    comment->changeVote(1, userId);
    return true;
}

bool Post::downvote(unsigned id, unsigned userId)
{
    CommentTree* comment = DFS(id);
    if (comment == nullptr) {
        return false;
    }
    comment->changeVote(-1, userId);
    return true;
}

String Post::getTitle()const {
    return title;
}

std::ostream& operator<<(std::ostream& out, const Post& post)
{
    out << post.id << " ";
    out << post.title.length() << " " << post.title << " ";
    out << post.content.length() << " " << post.content << " ";
    out << post.creator.length() << " " << post.creator << " ";
    out << post.tree.getSize() << std::endl;
    for (size_t i = 0; i < post.tree.getSize(); i++)
    {
        out << post.tree[i];
    }
    return out;
}
