#ifndef _ALICE_ENTITY_GAME_HPP_
#define _ALICE_ENTITY_GAME_HPP_

#include <vector>
#include <string>

#include <alice/entity.hpp>

#include "entity_item.hpp"

namespace dota {
    /** Contains method to access general game information */
    class entity_game {
        public:
            /** Constructor */
            entity_game(entity* eGame) : eGame(eGame) { }

            /** Default copy constructor */
            entity_game(const entity_game&) = default;

            /** Default move constructor */
            entity_game(entity_game&&) = default;

            /** Default destructor */
            ~entity_game() = default;

            /** Get the ID of this match */
            uint32_t getMatchId() {
                return eGame->prop<uint32_t>(".dota_gamerules_data.m_unMatchID");
            }

            /** Returns name of this lobby */
            std::string getLobbyName() {
                return eGame->prop<std::string>(".dota_gamerules_data.m_lobbyGameName");
            }

            /** Returns the number of players that joined the lobby */
            int32_t getExpectedPlayers() {
                return eGame->prop<int32_t>(".dota_gamerules_data.m_nExpectedPlayers");
            }

            /** Returns the number of players that correctly joined the game */
            int32_t getConnectedPlayers() {
                return eGame->prop<int32_t>(".dota_gamerules_data.m_nLoadedPlayers");
            }

            /** Returns Dire wins if this game is in a series */
            uint32_t getDireWins() {
                return eGame->prop<uint32_t>(".dota_gamerules_data.m_nDireSeriesWins");
            }

            /** Returns Radiant wins if this game is in a series */
            uint32_t getRadiantWins() {
                return eGame->prop<uint32_t>(".dota_gamerules_data.m_nRadiantSeriesWins");
            }

            /** Returns league ID if applicable */
            uint32_t getLeagueID() {
                return eGame->prop<uint32_t>(".dota_gamerules_data.m_lobbyLeagueID");
            }

            /** Returns the game mode */
            int32_t getGameMode() {
                return eGame->prop<int32_t>(".dota_gamerules_data.m_iGameMode");
            }

            /** Returns whether this game is running the stable mode */
            bool isStableMode() {
                return eGame->prop<uint32_t>(".dota_gamerules_data.m_bIsStableMode") == 1;
            }

            /** Returns the time at which the game has been started */
            int32_t getGameDate() {
                return eGame->prop<int32_t>(".dota_gamerules_data.m_iNetTimeOfDay");
            }

            /** Returns the current state of the game */
            int32_t getState() {
                return eGame->prop<int32_t>(".dota_gamerules_data.m_nGameState");
            }

            /** Returns the current hero pick state based on the game mode */
            int32_t getPickState() {
                return eGame->prop<int32_t>(".dota_gamerules_data.m_nHeroPickState");
            }

            /** Returns the team that started picking */
            int32_t getPickTeamStart() {
                return eGame->prop<int32_t>(".dota_gamerules_data.m_iStartingTeam");
            }

            /** Returns the current team picking */
            int32_t getPickTeamActive() {
                return eGame->prop<int32_t>(".dota_gamerules_data.m_iActiveTeam");
            }

            /** Returns player numbers of captains */
            std::vector<int32_t> getCaptains() {
                std::vector<int32_t> captains{
                    eGame->prop<int32_t>(".dota_gamerules_data.m_iCaptainPlayerIDs.0000"),
                    eGame->prop<int32_t>(".dota_gamerules_data.m_iCaptainPlayerIDs.0001")
                };

                return captains;
            }

            /** Returns the pick / ban order */
            int32_t getPickBanOrder() {
                return eGame->prop<int32_t>(".dota_gamerules_data.m_iCMModePickBanOrder", 0);
            }

            /** Returns extra pick time remaining for the radiant */
            float getRadiantPickTime() {
                return eGame->prop<float>(".dota_gamerules_data.m_fExtraTimeRemaining.0000");
            }

            /** Returns extra pick time remaining for the dire */
            float getDirePicktime() {
                return eGame->prop<float>(".dota_gamerules_data.m_fExtraTimeRemaining.0001");
            }

            /** Returns banned heroes in order, always 10, - 1 if not applicable */
            std::vector<int32_t> getBanned() {
                std::vector<int32_t> banned{
                    eGame->prop<int32_t>(".dota_gamerules_data.m_BannedHeroes.0000"),
                    eGame->prop<int32_t>(".dota_gamerules_data.m_BannedHeroes.0001"),
                    eGame->prop<int32_t>(".dota_gamerules_data.m_BannedHeroes.0002"),
                    eGame->prop<int32_t>(".dota_gamerules_data.m_BannedHeroes.0003"),
                    eGame->prop<int32_t>(".dota_gamerules_data.m_BannedHeroes.0004"),
                    eGame->prop<int32_t>(".dota_gamerules_data.m_BannedHeroes.0005"),
                    eGame->prop<int32_t>(".dota_gamerules_data.m_BannedHeroes.0006"),
                    eGame->prop<int32_t>(".dota_gamerules_data.m_BannedHeroes.0007"),
                    eGame->prop<int32_t>(".dota_gamerules_data.m_BannedHeroes.0008"),
                    eGame->prop<int32_t>(".dota_gamerules_data.m_BannedHeroes.0009")
                };

                return banned;
            }

            /** Returns array of selected heroes */
            std::vector<int32_t> getSelected() {
                std::vector<int32_t> selected{
                    eGame->prop<int32_t>(".dota_gamerules_data.m_SelectedHeroes.0000"),
                    eGame->prop<int32_t>(".dota_gamerules_data.m_SelectedHeroes.0001"),
                    eGame->prop<int32_t>(".dota_gamerules_data.m_SelectedHeroes.0002"),
                    eGame->prop<int32_t>(".dota_gamerules_data.m_SelectedHeroes.0003"),
                    eGame->prop<int32_t>(".dota_gamerules_data.m_SelectedHeroes.0004"),
                    eGame->prop<int32_t>(".dota_gamerules_data.m_SelectedHeroes.0005"),
                    eGame->prop<int32_t>(".dota_gamerules_data.m_SelectedHeroes.0006"),
                    eGame->prop<int32_t>(".dota_gamerules_data.m_SelectedHeroes.0007"),
                    eGame->prop<int32_t>(".dota_gamerules_data.m_SelectedHeroes.0008"),
                    eGame->prop<int32_t>(".dota_gamerules_data.m_SelectedHeroes.0009")
                };

                return selected;
            }

            /** Returns current ingame time */
            float getTime() {
                return eGame->prop<float>(".dota_gamerules_data.m_fGameTime");
            }

            /** Returns overall time spend including picking / pre-game phase */
            float getTimeAbsolute() {
                return getTime() - getTimeGamestart();
            }

            /** The time the game loaded */
            float getTimeLoaded() {
                return eGame->prop<float>(".dota_gamerules_data.m_flGameLoadTime");
            }

            /** Get the time the pregame started */
            float getTimePregame() {
                return eGame->prop<float>(".dota_gamerules_data.m_flPreGameStartTime");
            }

            /** Get the time the game started */
            float getTimeGamestart() {
                return eGame->prop<float>(".dota_gamerules_data.m_flGameStartTime");
            }

            /** Time the game ended if applicable */
            float getTimeEnd() {
                return eGame->prop<float>(".dota_gamerules_data.m_flGameEndTime");
            }

            /** Whether the game is currently paused */
            bool isPaused() {
                return eGame->prop<uint32_t>(".dota_gamerules_data.m_bGamePaused") == 1;
            }

            /** The team who paused the game */
            int32_t getPauseTeam() {
                return eGame->prop<int32_t>(".dota_gamerules_data.m_iPauseTeam");
            }

            /** Cooldown of radiant glyph if applicable */
            float getGlyphCooldownRadiant() {
                return eGame->prop<float>(".dota_gamerules_data.m_fGoodGlyphCooldown");
            }

            /** Cooldown of dire glpyh if applicable */
            float getGlyphCooldownDire() {
                return eGame->prop<float>(".dota_gamerules_data.m_fBadGlyphCooldown");
            }

            /** Returns the team that called GG */
            int32_t getGGTeam() {
                return eGame->prop<int32_t>(".dota_gamerules_data.m_nGGTeam");
            }

            /** Time the game ends because one team called GG */
            float getGGTime() {
                return eGame->prop<float>(".dota_gamerules_data.m_flGGEndsAtTime");
            }

            /** Whether this night is caused due to nightstalker using his ultimate */
            bool isNightstalkerNight() {
                return eGame->prop<uint32_t>(".dota_gamerules_data.m_bIsNightstalkerNight") == 1;
            }

            /** Returns the winner of the game if applicable */
            int32_t getWinner() {
                return eGame->prop<int32_t>(".dota_gamerules_data.m_nGameWinner");
            }

             /** Returns items that have a maximum stock count and their corresponding stati. */
            std::vector<item_stock> getItemStockRadiant() {
                std::vector<item_stock> items;

                // index to modify = 44
                std::string strMutable = ".dota_gamerules_data.m_ItemStockInfoGood.0000";

                for (uint32_t i = 0; i < 8; ++i) {
                    strMutable[44] = (char)(((int)'0')+i);
                    items.push_back({
                        eGame->prop<uint32_t>(strMutable+".usItemIndex"),
                        eGame->prop<float>(strMutable+".fStockDuration"),
                        eGame->prop<float>(strMutable+".fStockTime"),
                        eGame->prop<uint32_t>(strMutable+".iMaxCount"),
                        eGame->prop<uint32_t>(strMutable+".iStockCount")
                    });
                }

                return items;
            }

            /** Returns items that have a maximum stock count and their corresponding stati. */
            std::vector<item_stock> getItemStockDire() {
                std::vector<item_stock> items;

                // index to modify = 43
                std::string strMutable = ".dota_gamerules_data.m_ItemStockInfoBad.0000";

                for (uint32_t i = 0; i < 8; ++i) {
                    strMutable[43] = (char)(((int)'0')+i);
                    items.push_back({
                        eGame->prop<uint32_t>(strMutable+".usItemIndex"),
                        eGame->prop<float>(strMutable+".fStockDuration"),
                        eGame->prop<float>(strMutable+".fStockTime"),
                        eGame->prop<uint32_t>(strMutable+".iMaxCount"),
                        eGame->prop<uint32_t>(strMutable+".iStockCount")
                    });
                }

                return items;
            }

            // CDOTAGameManagerProxy
            // TODO:
            // - .dota_gamemanager_data.m_StableHeroAvailable. 0 - 127
        private:
            /** Points at the CDOTAGamerulesProxy entity */
            entity* eGame;
    };
}

#endif // _ALICE_ENTITY_GAME_HPP_