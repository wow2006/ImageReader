// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <string>
#include <iostream>
#include <boost/program_options.hpp>

#include <QApplication>
#include "Encoder.hpp"

#include "maindialog.h"

auto readInputArgs(const int argc, char* argv[]) {
  namespace po = boost::program_options;
  using pair = std::pair<std::string, std::string>;

  // Declare the supported options.
  po::options_description desc("Allowed options");
  desc.add_options()("help", "produce help message.")(
      "input,i", po::value<std::string>(), "set input image.")(
      "output,o", po::value<std::string>(), "set output image.");

  po::variables_map variables_map;
  po::store(po::parse_command_line(argc, argv, desc), variables_map);
  po::notify(variables_map);

  if (variables_map.count("help") != 0u) {
    std::cout << desc << "\n";
    return pair(std::string(), std::string());
  }

  std::string inputImage, outputImage;
  if (variables_map.count("input") != 0u) {
    inputImage = variables_map["input"].as<std::string>();
  }
  if (variables_map.count("output") != 0u) {
    outputImage = variables_map["output"].as<std::string>();
  }

  return pair(inputImage, outputImage);
}

int main(int argc, char* argv[]) {
  auto args = readInputArgs(argc, argv);
  int returnCode = 0;
  if (args.first.empty() && args.second.empty()) {
    QApplication application(argc, argv);
    mainDialog widget;
    widget.show();
    returnCode = application.exec();
  } else {
    Timer timer;
    std::cout << "Reading " << args.first << std::endl;

    BaseImage image(args.first);
    image.convert();
    image.save(args.second);

    std::cout << "Done!\nIt take " << timer.end<std::chrono::milliseconds>()
              << " ms\n";
  }
  return returnCode;
}
