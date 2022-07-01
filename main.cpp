#include <Eigen/Dense>
#include <iostream>
using namespace std;
using namespace Eigen;

template <typename T>
struct vec_selector
{
};

template <>
struct vec_selector<double>
{
    using vec3_type = Vector3d;
    using vec2_type = Vector2d;
    using SMat3_type = double[3][3];
};

template <>
struct vec_selector<float>
{
    using vec3_type = Vector3f;
    using vec2_type = Vector2f;
    using SMat3_type = float[3][3];
};

template <typename P>
using vec3_select_t = typename vec_selector<P>::vec3_type;

template <typename P>
using vec2_select_t = typename vec_selector<P>::vec2_type;

template <typename P>
using SMat3_select_t = typename vec_selector<P>::SMat3_type;

template <typename P>
struct Vertex
{
    vec3_select_t<P> position;
    vec3_select_t<P> normal;
    vec2_select_t<P> texcoords;
    SMat3_select_t<P> MatR;

    void SetNormal(vec3_select_t<P> SF);
    void GetMatR(P SR[3][3]);
};

template <typename P>
void Vertex<P>::SetNormal(vec3_select_t<P> SF)
{
    normal = SF;
};
template void Vertex<double>::SetNormal(vec3_select_t<double> SF);
template void Vertex<float>::SetNormal(vec3_select_t<float> SF);

template <typename P>
void Vertex<P>::GetMatR(P SR[3][3])
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            SR[i][j] = MatR[i][j];
};
template void Vertex<double>::GetMatR(double SR[3][3]);
template void Vertex<float>::GetMatR(float SR[3][3]);

// Main Function
int main()
{
    Vertex<float> YIN;
    YIN.position << 1, 2, 3;

    cout << YIN.position.transpose() << endl;
    vec3_select_t<float> TY;
    TY = YIN.position;

    YIN.SetNormal(YIN.position);

    cout << YIN.normal.transpose() << endl;
    Vector3f K = YIN.normal;

    YIN.MatR[0][0] = 1;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            cout << YIN.MatR[i][j] << (j == 2 ? "\n" : ", ");

    float UI[3][3];

    YIN.GetMatR(UI);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            cout << UI[i][j] << (j == 2 ? "\n" : ", ");
    return 0;
}
