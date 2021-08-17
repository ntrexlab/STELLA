#define wheel_to_wheel_d            0.337       // ๋ฐํด์? ๋ฐํ?๊ฐ?๊ฑฐ๋ฆฌ  [m]
#define distance_per_rev            0.5652        // ?๋ฐ???์ ???ด๋ ๊ฑฐ๋ฆฌ [m / rev]
#define pulse_per_rev               54000        // ?๋ฐ???์ ???์ฝ???์ค ์นด์ด????๊ฐ์? ๋ถ์ฐฉ๋ ?์ฝ?์? ๊ฐ์๊ธฐ๋? ๊ณ ๋ ค???ํด์ง๋ค.) [pulse / rev] 
#define pulse_per_distance          95541.4012739    // 1m ?ด๋???์ฝ???์ค ์นด์ด??[pulse / m]
#define gear_ratio                  27           // ๊ฐ์๋น?
#define motor_scale_const           2866.24203822    // gear_ratio * 60 / distance_per_rev




void calculate_wheel_vel(float linear, float angular, float *left_rpm,  float *right_rpm);
