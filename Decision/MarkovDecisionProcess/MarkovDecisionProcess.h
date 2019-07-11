#ifndef MARKOV_DECISION_PROCESS_H_
#define MARKOV_DECISION_PROCESS_H_

#include"DataStructures.h"
#include"StateActionEncoder.h"
#include"TransitionParse.h"
#include"RewardParse.h"
#include"PolicyParse.h"

namespace autopilot{
    namespace mdp
    {
        class MarkovDecisionProcess
        {
        private:
            std::vector<observation> d_observations_;
            std::map<std::string,std::string> d_policy_;

            observation* p_current_obsercation_;
            StateActionEncoder* p_state_action_encoder_;
            RewardParse* p_reward_parser_;
            TransitionParse* p_transition_parser_;
            PolicyParse* p_policy_parser_;

            void scaffold();

        public:
            MarkovDecisionProcess();
            MarkovDecisionProcess(const MarkovDecisionProcess&)=delete;
            MarkovDecisionProcess& operator=(const MarkovDecisionProcess&)=delete;
            ~MarkovDecisionProcess();

            void learn();
            void transition(state_transition trans);
            void reward(double value);
            std::string action(const std::string& state) const;
        };
    } // namespace mdp
} // namespace autopilot


#endif //MARKOV_DECISION_PROCESS_H_