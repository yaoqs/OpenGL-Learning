// proctex.cpp
// OpenGL SuperBible, Chapter 17
// Demonstrates procedural texture mapping
// Program by Benjamin Lipchak

#include "../../shared/gltools.h"   // OpenGL toolkit
#include "../../shared/glFrame.h"   // OpenGL toolkit

#include <stdio.h>

#define CHECKERBOARD      0
#define BEACHBALL         1
#define TOYBALL           2
#define TOTAL_SHADER_SETS 3

GLuint fShader[TOTAL_SHADER_SETS]; // shader object names
GLuint vShader[TOTAL_SHADER_SETS]; 
GLuint progObj[TOTAL_SHADER_SETS]; 
GLboolean needsValidation[TOTAL_SHADER_SETS];
char *shaderNames[TOTAL_SHADER_SETS] = {"checkerboard", "beachball", "toyball"};

GLint whichShader = CHECKERBOARD;       // current shader

GLint windowWidth = 1024;               // window size
GLint windowHeight = 768;

GLint mainMenu, shaderMenu;             // menu handles

GLfloat cameraPos[] = { 50.0f, 50.0f, 150.0f, 1.0f};
GLdouble cameraZoom = 0.4;

GLfloat lightPos[] = { 140.0f, 250.0f, 140.0f, 1.0f};

GLfloat lightRotation = 0.0f;
GLint tess = 75;

#define MAX_INFO_LOG_SIZE 2048

// Load shader from disk into a null-terminated string
GLchar *LoadShaderText(const char *fileName)
{
    GLchar *shaderText = NULL;
    GLint shaderLength = 0;
    FILE *fp;

    fp = fopen(fileName, "r");
    if (fp != NULL)
    {
        while (fgetc(fp) != EOF)
        {
            shaderLength++;
        }
        rewind(fp);
        shaderText = (GLchar *)malloc(shaderLength+1);
        if (shaderText != NULL)
        {
            fread(shaderText, 1, shaderLength, fp);
        }
        shaderText[shaderLength] = '\0';
        fclose(fp);
    }

    return shaderText;
}

// Compile shaders
void PrepareShader(GLint shaderNum)
{
    char fullFileName[255];
    GLchar *shString;
    const GLchar *shStringPtr[1];
    GLint success;

    // Create shader objects and specify shader text
    sprintf(fullFileName, "./shaders/%s.vs", shaderNames[shaderNum]);
    shString = LoadShaderText(fullFileName);
    if (!shString)
    {
        fprintf(stderr, "Unable to load \"%s\"\n", fullFileName);
        Sleep(5000);
        exit(0);
    }
    vShader[shaderNum] = glCreateShader(GL_VERTEX_SHADER);
    shStringPtr[0] = shString;
    glShaderSource(vShader[shaderNum], 1, shStringPtr, NULL);
    free(shString);

    // Compile shaders and check for any errors
    glCompileShader(vShader[shaderNum]);
    glGetShaderiv(vShader[shaderNum], GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[MAX_INFO_LOG_SIZE];
        glGetShaderInfoLog(vShader[shaderNum], MAX_INFO_LOG_SIZE, NULL, infoLog);
        fprintf(stderr, "Error in vertex shader #%d compilation!\n", shaderNum);
        fprintf(stderr, "Info log: %s\n", infoLog);
        Sleep(10000);
        exit(0);
    }

    sprintf(fullFileName, "./shaders/%s.fs", shaderNames[shaderNum]);
    shString = LoadShaderText(fullFileName);
    if (!shString)
    {
        fprintf(stderr, "Unable to load \"%s\"\n", fullFileName);
        Sleep(5000);
        exit(0);
    }
    fShader[shaderNum] = glCreateShader(GL_FRAGMENT_SHADER);
    shStringPtr[0] = shString;
    glShaderSource(fShader[shaderNum], 1, shStringPtr, NULL);
    free(shString);

    // Compile shaders and check for any errors
    glCompileShader(fShader[shaderNum]);
    glGetShaderiv(fShader[shaderNum], GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[MAX_INFO_LOG_SIZE];
        glGetShaderInfoLog(fShader[shaderNum], MAX_INFO_LOG_SIZE, NULL, infoLog);
        fprintf(stderr, "Error in fragment shader #%d compilation!\n", shaderNum);
        fprintf(stderr, "Info log: %s\n", infoLog);
        Sleep(10000);
        exit(0);
    }
    else
    {
        GLchar infoLog[MAX_INFO_LOG_SIZE];
        glGetShaderInfoLog(fShader[shaderNum], MAX_INFO_LOG_SIZE, NULL, infoLog);
        //fprintf(stderr, "Fragment shader #%d info log: %s\n", shaderNum, infoLog);
    }

    // Create program object, attach shader, then link
    progObj[shaderNum] = glCreateProgram();
    glAttachShader(progObj[shaderNum], vShader[shaderNum]);
    glAttachShader(progObj[shaderNum], fShader[shaderNum]);

    glLinkProgram(progObj[shaderNum]);
    glGetProgramiv(progObj[shaderNum], GL_LINK_STATUS, &success);
    if (!success)
    {
        GLchar infoLog[MAX_INFO_LOG_SIZE];
        glGetProgramInfoLog(progObj[shaderNum], MAX_INFO_LOG_SIZE, NULL, infoLog);
        fprintf(stderr, "Error in program #%d linkage!\n", shaderNum);
        fprintf(stderr, "Info log: %s\n", infoLog);
        Sleep(10000);
        exit(0);
    }
    else
    {
        GLchar infoLog[MAX_INFO_LOG_SIZE];
        glGetProgramInfoLog(progObj[shaderNum], MAX_INFO_LOG_SIZE, NULL, infoLog);
        //fprintf(stderr, "Program #%d info log: %s\n", shaderNum, infoLog);
    }

    // Program object has changed, so we should revalidate
    needsValidation[shaderNum] = GL_TRUE;
}

// Called to draw scene objects
void DrawModels(void)
{
    M3DVector3f lightPosEye;
    M3DMatrix44f mv;

    // Transform light position to eye space
    glPushMatrix();
    glRotatef(lightRotation, 0.0, 1.0, 0.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, mv);
    m3dTransformVector3(lightPosEye, lightPos, mv);
    glPopMatrix();

    GLint uniformLoc = glGetUniformLocation(progObj[whichShader], "lightPos");
    if (uniformLoc != -1)
    {
        glUniform3fv(uniformLoc, 1, lightPosEye);
    }

    // Draw sphere
    glutSolidSphere(50.0f, tess, tess);
}

// Called to draw scene
void RenderScene(void)
{
    // Track camera angle
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (windowWidth > windowHeight)
    {
        GLdouble ar = (GLdouble)windowWidth / (GLdouble)windowHeight;
        glFrustum(-ar * cameraZoom, ar * cameraZoom, -cameraZoom, cameraZoom, 1.0, 1000.0);
    }
    else
    {
        GLdouble ar = (GLdouble)windowHeight / (GLdouble)windowWidth;
        glFrustum(-cameraZoom, cameraZoom, -ar * cameraZoom, ar * cameraZoom, 1.0, 1000.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 
              0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glViewport(0, 0, windowWidth, windowHeight);
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    
    // Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Validate our shader before first use
    if (needsValidation[whichShader])
    {
        GLint success;

        glValidateProgram(progObj[whichShader]);
        glGetProgramiv(progObj[whichShader], GL_VALIDATE_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[MAX_INFO_LOG_SIZE];
            glGetProgramInfoLog(progObj[whichShader], MAX_INFO_LOG_SIZE, NULL, infoLog);
            fprintf(stderr, "Error in program #%d validation!\n", whichShader);
            fprintf(stderr, "Info log: %s\n", infoLog);
            Sleep(10000);
            exit(0);
        }

        needsValidation[whichShader] = GL_FALSE;
    }
    
    // Draw objects in the scene
    DrawModels();
    
    if (glGetError() != GL_NO_ERROR)
        fprintf(stderr, "GL Error!\n");

    // Flush drawing commands
    glutSwapBuffers();
}

// This function does any needed initialization on the rendering
// context. 
void SetupRC()
{
    GLint i;

    fprintf(stdout, "Procedural Texture Mapping Demo\n\n");

    // Make sure required functionality is available!
    if (!GLEE_VERSION_2_0 && (!GLEE_ARB_fragment_shader || 
                              !GLEE_ARB_vertex_shader || 
                              !GLEE_ARB_shader_objects || 
                              !GLEE_ARB_shading_language_100))
    {
        fprintf(stderr, "GLSL extensions not available!\n");
        Sleep(2000);
        exit(0);
    }

    fprintf(stdout, "Controls:\n");
    fprintf(stdout, "\tRight-click for menu\n\n");
    fprintf(stdout, "\tR/L arrows\t+/- rotate light\n\n");
    fprintf(stdout, "\tU/D arrows\t+/- increase/decrease tesselation\n\n");
    fprintf(stdout, "\tx/X\t\tMove +/- in x direction\n");
    fprintf(stdout, "\ty/Y\t\tMove +/- in y direction\n");
    fprintf(stdout, "\tz/Z\t\tMove +/- in z direction\n\n");
    fprintf(stdout, "\tq\t\tExit demo\n\n");
    
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

    // Misc. state
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);

    // Load and compile shaders
    for (i = 0; i < TOTAL_SHADER_SETS; i++)
    {
        PrepareShader(i);
    }

    // Install first shader
    glUseProgram(progObj[whichShader]);
}

void ProcessMenu(int value)
{
    whichShader = value - 1;
    {
        char menuEntry[128];
        sprintf(menuEntry, "Choose shader set (currently \"%s\")", shaderNames[whichShader]);
        glutSetMenu(mainMenu);
        glutChangeToSubMenu(1, menuEntry, shaderMenu);
    }
    glUseProgram(progObj[whichShader]);

    // Refresh the Window
    glutPostRedisplay();
}

void KeyPressFunc(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x':
        cameraPos[0] += 5.0f;
        break;
    case 'X':
         cameraPos[0] -= 5.0f;
        break;
    case 'y':
        cameraPos[1] += 5.0f;
        break;
    case 'Y':
        cameraPos[1] -= 5.0f;
        break;
    case 'z':
        cameraPos[2] += 5.0f;
        break;
    case 'Z':
        cameraPos[2] -= 5.0f;
        break;
    case 'q':
    case 'Q':
    case 27 : /* ESC */
        exit(0);
    }

    // Refresh the Window
    glutPostRedisplay();
}

void SpecialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        lightRotation -= 5.0f;
        break;
    case GLUT_KEY_RIGHT:
        lightRotation += 5.0f;
        break;
    case GLUT_KEY_UP:
        tess += 5;
        break;
    case GLUT_KEY_DOWN:
        tess -= 5;
        if (tess < 5) tess = 5;
        break;
    default:
        break;
    }

    // Refresh the Window
    glutPostRedisplay();
}

void ChangeSize(int w, int h)
{
    windowWidth = w;
    windowHeight = h;
}

int main(int argc, char* argv[])
{
    GLint i;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Procedural Texture Mapping Demo");
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(KeyPressFunc);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);

    SetupRC();

    // Create the menus
    shaderMenu = glutCreateMenu(ProcessMenu);
    for (i = 0; i < TOTAL_SHADER_SETS; i++)
    {
        char menuEntry[128];
        sprintf(menuEntry, "\"%s\"", shaderNames[i]);
        glutAddMenuEntry(menuEntry, 1+i);
    }

    mainMenu = glutCreateMenu(ProcessMenu);
    {
        char menuEntry[128];
        sprintf(menuEntry, "Choose fragment shader (currently \"%s\")", shaderNames[0]);
        glutAddSubMenu(menuEntry, shaderMenu);
    }
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();

    if (glDeleteProgram && glDeleteShader)
    {
        for (i = 0; i < TOTAL_SHADER_SETS; i++)
        {
            glDeleteProgram(progObj[i]);
            glDeleteShader(vShader[i]);
            glDeleteShader(fShader[i]);
        }
    }

    return 0;
}
