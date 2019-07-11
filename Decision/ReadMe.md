# Note

一个马尔科夫过程由一个四元组构成$M={S,A,P,R}$
- S 是一个状态集
- $P_{sa}$是一状态转移概率
- A是一个动作集合
- R是一个奖励函数

Bellman 方程:
$$V^{\pi}(s)=R(s)+\gamma\sum_{s'\in S} P_{s\pi(s)}(s')V^{\pi}(s') $$
