/* 
 * File:   HoughTransform.hpp
 * Author: simone
 *
 * Created on 22 maggio 2013, 12.38
 */

#ifndef HOUGHTRANSFORM_HPP
#define	HOUGHTRANSFORM_HPP

#include <opencv2/core/core.hpp>

class HoughTransform 
{
public:
    
    struct CmpPoint2i
    {
        bool operator()(cv::Point2i const& left, cv::Point2i const& right) const;
    };
    
    typedef std::vector<cv::Point2i> points;
    
    HoughTransform();
    HoughTransform(cv::Mat image, bool keep_locations=false);
    virtual ~HoughTransform();
    HoughTransform(const HoughTransform& orig);
    
    HoughTransform& operator=(const HoughTransform& other);
    
    void compute_hough(cv::Mat image, bool keep_locations=false);
    
    cv::Mat get_hough_image(int threshold=0);
    cv::Size get_hough_space_size();
    uint get(int theta, int rho);
    points get_points_at(int theta, int rho);
    
    cv::Mat hough_space;
    
private:
    
    typedef std::map<cv::Point2i, points, CmpPoint2i> locationsmap;
    
    bool _keep_loc;
    cv::Size _size;
    locationsmap _locations;
    
    int _max_theta;
    double _theta_step;
    
    double* sin_cache;
    double* cos_cache;
    
    void init();
    void add_point(int, int);
    void store_location(int,int,int,int);
};

#endif	/* HOUGHTRANSFORM_HPP */
