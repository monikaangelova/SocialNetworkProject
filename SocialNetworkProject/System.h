#pragma once
#include "Topic.h"
#include "Post.h"

class System
{
private:
    Vector<Topic> topics;
    Topic* currTopic;
    Post* currPost;

public:
    System();
    void search(String) const;
    void about(unsigned id) const;
    void createTopic(String title, String description, String creator);
    Topic* openTopic(unsigned id);
    Topic* openTopic(String title);
    void listPost() const;
    void post(String title, String content, String creator);
    Post* openPost(unsigned id);
    Post* openPost(String title);
    void listComments() const;
    void comment(String content, String creator);
    bool reply(unsigned id, String content, String creator);
    bool upvote(unsigned id, unsigned userId);
    bool downvote(unsigned id, unsigned userId);
    Topic* closeTopic();
    Post* closePost();
    ~System();
};