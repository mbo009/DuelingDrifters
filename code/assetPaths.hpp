#pragma once
#ifndef ASSET_PATHS_HPP
#define ASSET_PATHS_HPP
// Compile this file only once

#include <string>
#include <vector>
#include <map>
#include <filesystem>

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

// Directory to Assets
const std::string GENERAL = "assets/";

// Type of Assets
const std::string FONTS = GENERAL + "fonts/";
const std::string IMAGES = GENERAL + "images/";
const std::string SOUNDS = GENERAL + "sounds/";

// Type of Objects
const std::string BUTTONS = IMAGES + "buttons/";
const std::string ITEMS = IMAGES + "items/";
const std::string SOUND_EFFECTS = SOUNDS + "sound_effects/";
const std::string MAPS = IMAGES + "maps/";
const std::string MUSIC = SOUNDS + "music/";
const std::string CARS = IMAGES + "cars/";

//==================================================================================================//
//                                                Font                                              //
//==================================================================================================//
const std::string POM_FONT = FONTS + "PixeloidMono.ttf"; // PixeloidMono font

//==================================================================================================//
//                                               Buttons                                            //
//==================================================================================================//
const std::string START_BTN = BUTTONS + "baseStart.png";
const std::string HLT_START_BTN = BUTTONS + "highlightedStart.png";
const std::string EXIT_BTN = BUTTONS + "baseExit.png";
const std::string HLT_EXIT_BTN = BUTTONS + "highlightedExit.png";

//==================================================================================================//
//                                                Items                                             //
//==================================================================================================//
const std::string SPEED_ITM = ITEMS + "speedOrb.png";
const std::string OPP_SLOW_ITM = ITEMS + "opponentSlow.png";
const std::string BOMB_ITM = ITEMS + "bomb.png";
const std::string DASH_ITM = ITEMS + "dash.png";
const std::string REVERSE_ITM = ITEMS + "reverse.png";
const std::string STUN_ITM = ITEMS + "stun.png";
const std::string SWAP_ITM = ITEMS + "swap.png";
const std::string FLAG_ITM = ITEMS + "flag.jpg";

//==================================================================================================//
//                                            Sound Effects                                         //
//==================================================================================================//
const std::string GAMESTART_SFX = SOUND_EFFECTS + "gameStart.ogg";
const std::string CRASH_SFX = SOUND_EFFECTS + "crash.ogg";

//==================================================================================================//
//                                                Maps                                              //
//==================================================================================================//
const std::vector<std::string> MAP_LIST = loadFileList(MAPS);

//==================================================================================================//
//                                                Music                                             //
//==================================================================================================//
const std::vector<std::string> MUSIC_LIST = loadFileList(MUSIC);

//==================================================================================================//
//                                                Cars                                              //
//==================================================================================================//
const std::vector<std::string> CAR_LIST = loadFolderList(CARS);
const std::map<std::string, std::vector<std::string>> CAR_SPRITE_LIST = mapVectorList(CAR_LIST);

#endif