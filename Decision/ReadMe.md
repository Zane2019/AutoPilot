# $Markov Decision Process$

----
### **Markov Property**

$$P(S_{t+1}|S_t=P(S_{t+1}|S_1,S_2,...,S_T)$$
即给定当前状态$S_t$,将来的状态与t时刻之前的状态无关

### **State Transition Matrix**

状态转移公式:
$$P_{ss'}=P(S_{t+1}=s'|S_t=s)$$
状态转移矩阵定义了所有状态的转移概率,
$$P= \left[ \begin{matrix} P_{11} & \cdots & P_{12}\\ \vdots & \ddots & \vdots \\ P_{n1} & \cdots &p_{nn} \end{matrix} \right]$$
其中每一行的和为1.

### **Markov Process**

Markov Process是一个无记忆的随机过程,是一些具有马尔科夫性质的随机序列构成,
一个马尔科夫过程由一个二组构成$M=\{S,P\}$
- $S$是一个有限状态集
- $P$是一状态转移概率矩阵
    $P_{SS'}=P[S_{t+1}=s'|S_t=s]$

### Markov Reward Process
马尔科夫奖励过程是在马尔科夫过程的基础上增加了奖励$R$和衰减系数$\gamma :<S,P,R,\gamma>$
$R$是一个奖励函数.$S$状态下的奖励是在某一时刻$t$处在状态$s$下,在下一时刻$t+1$能获得的奖励期望,
$R_s=E[R_{t+1}|S_t=s]$
$\gamma$是一个折扣因子,$\gamma \in [0,1]$

### Return

定义,收获$G_t$是再一个马尔科夫链上,从$t$时刻开始往后所有的奖励的衰减的收益总和.
$$G_t=R_{t+1}+\gamma R_{t+2}+\gamma^2 R_{t+3}+\cdots=\sum_{k=0}^{\infty}\gamma^kR_{t+k+1} $$
其中的 $\gamma$ 指的是衰减因子，体现了未来的奖励在当前时刻的价值比例，这样要注意的就是$G_t$并不只是一条路径，从$t$时刻到终止状态，可能会有多条路径。
$\gamma$接近0，则表明趋向于“近视”性评估；$\gamma$ 接近1则表明偏重考虑远期的利益

### Value Function

值函数给出了某一状态或某一行为的长期价值.
定义:一个马尔科夫奖励过程中某一状态的价值函数为从该状态开始的马尔科夫收获的期望:
$$v(s)=E[G_t|S_t=s]$$
为什么是期望,因为从t时刻到终止状态的马尔科夫链不止一条,每一条都有相对应的概率和Return收益.

### Bellman Equation for MRPs  (Important!!!)

首先从Value Function的角度进行理解,Value Function可以分为两部分:
- 立即回报 $R_{t+1}$
- 未来状态的折扣价值 $\gamma v(S_{t+1})$

$$
\begin{aligned}
v(s)=&E[G_t|S_t=s]\\
=& E[R_{t+1}+\gamma*R_{t+2}+\gamma^2*R_{t+3}+\cdots|S_t=s]\\
=&E[R_{t+1}+\gamma(R_{t+2}+\gamma R_{t+3}+\cdots)|S_t=s]\\
=&E[R_{t+1}+\gamma G_{t+1}|S_t=s]\\
=&E[R_{t+1}+\gamma v(S_{t+1})|S_{t+1}=s]
\end{aligned}
$$
>Note:有疑问的会在导出最后一行时，将 $G_{t+1}$ 变成了 $v(S_{t+1})$。其理由是收获的期望等于收获的期望的期望.
> 通过最后一行可以看出$v(s)$由两部分组成,一是该状态的即时奖励期望,即时奖励期望等于即时奖励,因为根据即时奖励的定义,它与下一个状态无关,另一个是下一时刻状态的价值期望,可以根据下一时刻状态的概率分布得到其期望,如果用$s'$表示状态一下时刻任一可能的状态,那么$Bellman 方程$可以写成:
$$V(s)=R_s+\gamma\sum_{s'\in S}P_{ss'}V(s')$$

*Q:可能有个疑问,在算某一状态的value function时,其他状态的value function怎么知道呢?
A:其实这些值一开始可以任意初始化,后面进行学习更新,类似于神经网络的权值参数,一开始任意初始化,后面通过loss反向更新一样.*

### Bellman Equation in Matrix Form
Bellman方程可以使用矩阵形式进行简洁表达:
$$V=R+\gamma P V$$
结合具体的矩阵表达形式如下:
$$
\left[
\begin{matrix}
v(1)\\
\vdots \\
v(n)\\
\end{matrix}
\right]
=\left[
\begin{matrix}
R(1)\\
\vdots \\
R(n)\\
\end{matrix}
\right]+\gamma
\left[ \begin{matrix} P_{11}& \cdots &P_{1n}\\
\vdots& \ddots& \vdots\\
P_{n1}& \cdots& P_{nn}
\end{matrix}\right]
\left[
\begin{matrix}
v(1)\\
\vdots\\
v(n)
\end{matrix}
\right]
$$
Bellman方程是是一个线性方程组,理论上可以直接求解,
$$
\begin{aligned}
V&=R+\gamma P V\\
(I-\gamma P)V&=R\\
V&=(I-\gamma P)^{-1}
\end{aligned}$$
但是其计算时间复杂度为$O(n^3)$,$n$是状态数量,因为矩阵求拟的过程为$O(n^3)$.
由于求解复杂度较高,因为直接求解仅适用于小规模的MRPs
大规模MRP的求解通常需要使用迭代法,常用的迭代方法有
- 动态规划 *Dynamic Programming*
- 蒙特卡洛评估 *Monte-Carlo evaluation*
- 时序差分学习 *Temporal-Difference*
