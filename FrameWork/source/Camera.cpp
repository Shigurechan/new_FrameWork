#include "../header/Camera.hpp"


#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include "../header/Window.hpp"
#include "../header/Camera_Use.hpp"

std::shared_ptr<FrameWork::Camera> FrameWork::currentCamera = nullptr;


// #####################################  クライアントカメラ　設定　##################################### 
void FrameWork::SetCurrentCamera(std::shared_ptr<FrameWork::Camera> c)
{
	FrameWork::currentCamera = c;
}

// #####################################　クライアントカメラ　取得　##################################### 
std::shared_ptr<FrameWork::Camera> FrameWork::GetCurrentCamera()
{
	return currentCamera;
}

// ##################################### 初期化　##################################### 
FrameWork::Camera::Camera()
{	

	// レンダリングポリゴン
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);

	shader = std::make_shared<FrameWork::Shader>();

	shader->Load("asset/shader/FrameBuffer.vert", "asset/shader/FrameBuffer.frag");

	shader->setEnable();
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), &quad, GL_STATIC_DRAW);

	GLuint attrib = shader->getAttribLocation("vertexPosition");
	glEnableVertexAttribArray(attrib);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	shader->setBindAttribLocation("vertexPosition");

	attrib = shader->getAttribLocation("vertexUV");
	glEnableVertexAttribArray(attrib);
	glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	shader->setBindAttribLocation("vertexUV");

	shader->setDisable();
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	

	//MSAA バッファ
	glGenFramebuffers(1, &frameBufferFBO);	
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferFBO);	
	glGenTextures(1, &frameBuffer);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, frameBuffer);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 8, GL_RGB, currentWindow->getSize().x, currentWindow->getSize().y, GL_TRUE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, frameBuffer, 0);
	

	//レンダリングバッファ
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 8, GL_DEPTH24_STENCIL8, currentWindow->getSize().x, currentWindow->getSize().y);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	//MSAA　アタッチ
	GLuint attachment = GL_COLOR_ATTACHMENT0;
	glDrawBuffers(1,&attachment);
	

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cerr << "Framebuffer is not complete: 0x" << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;
		assert(0);
	}

	glBindFramebuffer(GL_FRAMEBUFFER,0);


	//深度マップ
	glGenFramebuffers(1, &depthMapFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, currentWindow->getSize().x, currentWindow->getSize().y, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);

	//カラーバッファ
	glGenFramebuffers(1, &colorBufferFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, colorBufferFBO);
	glGenTextures(1, &colorBuffer);
	glBindTexture(GL_TEXTURE_2D, colorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, currentWindow->getSize().x, currentWindow->getSize().y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer, 0);	// we only need a color buffer
	

	position = glm::vec3(0,0,1);	//座標
	vecLook = glm::vec3(0,0,-1);	//向き

	setPosition(position);
	setLook(vecLook);

}

// ##################################### フレームバッファ　クリア　##################################### 
void FrameWork::Camera::ClearBuffer()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferFBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferFBO);
	//glViewport(0, 0, currentWindow->getSize().x, currentWindow->getSize().y);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);


	setPosition(position);
	setLook(vecLook);


}

// ##################################### フレームバッファ　描画　##################################### 
void FrameWork::Camera::RendererBuffer()
{

	glDepthFunc(GL_LESS);
	glBindFramebuffer(GL_FRAMEBUFFER,0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	shader->setEnable();
	
	glBindFramebuffer(GL_READ_FRAMEBUFFER, frameBuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, colorBufferFBO);
	glBlitFramebuffer(0, 0, currentWindow->getSize().x, currentWindow->getSize().y, 0, 0, currentWindow->getSize().x, currentWindow->getSize().y, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	shader->setUniformSampler2D("screenTexture", 0,colorBufferFBO);
	glDrawArrays(GL_TRIANGLES,0,6);

	shader->setDisable();	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
}

// ##################################### 座標を設定 ##################################### 
void FrameWork::Camera::setPosition(glm::vec3 p)
{
	position = p;	//座標

	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 cameraDirection = glm::normalize(position - vecLook);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(vecLook, cameraRight);

	view = glm::lookAt(position, position + vecLook, up);
}

// ##################################### 視線を設定 ##################################### 
void FrameWork::Camera::setLook(glm::vec3 l)
{
	vecLook = l;		//向き

	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::vec3 cameraDirection = glm::normalize(position - vecLook);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(vecLook, cameraRight);

	view = glm::lookAt(position, position + vecLook,up);
}

// ##################################### 座標を取得 ##################################### 
glm::vec3 FrameWork::Camera::getPosition()
{
	return position;
}

// #####################################　視線を取得 ##################################### 
glm::vec3 FrameWork::Camera::getLook()
{
	return vecLook;
}

// ##################################### 透視投影行列 ##################################### 
glm::mat4 FrameWork::Camera::getViewPerspective()
{
	return glm::perspective(glm::radians(90.0f), ((float)currentWindow->getSize().x / (float)currentWindow->getSize().y), 0.1f, 1000.0f) * view;
}

// ##################################### 正射投影行列　##################################### 
glm::mat4 FrameWork::Camera::getViewOrthographic()
{
	return glm::ortho(-(float)currentWindow->getSize().x / 2.0f, (float)currentWindow->getSize().x / 2.0f, 
	-(float)currentWindow->getSize().y /2.0f , (float)currentWindow->getSize().y / 2.0f,0.1f, 100.0f) * view;
}

// ##################################### カラーバッファ　取得　##################################### 
GLuint FrameWork::Camera::getColorBuffer()
{
	return frameBuffer;
}

// ##################################### 深度バッファ　取得　##################################### 
GLuint FrameWork::Camera::getDepthBuffer()
{
	return depthMap;
}

// ##################################### カラーバッファ　設定　##################################### 
void FrameWork::Camera::setColorBuffer(GLuint frame)
{
	glDeleteTextures(1,&frameBuffer);
	frameBuffer = frame;
}

// ##################################### 深度バッファ　設定　##################################### 
void FrameWork::Camera::setDepthBuffer(GLuint frame)
{
	glDeleteTextures(1,&depthMap);
	depthMap = frame;
}

// ###################### デストラクタ ###################### 
FrameWork::Camera::~Camera()
{

}