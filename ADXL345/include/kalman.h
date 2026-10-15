#ifndef KALMAN_H
#define KALMAN_H

class Kalman {
public:
    Kalman() {
        q = 0.0;
        r = 0.0;
        p = 0.0;
        x = 0.0;
    };

    /**
     * @brief Initializes the Kalman filter
     * @param q Process noise covariance
     * @param r Measurement noise covariance
     * @param p Estimation error covariance
     * @param initial_value Initial value
     */
    void init(double q, double r, double p, double initial_value) {
        this->q = q;
        this->r = r;
        this->p = p;
        this->x = initial_value;
    };

    /**
     * @brief Updates the Kalman filter with a new measurement
     * @param measurement The new measurement
     * @return The updated estimate
     */
    double update(double measurement) {
        // Prediction update
        p = p + q;

        // Measurement update
        double k = p / (p + r);
        x = x + k * (measurement - x);
        p = (1 - k) * p;

        return x;
    };

private:
    double q; // Process noise covariance
    double r; // Measurement noise covariance
    double p; // Estimation error covariance
    double x; // Value
};

#endif // KALMAN_H