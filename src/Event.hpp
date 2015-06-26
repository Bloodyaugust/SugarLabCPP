#ifndef SRC_BUTTON_HPP
#define SRC_BUTTON_HPP

class Event {
    public:
        explicit Event(std::string type, std::string message);

        std::string type();
        std::string message();

    protected:
        std::string type_;
        std::string message_;
};

#endif /* end of include guard: SRC_BUTTON_HPP */
