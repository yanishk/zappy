/*
** EPITECH PROJECT, 2024
** refacto_branch2
** File description:
** AllPlayer
*/

#ifndef ALLPLAYER_HPP_
    #define ALLPLAYER_HPP_
    #define PLAYER_INFOBOX_WIDTH 400
    #define PLAYER_INFOBOX_POSY 5
    #define LOOP_ITEM_TAKE_DROP 2
    #define MAX_RGB 255
    #include "Player.hpp"
    #include "AallPlayer.hpp"


namespace Zappy {

    class AllPlayers : public AAllPlayerObj {

        public:

            AllPlayers(CommandManager &cmd, bool isAnimated);
            void renderAllElements(void) override {};
            void renderAllElements(Vector3 camPosition) override;
            void setAllElements(std::vector<std::pair<Model, float>> model) override;
            std::size_t getTotalNbrElements(void) override;

            void renderAll2D(std::pair<bool, int> moreInfo,
                std::unique_ptr<AllItem> &_allItem);
            std::pair<bool, int> isPlayerSelected(Vector3 target, Vector3 position);

        private:

            CommandManager &_cmd;
            std::vector<Player> _allPlayer;
            bool _isAnimated;

            Player &getPlayerByID(int PlayerID);
            void addPlayer(std::vector<std::pair<Model, float>> model);
            void movePlayer(void);
            void setPlayerLevel(void);
            void collectOrDropItem(void);
            void setInventory(void);
            void incantation(void);
            void startIncantation(int playerID, Vector2 pos);
            void endOfIncantation(Vector2 pos);
            void ejection(void);
            void playerDied(void);
            bool removePlayerFromIsland(int playerID);
            void getAllTeam(void);
            void broadcast(void);


            Model _model;
            Model _incantationModel;
            Model _expulsionModel;
            Vector3 _size;
            ModelAnimation *_anim;
            int _animsCount;
            std::vector<std::vector<int>> _bct;
            std::vector<std::string> _allTeamName;
            Color setPlayerColor(std::string teamName);
    };
}

#endif /* !ALLPLAYER_HPP_ */
