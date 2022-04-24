#include "../header/Shader.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include <glm/gtc/type_ptr.hpp>

#include "../header/Resource.hpp"



// ##################################### コンストラクタ ##################################### 
FrameWork::Shader::Shader()
{	
	
}

// ##################################### ロード ##################################### 
void FrameWork::Shader::Load(const char* vert,const char* frag)
{

	program = CreateProgram(LoadShader(vert)->data(),LoadShader(frag)->data());

	if (program == 0)
	{
		std::cerr<<vert<<" , "<< frag <<std::endl;
		std::cerr << "シェーダープログラム作成エラー" << std::endl;
		assert(0);
	}	
}

// ##################################### プログラムオブジェクトをロード ##################################### 
GLuint FrameWork::Shader::LoadProgram(const char* vert, const char* frag)
{
	std::vector<GLchar> vertSource;
	const bool v = ReadShaderSource(vert, vertSource);
	
	std::vector<GLchar> fragSource;
	const bool f = ReadShaderSource(frag, fragSource);
	

	if (v == true && f == true)
	{
		return CreateProgram(vertSource.data(), fragSource.data());		
	}
	else 
	{
		//assert(0);
		return 0;
	}
}

// ##################################### シェーダーファイルを読み込む ##################################### 
bool FrameWork::Shader::ReadShaderSource(const char* name, std::vector<GLchar>& buffer)
{
	if (name == NULL)
	{
		std::cerr << "シェーダーファイルが指定されていません。" << std::endl;
		assert(0);
		return false;
	}
	
	std::ifstream file(name, std::ios::binary);
	if (file.fail() == true)
	{
		std::cerr << "シェーダーファイルを読み込めません: " << name << std::endl;
		file.close();
		assert(0);
		return false;
	}
	else
	{
		file.seekg(0L, std::ios::end);
		GLsizei length = static_cast<GLsizei>(file.tellg());
		buffer.resize(length + 1);

		file.seekg(0L, std::ios::beg);
		file.read(buffer.data(), length);
		buffer[length] = '\0';

		file.close();
	}
	file.close();

	return true;
}

// ##################################### シェーダーエラーログを取得 ##################################### 
GLboolean FrameWork::Shader::CompileInfoLog(GLuint shader,const char* str)
{
	GLint status;

	//コンパイル結果
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		std::cerr << str << std::endl;

		//エラーログの長さを得る
		GLsizei bufSize;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);

		if (bufSize > 1)
		{
			std::vector<GLchar> infoLog(bufSize);
			GLsizei length;
			glGetShaderInfoLog(shader, bufSize, &length, &infoLog[0]);

			std::cerr << str << &infoLog[0];
		}
	}
	
	return (GLboolean)status;
}

// ##################################### プログラムオブジェクト作成 ##################################### 
GLuint FrameWork::Shader::CreateProgram(GLchar* vert,GLchar* frag)
{
	const GLuint p = glCreateProgram();	//シェーダープログラムを作成

	if (vert != NULL)
	{
		const GLuint vobj = glCreateShader(GL_VERTEX_SHADER);
		
		GLchar* v[] = { NULL };
		v[0] = vert;

		//std::cout << &v[0] << std::endl;


		glShaderSource(vobj, 1,&v[0], NULL);
		glCompileShader(vobj);
		glAttachShader(p, vobj);
		CompileInfoLog(vobj, "Complie Error: Vertex Shader");
		glDeleteShader(vobj);


	}
	else 
	{
		std::cerr << "頂点シェーダー読み込み失敗" << std::endl;
	}

	if (frag != NULL)
	{
		const GLuint fobj = glCreateShader(GL_FRAGMENT_SHADER);
		
		GLchar *v[] = {NULL};
		v[0] = frag;

		glShaderSource(fobj, 1, &v[0], NULL);
		glCompileShader(fobj);
		glAttachShader(p, fobj);
		CompileInfoLog(fobj, "Complie Error: Fragment Shader");

		glDeleteShader(fobj);
	}
	else 
	{
		std::cerr << "フラグメントシェーダー読み込み失敗" << std::endl;
	}

	glLinkProgram(p);		//リンクプログラム

	//リンク時のログを表示
	if(ProgramInfoLog(p) == false)
	{
		std::cerr<<"プログラムリンク失敗"<<std::endl;
		//assert(0);
		
	}
	
	return p;
}

// ##################################### プログラムのエラーを表示 ##################################### 
GLboolean FrameWork::Shader::ProgramInfoLog(GLuint p)
{
	GLsizei bufSize;
	glGetProgramiv(p, GL_INFO_LOG_LENGTH, &bufSize);

	if (bufSize > 1) 
	{
		std::vector<GLchar> infoLog(bufSize);	
		GLsizei length;
		glGetProgramInfoLog(p, bufSize, &length, &infoLog[0]);
		std::cerr<<"Program Info Log: "<< infoLog.data() <<std::endl;
		return false;
	}
	else
	{
		return true;
	}
}

// ##################################### Attriblocationを取得 ##################################### 
GLint FrameWork::Shader::getAttribLocation(const char* str)
{
	return glGetAttribLocation(program,str);
}

// ##################################### 頂点シェーダーに属性変数を関連ずける ##################################### 
void FrameWork::Shader::setBindAttribLocation(const char* str)
{
	GLint n = glGetAttribLocation(program, str);

	//エラー処理
	if (n == -1)
	{
		std::cerr <<"setBindAttribLocation(): "<< n << std::endl;
	}
	else 
	{
		glBindAttribLocation(program, n, str);
	}
}

// ##################################### フラグメントシェーダーに属性変数を関連ずける ##################################### 
void FrameWork::Shader::setBindAttribFragment(const char* str)
{
	GLint n = glGetAttribLocation(program, str);

	//エラー処理
	if (n == -1)
	{
		std::cerr << "setBindAttribFragment(): " << n << std::endl;
	}
	else 
	{
		glBindFragDataLocation(program, n, str);
	}
} 

// ##################################### 有効にする ##################################### 
void FrameWork::Shader::setEnable()
{
	glUseProgram(program);
}

// ##################################### 無効にする ##################################### 
void FrameWork::Shader::setDisable()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
}

// ##################################### Uniform 設定 ##################################### 
  
// ##################################### vec1 ##################################### 
void FrameWork::Shader::setUniform1f(const char* name, const float vec)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//エラー処理
	glUniform1f(object,vec);
}

// ##################################### vec2 ##################################### 
void FrameWork::Shader::setUniform2f(const char* name, const glm::vec2 vec)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//エラー処理
	glUniform2f(object,vec.x,vec.y);
}

// ##################################### vec3 ##################################### 
void FrameWork::Shader::setUniform3f(const char* name, const glm::vec3 vec)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//エラー処理
	glUniform3f(object,vec.x, vec.y,vec.z);
}

// ##################################### vec4 ##################################### 
void FrameWork::Shader::setUniform4f(const char* name, const glm::vec4 vec)
{	
	const GLuint object = glGetUniformLocation(program,name);
	if (object == -1) { assert(0); }	//エラー処理
	glUniform4f(object, vec.x, vec.y, vec.z, vec.w);	
}

// ##################################### vec1 ##################################### 
void FrameWork::Shader::setUniform1i(const char* name, const int vec)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//エラー処理
	glUniform1i(object,vec);
}

// ##################################### vec2 ##################################### 
void FrameWork::Shader::setUniform2i(const char* name, const glm::ivec2 vec)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//エラー処理
	glUniform2i(object,vec.x,vec.y);
}

// ##################################### vec3 ##################################### 
void FrameWork::Shader::setUniform3i(const char* name, const glm::ivec3 vec)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//エラー処理
	glUniform3i(object,vec.x, vec.y,vec.z);
}

// ##################################### vec4 ##################################### 
void FrameWork::Shader::setUniform4i(const char* name, const glm::ivec4 vec)
{	
	const GLuint object = glGetUniformLocation(program,name);
	if (object == -1) { assert(0); }	//エラー処理
	glUniform4i(object, vec.x, vec.y, vec.z, vec.w);	
}

// ##################################### mat2 ##################################### 
void FrameWork::Shader::setUniformMatrix2fv(const char* name, const glm::mat2 m)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//エラー処理
	glUniformMatrix2fv(object,1,false,glm::value_ptr(m));
}

// ##################################### mat3 ##################################### 
void FrameWork::Shader::setUniformMatrix3fv(const char* name, const glm::mat3 m)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//エラー処理
	glUniformMatrix3fv(object, 1, false, glm::value_ptr(m));
}

// ##################################### mat4 ##################################### 
void FrameWork::Shader::setUniformMatrix4fv(const char* name, const glm::mat4 m)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//エラー処理
	glUniformMatrix4fv(object, 1, false, glm::value_ptr(m));
}

// ##################################### Uniform　配列 設定 ##################################### 

// ##################################### vec1 ##################################### 

void FrameWork::Shader::setUniform1fv(const char* name, const int count,const GLfloat vec[])
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//エラー処理

	glUniform1fv(object,count, vec);
}

// ##################################### Program Uniform 設定 ##################################### 

// ##################################### vec1 ##################################### 
void  FrameWork::Shader::setProgramUniform1i(const char* name,const GLuint location, const int vec)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//エラー処理
	glProgramUniform1i(program,location,vec);
}

// ##################################### Uniform sampler2D　設定 ##################################### 
void FrameWork::Shader::setUniformSampler2D(const char* name,const GLuint num, const GLuint textureID)
{
	const GLuint object = glGetUniformLocation(program, name);
	if (object == -1) { assert(0); }	//エラー処理


	glUniform1i(object,num);
	glActiveTexture(GL_TEXTURE0 + num);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

// ##################################### 削除 ##################################### 
void FrameWork::Shader::Delete()
{
	glDeleteProgram(program);
}

// ##################################### デストラクタ ##################################### 
FrameWork::Shader::~Shader()
{
	
}