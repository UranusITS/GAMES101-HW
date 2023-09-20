#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>

std::vector<cv::Point2f> control_points;

void mouse_handler(int event, int x, int y, int flags, void *userdata) 
{
    if (event == cv::EVENT_LBUTTONDOWN && control_points.size() < 4) 
    {
        std::cout << "Left button of the mouse is clicked - position (" << x << ", "
        << y << ")" << '\n';
        control_points.emplace_back(x, y);
    }     
}

void naive_bezier(const std::vector<cv::Point2f> &points, cv::Mat &window) 
{
    auto &p_0 = points[0];
    auto &p_1 = points[1];
    auto &p_2 = points[2];
    auto &p_3 = points[3];

    for (double t = 0.0; t <= 1.0; t += 0.001) 
    {
        auto point = std::pow(1 - t, 3) * p_0 + 3 * t * std::pow(1 - t, 2) * p_1 +
                 3 * std::pow(t, 2) * (1 - t) * p_2 + std::pow(t, 3) * p_3;

        window.at<cv::Vec3b>(point.y, point.x)[2] = 255;
    }
}

cv::Point2f recursive_bezier(const std::vector<cv::Point2f> &control_points, float t) 
{
    // TODO: Implement de Casteljau's algorithm
    std::vector<cv::Point2f> points(control_points);
    while (points.size() > 1)
    {
        std::vector<cv::Point2f> next_points;
        for (unsigned int i = 1; i < points.size(); i++)
        {
            const cv::Point2f &pre_point = points[i - 1];
            const cv::Point2f &post_point = points[i];
            next_points.push_back(pre_point + t * (post_point - pre_point));
        }
        points = next_points;
    }
    return points[0];
}

float sigmoid(float x)
{
    return 1 / (1 + expf(-x));
}

void bezier(const std::vector<cv::Point2f> &control_points, cv::Mat &window) 
{
    // TODO: Iterate through all t = 0 to t = 1 with small steps, and call de Casteljau's 
    // recursive Bezier algorithm.
    for (double t = 0.0; t <= 1.0; t += 0.001) 
    {
        cv::Point2f point = recursive_bezier(control_points, t);
        // window.at<cv::Vec3b>(point.y, point.x)[1] = 255;

        for (int dx = 0; dx <= 1; dx++)
            for (int dy = 0; dy <= 1; dy++)
            {
                int x = point.x + dx;
                int y = point.y + dy;
                float dis = sqrt((point.x - x) * (point.x - x) + (point.y - y) * (point.y - y));
                int color = std::max(0.f, 255 * (2 - 2 * sigmoid(dis * 3)));
                if (255 - window.at<cv::Vec3b>(y, x)[1] > color)
                    window.at<cv::Vec3b>(y, x)[1] = window.at<cv::Vec3b>(y, x)[1] + color;
                else
                    window.at<cv::Vec3b>(y, x)[1] = 255;
            }
    }

}

int main() 
{
    cv::Mat window = cv::Mat(700, 700, CV_8UC3, cv::Scalar(0));
    cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
    cv::namedWindow("Bezier Curve", cv::WINDOW_AUTOSIZE);

    cv::setMouseCallback("Bezier Curve", mouse_handler, nullptr);

    int key = -1;
    while (key != 27) 
    {
        for (auto &point : control_points) 
        {
            cv::circle(window, point, 3, {255, 255, 255}, 3);
        }

        if (control_points.size() == 4) 
        {
            // naive_bezier(control_points, window);
            bezier(control_points, window);

            cv::imshow("Bezier Curve", window);
            cv::imwrite("my_bezier_curve.png", window);
            key = cv::waitKey(0);

            return 0;
        }

        cv::imshow("Bezier Curve", window);
        key = cv::waitKey(20);
    }

return 0;
}
