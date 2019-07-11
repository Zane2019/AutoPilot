#ifndef DATA_STRUCTURES_H_
#define DATA_STRUCTURES_H_

#include<string>
#include<vector>

namespace autopilot{
    namespace mdp{
        struct state_transition
        {
            std::string state;
            int encoded_state;
            
            std::string state_;
            int encoded_state_;

            std::string action;
            int encoded_action;

        };

        struct observation
        {
            std::vector<state_transition> state_transitions;
            double reward;
        };

        using const_obs_iter=std::vector<observation>::const_iterator; 
        using obs_iter=std::vector<observation>::iterator;

        using const_trans_iter=std::vector<state_transition>::const_iterator;
        using trans_iter=std::vector<state_transition>::iterator;

        using tensor=std::vector<std::vector<std::vector<double> > >;

        tensor makeTesor(int state_count,int action_count);


    }
}
#endif //DATA_STRUCTURES_H_