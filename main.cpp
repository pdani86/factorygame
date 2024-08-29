
#include <iostream>

#include <cstdint>
#include <vector>
#include <array>
#include <sstream>

#include "Items.hpp"
#include "ConveyorQueue.hpp"
#include "Recipe.hpp"
#include "ItemNames.hpp"
#include "ItemProduction.hpp"

namespace game {

    void print(const ConveyorQueue& state) {
        std::stringstream ss;
        bool first = true;
        const int N = state.items.size();
        for(int i = 0; i < N; ++i) {
            const auto& elem = state.items[(state.front_pos + i)%N];
            if(first) {
                first = false;
            } else {
                ss << " | ";
            }
            ss << elem;
        }
        std::cout << ss.str();// << std::endl;
    }

}

void test_conveyor() {
    std::cout << "Hello" << std::endl;
    using namespace game;
    ConveyorQueue conveyor;
    conveyor.items.resize(20);
    int cnt = 0;
    for(auto& slot : conveyor.items) {
        slot = ++cnt;
    }
    print(conveyor); std::cout << "\n";
    for(int i = 0; i < 15; ++i) {

        auto item_to_push = 1 * (i%2);
        auto popped = conveyor.push_and_pop(item_to_push);
        std::cout << popped << " <- ";
        print(conveyor);
        std::cout << " <- " << item_to_push << "\n";
    }

    for(int i = 0; i < 10; ++i) {
        auto item_to_push = i+1;
        const bool pushed = conveyor.try_push_backed(item_to_push);
        print(conveyor);
        std::cout << (pushed?std::string(" <- ") + std::to_string(item_to_push) : " BACKED") << "\n";
    }
}

void printRecipeInfo(const game::Recipe& recipe) {
    std::stringstream ss;
    ss << "RECIPE '" << recipe.name << "'\n";
    ss << "Duration (ms): " << recipe.duration.ms << "\n";
    ss << "Input(s):\n";
    for(const auto& input : recipe.inputRequirement) {
        auto countPerMin = input.count * 1000 * 60 / (double)recipe.duration.ms;
        ss << "    " << input.item << " '" << game::getItemName(input.item).value_or("-") << "' " <<
            input.count << " (" << countPerMin << " /min" << ")\n";
    }
    ss << "Output(s):\n";
    for(const auto& output : recipe.outputs) {
        auto countPerMin = output.count * 1000 * 60 / (double)recipe.duration.ms;
        ss << "    " << output.item << " '" << game::getItemName(output.item).value_or("-") << "' " <<
            output.count << " (" << countPerMin << " /min" << ")\n";
    }

    std::cout << ss.str() << std::endl;
}

void print(std::ostream& out, const game::ItemProductionSpeed& itemProductionSpeed) {
    out << game::getItemName(itemProductionSpeed.item).value_or(std::to_string(itemProductionSpeed.item));
    out << " (" << itemProductionSpeed.countPerMin << " /min)";
}

void print(const game::ProductionPlan& productionPlan) {
    std::stringstream ss;
    ss << "GOALS:\n";

    for(const auto& goal : productionPlan.goal.goals) {
        ss << "    ";
        print(ss, goal);
        ss << "\n";
    }

    ss << "PLAN:\n";
    for(const auto& recipeUse : productionPlan.recipeUses) {
        ss << "    ";
        ss << recipeUse.recipe->name << ":\n";
        for(const auto& product : recipeUse.speeds) {
            ss << "        ";
            print(ss, product);
            ss << "\n";
        }
        ss << "\n";
    }

    ss << "SOURCES:\n";
    for(const auto& source : productionPlan.sources) {
        ss << "    ";
        print(ss, source);
        ss << "\n";
    }

    std::cout << ss.str() << std::endl;
}

void test_recipes() {
    using namespace game;

    Recipe steelIngotRecipe;
    steelIngotRecipe.name = "Steel Ingot";
    steelIngotRecipe.inputRequirement.push_back(RecipeInputRequirement{item_ids::COAL, 45});
    steelIngotRecipe.inputRequirement.push_back(RecipeInputRequirement{item_ids::IRON_ORE, 45});
    steelIngotRecipe.outputs = {RecipeOutput{item_ids::STEEL_INGOT, 45}};
    steelIngotRecipe.duration.ms = 5000;
    printRecipeInfo(steelIngotRecipe);

    Recipe ironIngotRecipe;
    ironIngotRecipe.name = "Iron Ingot";
    ironIngotRecipe.inputRequirement.push_back(RecipeInputRequirement{item_ids::IRON_ORE, 30});
    ironIngotRecipe.outputs = {RecipeOutput{item_ids::IRON_INGOT, 30}};
    ironIngotRecipe.duration.ms = 4000;
    printRecipeInfo(ironIngotRecipe);

    RecipeCollection recipeCollection;
    recipeCollection.recipes.push_back(steelIngotRecipe);
    recipeCollection.recipes.push_back(ironIngotRecipe);


    ProductionGoal goal;
    goal.goals.push_back(ItemProductionSpeed{item_ids::STEEL_INGOT, 90.0});
    goal.goals.push_back(ItemProductionSpeed{item_ids::IRON_INGOT, 30.0});
    auto plan = RecipePlanner::planForGoal(goal, recipeCollection);
    print(plan);
}

int main() {
    test_conveyor();
    test_recipes();

    return 0;
}