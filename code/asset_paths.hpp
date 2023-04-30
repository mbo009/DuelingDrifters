#ifndef ASSET_PATHS_HPP
#define ASSET_PATHS_HPP

#include <string>
#include <vector>
#include <map>
#include <filesystem>

const unsigned int MAX_FILES = 500;

// Get all list of strings (paths) from a directory (DIR)
// Can not create constexpr for std::vector
inline const std::vector<std::string> loadFileList(const std::string &DIR) {
    std::vector <std::string> fileList;
    if (!std::filesystem::exists(DIR)) {
        // Throw Exception Here
        // std::cout << "Error: " << DIR << " does not exist" << std::endl;
        return fileList;
    }
    if (!std::filesystem::is_directory(DIR)) {
        // Throw Exception Here
        // std::cout << "Error: " << DIR << " is not a directory" << std::endl;
        return fileList;
    }
    for (const auto &entry : std::filesystem::directory_iterator(DIR)) {
        if(!entry.is_directory()) { // Only add files
            fileList.push_back(entry.path().string());
        }
    }
    return fileList;
}

inline const std::vector<std::string> loadPathList(const std::string &DIR) {
    std::vector <std::string> pathList;
    if (!std::filesystem::exists(DIR)) {
        // Throw Exception Here
        // std::cout << "Error: " << DIR << " does not exist" << std::endl;
        return pathList;
    }
    if (!std::filesystem::is_directory(DIR)) {
        // Throw Exception Here
        // std::cout << "Error: " << DIR << " is not a directory" << std::endl;
        return pathList;
    }
    for (const auto &entry : std::filesystem::directory_iterator(DIR)) {
        if(entry.is_directory()) { // Only add directories
            pathList.push_back(entry.path().string());
        }
    }
    return pathList;
}

const std::string GENERAL_PATH = "assets/";

const std::string FONTS_PATH = GENERAL_PATH + "fonts/";
const std::string IMAGES_PATH = GENERAL_PATH + "images/";
const std::string SOUNDS_PATH = GENERAL_PATH + "sounds/";

const std::string CAR_PATH = IMAGES_PATH + "cars/";
const std::string MAP_PATH = IMAGES_PATH + "maps/";
const std::string MUSIC_PATH = SOUNDS_PATH + "Music/";
const std::string SOUND_EFFECTS_PATH = SOUNDS_PATH + "sound_effects/";

const std::string STATS_FONT = FONTS_PATH + "PixeloidMono.ttf";
const std::string GAMESTART_SOUND = SOUND_EFFECTS_PATH + "gameStart.ogg";
const std::string CRASH_SOUND = SOUND_EFFECTS_PATH + "crash.ogg";
const std::vector<std::string> CAR_LIST = loadFileList(CAR_PATH);
const std::vector<std::string> MAP_LIST = loadFileList(MAP_PATH);
const std::vector<std::string> MUSIC_LIST = loadFileList(MUSIC_PATH);



#endif