#ifndef SRC_IMAGELOADER_IMAGELOADER_H_
#define SRC_IMAGELOADER_IMAGELOADER_H_

#include <boost/filesystem.hpp>
#include <SDL2/SDL.h>
#include <unordered_map>

class ImageLoader {
    public:
        explicit ImageLoader(char * image_folder, SDL_Renderer* renderer);

        SDL_Texture* get_texture(std::string texture_key);
        int file_count();
        bool surfaces_loaded();
        bool loaded();

    private:
        char * image_folder_;
        SDL_Surface* load_surface(std::string path);
        SDL_Renderer* renderer_;
        std::unordered_map<std::string, SDL_Surface*> surface_map_;
        std::unordered_map<std::string, SDL_Texture*> texture_map_;
        int file_count_;
        bool surfaces_loaded_;
        bool loaded_;
        void begin_load();
        void surface_to_texture();
};

#endif  // SRC_IMAGELOADER_IMAGELOADER_H_
