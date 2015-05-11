#ifndef SRC_ASSETCOLLECTION_ASSETCOLLECTION_H_
#define SRC_ASSETCOLLECTION_ASSETCOLLECTION_H_

#include "../../lib/rapidjson/rapidjson.h"
#include "../../lib/rapidjson/document.h"
#include "../../lib/rapidjson/writer.h"
#include "../../lib/rapidjson/stringbuffer.h"

class AssetCollection {
    public:
        explicit AssetCollection(char * file_path);
        rapidjson::Document assets_;

    private:
        FILE * file_obj_;
        char * file_path_;
};

#endif  // SRC_ASSETCOLLECTION_ASSETCOLLECTION_H_
