#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

int main(int argc, char **argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <path/to/image> <path/to/output>\n";
    std::exit(0);
  }

  const char *filename = argv[1];
  const char *output_filename = argv[2];

  int width = 0;
  int height = 0;
  int channels = 0;
  std::uint8_t *image =
      stbi_load(filename, &width, &height, &channels, STBI_default);

  if (channels == 1 || channels == 2) {
    std::cerr << "Image is already gray!\n";
    std::exit(0);
  }

  if (image == nullptr) {
    std::cerr << "Failed to load image!\n";
    std::exit(1);
  }

  const int gray_channels = channels == 4 ? 2 : 1;
  const std::size_t gray_image_size = width * height * gray_channels;
  std::vector<std::uint8_t> gray_image(gray_image_size);

  std::vector<std::size_t> indices(width * height);
  std::iota(indices.begin(), indices.end(), 0);

  std::for_each(std::execution::par, indices.begin(), indices.end(),
                [&](std::size_t idx) {
                  std::size_t i = idx * gray_channels;
                  std::size_t j = idx * channels;
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
