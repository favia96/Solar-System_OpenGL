#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "stb_image.h"

class texture 
{
	private:
		unsigned int m_RendererID;
		std::string m_filePath;
		unsigned char* m_localBuffer;
		int m_Width, m_Height, m_BPP;
	public:
		texture(const std::string& path);
		~texture();

		void bind(unsigned int slot = 0) const;
		void unbind() const;
		
		inline int getWidth() const 
		{ 
			return m_Width;
		}

		inline int getHeight() const 
		{ 
			return m_Height;
		}
};