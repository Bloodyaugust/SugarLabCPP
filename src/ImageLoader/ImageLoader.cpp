#include <iostream>
#include <string>
#include <thread>
#include <boost/filesystem.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "ImageLoader.h"
#include "../../src/Game/Game.h"

ImageLoader::ImageLoader(char * image_folder, SDL_Renderer* renderer) : image_folder_(image_folder), renderer_(renderer) {
    std::cout << "ImageLoader construction" << std::endl;

    this->loaded_ = false;
    this->surfaces_loaded_ = false;

    std::thread image_thread(&ImageLoader::begin_load, this);

    image_thread.join();
    std::cout << "Thread joined" << std::endl;

    this->surface_to_texture();
}

SDL_Texture* ImageLoader::get_texture(std::string texture_key) {
    return this->texture_map_[texture_key];
}

bool ImageLoader::loaded() {
    return this->loaded_;
}

SDL_Surface* ImageLoader::load_surface(std::string path) {
    SDL_Surface* new_surface = IMG_Load(path.c_str());

    if (new_surface == NULL) {
        std::cout << "Unable to load image " << path.c_str() << " Error: " << IMG_GetError() << std::endl;
    }

    return new_surface;
}

void ImageLoader::begin_load() {
    boost::filesystem::directory_iterator end_itr;
    boost::filesystem::path p (this->image_folder_);

    std::cout << "Beginning load of images" << std::endl;
    std::cout << this->loaded() << std::endl;

    for (boost::filesystem::directory_iterator itr(p); itr != end_itr; ++itr) {
        std::string current_file = itr->path().string();
        std::string file_name = current_file.substr(current_file.find_last_of("/\\") + 1, current_file.find("."));

        std::cout << file_name << std::endl;
        this->surface_map_[file_name] = this->load_surface(current_file);

        std::cout << "Loaded image to surface: " << file_name << std::endl;
    }

    this->surfaces_loaded_ = true;
}

void ImageLoader::surface_to_texture() {
    for (auto i = this->surface_map_.begin(); i != this->surface_map_.end(); i++) {
        std::cout << "Key name: " << i->first << std::endl;
        this->texture_map_[i->first] = SDL_CreateTextureFromSurface(this->renderer_, this->surface_map_[i->first]);

        if (this->texture_map_[i->first] == NULL) {
          std::cout << "Unable to create texture from image " << i->first << " Error: " << SDL_GetError() << std::endl;
        }

        SDL_FreeSurface(this->surface_map_[i->first]);
    }
}
