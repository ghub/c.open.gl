#include <thread>

#include <GLFW/glfw3.h>

int main()
{
    glfwInit();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    glfwTerminate();
}
