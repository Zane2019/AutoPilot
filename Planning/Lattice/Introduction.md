
#### Cost function

- evaluator

evaluator构造:  vector<pLateralTrajectory>,vector<pLonTrajectory>,share_ptr<STgraph>,shared_ptr<vector<pathpoint>> reference_line,planning_target

planning_target为一个消息定义
```c++
struct StopPoint{
    double s
    enum Type{
        Hard=0;
        Soft=1;
    }
    Type type;
}; 
struct planning_target{
    StopPoint stop_point;
    double cruise_speed
};
```
构造期间,处理检测首先检测规划目标中是否存在停止点,然后进行双层循环遍历,外层循环遍历每条纵向轨迹,如果轨迹中存在停止点,则直接进入访问以下一条轨迹,不存在则检查路径点是否有效(即检查速度,加速度,jerk是否在范围内),然后再进入内层循环,内层循环遍历每条横向轨迹,组合配对计算cost,用priority_queue<>存放cost和轨迹对.

其中计算cost时,对于纵向轨迹到达目的地待机,jerk代价,碰撞代价,向心加速度代价,
而为了评估横向轨迹,我们会设定评估长度,评估长度取纵向轨迹本身长度和根据速度定义的纵向长度二者中的教小值,然后去计算这段纵向长度范围内的横向偏移代价.最终求所有代价的加权和.

横向偏移代价input(lat_traj,s_values):   
    首先计算每个s下对应横向偏移lat_offset,
    cost=lat_offset/(Flag_lat_offset_bound)
    然后根据lat_offset和初始状态的横向偏移方向去计算cost平方和及绝对值和:

    ```c++
    if (lat_offset * lat_offset_start < 0.0) {
      cost_sqr_sum += cost * cost * FLAGS_weight_opposite_side_offset;
      cost_abs_sum += std::fabs(cost) * FLAGS_weight_opposite_side_offset;
    } else {
      cost_sqr_sum += cost * cost * FLAGS_weight_same_side_offset;
      cost_abs_sum += std::fabs(cost) * FLAGS_weight_same_side_offset;
    }
    ```

最终轨迹的代价 cost=cost_sqr_sum / (cost_abs_sum + FLAGS_numerical_epsilon)

横向舒适性代价input(lat_traje,lon_traje):
    
    ```c++
        取一定长度的时间范围,
        分别求出纵向的位移,速度,加速度,
        然后计算出相对于初始s的相对位移,relative_s
        然后计算对于relative_s下的横向速度l_prime,横向加速度l_prime_prime
        计算cost=l_primeprime*s_dot*s_dor+l_prime*s_dotdot;
        max_cost=std::max(max_cost,std::fabs(cost));
    ```
最终横向舒适度代价就为max_cost;

纵向舒适度代价:
    
    对于时间范围内的t,以一定步长遍历,计算每个时刻的jerk值,
     double cost = jerk / FLAGS_longitudinal_jerk_upper_bound;
    cost_sqr_sum += cost * cost;
    cost_abs_sum += std::fabs(cost);
    cost_sqr_sum / (cost_abs_sum + FLAGS_numerical_epsilon);

最终纵向轨迹的舒适性代价=cost_sqr_sum / (cost_abs_sum + FLAGS_numerical_epsilon);

纵向到达目的地成本:
```
首先计算纵向位移,dist
然后对应每个参考熟读点,去计算参考速度和纵向轨迹速度的差作为cost;
计算速度代价的累加和   
speed_cost_sqr_sum += t * t * std::fabs(cost);
speed_cost_weight_sum += t * t;
再根据累加和去计算速度代价
speed_cost =speed_cost_sqr_sum / (speed_cost_weight_sum + FLAGS_numerical_epsilon);
dist_travelled_cost = 1.0 / (1.0 + dist_s);
最终的到达目的地代价为(speed_cost * FLAGS_weight_target_speed +
          dist_travelled_cost * FLAGS_weight_dist_travelled) /
         (FLAGS_weight_target_speed + FLAGS_weight_dist_travelled)
 ```
计算到达目的地代价的子问题:如何去求解参考速度?
根据规划目标是否有停止点决定:如果有停止点,则根据初始纵向位移和目标的巡航速度确定一个分段加速轨迹,以该分段加速轨迹进行时间离散获得一个参考速度

纵向碰撞代价:
```

```





计算向心加速度代价:
```
//假设车没有突然偏离车道线
对于一定时间长度的内,计算每个时间点的 s,v
然后根据s找到参考线上匹配的参考点ref_point;
然后根据参考点的曲率导数去计算向心加速度 
centripetal_acc = v * v * ref_point.kappa();
计算向心加速度的累加和    
centripetal_acc_sum += std::fabs(centripetal_acc);

centripetal_acc_sqr_sum += centripetal_acc * centripetal_acc;
```

最终纵向加速度的代价为 centripetal_acc_sqr_sum /
         (centripetal_acc_sum + FLAGS_numerical_epsilon);


#### Tips:

再apollo中由于存在不同结束的曲线,它直接建立一个curve纯虚的基类,提供相应的接口(如计算曲线不同的阶数值),去做多台,以至于再规划层我们不需要知道曲线的具体实例,直接调用基类指针,去实现相应功能.