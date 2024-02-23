#include "imgcodecs.h"

// Image
Mat Image_IMRead(const char* filename, int flags) {
    cv::Mat img = cv::imread(filename, flags);
    return new cv::Mat(img);
}


bool Image_IMWrite(const char* filename, Mat img) {
    return cv::imwrite(filename, *img);
}

bool Image_IMWrite_WithParams(const char* filename, Mat img, IntVector params) {
    std::vector<int> compression_params;

    for (int i = 0, *v = params.val; i < params.length; ++v, ++i) {
        compression_params.push_back(*v);
    }

    return cv::imwrite(filename, *img, compression_params);
}

void Image_IMEncode(const char* fileExt, Mat img, void* vector, char** errMsg) {
    std::string error;
    try {
        auto vectorPtr = reinterpret_cast<std::vector<uchar> *>(vector);
        cv::imencode(fileExt, *img, *vectorPtr);
    } catch (const std::exception& e) {
        error = e.what();
    } catch (...) {
        error = "Caught unknown exception";
    }

    // If an error occurred, copy the error message to errMsg
    if (!error.empty()) {
        *errMsg = strdup(error.c_str());
    }
}

void Image_IMEncode_WithParams(const char* fileExt, Mat img, IntVector params, void* vector, char** errMsg) {
    std::string error;
    try {
        auto vectorPtr = reinterpret_cast<std::vector<uchar> *>(vector);
        std::vector<int> compression_params;

        for (int i = 0, *v = params.val; i < params.length; ++v, ++i) {
            compression_params.push_back(*v);
        }

        cv::imencode(fileExt, *img, *vectorPtr, compression_params);
    } catch (const std::exception& e) {
        error = e.what();
    } catch (...) {
        error = "Caught unknown exception";
    }

    // If an error occurred, copy the error message to errMsg
    if (!error.empty()) {
        *errMsg = strdup(error.c_str());
    }
}

Mat Image_IMDecode(ByteArray buf, int flags, char** errMsg) {
    std::string error;
    try {
        std::vector<uchar> data(buf.data, buf.data + buf.length);
        cv::Mat img = cv::imdecode(data, flags);
        return new cv::Mat(img);
    } catch (const std::exception& e) {
        error = e.what();
    } catch (...) {
        error = "Caught unknown exception";
    }

    // If an error occurred, copy the error message to errMsg
    if (!error.empty()) {
        *errMsg = strdup(error.c_str());
    }

    return new cv::Mat();
}

void Image_IMDecodeIntoMat(ByteArray buf, int flags, Mat dest) {
    std::vector<uchar> data(buf.data, buf.data + buf.length);
    cv::imdecode(data, flags, dest);
}
