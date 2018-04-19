#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include<unistd.h>

int main(int argc, char **argv) {
    if(argc > 1) {
        int opt;
        std::string file_name;
        while((opt = getopt(argc, argv, "i:")) != -1) {
            switch(opt) {
                case 'i':
                    file_name = optarg;
                    break;
                default:
                    std::cout << " use: " << argv[0] << " -i filename\n";
                    exit(0);
                    break;
            }
            
        }
        cv::VideoCapture cap(file_name);
        if(!cap.isOpened()) {
            std::cerr << "Error could not open file: " << file_name << "\n";
            exit(EXIT_FAILURE);
        }
        cv::namedWindow("Example01");
        while(1) {
            cv::Mat frame;
            if(!cap.read(frame)) {
                exit(0);
            }
            cv::imshow("Example01", frame);
            char key = cv::waitKey(10);
            if(key == 'q' || key == 'Q') break;
        }
        std::cout << "Program exiting...\n";
        exit(EXIT_SUCCESS);
        
    } else {
        std::cerr << "Error requires filename...\n" << argv[0] << " filename\n";
        exit(EXIT_FAILURE);
    }
    return 0;
}
