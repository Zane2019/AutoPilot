#include "MarkovDecisionProcess.h"

namespace autopilot {
namespace mdp {
MarkovDecisionProcess::MarkovDecisionProcess() {
  p_current_obsercation_ = new observation;
}
MarkovDecisionProcess::~MarkovDecisionProcess() {
  delete p_current_obsercation_;
  delete p_policy_parser_;
  delete p_reward_parser_;
  delete p_state_action_encoder_;
  delete p_transition_parser_;
}

void MarkovDecisionProcess::scaffold() {
  p_state_action_encoder_ = new StateActionEncoder(&d_observations_);
  p_state_action_encoder_->observation_to_int();
  const int state_count = p_state_action_encoder_->state_count();
  const int action_count = p_state_action_encoder_->action_count();

  p_reward_parser_ = new RewardParse(&d_observations_, state_count);
  p_transition_parser_ =
      new TransitionParse(&d_observations_, state_count, action_count);
  p_policy_parser_ = new PolicyParse(state_count, action_count);
}

void MarkovDecisionProcess::transition(state_transition trans){
    p_current_obsercation_->state_transitions.push_back(trans);
}
void MarkovDecisionProcess::reward(double value){
    p_current_obsercation_->reward=value;
    d_observations_.push_back(*p_current_obsercation_);
    p_current_obsercation_=new observation;
}

void MarkovDecisionProcess::learn(){
    scaffold();
    std::vector<double> R=p_reward_parser_->rewards();
    tensor P=p_transition_parser_->transition_probabilities();

    std::vector<int> encoded_policy=p_policy_parser_->policy(P,R);
    d_policy_=p_state_action_encoder_->parse_encoded_policy(encoded_policy);
}

std::string MarkovDecisionProcess::action(const std::string& state) const{
    if (d_policy_.find(state)==d_policy_.end())
    {
        return "Unknow_State";
    }else
    {
        return d_policy_.find(state)->second;
    }
    
    
}
}  // namespace mdp
}  // namespace autopilot
