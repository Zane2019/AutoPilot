#ifndef POLICY_PARSE_H_
#define POLICY_PARSE_H_

#include <vector>
#include "DataStructures.h"

namespace autopilot {
namespace mdp {
class PolicyParse {
 private:
  const int d_state_count_;
  const int d_action_count_;

 public:
  inline PolicyParse(int state_count, int action_state)
      : d_state_count_(state_count), d_action_count_(action_state){};
  std::vector<int> policy(const tensor& p,
                          const std::vector<double>& rewards) const;
  ~PolicyParse();
};
}  // namespace mdp
}  // namespace autopilot

#endif  // POLICY_PARSE_H_