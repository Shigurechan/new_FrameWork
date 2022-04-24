#ifndef ___SHADER_HPP_
#define ___SHADER_HPP_
#include <iostream>
#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <GL/glew.h>

/*#########################################################################
# シェーダークラス

説明
	継承してシェーダーを実装
###########################################################################*/
namespace FrameWork
{
	class Shader
	{

	public:
		Shader();  //コンストラクタ
		~Shader(); //デストラクタ

		void Load(const char* vert,const char* frag);

		void Delete();	//削除

		void setEnable();		//有効
		void setDisable();		//無効

		// Uniform  int型 設定
		void setUniform1i(const char* name, const int vec);
		void setUniform2i(const char* name, const glm::ivec2 vec);
		void setUniform3i(const char* name, const glm::ivec3 vec);
		void setUniform4i(const char* name, const glm::ivec4 vec);

		// Uniform float型 設定
		void setUniform1f(const char *name, const float vec);
		void setUniform2f(const char *name, const glm::vec2 vec);
		void setUniform3f(const char *name, const glm::vec3 vec);
		void setUniform4f(const char *name, const glm::vec4 vec);
		
		// Uniform float型　行列　設定
		void setUniformMatrix2fv(const char *name, const glm::mat2 m);
		void setUniformMatrix3fv(const char *name, const glm::mat3 m);
		void setUniformMatrix4fv(const char *name, const glm::mat4 m);
		
		// Uniform float型 配列 設定
		void setUniform1fv(const char* name, const int count, const GLfloat vec[]);
		void setUniform2fv(const char* name, const int count, const glm::vec2 vec[]);
		void setUniform3fv(const char* name, const int count, const glm::vec3 vec[]);
		void setUniform4fv(const char* name, const int count, const glm::vec4 vec[]);
	
		// ProgramUniform  int型 設定
		void setProgramUniform1i(const char* name,const GLuint location, const int vec);

		// ProgramUniform  float型 設定
		void setProgramUniform1f(const char* name, const GLuint location, const int vec);


		void setUniformSampler2D(const char* name, const GLuint num,const GLuint textureID);



		void setBindAttribLocation(const char *str);	//頂点シェーダーに属性変数を関連ずける
		void setBindAttribFragment(const char *str);	//フラグメントシェーダーに属性変数を関連ずける
		GLint getAttribLocation(const char *str);		//locationを取得

	private:

		GLuint CreateProgram(GLchar *vert, GLchar *frag);						//プログラムオブジェクトを作成
		GLboolean CompileInfoLog(GLuint shader, const char *str);				//コンパイルエラーログを取得
		GLboolean ProgramInfoLog(GLuint program);								//プログラムログを取得
		bool ReadShaderSource(const char *name, std::vector<GLchar> &buffer);	//ソースファイルを読み込み
		GLuint LoadProgram(const char *vert, const char *frag);					//プログラムをオブジェクトをロード

		int offset;				//頂点オフセット
		int attributeSize;		//頂点サイズ
		GLuint program; 		//プログラムオブジェクト
	};
}
#endif
