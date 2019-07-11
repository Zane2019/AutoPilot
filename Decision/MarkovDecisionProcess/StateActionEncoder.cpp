#include"StateActionEncoder.h"

namespace autopilot{
    namespace mdp
    {
        StateActionEncoder::StateActionEncoder(std::vector<observation>* observations):d_observations_(observations){
            parse_states_and_actions();
        }
        void StateActionEncoder::parse_states_and_actions(){
            int state_index=0;
            int action_index=0;

            std::string state,action;

            obs_iter obs_it=d_observations_->begin();
            while (obs_it!=d_observations_->end())
            {
                trans_iter trans_it=obs_it->state_transitions.begin();
                while (trans_it!=obs_it->state_transitions.end())
                {
                    state=trans_it->state;
                    action=trans_it->action;
                    if(d_state_to_int_.find(state)!=d_state_to_int_.end()){
                        d_state_to_int_[state]=state_index;
                        d_int_to_state_.push_back(state);
                        ++state_index;
                    }
                    if (d_action_to_int_.find(action)!=d_action_to_int_.end())
                    {
                        d_action_to_int_[action]=action_index;
                        d_int_to_action_.push_back(action);
                        ++action_index;
                    }
                    ++trans_it;
                }
                ++obs_it;
            }
            
        }

        void StateActionEncoder::observation_to_int()const{
            obs_iter obs_it=d_observations_->begin();
            while (obs_it!=d_observations_->end())
            {
                trans_iter trans_it=obs_it->state_transitions.begin();
                while(trans_it!=obs_it->state_transitions.end()){
                    trans_it->encoded_state=d_state_to_int_.find(trans_it->state)->second;
                    trans_it->encoded_state_=d_state_to_int_.find(trans_it->state_)->second;
                    trans_it->encoded_action=d_action_to_int_.find(trans_it->action)->second;

                    ++trans_it;
                }
                ++obs_it;
            }
        }

        std::map<std::string,std::string> StateActionEncoder::parse_encoded_policy(const std::vector<int> &encoded_policy)const{
            std::map<std::string,std::string> policy;
            std::string state,action;
            for (size_t i = 0; i < encoded_policy.size(); ++i)
            {
                state=d_int_to_state_[i];
                action=d_int_to_action_[encoded_policy[i]];

                policy[state]=action;
            }
            return policy;
        }

        int StateActionEncoder::state_count()const{
            return d_int_to_state_.size();
        }

        int StateActionEncoder::action_count()const{
            return d_int_to_action_.size();
        }



        
    } // namespace mdp
} // namespace autopilot

