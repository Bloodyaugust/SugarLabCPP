#include <string>
#include "Event.hpp"

Event::Event(std::string type, std::string message) : type_(type), message_(message) {

}

std::string Event::type() {
    return this->type_;
}

std::string Event::message() {
    return this->message_;
}
