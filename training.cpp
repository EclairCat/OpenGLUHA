#include "include/glad/glad.h"
#include "GLFW/glfw3.h"
#include "iostream"
#include "vector"

//Initialisation des Shaders,  Petits programmes qui sont chargé dans le GPU
// Vertex Shader,
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";


int nb_flocon = 1 ;

std::vector<GLfloat> dessinFlocon(GLfloat vertex[]){

    int flocon_done = nb_flocon;

    int size = 9;

    std::vector<GLfloat> new_vertex;

    while(flocon_done != 0){
        int i = 0;

        while(i < size-3){
            //On crée les 3 sommet entre les 2 points
            GLfloat p1[] = {0,0};
            GLfloat p2[] = {0,0};
            GLfloat p3[] = {0,0};

            GLfloat longueurX = (vertex[i] - vertex[i+3]) /3;
            GLfloat longueurY = (vertex[i+1] - vertex[i+4]) /3;

            p1[0] =  vertex[i] + longueurX ;
            p1[1] =  vertex[i] + longueurY ;

            p2[0] =  vertex[i] + 1.5*longueurX + 0.8660254* longueurY;
            p2[1] =  vertex[i] - 0.8660254* longueurX + 1.5*longueurY ;

            p3[0] =  vertex[i] + 2.0*longueurX ;
            p3[1] =  vertex[i] + 2.0*longueurY ;

            //On ajoute le sommet de départ puis les 3 autre sommet
            new_vertex.push_back(vertex[i]);
            new_vertex.push_back(vertex[i+1]);
            new_vertex.push_back(vertex[i+2]);

            new_vertex.push_back(p1[0]);
            new_vertex.push_back(p1[1]);
            new_vertex.push_back(0.0f);

            new_vertex.push_back(p2[0]);
            new_vertex.push_back(p2[1]);
            new_vertex.push_back(0.0f);

            new_vertex.push_back(p3[0]);
            new_vertex.push_back(p3[1]);
            new_vertex.push_back(0.0f);

            i = i+3;
        }

        //on Ajoute le dernier sommet
        new_vertex.push_back(vertex[size-3]);
        new_vertex.push_back(vertex[size-2]);
        new_vertex.push_back(vertex[size-1]);

        flocon_done --;
    }

    return new_vertex;

}

int main() {

    //Initialisation du GLFW
    glfwInit();

    //On donne la version qu'on va utiliser qui est ici la v3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    //On indique quel paquet de fonction on va utiliser (Core-Profile)
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    //On Créer la fenêtre avec un pointeur de la classe GLFWwindow (largeur, hauteur, titre, fullscreen ?, null)
    GLFWwindow* fenetre = glfwCreateWindow(800,800,"Training OpenGl", NULL, NULL);

    //Verification si la fenêtre à bien été build
    if(fenetre == NULL)
    {
        std::cout << "Fenêtre Non créer! Erreur au glfwCreateWindow" << std::endl;
        glfwTerminate();
        return -1;
    }
    //On indique a GLWF quel fenêtre on veut utiliser.
    glfwMakeContextCurrent(fenetre);

    //on va initialiser Glad pour loader les fonctionalités.
    gladLoadGL();

    //Indique la surface de la fenêtre afin qu'OpenGl fasse le rendu.
    glViewport(0,0,800,800);

    // Creation du Vertex Shader Object et récupère ses références
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Liaison du programme du vertex shader au vertex shader object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // compilation du vertex shader dans la machine
    glCompileShader(vertexShader);

    // Creation du Fragment Shader Object et récupère ses références
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Liaison du programme du fragment shader au fragment shader object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // compilation du fragment shader dans la machine
    glCompileShader(fragmentShader);

    // Creation du programme shader
    GLuint shaderProgram = glCreateProgram();
    // Liaison du Vertex et Fragment shaders au programme
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Liaison du programme shader dans la machine
    glLinkProgram(shaderProgram);

    // Nettoyage de la memoire
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //on va clear la couleur du buffer demander une autre couleur avec un code RGB (la dernière valeur c'est la transparence)
    glClearColor(0.3f,0.3f,0.3f,1.0f);

    //on execute la commande ci dessus sur le buffer de la couleur.
    glClear(GL_COLOR_BUFFER_BIT);

    //Coordonées des points

    GLfloat vertices[] = {
           0.5, -0.5, 0.0f,  //Sommet Bas Droite
           -0.5,-0.5, 0.0f,  //Sommet Bas Gauche
            0, 0.5, 0.0f,   //Sommet Haut
    };

    //Flocon de Koch
    std::vector<GLfloat> new_vect = dessinFlocon(vertices);
    GLfloat new_vec_to_array[new_vect.size()];
    std::copy(new_vect.begin(), new_vect.end(), new_vec_to_array);



    // Création du Vertex Array Object et du Vertex Buffer Object
    GLuint VAO, VBO;

    // Generation d'une Zone mémoire pour nos objects
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // On va Biend le Vertex Array Object en premier
    glBindVertexArray(VAO);

    // On Bind le Vertext Buffet Object precisant le type.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // On indique nos sommets dans le VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(new_vec_to_array), new_vec_to_array, GL_STATIC_DRAW);

    // Configuration des attributs du Vertex.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Activation du Vertex Attribute comme ça OpenGL sait comment l'utiliser
    glEnableVertexAttribArray(0);

    //du moment que la fenêtre est pas fermer, le code va boucler.
    while (!glfwWindowShouldClose(fenetre)) {

        // On met en place la couleur du background
        glClearColor(0.3f,0.3f,0.6f,1.0f);

        // On va clear le buffer du back pour mettre la couleur en palce
        glClear(GL_COLOR_BUFFER_BIT);

        // On indique le program à utiliser pour OpenGL
        glUseProgram(shaderProgram);

        // On indique le VAO que OpenGL va utiliser
        glBindVertexArray(VAO);

        // On Dessine notre Triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // On Change de buffer pour afficher le resultat.
        glfwSwapBuffers(fenetre);

        //on initialise les fonctionalité de la fenêtre (tel que la bouger, changer sa taille etc...) sinon on ne pourra pas interargir avec.
        glfwPollEvents();
    }

    // On Fait un ménage de la zone mémoire
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    //Une fois la fenêtre utiliser, il faut la supprimer.
    glfwDestroyWindow(fenetre);
    glfwTerminate(); //Fermeture du GLFW
    return 0;
};

