#define _USE_MATH_DEFINES

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cmath>
#include "AudioFile.h"

#define NUM_SAMPLES 48000
#define SAMPLE_RATE 48000
#define AMPLITUDE 16000
#define BIT_DEPTH 16
#define NUM_CHANNELS 1

void create_audio_file(AudioFile &audio_file, std::string &file_name, const int &wave_playtime){
    audio_file.load(file_name);
    audio_file.setSampleRate(SAMPLE_RATE);
    audio_file.setBitDepth(BIT_DEPTH);
    audio_file.setNumChannels(NUM_CHANNELS);
    std::cout << "Parameters set." << endl << audio_file.printSummary() << endl;
}

void print_sample(float &sample){ std::cout << sample << std::endl; }

void write_wave(std::vector<float> &wave, const std::string file_name){
    // create wave buffer
    std::stringstream buffer;
    for(float sample : wave){
        buffer << sample;
    }

    // write buffer to file
    std::ofstream file;
    file.open(file_name);
    file << buffer.str();
    file.close();
}

void generate_sine(const int &frequency, const int &playtime, const std::string &file_name){
    int block_size = playtime * NUM_SAMPLES;
    // this vector will hold the sample data
    std::vector<float> wave(block_size);
    // this loop calculates all the wave samples until
    // the end of the defined playtime
    for(int i = 0; i < NUM_SAMPLES * playtime; i++){
        wave[i] = 0.5 * sin(2 * M_PI * frequency * i/SAMPLE_RATE);
        print_sample(wave[i]);
    }
    write_wave(wave, file_name);
}

void generate_saw(const int &frequency, const int &playtime, const std::string &file_name){
    int block_size = playtime * NUM_SAMPLES;
    // this vector will hold the sample data
    std::vector<float> wave(block_size);
    // this loop calculates all the wave samples until
    // the end of the defined playtime
    float x = 0;
    for(int i = 0; i < NUM_SAMPLES * playtime; i++){
        wave[i] = x * (2 * M_PI * frequency * i/SAMPLE_RATE);
        x = x + 0.1;
        if (x > 1) x = -1;
        print_sample(wave[i]);
    }
    write_wave(wave, file_name);
}
void generate_triangle(const int &frequency, const int &playtime, const std::string &file_name){}
void generate_square(const int &frequency, const int &playtime, const std::string &file_name){}

void gen_wave(const std::string &wave_type, const int &frequency, const int &playtime, const std::string file_name){
    int sample = 0;

    if(wave_type == "sine"){
        std::cout << "Generating sine wave" << std::endl;
        generate_sine(frequency, playtime, file_name);
    } else if (wave_type == "saw"){
        std::cout << "Generating saw wave" << std::endl;
        generate_saw(frequency, playtime, file_name);
    } else if (wave_type == "triangle"){
        std::cout << "Generating triangle wave" << std::endl;
        //generate_triangle(frequency, playtime, file_name);
    } else if (wave_type == "square"){
        std::cout << "Generating square wave" << std::endl;
        //generate_square(frequency, playtime, file_name);
    }
}

void print_help(){
    std::cout << "Usage:" << std::endl <<
                 "wavegen <wavetype> <frequency> <playtime> <file_name>" << std::endl;
}

int main(int argc, char** argv){
    if(argv[1] == "-h"){
        print_help();
    }
    const std::string wave_type = argv[1];
    const int wave_frequency = atoi(argv[2]);
    const int wave_playtime = atoi(argv[3]);
    const std::string file_name = argv[4];
    AudioFile<double> audio_file;
    create_audio_file(audio_file, file_name, wave_playtime);
    if(argc != 5){
        print_help();
        return 1;
    } else {
        gen_wave(wave_type, wave_frequency, wave_playtime, audio_file);
    }
    return 0;
}
