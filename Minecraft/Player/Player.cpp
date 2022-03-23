#include "Player.h"
#include "../World/Chunk/ChunkContainer/ChunkContainer.h"
#include "../World/Ray/Ray.h"
#include "../Application/Application.h"


Camera* camera;

Player::Player(IO* io) : m_IO(io){
    m_Camera = new Camera(io);


}

void Player::Update() {
    m_Camera->Update();


    if(m_IO->KeyboardClicked[GLFW_KEY_ESCAPE]){
        Application::SceneManager->UnloadScene("GameView");
        Application::SceneManager->LoadScene("MainMenu");
    }
    if(m_IO->KeyboardClicked[GLFW_KEY_L]){
        if(m_Filled){
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        }else{
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        }
        m_Filled = !m_Filled;
    }
    if(m_IO->KeyboardClicked[GLFW_KEY_LEFT_CONTROL]){
        m_Cursor = !m_Cursor;
        GLFWwindow* window = reinterpret_cast<GLFWwindow*>(m_IO->Window);
        if(m_Cursor){
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }else{
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
    if(m_IO->Keyboard[GLFW_KEY_W]){
        m_Position += m_Camera->GetCameraSpeed() * m_Camera->GetCameraFront();
    }
    if(m_IO->Keyboard[GLFW_KEY_A]){
        m_Position -= glm::normalize(glm::cross(m_Camera->GetCameraFront(), m_Camera->GetCameraUp())) * m_Camera->GetCameraSpeed();
    }
    if(m_IO->Keyboard[GLFW_KEY_S]){
        m_Position -= m_Camera->GetCameraSpeed() * m_Camera->GetCameraFront();
    }
    if(m_IO->Keyboard[GLFW_KEY_D]){
        m_Position += glm::normalize(glm::cross(m_Camera->GetCameraFront(), m_Camera->GetCameraUp())) * m_Camera->GetCameraSpeed();
    }
    if(m_IO->Keyboard[GLFW_KEY_SPACE]){
        m_Position += glm::vec3(0.f, m_Camera->GetCameraSpeed(), 0.f);
    }
    if(m_IO->Keyboard[GLFW_KEY_LEFT_SHIFT]){
        m_Position += glm::vec3(0.f, -m_Camera->GetCameraSpeed(), 0.f);
    }

    m_Camera->SetCameraPosition(m_Position + glm::vec3(0,1,0));
}

void Player::Render() {

}
