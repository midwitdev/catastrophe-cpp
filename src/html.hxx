#include <string>
#include <vector>
#include <map>
#include <optional>

enum TagType
{
    TAG_STRING,
    TAG_ELEMENT,
    TAG_EMPTY,
    TAG_NO_BODY
};

struct Element
{
public:
    bool hasEndTag;
    TagType tagType;

    std::string tag;
    std::map<std::string, std::string> *attrs;

    std::string str_content;
    Element *elem_content;

    Element *next;

    Element(const std::string &t) : tag(t), elem_content(nullptr), str_content(std::string()), next(nullptr), attrs(new std::map<std::string, std::string>()), hasEndTag(false), tagType(TAG_NO_BODY) {}
    Element(const std::string &t, Element *e) : tag(t), str_content(std::string()), elem_content(e), next(nullptr), attrs(new std::map<std::string, std::string>()), hasEndTag(true), tagType(TAG_ELEMENT) {}
    Element(const std::string &t, const std::string &c) : tag(t), str_content(c), elem_content(nullptr), next(nullptr), attrs(new std::map<std::string, std::string>()), hasEndTag(true), tagType(TAG_STRING) {}

    ~Element(){};

    Element* add(Element *e)
    {
        Element *P = elem_content;

        if (P == nullptr) {
            elem_content = e;
            return this;
        }

        while (P->next != nullptr) {
            P = P->next;
        }

        P->next = e;

        return this;
    }

    Element* getLast()
    {
        Element *P = this;

        if (P == nullptr) {
            return nullptr;
        }

        while (P->next != nullptr) {
            P = P->next;
        }

        return P;
    }

    Element* content(Element *e)
    {
        elem_content = e;
        return this;
    }

    Element* insert(Element& e)
    {
        Element *old = next;
        next = (Element*) &e;
        (e.getLast())->next = old;
        return this;
    }

    void setAttr(const std::string &key, const std::string &value)
    {
        (*attrs)[key] = value;
    }

    void removeAttr(const std::string &key)
    {
        attrs->erase(key);
    }

    void setNext(Element *e)
    {
        next = e;
    }

    static Element *fromVector(const std::vector<Element *> &v);
};