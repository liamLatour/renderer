#include <thrust/host_vector.h>
#include <thrust/random.h>
#include <thrust/generate.h>
#include <thrust/sort.h>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <SFML/Graphics.hpp>
#include <string>

// defines the function prototype
#include "device.h"

// https://iquilezles.org/articles/

const int   screenSize_X = 640;
const int   screenSize_Y = 480;

int display_to_window(sf::Sprite sprite);
void generate_texture(sf::Texture& texture, std::string command);

int main(void)
{
    std::string command = "C";
    sf::Sprite sprite;

    sf::Texture texture;
    if (!texture.create(screenSize_X, screenSize_Y))
    {
        std::cout << "failed to create texture";
        return 1;
    }

    generate_texture(texture, command);
    sprite.setTexture(texture);
    display_to_window(sprite);

    return 0;
}

void generate_texture(sf::Texture& texture, std::string command){
    // interface to CUDA code
    int width = screenSize_X;
    int height = screenSize_Y;
    
    sf::Uint8* pixels = new sf::Uint8[width * height * 4];

    thrust::host_vector<int> red_pixels(width*height);
    thrust::host_vector<int> green_pixels(width*height);
    thrust::host_vector<int> blue_pixels(width*height);
    thrust::host_vector<int> alpha_pixels(width*height);

    render_on_device(
        width, 
        height, 
        command,
        red_pixels,
        green_pixels,
        blue_pixels,
        alpha_pixels
        );

    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++){
            int index = (i*width+j)*4;
            pixels[ index ] = red_pixels[i*width+j];
            pixels[index+1] = green_pixels[i*width+j];
            pixels[index+2] = blue_pixels[i*width+j];
            pixels[index+3] = alpha_pixels[i*width+j];
        }
    }

    texture.update(pixels);
} 

int display_to_window(sf::Sprite sprite){
    sf::RenderWindow window(sf::VideoMode(screenSize_X,screenSize_Y), "Display an Image");

    window.setFramerateLimit( 60 );
    
    bool program_running = true;
    while(program_running)
    {
        sf::Event evt;
        while( window.pollEvent(evt) )
        {
            if(evt.type == sf::Event::EventType::Closed)
                program_running = false;
        }

        window.draw(sprite);
        window.display();
    }

    return 0;
}