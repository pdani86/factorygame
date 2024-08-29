#ifndef FACTORYGAME_RECIPE_HPP
#define FACTORYGAME_RECIPE_HPP

#include <cstdint>
#include <vector>
#include <algorithm>

#include "Items.hpp"

namespace game {

    struct RecipeInputRequirement {
        item_id item;
        int count;
    };

    struct RecipeOutput {
        item_id item;
        int count;
    };

    struct RecipeDuration {
        int ms;
    };

    struct Recipe {
        std::string name;

        std::vector<RecipeInputRequirement> inputRequirement;
        std::vector<RecipeOutput> outputs;
        RecipeDuration duration;

        bool hasOutput(item_id item) const {
            return 0 != std::count_if(outputs.begin(), outputs.end(), [item](const auto& out){return out.item == item;});
        }
    };

    struct RecipeCollection {
        std::vector<Recipe> recipes;

        const Recipe* findRecipeForItem(item_id item) const {
            auto it = std::find_if(recipes.begin(), recipes.end(), [item](const auto& recipe){ return recipe.hasOutput(item); });
            return (it == recipes.end()) ? (nullptr) : &(*it);
        }
    };


}

#endif //FACTORYGAME_RECIPE_HPP
