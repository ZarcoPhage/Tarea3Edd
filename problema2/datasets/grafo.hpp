#ifndef grafo_hpp
#define grafo_hpp

typedef int tVertice;



class tGrafo{

private:

    int nVert;
    int nEdg;
    int** p_matrix;
    int* Marca;
public:

    //Constructor.
    tGrafo (int n);

    //Destructor.
    ~tGrafo();
    
    //Número de vértices.
    int nVertex();

    //Número de arcos.
    int nEdges();

    //Devuelve el primer vecino de un vértice v dado (asume que los
    //vecinos de un vértice están ordenados por número de vértice).
    tVertice first (tVertice v);

    //Devuelve el menor vecino de v, cuya numeración es mayor a w,
    //si no existe dicho vecino, retorna el número de vértices del grafo.
    tVertice next (tVertice v, tVertice w);

    //Agrega un nuevo arco al grafo entre vértices v1 y v2 (no se
    //pueden agregar nuevos vértices).
    void setEdge (tVertice v1, tVertice v2, int peso);

    //Borra un arco existente entre vértices v1 y v2.
    void deleteEdge (tVertice v1, tVertice v2);

    //Indica si existe un arco entre los vértices.
    int isEdge (tVertice v1, tVertice v2);

    //Indica el peso del arco entre vértices, si no existe un arco, retorna 0.
    int weight (tVertice v1, tVertice v2);

    //Obtiene la marca del vértice.
    int getMark (tVertice v);

    //Marca el vértice con un valor.
    void setMark (tVertice v, int val);

    tVertice maxGrado();

    tVertice secondcharacter(int* D);

    void restablecermarca();
};

#endif