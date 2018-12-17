//#include "skybox.h"
#include "Texture.h"
#include "stb_image.h"
/*
Skybox::Skybox()
{
	size = -1;

	for (unsigned int i = 0; i < 6; i++)
	{
		side[i] = -1;
	}
}
void Texture::init(const std::string& fileName)
{
	int width, height, numComponents; //width, height, and no of components of image
	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4); //load the image and store the data

	if (imageData == NULL)
	{
		std::cerr << "texture load failed" << fileName << std::endl;
	}

	glGenTextures(1, &textureHandler); // number of and address of textures
	glBindTexture(GL_TEXTURE_2D, textureHandler); //bind texture - define type 

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // wrap texture outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // wrap texture outside height

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // linear filtering for minification (texture is smaller than area)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // linear filtering for magnifcation (texture is larger)

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData); //Target, Mipmapping Level, Pixel Format, Width, Height, Border Size, Input Format, Data Type of Texture, Image Data
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(imageData);
}
Skybox::Skybox(unsigned int left, unsigned int back, unsigned int right, unsigned int front, unsigned int top, unsigned int bottom, float s)
{
	side[0] = left;
	side[1] = back;
	side[2] = right;
	side[3] = front;
	side[4] = top;
	side[5] = bottom;
	size = s;         
}
Skybox::~Skybox()
{
	glDeleteTextures(6, &side[0]);
}
void Skybox::drawSkybox()
{
	
}
*/