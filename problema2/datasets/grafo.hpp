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

    tGrafo (int n);

    ~tGrafo();
    
    int nVertex();
    
    int nEdges();

    tVertice first (tVertice v);
    
    tVertice next (tVertice v, tVertice w);

    void setEdge (tVertice v1, tVertice v2, int peso);

    void deleteEdge (tVertice v1, tVertice v2);
   
    int isEdge (tVertice v1, tVertice v2);
    
    int weight (tVertice v1, tVertice v2);
  
    int getMark (tVertice v);
  
    void setMark (tVertice v, int val);

    tVertice maxGrado();

    tVertice secondCharacter(int* D);

    void restablecerMarca();

    int sumaDeArcos();
};

#endif