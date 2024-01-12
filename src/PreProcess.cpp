#include "PreProcess.hpp"

namespace mchand
{
    int PreProcess::dst_height = 512;
    int PreProcess::dst_width = 384;

    cv::Mat PreProcess::processInput_img(cv::Mat& origin_image)
    {
        origin_image.convertTo(origin_image, CV_32F);
        // auto trans = Get_input_trans();
        std::vector<float> bbox{0, 0, origin_image.cols, origin_image.rows};
        process_bbox(bbox);
        auto res = generate_patch_image(origin_image, bbox);
        return res;
    }

    cv::Mat PreProcess::Get_output_trans( int  width,int height)
    {
        std::vector<float> bbox{0, 0,  width, height};
        process_bbox(bbox);
        auto bb_c_x = bbox[0] + 0.5f * bbox[2];
        auto bb_c_y = bbox[1] + 0.5f * bbox[3];
        auto res = gen_trans_from_patch_cv(bb_c_x, bb_c_y, bbox[2], bbox[3],  dst_width, dst_height, true);

        return res;
    }

    void PreProcess::process_bbox(std::vector<float>& bbox)
    {
        auto w = bbox[2] - 1;
        auto h = bbox[3] - 1;
        auto c_x = bbox[0] + w / 2;
        auto c_y = bbox[1] + h / 2;
        auto aspect_ratio = 0.75f;
        if (w > aspect_ratio * h)
        {
            h = w / aspect_ratio;
        }
        else if (w < aspect_ratio * h)
        {
            w = h * aspect_ratio;
        }
        bbox[2] = int(w * 1.25f);
        bbox[3] = int(h * 1.25f);
        bbox[0] = int(c_x - bbox[2] / 2);
        bbox[1] = int(c_y - bbox[3] / 2);
    }

 

    cv::Mat PreProcess::generate_patch_image(cv::Mat& origin_img, std::vector<float> bbox)
    {
        auto bb_c_x = float(bbox[0] + 0.5f * bbox[2]);
        auto bb_c_y = float(bbox[1] + 0.5f * bbox[3]);
        auto bb_width = bbox[2];
        auto bb_height = bbox[3];
        auto trans = gen_trans_from_patch_cv(bb_c_x,
                                             bb_c_y,
                                             bb_width,
                                             bb_height,
                                             dst_width,
                                             dst_height,
                                             false);
        // cv::Size ee{}
        std::vector vec(trans.ptr<float>(), trans.ptr<float>() + trans.total());
        // std::cout << trans << std::endl;
        cv::Mat dst_img;
        cv::warpAffine(origin_img, dst_img, trans, cv::Size{dst_width, dst_height});
        dst_img.convertTo(dst_img, CV_32F);
        dst_img /= 255.0f;
        return dst_img;
    };


    cv::Mat PreProcess::gen_trans_from_patch_cv(float c_x, float c_y, float src_width, float src_height,
                                                float dst_width,
                                                float dst_height, bool inv)
    {
        std::vector src_downdir = {0.f, 0.5f * src_height};
        std::vector src_rightdir = {0.5f * src_width, 0.f};
        auto src = cv::Mat(3, 2,CV_32F);
        src.at<float>(0, 0) = c_x;

        src.at<float>(0, 1) = c_y;
        src.at<float>(1, 0) = c_x + src_downdir[0];
        src.at<float>(1, 1) = c_y + src_downdir[1];
        src.at<float>(2, 0) = c_x + src_rightdir[0];
        src.at<float>(2, 1) = c_y + src_rightdir[1];

        // auto src00 = src.at<float>(0, 0);
        // auto src01 = src.at<float>(0, 1);
        // auto src10 = src.at<float>(1, 0);
        // auto src11 = src.at<float>(1, 1);
        // auto src20 = src.at<float>(2, 0);
        // auto src21 = src.at<float>(2, 1);

        auto dst = cv::Mat(3, 2,CV_32F);
        std::vector<float> dst_center{dst_width * 0.5f, dst_height * 0.5f};
        std::vector dst_downdir = {0.f, dst_height * 0.5f};
        std::vector dst_rightdir = {dst_width * 0.5f, 0.f};

        dst.at<float>(0, 0) = dst_width * 0.5f;
        dst.at<float>(0, 1) = dst_height * 0.5f;
        dst.at<float>(1, 0) = dst_width * 0.5f + dst_downdir[0];
        dst.at<float>(1, 1) = dst_height * 0.5f + dst_downdir[1];
        dst.at<float>(2, 0) = dst_width * 0.5f + dst_rightdir[0];
        dst.at<float>(2, 1) = dst_height * 0.5f + dst_rightdir[1];

        // auto dst00 = dst.at<float>(0, 0);
        // auto dst01 = dst.at<float>(0, 1);
        // auto dst10 = dst.at<float>(1, 0);
        // auto dst11 = dst.at<float>(1, 1);
        // auto dst20 = dst.at<float>(2, 0);
        // auto dst21 = dst.at<float>(2, 1);
        // auto d_type = dst.type();
        // auto s_type = src.type();
        std::vector<float> vec1(dst.ptr<float>(), dst.ptr<float>() + dst.total());
        std::vector<float> vec2(src.ptr<float>(), src.ptr<float>() + src.total());

        // cv::Point2f src_points[3]{
        //     {
        //         src.at<float>(0, 0),
        //         src.at<float>(0, 1)
        //     },
        //     {
        //         src.at<float>(1, 0),
        //         src.at<float>(1, 1)
        //     },
        //     {
        //         src.at<float>(2, 0),
        //         src.at<float>(2, 1)
        //     },
        // };
        // cv::Point2f dst_points[3]{
        //     {
        //         dst.at<float>(0, 0),
        //         dst.at<float>(0, 1)
        //     },
        //     {
        //         dst.at<float>(1, 0),
        //         dst.at<float>(1, 1)
        //     },
        //     {
        //         dst.at<float>(2, 0),
        //         dst.at<float>(2, 1)
        //     },
        // };
        if (inv)
        {
            return cv::getAffineTransform(dst, src);
        }
        else
        {
            return cv::getAffineTransform(src, dst);
        }
    };
}
