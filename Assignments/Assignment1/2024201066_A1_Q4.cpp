#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
using namespace cv;
using namespace std;

    template<typename T>
    class MyVect {

    private:
        T* data; 
        size_t size; 
        size_t cap; 

        // Resize the array with new array and delete old array
        void resize(size_t newCap) {
            T* newData = new T[newCap]; 
            for (size_t i = 0; i < size; i++) {
                newData[i] = data[i]; 
            }
            delete[] data; 
            data = newData; 
            cap = newCap; 
        }

    public:
        // Default constrctor
        MyVect() {
            data = nullptr; 
            size = 0;       
            cap = 0;   
        }

        // Constructor with initialsation of size parameter
        explicit MyVect(size_t init) {
            size = init;  
            cap = init; 
            data = new T[cap]; 

            // Initialize elements to default value for type
            for (size_t i = 0; i < size; i++) {
                data[i] = T(); // Default constructor of T type
            }
        }

        // Destructor
        ~MyVect() {
            delete[] data; //  Free/release the allocated memory
        }

        // fetch the current size of My vector
        size_t getSize() const {
            return size; 
        }

        // Accessing  element by indexes
        T& operator[](size_t ind) {
            if (ind >= size) {
                throw out_of_range("Index out of bounds, check range of array."); 
            }
            return data[ind]; 
        }

        // Accessing element by index const keyword to restrict to size for My Vector
        const T& operator[](size_t ind) const {
            if (ind >= size) {
                throw out_of_range("Index are out of bounds, check range of array."); 
            return data[ind]; 
            }
        }

        // Add an element to the end of the My vector
        void pushBack(const T& val) {
            // Check if we need more space/ resize
            if (size == cap) {
                size_t newCap = cap == 0 ? 1 : cap * 2; // Double the capacity if full to resize
                resize(newCap);
            }
            data[size] = val; 
            ++size;
        }

        // Clear all the stored elements in My Vector
        void clear() {
            size = 0; 
        }
    };
    
        
    const int VERTICAL = 0;
    const int  HORIZONTAL = 1;
    const int seamDisplayTime = 45;
    const string windowName = "SEAM-CARVING";

    // This function finds the vertical direction seam in image with the lowest energy
    MyVect<int> getVerticalSeam(Mat& energyMat) {
        int rows = energyMat.rows;
        int cols = energyMat.cols;
        Mat pathCost(rows, cols, CV_64F, Scalar(DBL_MAX));
        Mat backtrackSeam(rows, cols, CV_32S, Scalar(-1));
        int dcol[3] = {-1, 0 , 1};

        // Initializes only the first row of the pathCost matrix with the energy values
        for (int j = 0; j < cols; ++j) {
            pathCost.at<double>(0, j) = energyMat.at<uchar>(0, j);
        }
        // Iterating to fill backtrackSeam matrix and the remaining values of pathCost
        for (int i = 1; i < rows; i++) {
            for (int j = 0; j < cols; j++) {

                double minmCost = DBL_MAX; 
                for (int k = 0; k < 3; k++) {
                    int dcolm = j + dcol[k]; 
                    if (dcolm >= 0 && dcolm < cols) {
                        if( pathCost.at<double>(i - 1, dcolm) < minmCost ) {
                            minmCost = pathCost.at<double>(i - 1, dcolm);
                            backtrackSeam.at<int>(i, j) = dcolm;
                        }
                    }
                }
                pathCost.at<double>(i, j) = minmCost + energyMat.at<uchar>(i, j);
            }
        }

        // Tracing back to find the minimum seam path
        MyVect<int> seamTrace(rows);
        int minCol = 0;
        double minVal = DBL_MAX;

        // finding min value in last row
        for (int j = 0; j < cols; ++j) {
            if (pathCost.at<double>(rows - 1, j) < minVal) {
                minVal = pathCost.at<double>(rows - 1, j);
                minCol = j;
            }
        }
        // finding min path from min value of last row
        for (int i = rows - 1; minCol != -1 && i >= 0; --i) {
            seamTrace[i] = minCol;
            minCol = backtrackSeam.at<int>(i, minCol);
        }

        return seamTrace;
    }

    // This function identifies the horizontal direction seam in image with the lowest energy
    MyVect<int> getHorizontalSeam(Mat& energyMat) {
        int rows = energyMat.rows;
        int cols = energyMat.cols;

        Mat pathCost(rows, cols, CV_64F, Scalar(DBL_MAX));
        Mat backtrackSeam(rows, cols, CV_32S, Scalar(-1));
        int drow[3] = {-1, 0 , 1};

        // Initializes only the first row of the pathCost matrix with the energy values
        for (int i = 0; i < rows; ++i) {
            pathCost.at<double>(i, 0) = energyMat.at<uchar>(i, 0);
        }

        // Iterating to fill backtrackSeam matrix and the remaining values of pathCost
        for (int j = 1; j < cols; j++) {
            for (int i = 0; i < rows; i++) {
                
                double minmCost = DBL_MAX; 
                for (int k = 0; k < 3; k++) {
                     int droww = i + drow[k]; 

                    if (droww >= 0 && droww < rows) {
                        if( pathCost.at<double>(droww, j - 1) < minmCost ) {
                            minmCost = pathCost.at<double>(droww, j - 1);
                            backtrackSeam.at<int>(i, j) = droww;
                        }
                    }
                }
                pathCost.at<double>(i, j) = minmCost + energyMat.at<uchar>(i, j);
            }
        }


        // Tracing back to find the minimum seam path
        MyVect<int> seamTrace(cols);
        int minRow = 0;
        double minVal = DBL_MAX;
        for (int i = 0; i < rows; i++) {
            if (pathCost.at<double>(i, cols - 1) < minVal) {
                minVal = pathCost.at<double>(i, cols - 1);
                minRow = i;
            }
        }

        for (int j = cols - 1; j >= 0; j--) {
            seamTrace[j] = minRow;
            minRow = backtrackSeam.at<int>(minRow, j);
        }

        return seamTrace;
    }

    // This function calculates the energy of an image using the Sobel operator
    Mat getEnergyImgFromSobel( Mat& image) {
        Mat gray, grad_x, grad_y, abs_grad_x, abs_grad_y, energyMat;

        // Converts the image to grayscale image
        cvtColor(image, gray, cv::COLOR_BGR2GRAY);

        // Computes the image gradients in the x and y direction
        Sobel(gray, grad_x, CV_64F, 1, 0, 3);
        Sobel(gray, grad_y, CV_64F, 0, 1, 3);

        // Gets the absolute values of gradients
        convertScaleAbs(grad_x, abs_grad_x);
        convertScaleAbs(grad_y, abs_grad_y);

        // Combines both gradients to create an energy map
        addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, energyMat);
        return energyMat;
    }

    // This function eliminates a specified seam from the image and marks it in yellow for visualization
    Mat delTargetSeam(Mat& image, MyVect<int>& seamTrace, int isHorizontal) {
        int rows = image.rows;
        int cols = image.cols;
        Mat resizedImg(rows - isHorizontal, cols - 1 + isHorizontal, image.type());
        Mat intermediateImg = image.clone(); 

        if(!isHorizontal){
            for (int i = 0; i < rows; i++) {
                int seamCol = seamTrace[i];
                
                // Highlight the seam in Orange
                intermediateImg.at<Vec3b>(i, seamCol) = Vec3b(0, 125, 245); //Orange  BGR

                // Copy the left and right sections/parts of the row except the low energy part to remove the seam
                if (seamCol > 0) {
                    Mat leftPart(image.row(i).colRange(0, seamCol));
                    Mat tempTarget = resizedImg.row(i).colRange(0, seamCol);
                    leftPart.copyTo(tempTarget);
                }
                if (seamCol < cols - 1) {
                    Mat rightPart(image.row(i).colRange(seamCol + 1, cols));
                    Mat tempTarget = resizedImg.row(i).colRange(seamCol, cols - 1);
                    rightPart.copyTo(tempTarget);
                }
            }
        }
        else {
            for (int j = 0; j < cols; ++j) {
                int seamRow = seamTrace[j];
                
                // Highlight the seam in yellow
                intermediateImg.at<Vec3b>(seamRow, j) = Vec3b(1, 225, 245); // Yellow BGR code, plain yellow: (0, 255, 255); 

                // Copy up and down parts of the column except the low energy part to remove the seam
                if (seamRow > 0) {
                    Mat upPart(image.rowRange(0, seamRow).col(j));
                    Mat tempTarget = resizedImg.rowRange(0, seamRow).col(j);
                    upPart.copyTo(tempTarget);
                }
                if (seamRow < rows - 1) {
                    Mat downPart(image.rowRange(seamRow + 1, rows).col(j));
                    Mat tempTarget = resizedImg.rowRange(seamRow, rows - 1).col(j);
                    downPart.copyTo(tempTarget);
                }
            }
        }

        // Shows the image with highlighted seam.
        imshow(windowName, intermediateImg);
        waitKey(seamDisplayTime); 

        return resizedImg;
    }
    
    // This function manages the complete seam carving process to resize the image
    Mat processSeam(Mat &image, int isHorizonal ) { 
        Mat energyMat = getEnergyImgFromSobel(image);
        MyVect<int> seamTrace = isHorizonal? getHorizontalSeam(energyMat) : getVerticalSeam(energyMat);
        return delTargetSeam(image,seamTrace, isHorizonal);
    }
    

    int main(int argc, char** argv) {
        
        // Display Usage Syntax for wrong input format
        if (!(argc == 5 || argc ==4)) {
            cerr << "Usage Syntax: " << argv[0] << " <InputImage Path/Name> <OutputImage Path/Name> <NewWidth> <NewHeight>  " << endl 
            << "    OR" << endl << "       "<< argv[0] <<  "<InputImage Path/Name> <OutputImage Path/Name> <NewWidth> 0  " <<  endl 
            << "    OR" << endl << "       "<< argv[0] <<  "<InputImage Path/Name> <OutputImage Path/Name> 0 <NewHeight> " <<  endl ;
            exit(EXIT_FAILURE);
        }

        string inputImagePath = argv[1];
        string outputImagePath = argv[2];

        int newWidth = stoi(argv[3]);
        int newHeight = argv[4] == NULL? 0 : stoi(argv[4]);
        
        // Displays valid input values
        if(newWidth || newHeight){
            cout<<"INPUTS: " ; 
            if(newWidth) 
                cout<<"  New Width= " << newWidth;
            if(newHeight) 
                cout<<  "   New Hieght= "  << newHeight ;
            cout<< endl;
        }

        // exits if input dimensions are invalid ( negative or both zero)
        if(!(newHeight>=0 && newWidth>=0) || (newHeight==0 && newWidth==0)) {
            cerr << "Could not resize for given inputs: width or heigth!" << endl;
            exit(EXIT_FAILURE);
        }

        // Loading the image
        Mat image = imread(inputImagePath, IMREAD_COLOR);
        if (image.empty()) {
            cerr << "Could not open or find the image!" << endl;
            exit(EXIT_FAILURE);
        } 
        else if(image.rows <= 0 || image.cols <= 0) {
            cerr << "Check image dimensions it looks W or H is not a positive value or image maybe currupted!" << endl;
            exit(EXIT_FAILURE);
        }

        // Some sanity checks on given input dimensions
        if( newWidth > 0 && newHeight > 0 && ( ((newHeight*newWidth*1.0) /  (image.rows*image.cols))*100 <= 40) ) {
            cout << "Input dimensions of new image is within 40% size of original Image, content may be lost but still resizing!" << endl;
        }
        else if( (newHeight<= 0 && ((((newWidth*1.0) / image.cols)*100)  <= 35.0 )) || (newWidth<= 0 && ((((newHeight*1.0) / image.rows)*100)  <= 35.0 ))) { 
            cout << "Input width of new image is within 35% size of original Image, content may be lost but still resizing!" << endl;
        }


        if(newWidth <= 0 )
            newWidth = image.cols + 1;

        if(newHeight <= 0)
            newHeight = image.rows + 1;
        

        if(newHeight >= image.rows && newWidth >= image.cols)
            cout << "Input dimensions are more than or equal to dimension of original Image, No Operation is done!" << endl;
        else if(newHeight >= image.rows && newWidth < image.cols ) {
            cout << "Input newHeight is more than or equal to Height of original Image, Only Width resize Operation will happen!" << endl;
        }
        else if(newWidth >= image.cols && newHeight < image.rows) {
            cout << "Input newWidth is more than or equal to Width of original Image, Only Height resize Operation will happen!" << endl;   
        }

        // Resize the image to the new height and width using seam carving
        while (image.rows > newHeight || image.cols > newWidth) {
            if (image.cols > newWidth) {
                image = processSeam(image, VERTICAL);
            }
            if (image.rows > newHeight) {
                image = processSeam(image, HORIZONTAL);
            }
        }
        

        // writing and displaying final image once it is ready
        imwrite(outputImagePath, image);
        imshow(windowName, image);
        // Waiting to press a key or exit once final image is ready
        waitKey(0);
        
        return 0;
    } 

/**********************************************************************
 
        For compilation use below command 
        g++ 2024201066_A1_Q4.cpp -o seam_carving -I/usr/local/include/opencv4 -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc
        (OR)
        make

        For execution:

************************************************************************/