#include <string>
#include <iostream>
#include <fstream>

#include <QApplication>

#include <boost/program_options.hpp>
auto readInputArgs(const int argc, char* argv[]){
    namespace po = boost::program_options;
    using pair = std::pair<std::string, std::string>;

    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message.")
        ("input,i", po::value<std::string>(), "set input image.")
        ("output,o", po::value<std::string>(), "set output image.");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return pair(std::string(), std::string());
    }

    std::string inputImage, outputImage;
    if(vm.count("input")){
        inputImage = vm["input"].as<std::string>();
    }
    if(vm.count("output")){
        outputImage = vm["output"].as<std::string>();
    }

    return pair(inputImage, outputImage);
}
#include "Encoder.hpp"

#include "maindialog.h"
#include "ImageReader.hpp"

int
main(int argc, char* argv[]){
    auto args = readInputArgs(argc, argv);
    if(args.first.empty() && args.second.empty()){
        QApplication a(argc, argv);
        mainDialog w;
        w.show();
        return a.exec();
    }else{
        Timer t;
        std::cout << "Reading " << args.first << std::endl;

        BaseImage im(args.first);
        im.convert();
        im.save(args.second);

        std::cout << "Done!\nIt take " << t.end<std::chrono::milliseconds>() << " ms\n";
    }
    return 0;
}
