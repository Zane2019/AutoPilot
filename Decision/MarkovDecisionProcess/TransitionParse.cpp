#include "TransitionParse.h"

namespace autopilot {
namespace mdp {
TransitionParse::TransitionParse(std::vector<observation>* observations,
                                 int state_count, int action_count)
    : p_obs_(observations),
      d_state_count(state_count),
      d_action_count(action_count) {}
tensor TransitionParse::count_transition() const {
  tensor transition_count = makeTesor(d_state_count, d_action_count);
  obs_iter obs_it = p_obs_->begin();
  while (obs_it != p_obs_->end()) {
    trans_iter trans_it = obs_it->state_transitions.begin();
    while (trans_it != obs_it->state_transitions.end()) {
      int state = trans_it->encoded_state;
      int action = trans_it->encoded_action;
      int state_ = trans_it->encoded_state_;
      transition_count[state][action][state_] += 1;
      ++trans_it;
    }
    ++obs_it;
  }
  return transition_count;
}
tensor TransitionParse::parse_probabilities(tensor& transition_count) const {
  tensor prob = makeTesor(d_state_count, d_action_count);

  for (int state = 0; state < d_state_count; ++state) {
    for (int action = 0; action < d_action_count; ++action) {
      int total_transition = 0;
      for (int state_ = 0; state_ < d_state_count; ++state_) {
        total_transition += transition_count[state][action][state_];
      }

      for (int state_ = 0; state_ < d_state_count; ++state_) {
        if (total_transition > 0) {
          double transitions = transition_count[state][action][state_];
          prob[state][action][state_] = transitions / total_transition;
        } else {
          prob[state][action][state_] = 1.0 / d_state_count;
        }
      }
    }
  }
  return prob;
}

tensor TransitionParse::transition_probabilities() const {
  tensor transition_count = count_transition();
  return parse_probabilities(transition_count);
}

}  // namespace mdp
}  // namespace autopilot
