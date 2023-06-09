#!/usr/bin/bash
#sudo apt install libopencv-{core,highgui,ml}-dev libboost-filesystem-dev libboost-chrono-dev libboost-program-options-dev 
grep -lr '#include <opencv2/#include <opencv2/ s,opencv2/[^/]*/,opencv2/,' 
grep -Flr -- '-Iinclude' $(find . -type f -name 'Makefile*') | while read -r fn; do
  if ! grep -Fq -- '-I/usr/include/opencv4'; then
    echo "$fn"
  fi
done | xargs -r sed -i -e '/-Iinclude/ s,-Iinclude,-Iinclude -I/usr/include/opencv4,'

replacements=(
  CV_GRAY2BGR cv::COLOR_GRAY2BGR 
  CV_RETR_TREE cv::RetrievalModes::RETR_TREE 
  CV_CHAIN_APPROX_SIMPLE cv::CountourApproximationModes::CHAIN_APPROX_SIMPLE 
  CV_LOAD_IMAGE_GRAYSCALE cv::IMREAD_GRAYSCALE
  CV_LOAD_IMAGE_COLOR cv::IMREAD_COLOR 
)
for i in in $(seq 0 2 $(("${#replacements[@]}" - 1))); do
  from="${replacements[$i]}"
  to="${replacements[$((i+1))]}"
  echo "# $from -> $to" >&2
  grep -lr "$from" | grep -v $(basename "$0") 
  grep -lr "$from" | grep -v $(basename "$0") | xargs -r sed -i -e "/$from/ s/$from/$to/g"
done
