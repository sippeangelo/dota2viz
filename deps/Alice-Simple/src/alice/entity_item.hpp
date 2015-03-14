#ifndef _ALICE_ENTITY_ITEM_HPP_
#define _ALICE_ENTITY_ITEM_HPP_

namespace dota {
    /** Data related ot items that have a maximum number of stocks */
    struct item_stock {
        /** ID of the item in question */
        uint32_t item;
        /** The time until this item is restocked */
        float restock_duration;
        /** The time the next item will be added to the stock */
        float restock_date;
        /** Maximum number of items in stock at any given point */
        uint32_t items_max;
        /** Current number of items in stock */
        uint32_t items_current;
    };

    /** A single item entity */
    class entity_item {
        public:
            /** Creates an item from it's entity */
            entity_item(entity* item) : eItem(item) {

            }

            /** Entity ID of the owner */
            uint32_t getOwner() {
                return eItem->prop<uint32_t>(".m_hOwnerEntity");
            }

            /** The owners team */
            int32_t getTeam() {
                return eItem->prop<int32_t>(".m_iTeamNum");
            }

            /** When this item was purchaes */
            float getPurchaseTime() {
                return eItem->prop<float>(".m_flPurchaseTime");
            }

            /** Who purchased this item */
            uint32_t getPurchaser() {
                return eItem->prop<uint32_t>(".m_hPurchaser");
            }

            /** Name of the item */
            std::string getName() {
                return eItem->prop<std::string>(".m_iName");
            }

            /** Whether this item can be activated */
            bool isActivated() {
                return eItem->prop<uint32_t>(".m_bActivated") == 1;
            }

            /** Level of the item (e.g. 1-3 for necronomicon) */
            uint32_t getLevel() {
                return eItem->prop<uint32_t>(".m_iLevel");
            }

            /** Current toggle state */
            bool getToggleState() {
                return eItem->prop<uint32_t>(".m_bToggleState") == 1;
            }

            /** Time the item comes off cooldown */
            float getCooldown() {
                return eItem->prop<float>(".m_fCooldown");
            }

            /** If the item has a cooldown, how long is it */
            float getCooldownLength() {
                return eItem->prop<float>(".m_flCooldownLength");
            }

            /** Cast range */
            uint32_t getCastRange() {
                return eItem->prop<uint32_t>(".m_iCastRange");
            }

            /** Mana Cost */
            uint32_t getManaCost() {
                return eItem->prop<uint32_t>(".m_iManaCost");
            }

            /** Initial number of charges */
            uint32_t getInitialCharges() {
                return eItem->prop<uint32_t>(".m_iInitialCharges");
            }

            /** Current charges */
            uint32_t getCurrentCharges() {
                return eItem->prop<uint32_t>(".m_iCurrentCharges");
            }

            /** If this items requires charges to be cast */
            bool requiresCharges() {
                return eItem->prop<uint32_t>(".m_bRequiresCharges") == 1;
            }

            /** Combinable with other items? */
            bool isCombinable() {
                return eItem->prop<uint32_t>(".m_bCombinable") == 1;
            }

            /** Is this item stackable? */
            bool isStackable() {
                return eItem->prop<uint32_t>(".m_bStackable") == 1;
            }

            /** Is this a recipe? */
            bool isRecipe() {
                return eItem->prop<uint32_t>(".m_bRecipe") == 1;
            }

            /** Teams this item can be shared with. */
            int32_t getSharability() {
                return eItem->prop<int32_t>(".m_iSharability");
            }

            /** Droppable (e.g. Aegis) ? */
            bool isDroppable() {
                return eItem->prop<uint32_t>(".m_bDroppable") == 1;
            }

            /** Puchasable (e.g. Aegis) ? */
            bool isPurchasable() {
                return eItem->prop<uint32_t>(".m_bPurchasable") == 1;
            }

            /** Sellable */
            bool isSellable() {
                return eItem->prop<uint32_t>(".m_bSellable") == 1;
            }

            /** If this item is dissasemblable */
            bool isDissasemblable() {
                return eItem->prop<uint32_t>(".m_bDisassemblable") == 1;
            }

            /** If you can alert your teammates about this ite, */
            bool isAlertable() {
                return eItem->prop<uint32_t>(".m_bAlertable") == 1;
            }
        private:
            /** Points at the entity containing the item */
            entity* eItem;
    };
}

#endif // _ALICE_ENTITY_ITEM_HPP_