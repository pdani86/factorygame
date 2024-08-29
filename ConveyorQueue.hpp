#ifndef FACTORYGAME_CONVEYORQUEUE_HPP
#define FACTORYGAME_CONVEYORQUEUE_HPP

#include "Items.hpp"

namespace game {

    struct ConveyorQueue {
        std::vector<item_id> items{1};
        int front_pos = 0;
        bool is_fully_backed = false;

        bool try_push_backed(item_id in) {
            tick_backed();
            auto back_ix = (front_pos + items.size() - 1) % items.size();
            if(items[back_ix] != NULL_ITEM_ID) {
                return false;
            }
            items[back_ix] = in;
            return true;
        }

        void tick_backed() {
            if(is_fully_backed) {
                return;
            }
            bool any_moved = false;
            for(int i=front_pos; i < front_pos + items.size()-1; ++i) {
                auto ix = i % items.size();
                auto nextIx = (ix+1) % items.size();
                auto& slot = items[ix];
                auto& nextSlot = items[nextIx];
                if(slot == NULL_ITEM_ID) {
                    slot = nextSlot;
                    nextSlot = NULL_ITEM_ID;
                    any_moved = true;
                }
            }
            if(!any_moved) {
                is_fully_backed = true;
            }
        }

        item_id front() const {
            return items[front_pos];
        }

        item_id push_and_pop(item_id in) {
            auto pop_item = items[front_pos];
            items[front_pos] = in;
            front_pos = (front_pos+1) % items.size();
            is_fully_backed = false;
            return pop_item;
        }
    };

}

#endif //FACTORYGAME_CONVEYORQUEUE_HPP
