#include <iostream>
#include <GL/glut.h>
#include "/usr/include/asoundlib.h"
#include <fstream>

int screenWidth = 840;
int screenHeight = 680;

struct WAVHeader {
    char chunkID[4];
    unsigned int chunkSize;
    char format[4];
    char subchunk1ID[4];
    unsigned int subchunk1Size;
    unsigned short audioFormat;
    unsigned short numChannels;
    unsigned int sampleRate;
    unsigned int byteRate;
    unsigned short blockAlign;
    unsigned short bitsPerSample;
};

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.9f, 0.9f, 0.9f, 0.0);
    glColor3f(1, 0, 0);
    glFlush();
}

void playSound(const char* soundFile) {
    std::ifstream file(soundFile, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening audio file" << std::endl;
        return;
    }

    WAVHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(WAVHeader));

    unsigned int bufferSize = header.chunkSize - 36;
    char* soundBuffer = new char[bufferSize];
    file.read(soundBuffer, bufferSize);

    file.close();

    snd_pcm_t* handle;
    snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
    snd_pcm_set_params(handle, SND_PCM_FORMAT_S16_LE, SND_PCM_ACCESS_RW_INTERLEAVED, header.numChannels, header.sampleRate, 1, 500000);
    snd_pcm_writei(handle, soundBuffer, bufferSize / (header.numChannels * (header.bitsPerSample / 8)));
    snd_pcm_close(handle);

    delete[] soundBuffer;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(30, 30);
    glutCreateWindow("Sound program");
    glutDisplayFunc(display);
    playSound("Sickick.wav");
    glutMainLoop();
    return 0;
}
