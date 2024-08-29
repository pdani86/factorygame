#ifndef FACTORYGAME_ITEMPRODUCTION_HPP
#define FACTORYGAME_ITEMPRODUCTION_HPP

#include <queue>

#include "Recipe.hpp"

namespace game {

    struct ItemProductionSpeed {
        item_id  item;
        double countPerMin;
    };


    struct ProductionGoal {
        std::vector<ItemProductionSpeed> goals;
    };

    struct ProductionRecipeUse {
        const Recipe* recipe;
        std::vector<ItemProductionSpeed> speeds;
    };

    struct ProductionPlan {
        ProductionGoal goal;
        std::vector<ProductionRecipeUse> recipeUses;
        std::vector<ItemProductionSpeed> sources;
    };

    struct RecipePlanner {

        static ProductionPlan planForGoal(ProductionGoal goal, const RecipeCollection& recipeCollection) {
            std::queue<ItemProductionSpeed> q;
            ProductionPlan productionPlan;
            productionPlan.goal = goal;

            for(const auto& goalProduct : goal.goals) {
                q.push(goalProduct);
            }

            while(!q.empty()) {
                auto itemGoal = q.front();
                q.pop();
                auto* recipe = recipeCollection.findRecipeForItem(itemGoal.item);
                if(!recipe) {
                    productionPlan.sources.push_back(itemGoal);
                    continue;
                }
                productionPlan.recipeUses.push_back(ProductionRecipeUse{recipe, {}});
                auto& recipeUse = productionPlan.recipeUses.back();
                for(const auto& inputRequirement : recipe->inputRequirement) {
                    auto countPerMin = inputRequirement.count * 60 * 1000 / (double)recipe->duration.ms;
                    q.push(ItemProductionSpeed{inputRequirement.item, countPerMin});
                    recipeUse.speeds.push_back({inputRequirement.item, countPerMin});
                }
            }
            return productionPlan;
        }

    };

}

#endif //FACTORYGAME_ITEMPRODUCTION_HPP
