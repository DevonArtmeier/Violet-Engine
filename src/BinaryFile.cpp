/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#include "Violet.hpp"

namespace Violet {

	/// <summary>
	/// Binary file constructor
	/// </summary>
	/// <param name="fileName">File name</param>
	/// <param name="read">Read flag</param>
	BinaryFile::BinaryFile(std::string fileName, bool read) {
		fopen_s(&fp, fileName.c_str(), read ? "rb" : "wb");
		if (!fp) {
			Engine::Error("Failed to open file \"" + fileName + "\".");
		}

		this->fileName = fileName;
		this->read = read;
	}

	/// <summary>
	/// Binary file destructor
	/// </summary>
	BinaryFile::~BinaryFile() {
		if (fp) {
			fclose(fp);
		}
	}

	/// <summary>
	/// Read value
	/// </summary>
	/// <typeparam name="T">Value type</typeparam>
	/// <param name="fp">File handler</param>
	/// <param name="fileName">File name</param>
	/// <param name="read">Read flag</param>
	/// <returns>Read value</returns>
	template<typename T>
	T ReadValue(FILE* fp, std::string fileName, bool read) {
		T value = 0;
		if (fp) {
			if (!read) {
				Engine::Error("File \"" + fileName + "\" isn't open for reading.");
			}
			else {
				size_t sz = fread(&value, sizeof(T), 1, fp);
				if (sz != 1) {
					Engine::Error("Failed to read value from file \"" + fileName + "\".");
				}
			}
		}
		else {
			Engine::Error("File \"" + fileName + "\" isn't open.");
		}
		return value;
	}

	/// <summary>
	/// Check if the file is at the end
	/// </summary>
	/// <returns><True if at the end, false if not</returns>
	bool BinaryFile::AtEnd() {
		return feof(fp);
	}

	/// <summary>
	/// Read signed 8-bit integer 
	/// </summary>
	/// <returns>Read value</returns>
	S8 BinaryFile::ReadInt8() {
		return ReadValue<S8>(fp, fileName, read);
	}

	/// <summary>
	/// Read unsigned 8-bit integer 
	/// </summary>
	/// <returns>Read value</returns>
	U8 BinaryFile::ReadUInt8() {
		return ReadValue<U8>(fp, fileName, read);
	}

	/// <summary>
	/// Read signed 16-bit integer 
	/// </summary>
	/// <returns>Read value</returns>
	S16 BinaryFile::ReadInt16() {
		return ReadValue<S16>(fp, fileName, read);
	}
	
	/// <summary>
	/// Read unsigned 16-bit integer 
	/// </summary>
	/// <returns>Read value</returns>
	U16 BinaryFile::ReadUInt16() {
		return ReadValue<U16>(fp, fileName, read);
	}

	/// <summary>
	/// Read signed 32-bit integer 
	/// </summary>
	/// <returns>Read value</returns>
	S32 BinaryFile::ReadInt32() {
		return ReadValue<S32>(fp, fileName, read);
	}

	/// <summary>
	/// Read unsigned 32-bit integer 
	/// </summary>
	/// <returns>Read value</returns>
	U32 BinaryFile::ReadUInt32() {
		return ReadValue<U32>(fp, fileName, read);
	}

	/// <summary>
	/// Read signed 64-bit integer 
	/// </summary>
	/// <returns>Read value</returns>
	S64 BinaryFile::ReadInt64() {
		return ReadValue<S64>(fp, fileName, read);
	}

	/// <summary>
	/// Read unsigned 64-bit integer 
	/// </summary>
	/// <returns>Read value</returns>
	U64 BinaryFile::ReadUInt64() {
		return ReadValue<U64>(fp, fileName, read);
	}

	/// <summary>
	/// Read float
	/// </summary>
	/// <returns>Read value</returns>
	float BinaryFile::ReadFloat() {
		return ReadValue<float>(fp, fileName, read);
	}

	/// <summary>
	/// Read float
	/// </summary>
	/// <returns>Read value</returns>
	double BinaryFile::ReadDouble() {
		return ReadValue<double>(fp, fileName, read);
	}

	/// <summary>
	/// Read string
	/// </summary>
	/// <param name="length">String length (0 = automatic)</param>
	/// <returns>Read string</returns>
	std::string BinaryFile::ReadString(int length) {
		if (fp) {
			if (!read) {
				Engine::Error("File \"" + fileName + "\" isn't open for reading.");
			}
			else {
				char* buffer;
				bool calced_len = false;

				if (length == 0) {
					// Get length if not defined
					char c;
					while (fread(&c, sizeof(char), 1, fp) == 1) {
						if (!c) {
							break;
						}
						++length;
					}
					fseek(fp, -(length + 1), SEEK_CUR);
					calced_len = true;
				}

				buffer = (char*)malloc(length + 1);
				if (buffer) {
					if (fread(buffer, sizeof(char), length, fp) != length) {
						Engine::Error("Failed to read string from file \"" + fileName + "\".");
					}
					if (calced_len) {
						fseek(fp, 1, SEEK_CUR);
					}
					buffer[length] = 0;

					std::string str(buffer);
					free(buffer);
					return str;
				}
			}
		}
		else {
			Engine::Error("File \"" + fileName + "\" isn't open.");
		}
		return "";
	}

	/// <summary>
	/// Open binary file for reading
	/// </summary>
	/// <param name="fileName">File name</param>
	/// <param name="read">Read flag</param>
	/// <returns>Binary file handler</returns>
	std::shared_ptr<BinaryFile> Engine::OpenBinaryFile(std::string fileName, const bool read) {
		return std::shared_ptr<BinaryFile>(new BinaryFile(fileName, read));
	}

}
