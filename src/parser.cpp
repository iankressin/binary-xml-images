#include "parser.h"

#include <cstdint>
#include <regex>

#include "linked_stack.h"

Parser::Parser(std::string xml_content) : content(xml_content) {}

bool Parser::parse(void) {
  structures::LinkedStack<std::string> stack;
  std::string tag{""};
  std::size_t tag_begin_index{0u};
  std::size_t index{0u};
  char character{'0'};

  while (index < content.length()) {
    character = content[index];

    if (character == LEFT_BRACKET) {
      tag_begin_index = index;
    }

    if (character == RIGHT_BRACKET) {
      tag = content.substr(tag_begin_index, index - tag_begin_index + 1);

      if (tag[1] == SLASH) {
        std::string last_tag = stack.pop();

        if (!match(last_tag, tag)) {
          return false;
        }
      } else {
        stack.push(tag);
      }
    }
    index++;
  }
  return stack.empty();
}

bool Parser::match(const std::string& opening_tag,
                   const std::string& closing_tag) {
  std::regex reg("\\W");

  std::string opening_tag_text = std::regex_replace(opening_tag, reg, "");
  std::string closing_tag_text = std::regex_replace(closing_tag, reg, "");

  bool match = opening_tag_text.compare(closing_tag_text);

  return match == 0;
}
