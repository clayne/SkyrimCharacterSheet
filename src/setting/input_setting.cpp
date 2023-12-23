﻿#include "input_setting.h"

namespace setting {
    static bool is_debug;
    static std::set<uint32_t> open_key_combination;
    static std::set<uint32_t> close_key_combination;
    static bool is_enabled;
    static bool auto_show_inventory;
    static bool auto_show_magic;
    static bool pause_game;
    static std::vector<uint32_t> page_next_keys;
    static std::vector<uint32_t> page_previous_keys;

    void input_setting::load_setting() {
        logger::info("loading input setting file"sv);
        auto file = R"(Data\SKSE\Plugins\SkyrimCharacterSheet\SkyrimCharacterSheet_Input.json)";
        std::ifstream input_setting_file(file);
        if (!input_setting_file) {
            logger::warn("file {} not found"sv, file);
            return;
        }

        logger::info("loading key setting from file {}"sv, file);

        nlohmann::json json_setting;
        input_setting_file >> json_setting;

        if (auto& debug = json_setting.at("debug"); debug.is_boolean()) {
            is_debug = debug;
        }

        if (auto& open_keys = json_setting.at("open_key_combination"); open_keys.is_array()) {
            std::set<uint32_t> keys;
            for (auto& key : open_keys) {
                //cast needed in this case
                keys.insert(static_cast<uint32_t>(key));
            }
            open_key_combination = keys;
        }

        if (auto& close_keys = json_setting.at("close_key_combination"); close_keys.is_array()) {
            std::set<uint32_t> keys;
            for (auto& key : close_keys) {
                //cast needed in this case
                keys.insert(static_cast<uint32_t>(key));
            }
            close_key_combination = keys;
        }

        if (auto& enabled = json_setting.at("enabled"); enabled.is_boolean()) {
            is_enabled = enabled;
        }

        if (auto& show_inventory = json_setting.at("auto_show_inventory"); show_inventory.is_boolean()) {
            auto_show_inventory = show_inventory;
        }

        if (auto& show_magic = json_setting.at("auto_show_magic"); show_magic.is_boolean()) {
            auto_show_magic = show_magic;
        }

        if (auto& next_keys = json_setting.at("page_next_keys"); next_keys.is_array()) {
            std::vector<uint32_t> keys;
            for (auto& key : next_keys) {
                keys.push_back(key);
            }
            page_next_keys = keys;
        }

        if (auto& previous_keys = json_setting.at("page_previous_keys"); previous_keys.is_array()) {
            std::vector<uint32_t> keys;
            for (auto& key : previous_keys) {
                keys.push_back(key);
            }
            page_previous_keys = keys;
        }

        if (auto& paused = json_setting.at("pause_game"); paused.is_boolean()) {
            pause_game = paused;
        }

        logger::info("done loading input setting file"sv);
    }

    bool input_setting::get_is_debug() { return is_debug; }

    std::set<uint32_t> input_setting::get_open_menu_key_combination() { return open_key_combination; }

    std::set<uint32_t> input_setting::get_close_menu_key_combination() { return close_key_combination; }

    std::vector<uint32_t> input_setting::get_next_page_menu_key_list() { return page_next_keys; }

    std::vector<uint32_t> input_setting::get_previous_page_menu_key_list() { return page_previous_keys; }

    bool input_setting::get_menu_pause_game() { return pause_game; }

    std::set<uint32_t> input_setting::get_open_inventory_menu_key_combination() { return open_key_combination; }

    std::set<uint32_t> input_setting::get_close_inventory_menu_key_combination() { return close_key_combination; }

    bool input_setting::is_inventory_menu_enabled() { return is_enabled; }

    bool input_setting::auto_open_inventory_menu_inventory() { return auto_show_inventory; }

    bool input_setting::auto_open_inventory_menu_magic() { return auto_show_magic; }

    void input_setting::log() {
        logger::debug(
            "menu: open {}, close {}, next {}, previous {}, paused {}. inventory: open {}, close {}, enabled {}, auto_inventory {}, auto_magic {}"sv,
            open_key_combination.size(),
            close_key_combination.size(),
            page_next_keys.size(),
            close_key_combination.size(),
            pause_game,
            open_key_combination.size(),
            close_key_combination.size(),
            is_enabled,
            auto_show_inventory,
            auto_show_magic);
    }
}  // setting
