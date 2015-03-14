/**
 * @file alice_simple.hpp
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

#ifndef _ALICE_SIMPLE_HPP_
#define _ALICE_SIMPLE_HPP_

#include <string>

#include <alice/config.hpp>
#include <alice/parser.hpp>

#include "entity_game.hpp"
#include "entity_player.hpp"

// Make sure we have all extra libraries available
static_assert(DOTA_EXTRA, "Error: Addon libraries not available. Please compile Alice with BUILD_ADDONS=1.");

namespace dota {
    /** Class providing a high-level API to entities / objects for Alice */
    class alice_simple {
        public:
            /** The different possible types of dem_streams */
            enum stream_type {
                USE_FILE = 0,
                USE_MEMORY
            };
            
            /** Initialize the API by providing a pointer to a new(!) parser object, does not free the parser after it's finished */
            alice_simple(parser* p) : p(p), players(32, nullptr), gameinfo(nullptr), status(true), freeP(false) {
                // Ssubscribe to register events for specific entities
                handlerRegisterCallback(p->getHandler(), msgStatus, REPLAY_FLATTABLES, alice_simple, handleReady)

                // Subscribe to to stop parsing once we are done
                handlerRegisterCallback(p->getHandler(), msgStatus, REPLAY_FINISH, alice_simple, handleFinish)
            }

            /** Initializes the API by loading the given replay */
            alice_simple(std::string replay, stream_type s = USE_FILE) : p(nullptr), players(32, nullptr), gameinfo(nullptr), status(true), freeP(true) {
                // Settings object for the parser
                settings parser_settings {
                    false, // forward_dem        -> Unessecary because any content is internal
                    false, // forward_net        -> Same as forward_dem
                    false, // forward_net_intern -> Nope
                    true,  // forward_user       -> Keep User-Messages ready
                    true,  // parse_stringtables -> Yes, we block the ones we don't require specifically
                    {},    // blocked            -> We don't need these tables
                    true,  // parse_entities     -> Very much nessecary
                    false, // track_entities     -> Not needed in this case, we access all information directly
                    true,  // forward_entities   -> Nessecary to assign certain entities to their parents
                    false, // skip_unused        -> No, we block the ones we don't require specifically
                    {      // blocked            -> We don't need these entities

                        // CParticleSystem
                        // CEnvDeferredLight
                        // CEnvTonemapController
                        // CDOTAPropCustomTexture
                        // CDOTAGameManagerProxy
                        // CFogController
                        // CBaseAnimating
                        // CDOTAWearableItem

                    },
                    false
                };

                // Initialize the parser with the given arguments
                switch (s) {
                    case USE_FILE:
                        p = new parser(parser_settings, new dem_stream_file);
                        p->open(replay);
                        break;
                    case USE_MEMORY:
                        p = new parser(parser_settings, new dem_stream_memory);
                        p->open(replay);
                        break;
                    default:
                        // Throw exception: Unkown parser type specified
                        break;
                }

                // Ssubscribe to register events for specific entities
                handlerRegisterCallback(p->getHandler(), msgStatus, REPLAY_FLATTABLES, alice_simple, handleReady)

                // Subscribe to to stop parsing once we are done
                handlerRegisterCallback(p->getHandler(), msgStatus, REPLAY_FINISH, alice_simple, handleFinish)
            }

            /** Releases all alocated ressources */
            ~alice_simple() {
                if (p != nullptr && freeP)
                    delete p;
            }

            /** Prevent copying */
            alice_simple(const alice_simple&) = delete;

            /** Prevent moving */
            alice_simple(alice_simple&&) = delete;

            /** Parses the specified amount of messages, returns true if data is left to be parsed */
            bool parse(uint32_t n = 1) {
                while (status && (n > 0)) {
                    p->read();
                    --n;
                }

                return status;
            }

            /** Returns pointer to the game information entity */
            entity_game* getGameinfo() {
                return gameinfo;
            }

            /** Returns number of currently active players */
            uint32_t countPlayers() {
                uint32_t c = 0;
                while (players[c] != nullptr && c < 31) {
                    ++c;
                }
                return c;
            }

            /** Returns pointer to specified player */
            entity_player* getPlayer(uint32_t id) {
                return players[id];
            }
        private:
            /** The APIs very own parser object */
            parser* p;
            /** Keeps track of all the players */
            std::vector<entity_player*> players;
            /** Pointer to gameinfo */
            entity_game* gameinfo;
            /** Parsing status */
            bool status;
            /** Whether the parser is managed by us or not */
            bool freeP;

            /** This function is called when all flattables have been parsed */
            void handleReady(handlerCbType(msgStatus) msg) {
                // contains basic game data
                handlerRegisterCallback(p->getHandler(), msgEntity, p->getEntityIdFor("CDOTAGamerulesProxy"), alice_simple, handleGame);

                // contains player ressources
                handlerRegisterCallback(p->getHandler(), msgEntity, p->getEntityIdFor("CDOTA_PlayerResource"), alice_simple, handlePlayers);
                
                // stubs for important but not directly requested entities, required when we skip unsubscribed entities
                handlerRegisterCallback(p->getHandler(), msgEntity, p->getEntityIdFor("CDOTAPlayer"), alice_simple, handleStub);
                handlerRegisterCallback(p->getHandler(), msgEntity, p->getEntityIdFor("CDOTA_Item"), alice_simple, handleStub);
                
                for (auto &Id : p->findEntityIdFor("CDOTA_Unit_Hero_")) {
                    handlerRegisterCallback(p->getHandler(), msgEntity, Id, alice_simple, handleStub);
                }
                
                for (auto &Id : p->findEntityIdFor("CDOTA_Ability_")) {
                    handlerRegisterCallback(p->getHandler(), msgEntity, Id, alice_simple, handleStub);
                }      
                
                for (auto &itemId : p->findEntityIdFor("CDOTA_Item_")) {
                    handlerRegisterCallback(p->getHandler(), msgEntity, itemId, alice_simple, handleStub);
                }
            }
            
            void handleStub(handlerCbType(msgEntity) msg) {
                // ignore 
            }

            /** Marks the replay as completed */
            void handleFinish(handlerCbType(msgStatus) msg) {
                status = false;
            }

            /** Handles the creation of the gamerules proxy object */
            void handleGame(handlerCbType(msgEntity) msg) {
                gameinfo = new entity_game(msg->msg);

                // TODO fix this working
                // handlerRemoveCallback(p->getHandler(), msgEntity, p->getEntityIdFor("CDOTAGamerulesProxy"), alice_simple, handleGame);
            }

            /** Handles the player ressource object and creates new player entity representations */
            void handlePlayers(handlerCbType(msgEntity) msg) {
                char id[5];
                entity* ePlayerRessource = msg->msg;

                // check the connection state of all 32 players
                for (int i = 0; i < 32; ++i) {
                    snprintf(id, 5, "%04d", i);

                    if (ePlayerRessource->prop<uint32_t>(std::string(".m_iConnectionState.")+id, 0) == 1)
                        continue;

                    if (players[i] == nullptr)
                        players[i] = new entity_player(p, i);
                }

                // TODO: check gametime from handle game
            }
    };
}

#endif /* _ALICE_SIMPLE_HPP_ */
