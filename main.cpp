
#include <fstream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/program_options.hpp>

#include "ImageProcessor.hpp"

#define foreach BOOST_FOREACH

using namespace artelab;
using std::string;
using std::cout;
using std::flush;
using std::endl;
using std::vector;
namespace po = boost::program_options;

bool quiet = false;
string input_file = "";
string netfile = "net61x3.net";
string outdir = "";


int main(int argc, char** argv)
{
    po::options_description desc("Usage");
    desc.add_options()
        ("help", "print help")
        ("input,i",       po::value<string>()->default_value("input.png"),      "input file")
        ("netfile,n",       po::value<string>()->default_value(netfile),         "trained network file")
        ("quiet,q",                                                              "suppress verbose output")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        cout << desc << endl;
        return EXIT_SUCCESS;
    }

    input_file = vm["input"].as<string>();
    outdir = vm["output"].as<string>();
    quiet = vm.count("quiet") > 0;
    netfile = vm["netfile"].as<string>();

    cv::Size win_size(61, 3);

    double time = 0;
    int count = 0;

    ImageProcessor pr(netfile, win_size, outdir, quiet);

    results res = pr.process(input_file);

    time += res.time;

    cout << endl
         << "Number of images: " << count << endl
         << "Average time (sec): " << time/count << endl;

    return EXIT_SUCCESS;
}
