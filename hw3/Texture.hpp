//
// Created by LEI XU on 4/27/19.
//

#ifndef RASTERIZER_TEXTURE_H
#define RASTERIZER_TEXTURE_H
#include "global.hpp"
#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>
class Texture{
private:
    cv::Mat image_data;

public:
    Texture(const std::string& name)
    {
        image_data = cv::imread(name);
        cv::cvtColor(image_data, image_data, cv::COLOR_RGB2BGR);
        width = image_data.cols;
        height = image_data.rows;
    }

    int width, height;

    Eigen::Vector3f getColor(float u, float v)
    {
        auto u_img = u * width;
        auto v_img = (1 - v) * height;
        auto color = image_data.at<cv::Vec3b>(v_img, u_img);
        return Eigen::Vector3f(color[0], color[1], color[2]);
    }

    Eigen::Vector3f getColorBilinear(float u, float v)
    {
        if (u <= 0 || u >= 1 || v <= 0 || v >= 1)
            return Eigen::Vector3f(0, 0, 0);

        float u_img = u * width;
        float v_img = (1 - v) * height;

        int u00_u = u * width;
        int u00_v = (1 - v) * height;
        auto c00 = image_data.at<cv::Vec3b>(u00_v, u00_u);

        int u01_u = u00_u;
        int u01_v = u00_v + 1;
        auto c01 = image_data.at<cv::Vec3b>(u01_v, u01_u);

        int u10_u = u00_u + 1;
        int u10_v = u00_v;
        auto c10 = image_data.at<cv::Vec3b>(u10_v, u10_u);

        int u11_u = u00_u + 1;
        int u11_v = u00_v + 1;
        auto c11 = image_data.at<cv::Vec3b>(u11_v, u11_u);

        float s = u_img - u00_u;
        float t = v_img - u00_v;

        auto c0 = c00 + s * (c10 - c00);
        auto c1 = c01 + s * (c11 - c01);

        auto color = c0 + t * (c1 - c0);
        return Eigen::Vector3f(color[0], color[1], color[2]);
    }

};
#endif //RASTERIZER_TEXTURE_H
