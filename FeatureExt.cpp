#include <QCoreApplication>
#include <cv.h>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/nonfree//nonfree.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/nonfree/features2d.hpp>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <string>

using namespace cv;
using namespace std;

const string DATASET("/home/hagar13/Desktop/Dataset");
const int images_count = 2;

int main(int argc, const char* argv[])
{
        // you need to add the path to the dataset and the count of images to the arguments
        std::string dataset_directory;
        int count;

        if (argc > 1)
        {
            dataset_directory = argv[1];
            count = atoi(argv[2]);
        }
        else
        {
            dataset_directory = DATASET;
            count = images_count;
        }

        for (int i=1; i<= count; ++i)
        {
            // assuming file names are in the structure img1.jpeg , img2.jpeg,...
            stringstream ss2;
            ss2 << i;
            string str2 = ss2.str();
            string name = dataset_directory + "/img"+ str2+ ".jpeg";
          //  sprintf(name,"/home/hagar13/Desktop/Dataset/img%d.jpeg",i);
            Mat img = imread( name, CV_LOAD_IMAGE_ANYCOLOR);


            // SURF dectector, faster than SIFT
            int minHessian = 600;   //a threshold to decide from which value you are willing to accept keypoints. Inversely proportional to the number of keypoints you get

            SurfFeatureDetector SURFdetector( minHessian );

            std::vector<KeyPoint> SURF_keypoints;

            SURFdetector.detect( img, SURF_keypoints );


            //-- Draw keypoints
            Mat SURF_output;
            drawKeypoints( img, SURF_keypoints, SURF_output, Scalar::all(-1), DrawMatchesFlags::DEFAULT );

            // to access the feature properties
            for (int i=0; i< SURF_keypoints.size() ; i++){
                cout<<"Angle of the keypoint: "<<SURF_keypoints.at(i).angle<<endl;
                cout<<"Coordinates of the keypoint: "<<SURF_keypoints.at(i).pt<<endl;
                cout<<"Diameter of the keypoint neighbourhood: "<<SURF_keypoints.at(i).size<<endl;
                cout<<"At reponse: "<<SURF_keypoints.at(i).response<<endl;   //the response by which the most strong keypoints have been selected. Can be used for the further sorting or subsampling
            }

            // SIFT detector, slower with more features detected
            SiftFeatureDetector SIFTdetector;
            std::vector<cv::KeyPoint> SIFT_keypoints;
            SIFTdetector.detect(img, SIFT_keypoints);

            cv::Mat SIFT_output;
            drawKeypoints(img, SIFT_keypoints, SIFT_output , Scalar::all(-1), DrawMatchesFlags::DEFAULT);


            /*** SURF feature descriptors ***/
            SurfDescriptorExtractor extractor;
            Mat descriptors;
            extractor.compute( img, SURF_keypoints, descriptors);
            /********************************/

            cout<<"SURF Number of features:"<<SURF_keypoints.size()<<endl;
            cout<<"SIFT Number of features: "<<SIFT_keypoints.size()<<endl;

            //show detected keypoints on the image
            imshow("SURF Result", SURF_output);
            imshow("SIFT Result", SIFT_output);

            waitKey(0);

            // writing feature points into files to be saved, in case you need them somewhere else.
            string fileName = dataset_directory + "/feature" + str2 + ".txt";
            std::ofstream outfile (fileName.c_str());
            for(int i = 0 ; i< SURF_keypoints.size() ; i++){
                outfile << SURF_keypoints.at(i).pt<<endl;
            }

        }
    return 0;
}
