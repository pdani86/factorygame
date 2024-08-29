#ifndef FACTORYGAME_ITEMNAMES_HPP
#define FACTORYGAME_ITEMNAMES_HPP

#include "Items.hpp"

#include <string>
#include <map>
#include <optional>

namespace game {

    namespace item_ids {
        constexpr item_id IRON_ORE = 1;
        constexpr item_id COPPER_ORE = 2;
        constexpr item_id IRON_INGOT = 3;
        constexpr item_id COPPER_INGOT = 4;
        constexpr item_id COAL = 5;
        constexpr item_id STEEL_INGOT = 6;
        constexpr item_id IRON_PLATE = 7;
        constexpr item_id IRON_ROD = 8;
        constexpr item_id SCREW = 9;
        constexpr item_id REINFORCED_IRON_PLATE = 10;
    }


    std::map<item_id, std::string> item_names = {
        {item_ids::IRON_ORE, "Iron Ore"},
        {item_ids::IRON_INGOT, "Iron Ingot"},
        {item_ids::COPPER_ORE, "Copper Ore"},
        {item_ids::COPPER_INGOT, "Copper Ingot"},
        {item_ids::COAL, "Coal"},
        {item_ids::STEEL_INGOT, "Steel Ingot"},
        {item_ids::IRON_PLATE, "IRON_PLATE"},
        {item_ids::IRON_ROD, "IRON_ROD"},
        {item_ids::SCREW, "SCREW"},
        {item_ids::REINFORCED_IRON_PLATE, "REINFORCED_IRON_PLATE"},
    };


    std::optional<std::string> getItemName(item_id id) {
        auto it = item_names.find(id);
        if(it == item_names.end()) {
            return std::nullopt;
        }
        return it->second;
    }

}

#endif //FACTORYGAME_ITEMNAMES_HPP
