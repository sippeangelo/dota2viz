#ifndef _ALICE_ENTITY_ABILITY_HPP_
#define _ALICE_ENTITY_ABILITY_HPP_

namespace dota {
    /** A single ability entity */
    class entity_ability {
        public:
            /** Creates an item from it's entity */
            entity_ability(entity* ability) : eAbility(ability) {

            }

            /** The name of this ability */
            std::string getName() {
                return eAbility->prop<std::string>(".m_iName");
            }

            /** Whether the ability is currently activated */
            bool isActivated() {
                return eAbility->prop<uint32_t>(".m_bActivated") == 1;
            }

            /** Is this ability autocasted? */
            bool getAutoCastState() {
                return eAbility->prop<uint32_t>(".m_bAutoCastState") == 1;
            }

            /** Returns the toogle state */
            bool getToogleState() {
                return eAbility->prop<uint32_t>(".m_bToggleState") == 1;
            }

            /** Current ability level (0 - 4+), e.g. invoker */
            uint32_t getLevel() {
                return eAbility->prop<uint32_t>(".m_iLevel");
            }

            /** Cooldown until */
            float getCooldown() {
                return eAbility->prop<float>(".m_fCooldown");
            }

            /** Cooldown length */
            float getCooldownLength() {
                return eAbility->prop<float>(".m_flCooldownLength");
            }

            /** Cast range in units */
            uint32_t getCastRange() {
                return eAbility->prop<uint32_t>(".m_iCastRange");
            }
        private:
            /** Points at the entity containing the ability */
            entity* eAbility;
    };
}

#endif // _ALICE_ENTITY_ABILITY_HPP_