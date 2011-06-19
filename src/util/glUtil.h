#ifndef GL_STUFF_H_INCLUDED
#define GL_STUFF_H_INCLUDED

struct inputData
{
   float position[3];
   float translation[3];
   float textcord[2];
   float rotation;

   float buffer[7];
};

#include <string>
void checkGLError();

unsigned int createShader(const std::string &filename, int type);
unsigned int createProgram(unsigned int vertShader, unsigned int fragShader);
void activateProgram(unsigned int program);

void loadTexture(int target, const std::string &filename);

#endif
