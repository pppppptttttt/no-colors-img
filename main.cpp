#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" // for stbi_image_free, stbi_load

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" // for stbi_write_png

#include <algorithm> // for for_each
#include <cstddef>   // for size_t
#include <cstdint>   // for uint8_t
#include <execution> // for execution::par
#include <iostream>  // for basic_ostream, operator<<
#include <limits>    // for numeric_limits
#include <numeric>   // for iota
#include <vector>    // for vector

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <path/to/image> <path/to/output>\n";
    return 0;
  }

  const char *filename = argv[1];
  const char *output_filename = argv[2];

  int width = 0;
  int height = 0;
  int channels = 0;
  std::uint8_t *image =
      stbi_load(filename, &width, &height, &channels, STBI_default);

  if (image == nullptr) {
    std::cerr << "Failed to load image!\n";
    stbi_image_free(image);
    return 1;
  }

  if (width <= 0 || height <= 0 || channels < 1 || channels > 4) {
    std::cerr << "Invalid image!\n";
    stbi_image_free(image);
    return 1;
  }

  if (channels == 1 || channels == 2) {
    std::cerr << "Image is already gray!\n";
    stbi_image_free(image);
    return 0;
  }

  if (std::numeric_limits<int>::max() / height / channels < width) {
    std::cerr << "Image is too large!\n";
    stbi_image_free(image);
    return 1;
  }

  const int gray_channels = channels == 4 ? 2 : 1;
  const std::size_t gray_image_size = width * height * gray_channels;
  std::vector<std::uint8_t> gray_image(gray_image_size);

  std::vector<std::size_t> indices(width * height);
  std::iota(indices.begin(), indices.end(), 0);

  std::for_each(
      std::execution::par, indices.cbegin(), indices.cend(),
      [gray_channels, channels, &gray_image, &image](std::size_t idx) {
        const std::size_t i = idx * gray_channels;
        const std::size_t j = idx * channels;
        gray_image[i] = static_cast<std::uint8_t>(
            (image[j] + image[j + 1] + image[j + 2]) / 3.0L);
        if (gray_channels == 2) {
          gray_image[i + 1] = image[j + 3];
        }
      });

  stbi_image_free(image);
  if (!stbi_write_png(output_filename, width, height, gray_channels,
                      gray_image.data(), width * gray_channels)) {
    std::cerr << "Failed to write output image!\n";
    return 1;
  }
}
