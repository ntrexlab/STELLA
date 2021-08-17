#define wheel_to_wheel_d            0.337       // 바퀴�? 바�?�?거리  [m]
#define distance_per_rev            0.5652        // ?�바???�전???�동 거리 [m / rev]
#define pulse_per_rev               54000        // ?�바???�전???�코???�스 카운????값�? 부착된 ?�코?��? 감속기�? 고려???�해진다.) [pulse / rev] 
#define pulse_per_distance          95541.4012739    // 1m ?�동???�코???�스 카운??[pulse / m]
#define gear_ratio                  27           // 감속�?
#define motor_scale_const           2866.24203822    // gear_ratio * 60 / distance_per_rev




void calculate_wheel_vel(float linear, float angular, float *left_rpm,  float *right_rpm);
