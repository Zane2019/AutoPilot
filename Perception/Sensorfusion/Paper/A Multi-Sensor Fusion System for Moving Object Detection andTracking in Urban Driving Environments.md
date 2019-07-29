
## Sensor Characterization

- Radar
$$z^{(R)}(k)=\{r_1,r_2,...,r_p\}$$

$$r_i=
\left [x,y,\dot{x},\dot{y}
\right]$$

- Lidar
$$z^{L}(k)=\{l_1ml_2,l_3,....,l_q\}$$

$$l_i=[x,y,\phi,\dot{x},\dot{y},\omega,l ]$$

- Camera

$$z^C=\{c_1,c_2,c_3,...,c_r\}$$

$$c_i=[x_1,y_1,x_2,y_2,class]$$

$(x_1,y_1)$,$(x_2,y_2)$分别是图像空间中bounding box的左上点和右下点,class则是object的类型名

故,
$$z(k)=\{z^R(k),z^L(k),z^C(k)\}$$