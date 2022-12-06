/******************************************************************/
/* Violet Engine                                                  */
/* (C) Devon Artmeier 2022                                        */
/******************************************************************/

#ifndef VIOLET_BINARY_FILE_HPP
#define VIOLET_BINARY_FILE_HPP

namespace Violet {

	/// <summary>
	/// Binary file
	/// </summary>
	class BinaryFile {
	public:
		/// <summary>
		/// Binary file destructor
		/// </summary>
		~BinaryFile();

		/// <summary>
		/// Check if the file is at the end
		/// </summary>
		/// <returns><True if at the end, false if not</returns>
		bool AtEnd();

		/// <summary>
		/// Read signed 8-bit integer 
		/// </summary>
		/// <returns>Read value</returns>
		S8 ReadInt8();

		/// <summary>
		/// Read unsigned 8-bit integer 
		/// </summary>
		/// <returns>Read value</returns>
		U8 ReadUInt8();

		/// <summary>
		/// Read signed 16-bit integer 
		/// </summary>
		/// <returns>Read value</returns>
		S16 ReadInt16();

		/// <summary>
		/// Read unsigned 16-bit integer 
		/// </summary>
		/// <returns>Read value</returns>
		U16 ReadUInt16();

		/// <summary>
		/// Read signed 32-bit integer 
		/// </summary>
		/// <returns>Read value</returns>
		S32 ReadInt32();

		/// <summary>
		/// Read unsigned 32-bit integer 
		/// </summary>
		/// <returns>Read value</returns>
		U32 ReadUInt32();

		/// <summary>
		/// Read signed 64-bit integer 
		/// </summary>
		/// <returns>Read value</returns>
		S64 ReadInt64();

		/// <summary>
		/// Read unsigned 64-bit integer 
		/// </summary>
		/// <returns>Read value</returns>
		U64 ReadUInt64();

		/// <summary>
		/// Read float
		/// </summary>
		/// <returns>Read value</returns>
		float ReadFloat();

		/// <summary>
		/// Read double
		/// </summary>
		/// <returns>Read value</returns>
		double ReadDouble();

		/// <summary>
		/// Read string
		/// </summary>
		/// <param name="length">String length (0 = automatic)</param>
		/// <returns>Read string</returns>
		std::string ReadString(int length = 0);

		// Friend classes
		friend class Engine;

	private:
		/// <summary>
		/// Binary file constructor
		/// </summary>
		/// <param name="fileName">File name</param>
		/// <param name="read">Read flag</param>
		BinaryFile(std::string fileName, bool read);

		/// <summary>
		/// File handler
		/// </summary>
		FILE* fp{ nullptr };

		/// <summary>
		/// Read flag
		/// </summary>
		bool read{ false };

		/// <summary>
		/// File name
		/// </summary>
		std::string fileName;
	};

}

#endif // VIOLET_BINARY_FILE_HPP
