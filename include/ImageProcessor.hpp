
#ifndef IMAGEPROCESSOR_HPP
#define	IMAGEPROCESSOR_HPP

#include <opencv2/core.hpp>

#include "MLP.hpp"
#include "ArtelabDataset.hpp"
#include "accuracy.hpp"

namespace artelab
{
    class ImageProcessor
    {
    public:

        ImageProcessor(std::string mlp_file, cv::Size win_size, std::string outdir="", bool quiet=false);
        virtual ~ImageProcessor();

        ImageProcessor& show(bool b=true);
        ImageProcessor& set_output(std::string outdir);

        results process(std::string imagename, ArtelabDataset::barcode_image barcode);

    private:

        MLP _mlp;
        cv::Size _winsize;
        DirectoryInfo _output;
        bool _show;
        bool _quiet;
    };

}

#endif	/* IMAGEPROCESSOR_HPP */
