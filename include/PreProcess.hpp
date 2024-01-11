#include "opencv2/opencv.hpp"

namespace mchand
{
    class PreProcess
    {
    public:
        static cv::Mat processInput_img(cv::Mat& origin_image);
        static int dst_width, dst_height;

    private:
        static void process_bbox(std::vector<float>& bbox);
        static cv::Mat generate_patch_image(cv::Mat& origin_img, std::vector<float> bbox);
        static cv::Mat gen_trans_from_patch_cv(float c_x, float c_y, float src_width, float src_height, float dst_width,
                                               float dst_height, bool inv);
    };
}
