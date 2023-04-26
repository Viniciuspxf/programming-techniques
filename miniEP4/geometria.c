#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// public final Double PI = 3.14159265;
//
// class Quadrado {
//   public Double lado;
// }
//
// Quadrado q = new Quadrado();
// q.lado;


/*====================================================================*/

struct formaGeometrica;
typedef struct formaGeometrica* FormaGeometrica;

typedef void(*Imprime)(FormaGeometrica);
typedef float(*CalculaArea)(void*);

struct formaGeometrica {
  // Atributos auxiliares
  void* child;
  // Atributos pai
  char simbolo;

  // Método concreto
  Imprime imprime;
  // Método abstrato
  CalculaArea calculaArea;
};

void imprimeAreaFormaGeometrica(FormaGeometrica fg);

// Construtor
FormaGeometrica alocaFormaGeometrica() {
  return malloc(sizeof(struct formaGeometrica));
}
// Construtor
void inicializaFormaGeometrica(
    FormaGeometrica novaFormaGeometrica,
    void* child,
    char simbolo,
    CalculaArea calculaArea // override
) {
  novaFormaGeometrica->child = child;
  novaFormaGeometrica->simbolo = simbolo;
  novaFormaGeometrica->calculaArea = calculaArea;
  novaFormaGeometrica->imprime = imprimeAreaFormaGeometrica;

  return novaFormaGeometrica;
}

// Destrutor
void removeFormaGeometrica(FormaGeometrica fg) {
  fg->child = NULL;
  fg->simbolo = ' ';
  fg->calculaArea = NULL;
  fg->imprime = NULL;
  free(fg);
}

void imprimeAreaFormaGeometrica(FormaGeometrica fg) {
  fprintf(stderr, "Endereco forma geometrica %p", fg);
  printf("Forma Geometrica %c %f\n",
      fg->simbolo, fg->calculaArea(fg->child));
}

/*====================================================================*/

float calculaAreaQuadrado(void* this);

struct quadrado {
  FormaGeometrica super;
  float lado;
};
typedef struct quadrado* Quadrado;
// typedef float(*CalculaAreaQuadrado)(Quadrado);
// using CalculaAreaQuadrado = float(*)(Quadrado);

// Alocador
Quadrado alocaQuadrado() {
  Quadrado novoQuadrado = malloc(sizeof(*novoQuadrado));
  novoQuadrado->super = alocaFormaGeometrica();
  return novoQuadrado;
}
// Inicializador
void inicializaQuadrado(
    Quadrado novoQuadrado, float lado) {
  // Inicializa superclasse - super()
  inicializaFormaGeometrica(
      novoQuadrado->super,  // objeto superclasse
      novoQuadrado,         // referênciua subclasse
      'q',                  // Atributo superclasse
      calculaAreaQuadrado   // Método sobrescrito
  );

  // Inicializa atributos - this.bla = bla
  novoQuadrado->lado = lado;
}

// Construtor
Quadrado novoQuadrado(float lado) {
  Quadrado novoQuadrado = alocaQuadrado();
  inicializaQuadrado(novoQuadrado, lado);
  return novoQuadrado;
}

// Destrutor
void removeQuadrado(Quadrado q) {
  removeFormaGeometrica(q->super);
  q->super = NULL;
  q->lado = 0.0;
  free(q);
}

// float calculaAreaQuadrado(Quadrado quadrado) {
//   return quadrado->lado * quadrado->lado;
// }
float calculaAreaQuadrado(void* this) {
  Quadrado quadrado = (Quadrado) this;
  return quadrado->lado * quadrado->lado;
}

/*====================================================================*/

float calculaAreaRetangulo(void* this);

struct retangulo {
  FormaGeometrica super;
  float altura;
  float largura;
};
typedef struct retangulo* Retangulo;
// typedef float(*CalculaAreaRetangulo)(Retangulo);
// using CalculaAreaRetangulo = float(*)(Retangulo);

// Alocador
Retangulo alocaRetangulo() {
  Retangulo novoRetangulo = malloc(sizeof(*novoRetangulo));
  novoRetangulo->super = alocaFormaGeometrica();
  return novoRetangulo;
}
// Inicializador
void inicializaRetangulo(
    Retangulo novoRetangulo, float altura, float largura) {
  // Inicializa superclasse - super()
  inicializaFormaGeometrica(
      novoRetangulo->super,  // objeto superclasse
      novoRetangulo,         // referênciua subclasse
      'r',                   // Atributo superclasse
      calculaAreaRetangulo   // Método sobrescrito
  );

  // Inicializa atributos - this.bla = bla
  novoRetangulo->altura = altura;
  novoRetangulo->largura = largura;
}

// Construtor
Retangulo novoRetangulo(float altura, float largura) {
  Retangulo novoRetangulo = alocaRetangulo();
  inicializaRetangulo(novoRetangulo, altura, largura);
  return novoRetangulo;
}

// Destrutor
void removeRetangulo(Retangulo r) {
  removeFormaGeometrica(r->super);
  r->super = NULL;
  r->altura = 0.0;
  r->largura = 0.0;
  free(r);
}

// float calculaAreaRetangulo(Retangulo retangulo)  {
//   return retangulo->altura * retangulo->largura;
// }
float calculaAreaRetangulo(void* this)  {
  Retangulo retangulo = (Retangulo) this;
  return retangulo->altura * retangulo->largura;
}

/*====================================================================*/

float calculaAreaCirculo(void* this);

struct circulo {
  FormaGeometrica super;
  float raio;

  char simbolo;
  CalculaArea calculaArea;
};
typedef struct circulo* Circulo;
// typedef float(*CalculaAreaCirculo)(Circulo);
// using CalculaAreaCirculo = float(*)(Circulo);

// Alocador
Circulo alocaCirculo() {
  Circulo novoCirculo = malloc(sizeof(struct circulo));
  novoCirculo->super = alocaFormaGeometrica();
  return novoCirculo;
}
// Inicializador
void inicializaCirculo(Circulo novoCirculo, float raio) {
  // Inicializa superclasse - super()
  inicializaFormaGeometrica(
      novoCirculo->super,  // objeto superclasse
      novoCirculo,         // referênciua subclasse
      'c',                 // Atributo superclasse
      calculaAreaCirculo   // Método sobrescrito
  );

  // Inicializa atributos - this.bla = bla
  novoCirculo->raio = raio;
}

// Construtor
Circulo novoCirculo(float raio) {
  Circulo novoCirculo = alocaCirculo();
  inicializaCirculo(novoCirculo, raio);
  return novoCirculo;
}

// Destrutor
void removeCirculo(Circulo c) {
  removeFormaGeometrica(c->super);
  c->super = NULL;
  c->raio = 0.0;
  free(c);
}

float calculaAreaCirculo(void* this) {
  Circulo circulo = (Circulo) this;
  return M_PI * circulo->raio * circulo->raio;
}

/*====================================================================*/

int main(int /* argc */, char** /* argv */) {
  printf("Hello, World!\n");

  /* struct quadrado q = { .lado = 5.0 }; */
  Quadrado q = novoQuadrado(5.0);
  printf("Endereco quadrado %p\n", q);
  /* printf("Area quadrado %f\n", q->super->calculaArea(q)); */
  q->super->imprime(q->super);
  removeQuadrado(q);

  /* struct retangulo r = { .altura = 4.0, .largura = 3.0 }; */
  Retangulo r = novoRetangulo(4.0, 3.0);
  printf("Endereco retangulo %p\n", r);
  /* printf("Area retangulo %f\n", r->super->calculaArea(r)); */
  r->super->imprime(r->super);
  removeRetangulo(r);

  /* struct circulo c = { .raio = 1.0 }; */
  Circulo c = novoCirculo(1.0);
  printf("Endereco circulo %p\n", c);
  /* printf("Area circulo %f\n", c->super->calculaArea(c)); */
  c->super->imprime(c->super);
  removeCirculo(c);

  return 0;
}

//
//  |               |
//  |===============|
//  |     STACK     |
//  |===============|
//  |               |
//  |               |
//  |===============|
//  | altura        |
//  | largura       |
//  |---------------|
//  |      HEAP     |
//  |===============|
//  |      CODE     |
//  |===============|
//