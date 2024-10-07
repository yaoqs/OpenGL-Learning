// ooglTexture.h
// Declaration of ooglTexture2D Object
// This object is for simplifying two dimensional texture
// manipulation. This is for simple non mip-mapped textures.


////////////////////////////////////////////////////////
// Definition
class ooglTexture2D 
	{
	// Data members
	protected:
		void *_pBitmapData;				// Raw Bitmap Data
		BOOL _bValid;					// Indicates valid texture loaded
		unsigned int _nTextureID;		// Texture name
		unsigned int _nTextureWidth;	// Texture width
		unsigned int _nTextureHeight;	// Texture height
		
	// Methods
	public:
		ooglTexture2D();
		~ooglTexture2D();

		// General Methods		

		inline unsigned int GetTexID()
			{ return _nTextureID;} 
		inline void SetActive() 
			{ glBindTexture(GL_TEXTURE_2D, _nTextureID); }
		
		inline BOOL IsValid() { return _bValid; }

		inline unsigned int GetWidth() { return _nTextureWidth; }
		inline unsigned int GetHeight() { return _nTextureHeight; }
		inline unsigned int GetTextureName() { return _nTextureID; }


		////////////////////////////////////////////////////////
		// OpenGL Wrappings
		inline void TexParameter(GLenum pname, GLint param) 
				{ SetActive(); glTexParameteri(GL_TEXTURE_2D, pname, param); } 

		inline void TexParamter(GLenum pname, GLfloat param)
				{ SetActive(); glTexParameterf(GL_TEXTURE_2D, pname, param); }

		inline void TexParameter(GLenum pname, const GLfloat *param)
				{ SetActive(); glTexParameterfv(GL_TEXTURE_2D, pname, param); }

		inline void TexParameter(GLenum pname, const GLint *param)
				{ SetActive(); glTexParameteriv(GL_TEXTURE_2D, pname, param); }


		// These apply to all texturing operations
		static inline void TexEnv(GLenum pname, GLfloat param)
				{ glTexEnvf(GL_TEXTURE_ENV, pname, param); }

		static inline void TexEnv(GLenum pname, GLint param)
				{ glTexEnvi(GL_TEXTURE_ENV, pname, param); }

		static inline void TexEnv(GLenum pname, const GLfloat *params)
				{ glTexEnvfv(GL_TEXTURE_ENV, pname, params); }

		static inline void TexEnv(GLenum pname, const GLint *params)
				{ glTexEnviv(GL_TEXTURE_ENV, pname, params); }



		static inline void TexGen(GLenum coord, GLenum pname, GLdouble param)
				{ glTexGend(coord, pname, param); }

		static inline void TexGen(GLenum coord, GLenum pname, GLfloat param)
				{ glTexGenf(coord, pname, param); }

		static inline void TexGen(GLenum coord, GLenum pname, GLint param)
				{ glTexGeni(coord, pname, param); }
				
		static inline void TexGen(GLenum coord, GLenum pname, const GLdouble *params)
				{ glTexGendv(coord, pname, params); } 
 
		static inline void TexGen(GLenum coord, GLenum pname, const GLfloat *params)
				{ glTexGenfv(coord, pname, params); }
				
		static inline void TexGen(GLenum coord, GLenum pname, const GLint *params)
				{ glTexGeniv(coord, pname, params); }
				 


		/////////////////////////////////////////////////////////////
		// Load Textures from files
		BOOL LoadBMP(TCHAR* szFileName);
		BOOL LoadBMPA(TCHAR* szFileName, int iblend);
		BOOL LoadBMPA64(TCHAR* szFileName, int iblend);
//		BOOL GetBMP(TCHAR* szFileName, GLubyte* uData, int *w, int *h);

		// Load SGI textures
		// BOOL LoadRGB(TCHAR* szFileName);
		
		// Load DirectX textures
		// BOOL LoadPPM(TCHAR* szFileName);

		// Load RAW DIB?
		// BOOL LoadDIB(TCHAR* szFileName);

		// Load From Resource
		// BOOL LoadBMPResource(UINT uiResourceID);

		// Load Palettized Bitmaps
		// Use LoadBMP, just figure it out along the way

		// Load TGA (very simple format)
		// BOOL LoadTGA(TCHAR* szFileName);

		// Load TIFF 
		// BOOL LoadTIFF(TCHAR* szFileName);

		// Load PCX
		// BOOL LoadPCX(TCHAR* szFileName);
	};
