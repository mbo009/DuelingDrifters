#pragma once
#ifndef ASSET_PATHS_HPP
#define ASSET_PATHS_HPP
// Compile this file only once

#include <string>
#include <vector>
#include <map>
#include <filesystem>

const unsigned int MAX_FILES = 500;

// Get all list of strings (paths) from a directory (DIR)
inline const std::vector<std::string> loadFileList(const std::string &DIR)
{
    std::vector<std::string> fileList;
    if (!std::filesystem::exists(DIR))
    {
        // Throw Exception Here
        // std::cout << "Error: " << DIR << " does not exist" << std::endl;
        return fileList;
    }
    if (!std::filesystem::is_directory(DIR))
    {
        // Throw Exception Here
        // std::cout << "Error: " << DIR << " is not a directory" << std::endl;
        return fileList;
    }
    for (const auto &entry : std::filesystem::directory_iterator(DIR))
    {
        if (!entry.is_directory())
        { // Only add files
            fileList.push_back(entry.path().string());
        }
    }
    return fileList;
}

inline const std::vector<std::string> loadFolderList(const std::string &DIR)
{
    std::vector<std::string> folderList;
    if (!std::filesystem::exists(DIR))
    {
        // Throw Exception Here
        // std::cout << "Error: " << DIR << " does not exist" << std::endl;
        return folderList;
    }
    if (!std::filesystem::is_directory(DIR))
    {
        // Throw Exception Here
        // std::cout << "Error: " << DIR << " is not a directory" << std::endl;
        return folderList;
    }
    for (const auto &entry : std::filesystem::directory_iterator(DIR))
    {
        if (entry.is_directory())
        { // Only add directories
            folderList.push_back(entry.path().string());
        }
    }
    return folderList;
}
#include <iostream>
inline const std::map<std::string, std::vector<std::string>> mapVectorList(const std::vector<std::string> &DIRS)
{
    std::map<std::string, std::vector<std::string>> mapList;
    for (const auto &DIR : DIRS)
    {
        // Get key as last level directory name
        std::string key = DIR.substr(DIR.find_last_of("/\\") + 1);
        mapList[key] = loadFileList(DIR);
    }
    return mapList;
}
// Directory level 1
const std::string GENERAL_PATH = "assets/";
// Directory level 2
const std::string FONTS_PATH = GENERAL_PATH + "fonts/";
const std::string IMAGES_PATH = GENERAL_PATH + "images/";
const std::string SOUNDS_PATH = GENERAL_PATH + "sounds/";
// Directory level 3
const std::string CAR_PATH = IMAGES_PATH + "cars/";
const std::string MAP_PATH = IMAGES_PATH + "maps/";
const std::string ITEM_PATH = IMAGES_PATH + "items/";
const std::string MUSIC_PATH = SOUNDS_PATH + "music/";
const std::string SOUND_EFFECTS_PATH = SOUNDS_PATH + "sound_effects/";
// Directory level 4
const std::string STATS_FONT = FONTS_PATH + "PixeloidMono.ttf";
const std::string GAMESTART_SOUND = SOUND_EFFECTS_PATH + "gameStart.ogg";
const std::string CRASH_SOUND = SOUND_EFFECTS_PATH + "crash.ogg";
const std::string SPEED_ORB = ITEM_PATH + "speedOrb.png";
const std::string OPPONENT_SLOW_ORB = ITEM_PATH + "opponentSlow.png";
const std::string BOMB_ORB = ITEM_PATH + "bomb.png";
const std::string DASH_ORB = ITEM_PATH + "dash.png";
const std::string REVERSE_ORB = ITEM_PATH + "reverse.png";
const std::string STUN_ORB = ITEM_PATH + "stun.png";
const std::string SWAP_ORB = ITEM_PATH + "swap.png";

const std::vector<std::string> CAR_LIST = loadFolderList(CAR_PATH);
const std::vector<std::string> MAP_LIST = loadFileList(MAP_PATH);
const std::vector<std::string> MUSIC_LIST = loadFileList(MUSIC_PATH);
// Directory level 5
const std::map<std::string, std::vector<std::string>> CAR_SPRITE_LIST = mapVectorList(CAR_LIST);

#endif