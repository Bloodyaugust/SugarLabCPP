#ifndef SRC_ASSET_LOADER_HPP
#define SRC_ASSET_LOADER_HPP

#include <iostream>
#include <thread>
#include <string>
#include <unordered_map>
#include <boost/filesystem.hpp>
#include <boost/lambda/bind.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

class AssetLoader {
    public:
        explicit AssetLoader(std::string img_path, std::string sfx_path, SDL_Renderer* renderer_);

        SDL_Texture* texture(std::string file_name);
        Mix_Chunk* sfx(std::string file_name);
        int file_count();
        void load();
        void begin_load();
        void finalize_load();

    protected:
        std::unordered_map<std::string, Mix_Chunk*> sfx_map_;
        std::unordered_map<std::string, SDL_Surface*> surface_map_;
        std::unordered_map<std::string, SDL_Texture*> texture_map_;

    private:
        SDL_Renderer* renderer_;
        SDL_Surface* load_surface(std::string path);
        std::string image_path_;
        std::string sfx_path_;
        int file_count_;
        int file_count_loaded_;
};

#endif /* end of include guard: SRC_ASSET_LOADER_HPP */
