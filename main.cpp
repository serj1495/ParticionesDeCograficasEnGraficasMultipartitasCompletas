#include<iostream>
#include "tests.cpp"
using namespace std;


int main(int argc, char *argv[])
{
    int opcion;

    cout << "   1. Desplegar los coárboles no etiquetados de n hojas." << endl;
    cout << "   2. Desplegar los coárboles de n hojas cuya raíz tiene etiqueta 0." << endl;
    cout << "   3. Desplegar los coárboles de n hojas cuya raíz tiene etiqueta 1." << endl;
    cout << "   4. Desplegar un coárbol binario por cada coárbol de n hojas con raíz 0." << endl;
    cout << "   5. Desplegar los coárboles con n hojas y determinar si son MPC." << endl;
    cout << "   6. Desplegar los coárboles con n hojas y determinar si son elementos de M2." << endl;
    cout << "   7. Desplegar un M2-certificado para los coárboles con n hojas." << endl;
    cout << "   8. Realizar un test de coherencia entre el identificador y el certificador." << endl;
    cout << "   9. Desplegar los coárboles con n hojas de cográficas que están en M2 y su cpm." << endl;
    cout << "   10.Desplegar los coárboles con n hojas y determinar si son elementos de (a,b)-M2" << endl;
    cout << "   11.Desplegar las obstrucciones mínimas de la clase (a,b)-M2 de a lo más 14 vértices" << endl;

    cout << endl << "Introduzca el número del problema que se va a ejecutar: ";
    cin >>opcion;

    cout << endl;

    int tam,alfa,beta;

    switch (opcion) {
        case(1):
            cout << "Introduzca el número de hojas en los coárboles que se generarán: ";
            cin >> tam;
            cout << endl << endl;
            test_nextTree(tam);
        break;
        case(2):
            cout << "Introduzca el número de hojas en los coárboles que se generarán: ";
            cin >> tam;
            cout << endl << endl;
            testCotreeConstructor(tam,0);
        break;
        case(3):
            cout << "Introduzca el número de hojas en los coárboles que se generarán: ";
            cin >> tam;
            cout << endl << endl;
            testCotreeConstructor(tam,0);
        break;
        case(4):
            cout << "Introduzca el número de hojas en los coárboles que se generarán: ";
            cin >> tam;
            cout << endl << endl;
            testCrearArbolBinario(tam);
        break;
        case(5):
            cout << "Introduzca el número de hojas en los coárboles que se evaluarán: ";
            cin >> tam;
            cout << endl << endl;
            testContainsSubcograph(tam);
        break;
        case(6):
            cout << "Introduzca el número de hojas en los coárboles que se evaluarán: ";
            cin >> tam;
            cout << endl << endl;
            testM2_identifier(tam);
        break;
        case(7):
            cout << "Introduzca el número de hojas en los coárboles que se evaluarán: ";
            cin >> tam;
            cout << endl << endl;
            test_certificador(tam);
        break;
        case(8):
            cout << "El test de coherencia crea todos los coárboles con n hojas y determina si son elementos de M2 tanto con el algoritmo identificador como con el certificador. Si las respuestas son diferentes, despliega el coárbol." << endl;
            cout << "Introduzca el número de hojas en los coárboles que se evaluarán: ";
            cin >> tam;
            cout << endl << endl;
            test_coherencia(tam);
        break;
        case(9):
            cout << "Introduzca el número de hojas en los coárboles que se evaluarán: ";
            cin >> tam;
            cout << "LOS COLORES DE LAS HOJAS NO NECESARIAMENT ECORRESPONDEN CON UNA PARTICIÓN CUYO TAMAÑO ESTÁ EN EL CPM" << endl;
            cout << endl << endl;
            test_cpm(tam);
        break;
        case(10):
            cout << "Introduzca el número de hojas en los coárboles que se evaluarán: ";
            cin >> tam;
            cout << "Introduzca a y b: ";
            cin >> alfa >> beta;
            cout << endl << endl;
            test_skM2_Identifier(tam,alfa,beta);
        break;
        case(11):
            cout << "Introduzca a y b: ";
            cin >> alfa >> beta;
            cout << endl << endl;
            skm2_finder::print_obstructions(make_pair(alfa,beta));
        break;
        default:
            cout << "Opción no válida" << endl;
        break;
    }


}
