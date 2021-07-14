#include "listener.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "mw_ahrs");
    ros::NodeHandle n;

    ros::Publisher chatter_pub = n.advertise<sensor_msgs::Imu>("imu", 10);

    serial_port = open("/dev/AHRS", O_RDWR);

    struct termios tty;

    if (tcgetattr(serial_port, &tty) != 0)
    {
        printf("Error %i from tcgetattr: %d\n", errno, strerror(errno));
        return -1;
    }

    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;

    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO;
    tty.c_lflag &= ~ECHOE;
    tty.c_lflag &= ~ECHONL;
    tty.c_lflag &= ~ISIG;
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);

    tty.c_oflag &= ~OPOST;
    tty.c_oflag &= ~ONLCR;

    tty.c_cc[VTIME] = 10;
    tty.c_cc[VMIN] = 0;

    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    if (tcsetattr(serial_port, TCSANOW, &tty) != 0)
    {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return -1;
    }

    imu.orientation_covariance = {0.0025, 0, 0, 0, 0.0025, 0, 0, 0, 0.0025};
    imu.angular_velocity_covariance = {0.02, 0, 0, 0, 0.02, 0, 0, 0, 0.02};
    imu.linear_acceleration_covariance = {0.04, 0, 0, 0, 0.04, 0, 0, 0, 0.04};

    imu.linear_acceleration.x = 0;
    imu.linear_acceleration.y = 0;
    imu.linear_acceleration.z = 0;

    imu.angular_velocity.x = 0;
    imu.angular_velocity.y = 0;
    imu.angular_velocity.z = 0;

    imu.orientation.w = 0;
    imu.orientation.x = 0;
    imu.orientation.y = 0;
    imu.orientation.z = 0;

    while (ros::ok())
    {
        ros::Rate rate(12);

        while (rx_count < 13)
        {
            read(serial_port, &buff,1);

            if(buff == STX) rx_flag = true;

            if(rx_flag == true) buff_arrey[rx_count++] = buff;
        }
        rx_flag = false;
        rx_count = 0;
        cs = 0;

        if (buff_arrey[0] == STX && buff_arrey[2] == DeviceID && buff_arrey[3] == Command && buff_arrey[12] == ETX)
        {
            for (int i = 2; i < 11; ++i)
            {
                cs += buff_arrey[i];
            }

            if (cs == buff_arrey[11])
            {
                switch (buff_arrey[4])
                {
                    case ACC:
                        acc_x = (buff_arrey[5] | buff_arrey[6] << 8);
                        acc_y = (buff_arrey[7] | buff_arrey[8] << 8);
                        acc_z = (buff_arrey[9] | buff_arrey[10] << 8);

                        imu.linear_acceleration.x = acc_x / 1000.0 * 0.01745;
                        imu.linear_acceleration.y = acc_y / 1000.0 * 0.01745;
                        imu.linear_acceleration.z = acc_z / 1000.0 * 0.01745;
                        break;

                    case GYO:
                        gyo_x = (buff_arrey[5] | buff_arrey[6] << 8);
                        gyo_y = (buff_arrey[7] | buff_arrey[8] << 8);
                        gyo_z = (buff_arrey[9] | buff_arrey[10] << 8);

                        imu.angular_velocity.x = gyo_x / 10.0 * 0.01745;
                        imu.angular_velocity.y = gyo_y / 10.0 * 0.01745;
                        imu.angular_velocity.z = gyo_z / 10.0 * 0.01745;
                        break;

                    case DEG:
                        deg_x = (buff_arrey[5] | buff_arrey[6] << 8);
                        deg_y = (buff_arrey[7] | buff_arrey[8] << 8);
                        deg_z = (buff_arrey[9] | buff_arrey[10] << 8);

                        float x = deg_x / 100.0;
                        float y = deg_y / 100.0;
                        float z = deg_z / 100.0;

                        imu.orientation.w = (COS(x) * COS(y) * COS(z)) + (SIN(x) * SIN(y) * SIN(z));
                        imu.orientation.x = (COS(x) * COS(y) * SIN(z)) - (SIN(x) * SIN(y) * COS(z));
                        imu.orientation.y = (COS(x) * SIN(y) * COS(z)) + (SIN(x) * COS(y) * SIN(z));
                        imu.orientation.z = (SIN(x) * COS(y) * COS(z)) - (COS(x) * SIN(y) * SIN(z));
                        break;
                }
            }
        }
        imu.header.frame_id = "imu_link";
        imu.header.stamp = ros::Time::now();

        chatter_pub.publish(imu);
        
        rate.sleep();
    }
    return 0;
}
