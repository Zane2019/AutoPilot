#ifndef REWARD_H_
#define REWARD_H_

#include"DataStructures.h"

namespace autopilot{
    namespace mdp
    {
        class RewardParse
        {
        private:
        std::vector<observation>* p_obs_;
        const int d_state_count_;

        public:
            RewardParse(std::vector<observation>* p_obs,int state_count);
            RewardParse(const RewardParse&)=delete;
            const RewardParse& operator=(const RewardParse&)=delete;
            std::vector<double> rewards()const;
            ~RewardParse();
        };
    } // namespace mdp
} // namespace autopilot
#endif //REWARD_H_