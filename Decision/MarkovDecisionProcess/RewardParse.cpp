#include "RewardParse.h"

namespace autopilot {
namespace mdp {
RewardParse::RewardParse(std::vector<observation>* p_obs, int state_count)
    : p_obs_(p_obs), d_state_count_(state_count) {}

//need to review twice
std::vector<double> RewardParse::rewards() const {
  std::vector<double> total_state_reward(d_state_count_);
  std::vector<int> total_state_visits(d_state_count_);

  const_obs_iter obs_it = p_obs_->cbegin();
  while (obs_it != p_obs_->cend()) {
    int visits = obs_it->state_transitions.size();
    double reward_per_visit = (obs_it->reward) / visits;  // why?

    const_trans_iter tran_it = obs_it->state_transitions.begin();
    while (tran_it != obs_it->state_transitions.end()) {
      int state = tran_it->encoded_state;
      total_state_reward[state] += reward_per_visit;
      total_state_visits[state] += 1;
      ++tran_it;
    }
    ++obs_it;
  }
  std::vector<double> average_state_rewards;
  for (int i = 0; i < d_state_count_; ++i) {
    double state_reward = total_state_reward[i];
    if (total_state_visits[i] > 0) {
      state_reward /= total_state_visits[i];
    }
    average_state_rewards.push_back(state_reward);
  }
  return average_state_rewards;
}
}  // namespace mdp
}  // namespace autopilot
