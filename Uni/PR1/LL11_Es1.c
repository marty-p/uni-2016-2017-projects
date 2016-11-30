#include <stdio.h>
#include <stdlib.h>
/*1. Implementare una struttura Vector2D composta da due componenti x e y. Implementare una funzione per la somma e il prodotto, componente per componente, di due vettori.
Implementare successivamente una struttura e le relative operazioni che gestisce un Vector3D.*/
typedef struct {
    float x;
    float y;
} Vector2D;

typedef struct {
    float x;
    float y;
    float z;
} Vector3D;

Vector2D somma(Vector2D a1, Vector2D a2);
void somma_ptr(Vector2D a1, Vector2D a2, Vector2D * res);
Vector2D prodotto(Vector2D a1, Vector2D a2);
void prodotto_ptr(Vector2D a1, Vector2D a2, Vector2D * res);
void printa_v2d(Vector2D * a1);

Vector3D somma3d(Vector3D a1, Vector3D a2);
void somma3d_ptr(Vector3D a1, Vector3D a2, Vector3D * res);
Vector3D prodotto3d(Vector3D a1, Vector3D a2);
void prodotto3d_ptr(Vector3D a1, Vector3D a2, Vector3D * res);
void printa_v3d(Vector3D * a1);

int main()
{
    Vector2D a1 = {11, 22};
    Vector2D a2 = {33, 44};
    Vector2D res_somma;
    Vector2D res_prodotto;

    Vector3D a1_3 = {11, 22, 33};
    Vector3D a2_3 = {44, 55, 66};
    Vector3D res_somma3;
    Vector3D res_prodotto3;

    somma_ptr(a1, a2, &res_somma);
    printa_v2d(&res_somma);
    prodotto_ptr(a1, a2, &res_prodotto);
    printa_v2d(&res_prodotto);

    somma3d_ptr(a1_3, a2_3, &res_somma3);
    printa_v3d(&res_somma3);
    prodotto3d_ptr(a1_3, a2_3, &res_prodotto3);
    printa_v3d(&res_prodotto3);

    return 0;
}

Vector2D somma(Vector2D a1, Vector2D a2)
{
    Vector2D res = {};
    res.x = a1.x + a2.x;
    res.y = a1.y + a2.y;
    return res;
}

void somma_ptr(Vector2D a1, Vector2D a2, Vector2D * res)
{
    res->x = a1.x + a2.x;
    res->y = a1.y + a2.y;
}

Vector2D prodotto(Vector2D a1, Vector2D a2)
{
    Vector2D res = {};
    res.x = a1.x * a2.x;
    res.y = a1.y * a2.y;
    return res;
}

void prodotto_ptr(Vector2D a1, Vector2D a2, Vector2D * res)
{
    res->x = a1.x * a2.x;
    res->y = a1.y * a2.y;
}

void printa_v2d(Vector2D * a1)
{
    printf("x: %.2f, y: %.2f\n", a1->x, a1->y);
}

void somma3d_ptr(Vector3D a1, Vector3D a2, Vector3D * res)
{
    res->x = a1.x + a2.x;
    res->y = a1.y + a2.y;
    res->z = a1.z + a2.z;
}

void prodotto3d_ptr(Vector3D a1, Vector3D a2, Vector3D * res)
{
    res->x = a1.x * a2.x;
    res->y = a1.y * a2.y;
    res->z = a1.z * a2.z;
}

void printa_v3d(Vector3D * a1)
{
    printf("x: %.2f, y: %.2f, z: %.2f\n", a1->x, a1->y, a1->z);
}

