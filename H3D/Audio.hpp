#pragma once
#if defined DLL_EXPORT
#define H3D_API _declspec(dllexport)
#else
#define H3D_API _declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
// external
#include <al.h>
#include <alc.h>
#include <vorbisenc.h>
#include <vorbisfile.h>
// cpp headers
#include <stdint.h>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
// internal 
#include "Utilities.hpp"
#include "Vector.hpp"
#include "AudioAccessories.hpp"
/////////////////////////////////////////////////////////////////
// Audio Module
/////////////////////////////////////////////////////////////////
namespace h3d{
	namespace Audio {
		/////////////////////////////////////////////////////////
		// Audio Engine Functions
		/////////////////////////////////////////////////////////
		bool H3D_API initialize(char* default_device = NULL);
		bool H3D_API shutdown();
		/////////////////////////////////////////////////////////
		// global Listener Class
		/////////////////////////////////////////////////////////
		class tagListener 
		{
		private:
			
		public:
			void setMasterGain(float gain);
			void setPosition(h3d::Vec3<float> pos);
			void setVelocity(h3d::Vec3<float> vel);
			void setOrientation(h3d::Vec3<float>at,h3d::Vec3<float>up);
		};
		const H3D_API tagListener Listener;
		/////////////////////////////////////////////////////////
		// Audio Scene
		/////////////////////////////////////////////////////////
		class Scene
		{
		public:

		private:

		};
		/////////////////////////////////////////////////////////
		// Audio Buffer Classes
		/////////////////////////////////////////////////////////
		// static Audio Object
		class AudioBuffer
		{
		private:
			ALuint  m_bufferID;
			ALsizei m_size;
			ALsizei m_frequency;
			ALenum  m_format;
			int     m_fileType;
		public:
			// Con-/Destructor
			H3D_API AudioBuffer();
			H3D_API ~AudioBuffer();
			
			// Identify Type
			struct Type{
				static const int WAV;
				static const int OGG;
			};
			int H3D_API getType();

			// File Loading
			bool H3D_API loadFromFile(char path[]);
		};
		/////////////////////////////////////////////////////////
		// streamed Audio Object
		class AudioBufferStream
		{
		private:

		public:
			H3D_API AudioBufferStream();
			H3D_API ~AudioBufferStream();

			bool H3D_API open(char Path[]);
		};
		/////////////////////////////////////////////////////////
		// Audio Sources
		/////////////////////////////////////////////////////////
		class AudioSource
		{
		private:
			ALuint m_sourceID;
		public:
			// Con-/Destructor
			H3D_API AudioSource();
			H3D_API ~AudioSource();

			// Add Buffers to queue
			bool queueBuffer(const AudioBuffer& ab_static);
			bool queueBuffer(const AudioBufferStream& ab_stream);
			bool unqueueBuffer(const AudioBuffer& ab_static);
			bool unqueueBuffer(const AudioBufferStream& ab_stream);

			// Actions
			void play();
			void pause();
			void stop();
			void rewind();

			// Set Properties
			void setPosition(h3d::Vec3<float> pos);
			void setVelocity(h3d::Vec3<float> vel);
			void setDirection(h3d::Vec3<float> dir);

			void setPitch(float val);
			void setGain(float val);
			

		};
		/////////////////////////////////////////////////////////
	}
	
}