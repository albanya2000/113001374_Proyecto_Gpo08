// Std. Includes
#include <string>
// GLEW
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>
// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"
// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;
// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );

// Camera
Camera camera( glm::vec3( 0.0f, 0.0f, 3.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
float rot = 0.0f;
float mov1 = 0.0f;
float mov2 = 0.0f;
float mov3 = 0.0f;

int main( ){
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Proyecto Final", nullptr, nullptr );
    if ( nullptr == window ){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent( window );
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) ){
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    // Setup and compile our shaders
    Shader shader( "Shaders/modelLoading.vs", "Shaders/modelLoading.frag" );
    Shader lampshader( "Shaders/lamp.vs", "Shaders/lamp.frag" );

    // Load models
    //Alfombra
    Model alfombra1((char*)"Models/Alfombra/alfombra1.obj");
    Model alfombra2((char*)"Models/Alfombra/alfombra2.obj");
    //Banco
    Model banco((char*)"Models/banco/banco.obj");
    //Casa
    Model casa((char*)"Models/casa/casaSinPuerta.obj");
    Model puerta((char*)"Models/casa/puerta.obj");
    //Chimenea
    Model chimenea((char*)"Models/chimenea/chimenea.obj");
    //Librero
    Model librero((char*)"Models/estante/Librero.obj");
    Model lObj1((char*)"Models/estante/Objeto1.obj");
    Model lObj2((char*)"Models/estante/Objeto2.obj");
    Model lObj3((char*)"Models/estante/Objeto3.obj");
    Model lObj4((char*)"Models/estante/Objeto4.obj");
    Model lObj5((char*)"Models/estante/Objeto5.obj");
    Model lObj6((char*)"Models/estante/Objeto6.obj");
    Model lObj7((char*)"Models/estante/Objeto7.obj");
    Model lObj8((char*)"Models/estante/Objeto8.obj");
    Model lObj9((char*)"Models/estante/Objeto9.obj");
    Model lObj10((char*)"Models/estante/Objeto10.obj");
    Model lObj11((char*)"Models/estante/Objeto11.obj");
    Model lObj12((char*)"Models/estante/Objeto12.obj");
    //Fon�grafo
    Model fonografo((char*)"Models/fonografo/fonografo.obj");
    Model disco((char*)"Models/fonografo/disco.obj");
    Model manivela((char*)"Models/fonografo/manivela.obj");
    //Lampara
    Model base((char*)"Models/lampara/base.obj");
    Model mampara((char*)"Models/lampara/mampara.obj");
    //Mesa
    Model mesa((char*)"Models/mesa/mesa.obj");
    //Sofa
    Model sofa((char*)"Models/sofa/sofa.obj");

    glm::mat4 projection = glm::perspective( camera.GetZoom( ), ( float )SCREEN_WIDTH/( float )SCREEN_HEIGHT, 0.1f, 100.0f );
    GLfloat vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f    // top left 

    };

    GLuint indices[] ={
        // Note that we start from 0!
        0,1,3,
        1,2,3

    };
    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    //// Load textures
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    int textureWidth, textureHeight, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    //unsigned char* image;
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
   /* image = stbi_load("images/star1.png", &textureWidth, &textureHeight, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    if (image){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(image);*/
    // Game loop
    while (!glfwWindowShouldClose(window)){
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        // Check and call events
        glfwPollEvents();
        DoMovement();
        // Clear the colorbuffer
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader.Use();
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        //Alfombra1
        glm::mat4 model(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        alfombra1.Draw(shader);
        glBindVertexArray(0);
        //Alfombra2
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        alfombra2.Draw(shader);
        glBindVertexArray(0);
        //Banco
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        banco.Draw(shader);
        glBindVertexArray(0);
        //Casa
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        casa.Draw(shader);
        glBindVertexArray(0);
        //puerta
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        puerta.Draw(shader);
        glBindVertexArray(0);
        //Chimenea
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        chimenea.Draw(shader);
        glBindVertexArray(0);
        //Estante
        //Librero
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        librero.Draw(shader);
        glBindVertexArray(0);
        //Objetos
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lObj1.Draw(shader);
        glBindVertexArray(0);
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lObj2.Draw(shader);
        glBindVertexArray(0);
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lObj3.Draw(shader);
        glBindVertexArray(0);
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lObj4.Draw(shader);
        glBindVertexArray(0);
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lObj5.Draw(shader);
        glBindVertexArray(0);
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lObj6.Draw(shader);
        glBindVertexArray(0);
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lObj7.Draw(shader);
        glBindVertexArray(0);
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lObj8.Draw(shader);
        glBindVertexArray(0);
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lObj9.Draw(shader);
        glBindVertexArray(0);
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lObj10.Draw(shader);
        glBindVertexArray(0);
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lObj11.Draw(shader);
        glBindVertexArray(0);
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lObj12.Draw(shader);
        glBindVertexArray(0);
        //Fon�grafo
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        fonografo.Draw(shader);
        glBindVertexArray(0);
        //Disco
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        disco.Draw(shader);
        glBindVertexArray(0);
        //Manivela
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        manivela.Draw(shader);
        glBindVertexArray(0);
        //Lampara
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        base.Draw(shader);
        glBindVertexArray(0);
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        mampara.Draw(shader);
        glBindVertexArray(0);
        //Mesa
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        mesa.Draw(shader);
        glBindVertexArray(0);
        //Sofa
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        sofa.Draw(shader);
        glBindVertexArray(0);

        //model = glm:: mat4(1);
        //model = glm::rotate(model, glm::radians(rot), glm::vec3(1.0f, 0.0f, 0.0f));

        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( ){
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] ){
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] ){
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] ){
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] ){
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }
    //Movimiento del sillon
    if (keys[GLFW_KEY_1]){
        mov1 += 0.5f;
    }
    //Movimiento de la Lampara
    if (keys[GLFW_KEY_2]) {
        mov2 += 0.5f;
    }
    //Giro de Disco y Manivela
    if (keys[GLFW_KEY_3]) {
        mov3 += 0.5f;
    }
    if (keys[GLFW_KEY_4]) {
        rot += 0.5f;
    }
    if (keys[GLFW_KEY_5]) {
        rot += 0.5f;
    }
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode ){
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action ){
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if ( key >= 0 && key < 1024 ){
        if ( action == GLFW_PRESS ){
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE ){
            keys[key] = false;
        }
    }
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos ){
    if ( firstMouse ){
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    lastX = xPos;
    lastY = yPos;
    camera.ProcessMouseMovement( xOffset, yOffset );
}

