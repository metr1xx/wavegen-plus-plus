#define _USE_MATH_DEFINES

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cmath>

#define NUM_SAMPLES 48000
#define SAMPLING_RATE 48000
#define AMPLITUDE 16000
#define BIT_DEPTH 16


void print_sample(float &sample){ std::cout << sample << std::endl; }

void write_wave(std::vector<float> &wave, const std::string filename){
    // create wave buffer
    std::stringstream buffer;
    for(float sample : wave){
        buffer << sample;
    }

    // write buffer to file
    std::ofstream file;
    file.open(filename);
    file << buffer.str();
    file.close();
}

void generate_sine(const int &frequency, const int &playtime, const std::string &filename){
    int block_size = playtime * NUM_SAMPLES;
    // this vector will hold the sample data
    std::vector<float> wave(block_size);
    // this loop calculates all the wave samples until
    // the end of the defined playtime
    for(int i = 0; i < NUM_SAMPLES * playtime; i++){
        wave[i] = sin(2 * M_PI * frequency * i/SAMPLING_RATE);
        print_sample(wave[i]);
    }
    write_wave(wave, filename);
}

void generate_saw(const int &frequency, const int &playtime, const std::string &filename){
    int block_size = playtime * NUM_SAMPLES;
    // this vector will hold the sample data
    std::vector<float> wave(block_size);
    // this loop calculates all the wave samples until
    // the end of the defined playtime
    float x = 0;
    for(int i = 0; i < NUM_SAMPLES * playtime; i++){
        wave[i] = x * (2 * M_PI * frequency * i/SAMPLING_RATE);
        x = x + 0.1;
        if (x > 1) x = -1;
        print_sample(wave[i]);
    }
    write_wave(wave, filename);
}
void generate_triangle(const int &frequency, const int &playtime, const std::string &filename){}
void generate_square(const int &frequency, const int &playtime, const std::string &filename){}

void gen_wave(const std::string &wave_type, const int &frequency, const int &playtime, const std::string filename){
    int sample = 0;

    if(wave_type == "sine"){
        std::cout << "Generating sine wave" << std::endl;
        generate_sine(frequency, playtime, filename);
    } else if (wave_type == "saw"){
        std::cout << "Generating saw wave" << std::endl;
        generate_saw(frequency, playtime, filename);
    } else if (wave_type == "triangle"){
        std::cout << "Generating triangle wave" << std::endl;
        //generate_triangle(frequency, playtime, filename);
    } else if (wave_type == "square"){
        std::cout << "Generating square wave" << std::endl;
        //generate_square(frequency, playtime, filename);
    }
}

void print_help(){
    std::cout << "Usage:" << std::endl <<
                 "wavegen <wavetype> <frequency> <playtime> <filename>" << std::endl;
}

int main(int argc, char** argv){
    if(argv[1] == "-h"){
        print_help();
    }
    const std::string wave_type = argv[1];
    const int wave_frequency = atoi(argv[2]);
    const int wave_playtime = atoi(argv[3]);
    const std::string filename = argv[4];
    if(argc != 5){
        print_help();
        return 1;
    } else {
        gen_wave(wave_type, wave_frequency, wave_playtime, filename);
    }
    return 0;
}
