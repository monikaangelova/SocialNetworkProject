#pragma once
#include "Unique.h"
#include "Post.h"
class Topic : public Unique
{
private:
    unsigned id;
    String title;
    String description;
    String creator;
    Vector<Post> posts;

public:
    Topic() = default;
    Topic(String title, String description, String creator);
    Topic(std::istream& in);
    bool checkId(unsigned id) const;
    bool checkTitle(String title) const;
    bool contain(String title) const;
    Post* getPost(unsigned id);
    Post* getPost(String);
    void printPosts(std::ostream& out) const;
    void print(std::ostream& out) const;
    void post(String title, String content, String creator);
    String getTitle() const;
    void printFullInfo()const;
    friend std::ostream& operator<<(std::ostream& out, const Topic& topic);
};
