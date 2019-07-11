#ifndef TRANSITION_PARSE_H_
#define TRANSITION_PARSE_H_

#include"DataStructures.h"

namespace autopilot{
    namespace mdp{

        class TransitionParse
        {
        private:
            std::vector<observation>* p_obs_;
            const int d_state_count;
            const int d_action_count;

            tensor count_transition()const;
            tensor parse_probabilities(tensor & transition_count) const;
        public:
            TransitionParse(std::vector<observation>*observations,int state_count,int action_count);
            TransitionParse(const TransitionParse&)=delete;
            const TransitionParse& operator=(const TransitionParse&)=delete;
            tensor transition_probabilities()const;

            ~TransitionParse();
        };
    } // namespace mdp
} // namespace autopilot
#endif //TRANSITION_PARSE_H_