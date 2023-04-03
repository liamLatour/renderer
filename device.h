#pragma once

#include <thrust/host_vector.h>
#include <string>

void render_on_device(
    int width,
    int height,
    std::string command,
    thrust::host_vector<int>& red_pixels,
    thrust::host_vector<int>& green_pixels,
    thrust::host_vector<int>& blue_pixels,
    thrust::host_vector<int>& alpha_pixels
);