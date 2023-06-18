#include "System.h"

System::System()
{
    std::ifstream fin("topics.txt");
    this->topics = Vector<Topic>();
    this->currTopic = nullptr;
    this->currPost = nullptr;
    if (fin)
    {
        unsigned gloabalId;
        size_t topicsCount;
        fin >> gloabalId >> topicsCount;
        Unique::setGlobalId(gloabalId - 1);
        for (size_t i = 0; i < topicsCount; i++)
        {
            topics.pushBack(Topic(fin));
        }
    }
}

void System::search(String title) const
{
    for (size_t i = 0; i < topics.getSize(); i++)
    {
        if (topics[i].contain(title))
        {
            topics[i].print(std::cout);
        }
    }
}

void System::createTopic(String title, String description, String creator)
{
    topics.pushBack(Topic(title, description, creator));
}

Topic* System::openTopic(unsigned id)
{
    if (currTopic == nullptr)
    {
        for (size_t i = 0; i < topics.getSize(); i++)
        {
            if (topics[i].checkId(id))
            {
                currTopic = &topics[i];
                return currTopic;
            }
        }
    }
    return nullptr;
}

Topic* System::openTopic(String title)
{
    if (currTopic == nullptr)
    {
        for (size_t i = 0; i < topics.getSize(); i++)
        {
            if (topics[i].checkTitle(title))
            {
                currTopic = &topics[i];
                return currTopic;
            }
        }
    }
    return nullptr;
}

void System::about(unsigned id) const {

    for (size_t i = 0; i < topics.getSize(); i++)
    {
        if (topics[i].checkId(id))
        {
            topics[i].printFullInfo();
            return;
        }
    }
    std::cout << "This topic does not exist!" << std::endl;
}

void System::listPost() const
{
    if (currTopic != nullptr)
    {
        currTopic->printPosts(std::cout);
    }
}

void System::post(String title, String content, String creator)
{
    if (currTopic != nullptr)
    {
        currTopic->post(title, content, creator);
    }
}

Post* System::openPost(unsigned id)
{
    if (currTopic != nullptr && currPost == nullptr)
    {
        currPost = currTopic->getPost(id);
        return currPost;
    }
    return nullptr;
}

Post* System::openPost(String title)
{
    if (currTopic != nullptr && currPost == nullptr)
    {
        currPost = currTopic->getPost(title);
        return currPost;
    }
    return nullptr;
}

void System::listComments() const
{
    if (currPost != nullptr)
    {
        currPost->printComments(std::cout);
    }
}

void System::comment(String content, String creator)
{
    if (currPost != nullptr)
    {
        currPost->comment(content, creator);
    }
}

bool System::reply(unsigned id, String content, String creator)
{
    if (currPost != nullptr)
    {
        return currPost->reply(id, content, creator);
    }
    return false;
}

bool System::upvote(unsigned id, unsigned userId)
{
    if (currPost != nullptr)
    {
        return currPost->upvote(id, userId);
    }
    return false;
}

bool System::downvote(unsigned id, unsigned userId)
{
    if (currPost != nullptr)
    {
        return currPost->downvote(id, userId);
    }
    return false;
}

Topic* System::closeTopic() {
    if (currTopic == nullptr) {
        return nullptr;
    }
    Topic* temp = currTopic;
    currTopic = nullptr;
    return temp;
}
Post* System::closePost() {
    if (currPost == nullptr) {
        return nullptr;
    }
    Post* temp = currPost;
    currPost = nullptr;
    return temp;
}

System::~System()
{
    
    std::ofstream fout("topics.txt");
    if (!fout)
    {
        std::cout << "Error" << std::endl;
    }
    fout << Unique::genetateId() << std::endl;
    fout << topics.getSize() << std::endl;
    for (size_t i = 0; i < topics.getSize(); i++)
    {
        fout << topics[i];
    }
}
