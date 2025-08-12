#include <opencv2/opencv.hpp>
#include <iostream>

// --- Simple reversible PRNG (xorshift32) ---
uint32_t xorshift32(uint32_t &state) {
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Usage: ./chall1 input.mp4 output.avi\n";
        return 1;
    }

    std::string inputPath = argv[1];
    std::string outputPath = argv[2];

    cv::VideoCapture cap(inputPath);
    if (!cap.isOpened()) {
        std::cerr << "Failed to open input video.\n";
        return 1;
    }

    int width  = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
    int fps    = static_cast<int>(cap.get(cv::CAP_PROP_FPS));

    cv::VideoWriter writer(outputPath,
        cv::VideoWriter::fourcc('X','V','I','D'),
        fps,
        cv::Size(width, height));

    if (!writer.isOpened()) {
        std::cerr << "Failed to open output video.\n";
        return 1;
    }

    // --- Hardcoded secret seed (this is the CTF "flag" in a way) ---
    uint32_t prng_state = 0xDEADBEEF; // Change this for your actual challenge

    cv::Mat frame;
    while (cap.read(frame)) {
        cv::Mat encrypted = frame.clone();

        // XOR every byte (3 channels per pixel)
        for (int y = 0; y < encrypted.rows; ++y) {
            for (int x = 0; x < encrypted.cols; ++x) {
                cv::Vec3b &pixel = encrypted.at<cv::Vec3b>(y, x);
                for (int c = 0; c < 3; ++c) {
                    uint8_t key = static_cast<uint8_t>(xorshift32(prng_state) & 0xFF);
                    pixel[c] ^= key;
                }
            }
        }

        writer.write(encrypted);
    }

    cap.release();
    writer.release();
    std::cout << "Encryption done. Output: " << outputPath << "\n";
    return 0;
}
