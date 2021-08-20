#define wheel_to_wheel_d            0.337       // ë°”í€´ì? ë°”í€?ê°?ê±°ë¦¬  [m]
#define distance_per_rev            0.5652        // ?œë°”???Œì „???´ë™ ê±°ë¦¬ [m / rev]
#define pulse_per_rev               54000        // ?œë°”???Œì „???”ì½”???„ìŠ¤ ì¹´ìš´????ê°’ì? ë¶€ì°©ëœ ?”ì½”?”ì? ê°ì†ê¸°ë? ê³ ë ¤???•í•´ì§„ë‹¤.) [pulse / rev] 
#define pulse_per_distance          95541.4012739    // 1m ?´ë™???”ì½”???„ìŠ¤ ì¹´ìš´??[pulse / m]
#define gear_ratio                  27           // ê°ì†ë¹?
#define motor_scale_const           106.1032954



void calculate_wheel_vel(float linear, float angular, float *left_rpm,  float *right_rpm);
