#pragma once
#if defined DLL_EXPORT
#define H3D_API __declspec(dllexport)
#else
#define H3D_API __declspec(dllimport)
#endif
/////////////////////////////////////////////////////////////////
#include "..\hashing\CRC32.hpp"
#include "..\hashing\UniChecksum.hpp"
/////////////////////////////////////////////////////////////////
// Network Package	
/////////////////////////////////////////////////////////////////
namespace h3d {
	namespace Network {
		class Package;
		static void encryptPkgAES256(Package& pkg, char *key);
		static void decryptPkgAES256(Package& pkg, char *key);

		class Package
		{
		private:
			unsigned char*    buffer;
			uint64_t          buffersize;

		public:
			template<typename T>
				void operator=(T data)
				{
					buffersize = sizeof(data);
					buffer = new unsigned char[buffersize];
					memcpy(buffer, data, buffersize);
				};
			
			H3D_API unsigned char* data() const { return buffer; }

			template<typename T>
			T size() const {
				return static_cast<T>(buffersize);
				}

			template<typename checksumtype>
			checksumtype checksum(){
				checksumtype checksum;
				checksum.create(buffer,buffersize);
				return checksum;
			}
		};
	}
}
/////////////////////////////////////////////////////////////////
void h3d::Network::encryptPkgAES256(h3d::Network::Package& pkg, char *key)
{

}
void h3d::Network::decryptPkgAES256(h3d::Network::Package& pkg, char *key)
{

}