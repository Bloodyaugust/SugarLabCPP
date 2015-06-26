#include "AssetLoader.hpp"

AssetLoader::AssetLoader(std::string image_path, std::string sfx_path, SDL_Renderer* renderer) : image_path_(image_path), sfx_path_(sfx_path), renderer_(renderer) {
    this->file_count_loaded_ = 0;
    this->file_count_ = 0;
}

SDL_Texture* AssetLoader::texture(std::string file_name) {
    return this->texture_map_[file_name];
}

SDL_Surface* AssetLoader::load_surface(std::string path) {
    SDL_Surface* new_surface = IMG_Load(path.c_str());

    if (new_surface == NULL) {
        std::cout << "Unable to load image to surface: " << path.c_str() << " Error: " << IMG_GetError() << std::endl;
    }

    return new_surface;
}

Mix_Chunk* AssetLoader::sfx(std::string file_name) {
    return this->sfx_map_[file_name];
}

int AssetLoader::file_count() {
    return this->file_count_;
}

void AssetLoader::load() {
    std::chrono::time_point<std::chrono::system_clock> load_start;
    std::chrono::time_point<std::chrono::system_clock> load_end;
    std::chrono::duration<double> load_time;

    load_start = std::chrono::system_clock::now();

    std::thread asset_thread(&AssetLoader::begin_load, this);

    asset_thread.join();

    this->finalize_load();

    load_end = std::chrono::system_clock::now();
    load_time = load_end - load_start;

    std::cout << "Assets loaded in: " << load_time.count() * 1000 << " seconds" << std::endl;
}

void AssetLoader::begin_load() {
    boost::filesystem::directory_iterator end_itr;
    boost::filesystem::path image_path (this->image_path_);
    boost::filesystem::directory_iterator image_iterator(image_path);
    boost::filesystem::path sfx_path (this->sfx_path_);
    boost::filesystem::directory_iterator sfx_iterator(sfx_path);
    
    this->file_count_ += std::count_if(image_iterator, boost::filesystem::directory_iterator(), boost::lambda::bind(static_cast<bool(*)(const boost::filesystem::path&)>(boost::filesystem::is_regular_file), boost::lambda::bind(&boost::filesystem::directory_entry::path, boost::lambda::_1)));
    this->file_count_ += std::count_if(sfx_iterator, boost::filesystem::directory_iterator(), boost::lambda::bind(static_cast<bool(*)(const boost::filesystem::path&)>(boost::filesystem::is_regular_file), boost::lambda::bind(&boost::filesystem::directory_entry::path, boost::lambda::_1)));
    std::cout << "Files found: " << this->file_count_ << std::endl;

    std::cout << "Loading images" << std::endl;
    for (boost::filesystem::directory_iterator itr(image_path); itr != end_itr; ++itr) {
        std::string current_file = itr->path().string();
        std::string file_name = current_file.substr(current_file.find_last_of("/\\") + 1, current_file.find("."));

        this->surface_map_[file_name] = this->load_surface(current_file);
        std::cout << "Loaded image to surface: " << file_name << std::endl;

        this->file_count_loaded_++;
    }

    std::cout << "Loading sfx" << std::endl;
    for (boost::filesystem::directory_iterator itr(sfx_path); itr != end_itr; ++itr) {
        std::string current_file = itr->path().string();
        std::string file_name = current_file.substr(current_file.find_last_of("/\\") + 1, current_file.find("."));

        this->sfx_map_[file_name] = Mix_LoadWAV(current_file.c_str());
        std::cout << "Loaded sfx: " << file_name << std::endl;

        this->file_count_loaded_++;
    }
}

void AssetLoader::finalize_load() {
    std::cout << "Creating texures from surfaces" << std::endl;
    for (auto i = this->surface_map_.begin(); i != this->surface_map_.end(); i++) {
        this->texture_map_[i->first] = SDL_CreateTextureFromSurface(this->renderer_, this->surface_map_[i->first]);

        if (this->texture_map_[i->first] == NULL) {
          std::cout << "Unable to create texture from image " << i->first << " Error: " << SDL_GetError() << std::endl;
        }

        SDL_FreeSurface(this->surface_map_[i->first]);
    }
}
