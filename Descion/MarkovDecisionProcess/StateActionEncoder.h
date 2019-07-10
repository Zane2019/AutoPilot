#ifndef STATE_ACTION_ENCODER_H_
#define STATE_ACTION_ENCODER_H_

#include"DataStructures.h"
#include<map>

namespace autopilot{
   namespace mdp
   {
       class StateActionEncoder
       {
       private:
           void parse_states_and_actions();

           std::map<std::string,int> d_state_to_int;
           std::map<std::string,int> d_action_to_int;
           std::vector<std::string> d_int_to_state;
           std::vector<std::string> d_int_to_action;
           std::vector<observation>* d_observations;
       public:
           explicit StateActionEncoder(std::vector<observation>* observations);
           StateActionEncoder(const StateActionEncoder&)=delete;
           const StateActionEncoder operator=(const StateActionEncoder&)=delete;
           ~StateActionEncoder();
           int state_count() const;
           int action_count() const;
           void observation_to_int() const;
           std::map<std::string,std::string> parse_encoded_policy(const std::vector<int>&encoded_policy)const;
       };
   } // namespace mdp
} // namespace autopilot

#endif //STATE_ACTION_ENCODER_H_