
#ifndef IMAGEPROCESSOR_HPP
#define	IMAGEPROCESSOR_HPP

#include <opencv2/core/core.hpp>

#include "MLP.hpp"
#include "ArtelabDataset.hpp"
#include "accuracy.hpp"

namespace artelab
{
    class ImageProcessor 
    {
    public:

        ImageProcessor(std::string mlp_file, cv::Size win_size, std::string outdir="", bool show=false);
        virtual ~ImageProcessor();

        ImageProcessor& show(bool b=true);
        ImageProcessor& set_output(std::string outdir);

        results process(ArtelabDataset::barcode_image barcode);

    private:

        MLP _mlp;
        cv::Size _winsize;
        bool _show;
        DirectoryInfo _output;
        
        void show_image(std::string name, cv::Mat img);
    };

}
    
#endif	/* IMAGEPROCESSOR_HPP */

