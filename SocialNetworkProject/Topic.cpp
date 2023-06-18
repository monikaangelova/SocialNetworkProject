#include "Topic.h"
#include "HelperFunctions.h"

Topic::Topic(String title, String description, String creator)
{
    this->id = genetateId();
    this->title = title;
    this->description = description;
    this->creator = creator;
    this->posts = Vector<Post>();
}

Topic::Topic(std::istream& in)
{
    in >> id;
    readString(in, this->title);
    readString(in, this->description);
    readString(in, this->creator);
    posts = Vector<Post>();
    size_t postCount;
    in >> postCount;
    for (size_t i = 0; i < postCount; i++)
    {
        posts.pushBack(Post(in));
    }
}

bool Topic::checkId(unsigned id) const
{
    return this->id == id;
}

bool Topic::checkTitle(String title) const
{
    return this->title==title;
}

bool Topic::contain(String title) const
{
    return searchInText(this->title.c_str(), title.c_str());
}

Post* Topic::getPost(unsigned id)
{
    for (size_t i = 0; i < posts.getSize(); i++)
    {
        if (posts[i].checkId(id))
        {
            return &posts[i];
        }
    }
    return nullptr;
}

Post* Topic::getPost(String title)
{
    for (size_t i = 0; i < posts.getSize(); i++)
    {
        if (posts[i].checkTitle(title))
        {
            return &posts[i];
        }
    }
    return nullptr;
}

void Topic::print(std::ostream& out) const
{
    out << " >> " << this->title << " {id:" << this->id << "}" << std::endl;
}

void Topic::printPosts(std::ostream& out) const
{
    for (size_t i = 0; i < posts.getSize(); i++)
    {
        this->posts[i].print(out);
    }
}

void Topic::post(String title, String content, String creator)
{
    this->posts.pushBack(Post(title, content, creator));
}

String Topic::getTitle() const {
    return title;
}
void Topic::printFullInfo()const {
    std::cout << "  >> Name: \"" << title << "\"" << std::endl;
    std::cout << "  >> Description: " << description << std::endl;
    std::cout << "  >> Created by: " << creator << std::endl;
    std::cout << "  >> Questions asked : " << posts.getSize() << std::endl;

}

std::ostream& operator<<(std::ostream& out, const Topic& topic)
{
    out << topic.id << " ";
    out << topic.title.length() << " " << topic.title << " ";
    out << topic.description.length() << " " << topic.description << " ";
    out << topic.creator.length() << " " << topic.creator << " ";
    out << topic.posts.getSize() << std::endl;
    for (size_t i = 0; i < topic.posts.getSize(); i++)
    {
        out << topic.posts[i];
    }
    return out;
}
