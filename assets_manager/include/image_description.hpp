#ifndef IMAGE_DESCRIPTION_HPP
#define IMAGE_DESCRIPTION_HPP

namespace Zero {

struct ImageDescription {

    ImageDescription(unsigned char *data, uint32_t width, uint32_t height, uint32_t channels) : data(data), width(width), height(height), channels(channels) {};
    ~ImageDescription() {stbi_image_free(data);};

    ImageDescription(const ImageDescription &oldImage) : width(oldImage.width), height(oldImage.height), channels(oldImage.channels) {
        auto imageSize = width * height * channels;
        data = new unsigned char[imageSize];
        std::memcpy(data, oldImage.data, imageSize);
    }

    unsigned char *data;
    uint32_t width = 0;
    uint32_t height = 0;
    uint32_t channels = 0;
};

}


#endif