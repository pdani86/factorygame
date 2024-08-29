#ifndef FACTORYGAME_GAME_HPP
#define FACTORYGAME_GAME_HPP

#include "Items.hpp"

namespace game {

    struct EntityStore {
        std::vector<entity_id> entities;
    };

    struct Splitter {

    };

    struct Merger {

    };

    struct ItemStorage {

    };

    struct ItemSource {
        uint16_t nth_tick;
        item_id item_id;
    };

    struct SmartSplitter {

    };

    struct SmartMerger {

    };

    struct ConveyorNetwork {

    };

    class ConveyorSystem {
    public:
        void tick();
    };

    class Game {
    public:
        Game() {

        }
    private:
        EntityStore _entityStore;
    };
}

#endif //FACTORYGAME_GAME_HPP
