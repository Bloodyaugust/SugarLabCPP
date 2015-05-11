#include <iostream>
#include <string>
#include "../../lib/rapidjson/rapidjson.h"
#include "../../lib/rapidjson/document.h"
#include "../../lib/rapidjson/writer.h"
#include "../../lib/rapidjson/stringbuffer.h"
#include "AssetCollection.h"

AssetCollection::AssetCollection(char * file_path) : file_path_(file_path) {
    int32_t file_size;
    char * buffer;
    size_t result;
    std::string file_name(this->file_path_);

    this->file_obj_ = fopen(this->file_path_, "r");
    if (this->file_obj_ == NULL) {
        std::cout << std::string("File error: " + file_name).c_str() << std::endl;
    }

    fseek(this->file_obj_, 0, SEEK_END);
    file_size = ftell(this->file_obj_);
    rewind(this->file_obj_);

    buffer = reinterpret_cast<char*> (malloc(sizeof(char) * file_size));
    if (buffer == NULL) {
        std::cout << std::string("Memory error while allocating for: " + file_name).c_str() << std::endl;
    }

    result = fread(buffer, 1, file_size, this->file_obj_);
    if (result != file_size) {
        std::cout << std::string("Reading error: " + file_name).c_str() << std::endl;
    }

    this->assets_.Parse(buffer);

    rapidjson::StringBuffer sbuffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(sbuffer);
    this->assets_.Accept(writer);

    fclose(this->file_obj_);
    free(buffer);
}
