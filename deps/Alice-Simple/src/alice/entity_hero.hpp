/**
 * @file entity_hero.hpp
 * @author Robin Dietrich <me (at) invokr (dot) org>
 * @version 1.0
 *
 * @par License
 *    Alice Replay Parser
 *    Copyright 2014 Robin Dietrich
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#ifndef _ALICE_ENTITY_HERO_HPP_
#define _ALICE_ENTITY_HERO_HPP_

#include <string>

#include <alice/entity.hpp>
#include <alice/parser.hpp>

#include "entity_item.hpp"
#include "entity_ability.hpp"

namespace dota {
    /** Contains entity information about a hero */
    class entity_hero {
        public:
            /** Constructor, creates a new hero from the entity supplied */
            entity_hero(entity* hero, parser* p) : eHero(hero), p(p) { }

            /** Default copy constructor */
            entity_hero(const entity_hero&) = default;

            /** Default move constructor */
            entity_hero(entity_hero&&) = default;

            /** Default destructor */
            ~entity_hero() = default;

            /// @TODO Function to return position as struct

            /** Returns number of bits per cell */
            uint32_t getCellbits() {
                return eHero->prop<uint32_t>(".m_cellbits");
            }

            /** Returns X cell coordinate */
            uint32_t getCellX() {
                return eHero->prop<uint32_t>(".m_cellX");
            }

            /** Returns Y cell coordinate */
            uint32_t getCellY() {
                return eHero->prop<uint32_t>(".m_cellY");
            }

            /** Returns Z cell coordinate */
            uint32_t getCellZ() {
                return eHero->prop<uint32_t>(".m_cellZ");
            }

            /** Returns intelligence based on level / attributes */
            float getIntelligence() {
                return eHero->prop<float>(".m_flIntellect");
            }

            /** Returns intelligence including bonuses from items */
            float getIntelligenceTotal() {
                return eHero->prop<float>(".m_flIntellectTotal");
            }

            /** Returns agility based on level / attributes */
            float getAgility() {
                return eHero->prop<float>(".m_flAgility");
            }

            /** Returns agility including bonuses from items */
            float getAgilityTotal() {
                return eHero->prop<float>(".m_flAgilityTotal");
            }

            /** Returns strength based on level / attributes */
            float getStrength() {
                return eHero->prop<float>(".m_flStrength");
            }

            /** Returns strength including bonuses from items */
            float getStrengthTotal() {
                return eHero->prop<float>(".m_flStrengthTotal");
            }

            /** Returns current health */
            uint32_t getHealth() {
                 return eHero->prop<uint32_t>(".m_iHealth");
            }

            /** Returns maximum health */
            uint32_t getHealthMax() {
                 return eHero->prop<uint32_t>(".m_iMaxHealth");
            }

            /** Returns health regen per second */
            float getHealthRegen() {
                 return eHero->prop<float>(".m_flHealthThinkRegen");
            }

            /** Returns current mana */
            float getMana() {
                 return eHero->prop<float>(".m_flMana");
            }

            /** Returns maximum mana */
            float getManaMax() {
                 return eHero->prop<float>(".m_flMaxMana");
            }

            /** Returns mana regen per second */
            float getManaRegen() {
                 return eHero->prop<float>(".m_flManaThinkRegen");
            }

            /** The number of unspend ability points */
            uint32_t getAbilityPoints() {
                 return eHero->prop<uint32_t>(".m_iAbilityPoints");
            }

            /** Attack status, TODO investigate */
            uint32_t getAttackStatus() {
                 return eHero->prop<uint32_t>(".m_iAttackCapabilities");
            }

            /** The level of this hero */
            uint32_t getLevel() {
                 return eHero->prop<uint32_t>(".m_iCurrentLevel");
            }

            /** Current hero experience */
            int32_t getXP() {
                 return eHero->prop<int32_t>(".m_iCurrentXP");
            }

            /** Minimum damage inflicted */
            uint32_t getDamageMin() {
                 return eHero->prop<uint32_t>(".m_iDamageMin");
            }

            /** Maximum damage inflicted */
            uint32_t getDamageMax() {
                 return eHero->prop<uint32_t>(".m_iDamageMax");
            }

            /** Flat bonus damage from items */
            int32_t getDamageBonus() {
                 return eHero->prop<int32_t>(".m_iDamageBonus");
            }

            /** Day time vision range */
            uint32_t getDayVision() {
                 return eHero->prop<uint32_t>(".m_iDayTimeVisionRange");
            }

            /** Night time vision range */
            uint32_t getNightVision() {
                 return eHero->prop<uint32_t>(".m_iNightTimeVisionRange");
            }

            /** Damage inflicted in the last X seconds, TODO investigate */
            int32_t getRecentDamage() {
                 return eHero->prop<int32_t>(".m_iRecentDamage");
            }

            /** Investigate which bits belong to which team */
            uint32_t getTeamVisibility() {
                 return eHero->prop<uint32_t>(".m_iTaggedAsVisibleByTeam");
            }

            /** Life state of the hero, see defs.hpp */
            uint32_t getLifeState() {
                 return eHero->prop<uint32_t>(".m_lifeState");
            }

            /** Whether the heroes stash is enabled or not */
            bool hasStashEnabled() {
                return eHero->prop<uint32_t>(".m_Inventory.m_bStashEnabled") == 1;
            }

            /** Returns current hero items */
            std::vector<entity_item> getItems() {
                std::vector<entity_item> ret;
                for (uint32_t i = 0; i < 14; ++i) {
                    char id[27];
                    snprintf(id, 27, ".m_Inventory.m_hItems.%04d", i);

                    uint32_t iId = eHero->prop<uint32_t>(id);
                    if (iId != 2097151) {
                        ret.push_back(entity_item(&p->getEntities()[iId & 0x7FF])); // TODO validate iId
                    }
                }

                return ret;
            }

            /** Returns current hero abilities */
            std::vector<entity_ability> getAbilities() {
                std::vector<entity_ability> ret;
                for (uint32_t i = 0; i < 16; ++i) {
                    char id[19];
                    snprintf(id, 19, ".m_hAbilities.%04d", i);

                    uint32_t aId = eHero->prop<uint32_t>(id);
                    if (aId != 2097151) {
                        ret.push_back(entity_ability(&p->getEntities()[aId & 0x7FF])); // TODO validate aId
                    }
                }

                return ret;
            }

            // To Implement:
            // .m_hMyWearables.0000 - 19        - > entity_wearable.hpp (Parse this using keyvalue and models?)
            // .m_Inventory.m_hInventoryParent  - > Check what this refers to
        private:
            /** Pointer to the hero entity */
            entity* eHero;
            /** Pointer to parser */
            parser* p;
    };
}

#endif /* _ALICE_ENTITY_HERO_HPP_ */