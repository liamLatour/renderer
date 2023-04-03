#include <thrust/sort.h>
#include <thrust/device_vector.h>
#include <thrust/copy.h>

#include "device.h"

float sdSphere(int p, float s){
    return 1.0f;
}

void length(){
    
}

void render_on_device(
    int width,
    int height,
    std::string command,
    thrust::host_vector<int>& red_pixels,
    thrust::host_vector<int>& green_pixels,
    thrust::host_vector<int>& blue_pixels,
    thrust::host_vector<int>& alpha_pixels
    )
{
    // transfer data to the device
    thrust::device_vector<int> d_red_pixels = red_pixels;
    thrust::device_vector<int> d_green_pixels = green_pixels;
    thrust::device_vector<int> d_blue_pixels = blue_pixels;
    thrust::device_vector<int> d_alpha_pixels = alpha_pixels;

    // manipulation
    thrust::fill(d_red_pixels.begin(), d_red_pixels.end(), 0);
    thrust::fill(d_green_pixels.begin(), d_green_pixels.end(), 255);
    thrust::fill(d_blue_pixels.begin(), d_blue_pixels.end(), 0);
    thrust::fill(d_alpha_pixels.begin(), d_alpha_pixels.end(), 255);

    // transfer data back to host
    thrust::copy(d_red_pixels.begin(), d_red_pixels.end(), red_pixels.begin());
    thrust::copy(d_green_pixels.begin(), d_green_pixels.end(), green_pixels.begin());
    thrust::copy(d_blue_pixels.begin(), d_blue_pixels.end(), blue_pixels .begin());
    thrust::copy(d_alpha_pixels.begin(), d_alpha_pixels.end(), alpha_pixels.begin());
}