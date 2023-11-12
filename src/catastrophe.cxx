#include "html.hxx"
#include "iostream"
#include "sstream"

void printElement(const Element *_T, int tabLevel)
{
    auto T = *_T;

    std::stringstream ss = std::stringstream();

    for (int i = 0; i < tabLevel; i++)
    {
        ss << '\t';
    }

    std::string tabs = ss.str();

    if (T.tagType == TAG_NO_BODY)
        std::cout << tabs
                  << '<' << T.tag << ">\n";
    else if (T.tagType == TAG_STRING)
        std::cout << tabs << '<' << T.tag << ">\n"
                  << tabs << '\t' << T.str_content << "\n"
                  << tabs << "</" << T.tag << ">\n";
    else if (T.tagType == TAG_ELEMENT && T.elem_content != nullptr) {
                // Another element
                std::cout << tabs << '<' << T.tag << ">\n";
                printElement(T.elem_content, tabLevel + 1);
                std::cout << tabs << "</" << T.tag << ">\n";
    }
    else if (T.tagType == TAG_ELEMENT && T.elem_content == nullptr) {
                // Empty element
                std::cout << tabs << '<' << T.tag << ">\n";
                std::cout << tabs << "</" << T.tag << ">\n";
    }

    if (T.next != nullptr)
    {
        printElement(T.next, tabLevel);
    }
}

int main(void)
{
    Element* vec = Element::fromVector(std::vector<Element*>(
        new Element("head", nullptr),
        new Element("body", nullptr)
    ));

    Element* doc = 
    (new Element("html", nullptr))->
        add(new Element("head", nullptr))->
        add((new Element("body", nullptr))->
            add(new Element("div", nullptr))->
            add(new Element("div", "Hello, world!")));

    printElement(doc, 0);
    printElement(vec, 0);

    return 0;
}